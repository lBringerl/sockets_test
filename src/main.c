#include <stdio.h>


int loop()
{
    int counter = 0;
    int multiplier = 100000000;
    while(1)
    {
        if (counter % multiplier == 0)
            printf("(%d)Healthcheck...\n", counter / multiplier);
        counter += 1;
    }
}


int main()
{
    loop();
    return 0;
}
