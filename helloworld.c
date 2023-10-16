#include <stdio.h>

int main()
{
    int a = 0;
    for (int i=0;i<23000;i++)
    {
        a+=1;
    }
    printf("%d", a);
}