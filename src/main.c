#include <stdio.h>
#include <time.h>


int loop()
{
    time_t time_beg = time(NULL);
    time_t delay = 5;
    time_t prev_diff = -1;
    while(1)
    {
        time_t time_cur = time(NULL);
        time_t diff = time_cur - time_beg;
        if (diff != prev_diff && diff % delay == 0)
        {
            printf("(%d)Healthcheck...\n", diff);
            prev_diff = diff;
        }
    }
}


int main()
{
    loop();
    return 0;
}
