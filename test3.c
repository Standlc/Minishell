#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

int main()
{
    printf("int : %d\nkill : %d\nsys : %d\n", SIGINT, SIGKILL, SIGSYS);
}