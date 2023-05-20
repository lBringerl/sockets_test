#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


struct loop_state
{
    bool exit_flag;
};


int loop(struct loop_state *state)
{
    time_t time_beg = time(NULL);
    time_t delay = 5;
    time_t prev_printed = -1;
    while(!state->exit_flag)
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


void ask_exit()
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
}


int main()
{
    pthread_t loop_thread_id;
    struct loop_state state;
    state.exit_flag = false;
    pthread_create(&loop_thread_id, NULL, (void *)&loop, (void *)&state);
    ask_exit();
    state.exit_flag = true;
    pthread_join(loop_thread_id, NULL);
    return 0;
}
