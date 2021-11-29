#include <iostream>
#include "vector"
#include "algorithm"
#include "queue"
#include "fmt/format.h"

using namespace std;

typedef pair<int, int> pii;

using pii = pair<int, int>;

int main() {
    vector<int> arr(10);

    auto cmp = [&](const pii &x,
                   const pii &y) {
        // x1/y1 > x2/y2
        return arr[x.first] * arr[y.second] > arr[x.second] * arr[y.first];
    };

    priority_queue<pii, vector<pii>, decltype(cmp)> q(cmp);
    return 0;
}
