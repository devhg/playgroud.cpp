#include <iostream>
#include <fstream>
#include <cassert>
#include "json/json.h" // 直接就可以include，无需额外配置
#include "boost/uuid/uuid_generators.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/uuid/uuid_io.hpp"

std::string createJson() {
    std::string jsonStr;
    Json::Value root;
    Json::StreamWriterBuilder writerBuilder;
    std::ostringstream os;
    // 设置默认无格式化的输出
    writerBuilder.settings_["indentation"] = "";
    root["Name"] = "Zhangsan";
    root["Age"] = 25;
    // jsonWriter是智能指针, 当jsonWriter被析构时, 它所指向的对象(内存)也被自动释放
    std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &os);
    jsonStr = os.str();

    return jsonStr;
}

void saveJsonStringToFile(const char *file, std::string &jsonStr) {
    std::ofstream ofs;
    ofs.open(file);
    assert(ofs.is_open());
    ofs << jsonStr;
    ofs.close();
}

int main() {
    std::string jsonStr;
    jsonStr = createJson();
    saveJsonStringToFile("./test.json", jsonStr);


    boost::uuids::random_generator gen;
    std::cout << boost::lexical_cast<std::string>(gen()) << std::endl;
    return 0;
}
