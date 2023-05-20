#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


struct loop_state
{
    bool exit_flag;
};

struct health_check_args
{
    struct loop_state *state;
    time_t delay;
};

struct ask_exit_args
{
    struct loop_state *state;
};


void health_check(struct health_check_args *args)
{

    time_t time_beg = time(NULL);
    time_t delay = args->delay;
    time_t prev_printed = -1;
    while(!args->state->exit_flag)
    {
        time_t time_cur = time(NULL);
        time_t diff = time_cur - time_beg;
        if (diff % delay == 0 && time_cur != prev_printed)
        {
            printf("(%d)Healthcheck...\n", diff);
            prev_printed = time_cur;
        }
    }
}


void ask_exit(struct ask_exit_args *args)
{
    char input_str[10];
    char exit_str[] = "EXT";
    while(1)
    {
        printf("Enter '%s' to exit.\n", exit_str);
        scanf("%s", input_str);
        if (!strcmp(input_str, exit_str))
            break;
        else
            printf("Unknown input. Try again\n");
    }
    args->state->exit_flag = true;
}


int loop(struct loop_state *state)
{
    pthread_t health_check_thread_id;
    pthread_t ask_exit_thread_id;
    struct health_check_args health_check_args;
    struct ask_exit_args ask_exit_args;
    health_check_args.state = state;
    health_check_args.delay = 5;
    ask_exit_args.state = state;
    pthread_create(&health_check_thread_id, NULL, &health_check, (void *)&health_check_args);
    pthread_create(&ask_exit_thread_id, NULL, &ask_exit, (void *)&ask_exit_args);
    pthread_join(health_check_thread_id, NULL);
    pthread_join(ask_exit_thread_id, NULL);
}


int main()
{
    pthread_t loop_thread_id;
    struct loop_state state;
    state.exit_flag = false;
    pthread_create(&loop_thread_id, NULL, (void *)&loop, (void *)&state);
    pthread_join(loop_thread_id, NULL);
    return 0;
}
