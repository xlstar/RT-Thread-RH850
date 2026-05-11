#include "rtthread.h"
#include "rtconfig.h"

/* 定义任务栈大小，单位为字节 */
#define TASK_1MS_STACK_SIZE  (2048)
#define TASK_5MS_STACK_SIZE  (2048)
#define TASK_10MS_STACK_SIZE (2048)
#define TASK_20MS_STACK_SIZE (2048)

/* 定义任务优先级，数值越小优先级越高 */
/* 注意：软件定时器默认在定时器线程中执行，其优先级通常由 RT_TIMER_THREAD_PRIO 定义 */
/* 这里建议任务优先级高于定时器线程，或者根据系统调度需求调整 */
#define TASK_1MS_PRIO  (RT_TIMER_THREAD_PRIO + 1) /* 1ms任务优先级最高 */
#define TASK_5MS_PRIO  (TASK_1MS_PRIO + 1)
#define TASK_10MS_PRIO (TASK_5MS_PRIO + 1)
#define TASK_20MS_PRIO (TASK_10MS_PRIO + 1)

/* 定义任务句柄 */
rt_thread_t task_1ms_handle = RT_NULL;
rt_thread_t task_5ms_handle = RT_NULL;
rt_thread_t task_10ms_handle = RT_NULL;
rt_thread_t task_20ms_handle = RT_NULL;

/* 任务栈 */
rt_uint8_t task_1ms_stack [TASK_1MS_STACK_SIZE ];
rt_uint8_t task_5ms_stack [TASK_5MS_STACK_SIZE ];
rt_uint8_t task_10ms_stack[TASK_10MS_STACK_SIZE];
rt_uint8_t task_20ms_stack[TASK_20MS_STACK_SIZE];

/* 任务控制块 */
struct rt_thread task_1ms_thread;
struct rt_thread task_5ms_thread;
struct rt_thread task_10ms_thread;
struct rt_thread task_20ms_thread;

/* 定义信号量控制块 */
struct rt_semaphore sem_1ms;
struct rt_semaphore sem_5ms;
struct rt_semaphore sem_10ms;
struct rt_semaphore sem_20ms;

/* 定义定时器控制块 */
struct rt_timer timer_1ms;
struct rt_timer timer_5ms;
struct rt_timer timer_10ms;
struct rt_timer timer_20ms;

/* 任务计数器 */
volatile rt_uint32_t task_1ms_cnt = 0;
volatile rt_uint32_t task_5ms_cnt = 0;
volatile rt_uint32_t task_10ms_cnt = 0;
volatile rt_uint32_t task_20ms_cnt = 0;

float task_1ms_period = 1.0;

/* 定时器超时回调函数 */
static void timer_1ms_timeout(void *parameter)
{
    rt_sem_release(&sem_1ms);
}

static void timer_5ms_timeout(void *parameter)
{
    rt_sem_release(&sem_5ms);
}

static void timer_10ms_timeout(void *parameter)
{
    rt_sem_release(&sem_10ms);
}

static void timer_20ms_timeout(void *parameter)
{
    rt_sem_release(&sem_20ms);
}

/* 任务函数 */
static void task_1ms_entry(void *parameter)
{
    while (1)
    {
        /* 等待信号量，由定时器触发 */
        if (rt_sem_take(&sem_1ms, RT_WAITING_FOREVER) == RT_EOK)
        {
            /* 1ms任务处理 */
            task_1ms_cnt++;
            rt_kprintf("1ms task running, cnt: %d\n", task_1ms_cnt);
        }
    }
}

static void task_5ms_entry(void *parameter)
{
    while (1)
    {
        /* 等待信号量，由定时器触发 */
        if (rt_sem_take(&sem_5ms, RT_WAITING_FOREVER) == RT_EOK)
        {
            /* 5ms任务处理 */
            task_5ms_cnt++;
            rt_kprintf("5ms task running, cnt: %d\n", task_5ms_cnt);
        }
    }
}

