//
// Created by devhg on 2021/9/9.
//

#include "thread_pool.h"
#include <cstdio>
#include <cstdlib>

struct ctrip_thread_info g_thread_info;

int thread_running = 0;

void ctrip_init_thread_pool(int thread_num) {
    if (thread_num <= 0) thread_num = 5;

    pthread_mutex_init(&g_thread_info.mutex, nullptr);
    pthread_cond_init(&g_thread_info.cond, nullptr);

    g_thread_info.thread_num     = thread_num;
    g_thread_info.thread_running = 1;
    g_thread_info.thread_num     = 0;
    g_thread_info.tasks          = nullptr;

    thread_running = 1;

    g_thread_info.thread_id = (pthread_t *) malloc(sizeof(pthread_t) * thread_num);

    for (int i = 0; i < thread_num; ++i) {
        pthread_create(&g_thread_info.thread_id[i], nullptr, ctrip_thread_routine, nullptr);
    }

}

void ctrip_destroy_thread_pool() {
    g_thread_info.thread_running = 0;
    thread_running = 0;
    pthread_cond_broadcast(&g_thread_info.cond);

    for (int i = 0; i < g_thread_info.thread_num; ++i) {
        pthread_join(g_thread_info.thread_id[i], nullptr);
    }

    free(g_thread_info.thread_id);

    pthread_mutex_destroy(&g_thread_info.mutex);
    pthread_cond_destroy(&g_thread_info.cond);
}

void ctrip_thread_pool_add_task(struct ctrip_task *t) {
    if (t == nullptr) return;

    pthread_mutex_lock(&g_thread_info.mutex);

    struct ctrip_task *head = g_thread_info.tasks;
    if (head == nullptr) {
        g_thread_info.tasks = t;
    } else {
        while (head->pNext != nullptr) {
            head = head->pNext;
        }
        head->pNext = t;
    }

    ++g_thread_info.task_num;

    // 当有变化后，使用signal通知wait函数
    pthread_cond_signal(&g_thread_info.cond);
    pthread_mutex_unlock(&g_thread_info.mutex);
}

struct ctrip_task *ctrip_pool_retrieve_task() {
    struct ctrip_task *head = g_thread_info.tasks;
    if (head != nullptr) {
        g_thread_info.tasks = head->pNext;
        --g_thread_info.task_num;
        printf("retrieve a task, task value is [%d]\n", head->value);
        return head;
    }

    printf("no task\n");
    return nullptr;
}

void ctrip_thread_pool_do_task(struct ctrip_task *t) {
    if (t == nullptr)
        return;
    printf("task value is [%d]\n", t->value);
}

void *ctrip_thread_routine(void *thread_param) {
    while (thread_running /*g_thread_info.thread_running*/ ) {
        struct ctrip_task *current = nullptr;

        pthread_mutex_lock(&g_thread_info.mutex);

        while (g_thread_info.task_num <= 0) {
            // 如果获得了互斥锁，但是条件不合适的话，wait会释放锁，不往下执行。
            // 当变化后，条件合适，将直接获得锁。
            pthread_cond_wait(&g_thread_info.cond, &g_thread_info.mutex);

            if (!g_thread_info.thread_running) break;

        }

        current = ctrip_pool_retrieve_task();

        pthread_mutex_unlock(&g_thread_info.mutex);

        ctrip_thread_pool_do_task(current);
    }
    return nullptr;
}