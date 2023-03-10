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

int main()
{
    int sockfd;
    struct ifreq ifr;
    struct sockaddr_in *addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    strcpy(ifr.ifr_name, "eth0");

    addr = (struct sockaddr_in *)&ifr.ifr_addr;
    addr->sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.100", &addr->sin_addr);

    ioctl(sockfd, SIOCSIFADDR, &ifr);

    printf("Adresse IP configurée avec succès.\n");

    close(sockfd);

    return 0;
}