static void task_10ms_entry(void *parameter)
{
    while (1)
    {
        /* 等待信号量，由定时器触发 */
        if (rt_sem_take(&sem_10ms, RT_WAITING_FOREVER) == RT_EOK)
        {
            /* 10ms任务处理 */
            task_10ms_cnt++;
            rt_kprintf("10ms task running, cnt: %d\n", task_10ms_cnt);
        }
    }
}

static void task_20ms_entry(void *parameter)
{
    while (1)
    {
        /* 等待信号量，由定时器触发 */
        if (rt_sem_take(&sem_20ms, RT_WAITING_FOREVER) == RT_EOK)
        {
            /* 20ms任务处理 */
            task_20ms_cnt++;
            rt_kprintf("20ms task running, cnt: %d\n", task_20ms_cnt);
        }
    }
}

/* 初始化所有任务 */
int rtthread_taskinit(void)
{
    rt_err_t result;

    /* 初始化信号量，初始值为0 */
    rt_sem_init(&sem_1ms, "sem_1ms", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_5ms, "sem_5ms", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_10ms, "sem_10ms", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_20ms, "sem_20ms", 0, RT_IPC_FLAG_FIFO);

    /* 初始化定时器 */
    /* 参数: 定时器句柄, 名字, 回调函数, 参数, 超时时间(1ms=1tick), 周期性定时器标志 */
    rt_timer_init(&timer_1ms, "timer_1ms", timer_1ms_timeout, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);
    rt_timer_init(&timer_5ms, "timer_5ms", timer_5ms_timeout, RT_NULL, 5, RT_TIMER_FLAG_PERIODIC);
    rt_timer_init(&timer_10ms, "timer_10ms", timer_10ms_timeout, RT_NULL, 10, RT_TIMER_FLAG_PERIODIC);
    rt_timer_init(&timer_20ms, "timer_20ms", timer_20ms_timeout, RT_NULL, 20, RT_TIMER_FLAG_PERIODIC);

    /* 创建1ms任务 */
    task_1ms_handle = &task_1ms_thread;
    result = rt_thread_init(task_1ms_handle,
                            "task_1ms",
                            task_1ms_entry,
                            RT_NULL,
                            task_1ms_stack,
                            sizeof(task_1ms_stack),
                            TASK_1MS_PRIO,
                            20);
    RT_ASSERT(result == RT_EOK);
    rt_thread_startup(task_1ms_handle);
    
    /* 创建5ms任务 */
    task_5ms_handle = &task_5ms_thread;
    result = rt_thread_init(task_5ms_handle,
                            "task_5ms",
                            task_5ms_entry,
                            RT_NULL,
                            task_5ms_stack,
                            sizeof(task_5ms_stack),
                            TASK_5MS_PRIO,
                            20);
    RT_ASSERT(result == RT_EOK);
    rt_thread_startup(task_5ms_handle);
    
    /* 创建10ms任务 */
    task_10ms_handle = &task_10ms_thread;
    result = rt_thread_init(task_10ms_handle,
                            "task_10ms",
                            task_10ms_entry,
                            RT_NULL,
                            task_10ms_stack,
                            sizeof(task_10ms_stack),
                            TASK_10MS_PRIO,
                            20);
    RT_ASSERT(result == RT_EOK);
    rt_thread_startup(task_10ms_handle);
    
    /* 创建20ms任务 */
    task_20ms_handle = &task_20ms_thread;
    result = rt_thread_init(task_20ms_handle,
                            "task_20ms",
                            task_20ms_entry,
                            RT_NULL,
                            task_20ms_stack,
                            sizeof(task_20ms_stack),
                            TASK_20MS_PRIO,
                            20);
    RT_ASSERT(result == RT_EOK);
    rt_thread_startup(task_20ms_handle);

    /* 启动定时器 */
    rt_timer_start(&timer_1ms);
    rt_timer_start(&timer_5ms);
    rt_timer_start(&timer_10ms);
    rt_timer_start(&timer_20ms);
    
    return result;
}

/* 导出到自动初始化 */
INIT_APP_EXPORT(rtthread_taskinit);
