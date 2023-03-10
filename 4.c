#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int tty_num = ttyslot();
    if (tty_num == -1) {
        printf("Aucun slot de terminal n'est associé à ce processus\n");
    } else {
        printf("Le numéro de slot de terminal est : %d\n", tty_num);
    }
    return 0;
}
