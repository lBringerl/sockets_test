#include <stdio.h>
#include <time.h>


int loop()
{
    time_t time_beg = time(NULL);
    time_t delay = 5;
    while(1)
    {
        time_t time_cur = time(NULL);
        time_t diff = time_cur - time_beg;
        printf("(%d)Healthcheck...\n", diff);
        sleep(delay);
    }
}


int main()
{
    loop();
    return 0;
}
