#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>


struct loop_args
{
    bool *exit_flag_ptr;
};


int loop(struct loop_args *args)
{
    bool *exit_flag = args->exit_flag_ptr;
    time_t time_beg = time(NULL);
    time_t delay = 5;
    while(1)
    {
        if(*exit_flag) break;
        time_t time_cur = time(NULL);
        time_t diff = time_cur - time_beg;
        printf("(%d)Healthcheck...\n", diff);
        sleep(delay);
    }
}



int main()
{
    bool exit_flag = false;
    pthread_t thread_id;
    pthread_t thread_id2;
    struct loop_args args;
    args.exit_flag_ptr = &exit_flag;
    pthread_create(&thread_id, NULL, (void *)&loop, (void *)&args);
    pthread_join(thread_id, NULL);
    return 0;
}
