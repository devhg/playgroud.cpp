#include <iostream>
#include <cassert>
#include <boost/version.hpp>
#include <boost/type_index.hpp>
#include "base/base.h"

using namespace std;
using namespace base;
using namespace boost::typeindex;

#include "base/threadpool/thread_pool.h"

int main() {
    ctrip_init_thread_pool(5);
    struct ctrip_task *task = nullptr;

    for (int i = 0; i < 100; ++i) {
        task = (struct ctrip_task *) malloc(sizeof(struct ctrip_task));
        task->value = i + 1;
        task->pNext = nullptr;
        printf("add task, task value [%d]\n", task->value);
        ctrip_thread_pool_add_task(task);
    }

    sleep(10);
    ctrip_destroy_thread_pool();

    return 0;
}
