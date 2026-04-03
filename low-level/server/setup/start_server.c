
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <pthread.h>

#include "../constants.h"
#include "../handling/start_accepting.h"

void start_server()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    struct sockaddr_in address;

    if (server_fd == 0)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(V_HID_SERVER_PORT);

    struct sockaddr *addr = (struct sockaddr *)&address;

    if (bind(server_fd, addr, sizeof(address)) < 0)
    {
        perror("bind()");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0)
    {
        perror("listen()");
        exit(EXIT_FAILURE);
    }

    printf("TCP server is started\n");
    fflush(stdout);

    struct args____start_accepting* a = malloc(sizeof(struct args____start_accepting));
    a->server_fd = &server_fd;

    pthread_t tid;
    int creation = pthread_create(&tid, NULL, start_accepting, (void*)a);
    if(creation < 0){
        perror("error creating start_accepting() thread");
        free(a);
    }

    pthread_join(tid, NULL);

}
