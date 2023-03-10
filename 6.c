#include <curses.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void    t_tests()
{
    int return_value;

    return_value = tgetent(NULL, getenv("TERM"));
    if (return_value == -1)
        (printf("error in the return_value : -1\n"), exit(errno));
    if (return_value == 0)
        (printf("error in the return_value : 0\n"), exit(errno));
    int column_count = tgetnum("co");
    int line_count = tgetnum("li");
    printf("lines %d\ncolumns %d\n", line_count, column_count);
    sleep(3);
    char *str;
    str = tgetstr("cl", NULL);
    if (tputs(str, 1, &putchar) == -1)
        (printf("error tputs\n"), exit(errno));
    sleep(3);
    if (tputs(tgoto(tgetstr("cm", NULL), 40, 7), 1, &putchar) == -1)
        (printf("error tputs\n"), exit(errno));
    sleep(3);
}

int main()
{
    struct termios opt_term;
    struct termios save;
    char *str = malloc(21);

    
    if (tcgetattr(0, &opt_term) == -1)
        return(printf("error getattr\n"));
    if (tcgetattr(0, &save) == -1)
        return(printf("error getattr\n"));
    opt_term.c_lflag &= ~ECHO;
    if (tcsetattr(0, 0, &opt_term) == -1)
        return(printf("error setattr\n"));
    t_tests();
    //read(0, str, 20);
    //str[20] = '\0';
    //printf("%s", str);
    sleep(2);
    if (tcsetattr(0, 0, &save) == -1)
        return(printf("error setattr\n"));
}