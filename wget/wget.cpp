#include "requests.h"

using namespace hv;

static int wget(const char *url, const char *filepath) {
    HFile file;
    if (file.open(filepath, "wb") != 0) {
        fprintf(stderr, "failed to open %s\n", filepath);
        return -20;
    }
    printf("Save file to %s ...\n", filepath);

    // HEAD
    auto resp = requests::head(url);
    if (resp == nullptr) {
        fprintf(stderr, "request failed!\n");
        return -1;
    }
    printd("%s", resp->Dump(true, false).c_str());

    bool use_range = false;
    int range_bytes = 1 << 20; // 1MB
    std::string accept_ranges = resp->GetHeader("Accept-Ranges");
    size_t content_length = hv::from_string<int>(resp->GetHeader("Content-Length"));

    // use Range if server accept_ranges and content_length > 1M
    if (resp->status_code == 200 &&
    accept_ranges == "bytes" &&
    content_length > range_bytes) {
        use_range = true;
    }

    // GET
    if (!use_range) {
        resp = requests::get(url);
        if (resp == nullptr) {
            fprintf(stderr, "request failed!\n");
            return -1;
        }
        printd("%s", resp->Dump(true, false).c_str());
        file.write(resp->body.data(), resp->body.size());
        printf("progress: %ld/%ld = 100%%\n", (long) resp->body.size(), (long) resp->body.size());
        return 0;
    }

    // Range: from-to
    long from = 0, to = 0;
    long last_progress = 0;
    http_client_s *cli = http_client_new();
    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_GET;
    req->url = url;
    while (from < content_length) {
        to = from + range_bytes - 1;
        if (to >= content_length) to = (long) content_length - 1;
        req->SetRange(from, to);
        printd("%s", req->Dump(true, false).c_str());

        int ret = http_client_send(cli, req.get(), resp.get());
        if (ret != 0) {
            fprintf(stderr, "request failed!\n");
            return -1;
        }
        printd("%s", resp->Dump(true, false).c_str());
        file.write(resp->body.data(), resp->body.size());
        from = to + 1;

        // print progress
        int cur_progress = from * 100 / content_length;
        if (cur_progress > last_progress) {
            printf("progress: %ld/%ld = %d%%\n", (long) from, (long) content_length, (int) cur_progress);
            last_progress = cur_progress;
        }
    }
    http_client_del(cli);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s url [filepath]\n", argv[0]);
        return -10;
    }
    const char *url = argv[1];
    const char *filepath = "index.html";
    if (argc > 2) {
        filepath = argv[2];
    } else {
        const char *path = strrchr(url, '/');
        if (strlen(path) > 1) {
            filepath = path + 1;
        }
    }

    wget(url, filepath);
    return 0;
}