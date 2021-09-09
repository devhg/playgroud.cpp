//
// Created by devhg on 2021/9/9.
//

/**
 * 线程池工具, ctrip_thread_pool.h
 * devhg 2021.09.09
 */
#ifndef PLAYGROUND_CPP_THREAD_POOL_H
#define PLAYGROUND_CPP_THREAD_POOL_H

#include <pthread.h>

struct ctrip_task {
    struct ctrip_task *pNext;
    int               value;
};

struct ctrip_thread_info {
    int               thread_running;
    int               thread_num;
    int               task_num;
    struct ctrip_task *tasks;
    pthread_t         *thread_id;
    pthread_mutex_t   mutex;
    pthread_cond_t    cond;
};

// 初始化线程池线程数目
void ctrip_init_thread_pool(int thread_num);

// 销毁线程池
void ctrip_destroy_thread_pool();

// 添加任务到线程池
void ctrip_thread_pool_add_task(struct ctrip_task *);

// 从线程池获取任务
struct ctrip_task *ctrip_pool_retrieve_task();

// 进行任务
void ctrip_thread_pool_do_task(struct ctrip_task *);

// 消费任务
void *ctrip_thread_routine(void *thread_param);

#endif //PLAYGROUND_CPP_THREAD_POOL_H
