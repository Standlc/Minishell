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
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *str;
    while (1)
    {
        char *abr = "abracadabraifhweoifhweondwejofneripnwejfnsjongejrf";
        str = readline("tapez $>");
        if (!strcmp(str, "quit"))
            return(free(str), rl_clear_history(), 0);
        if (!strcmp(str, "clear"))
            rl_clear_history();
        if (!strcmp(str, "modifu"))
        {
            rl_replace_line(abr, 2344);
            printf("rl_replace_line good\n");
            
            printf("rl_on_new_line good\n");
            printf("str : %s\n", str);
            rl_on_new_line();
            rl_redisplay();
        }
        add_history(str);
        free(str);
    }
}