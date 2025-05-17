#include <stdio.h>
int main()
{
    printf("Hello world\n");
    if (1)
    {
        printf("Condition is true\n");
        if (0)
        {
            printf("Nested condition is true\n");
        }
        else
        {
            printf("Nested condition is false\n");
        }
    }
    else
    {
        printf("Condition is false\n");
    }
    return 0;
}