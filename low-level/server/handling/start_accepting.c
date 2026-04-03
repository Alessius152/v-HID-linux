
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "./start_accepting.h"
#include "../../protocol/packets-layout.h"
#include "./handle_client.h"
#include "../global_vars.h"

void *start_accepting(void *args)
{
    struct args____start_accepting *args_ = (struct args____start_accepting *)args;
    int client_fd;

    while (1)
    {
        client_fd = accept(*args_->server_fd, NULL, NULL);

        if (client_fd < 0)
        {
            perror("accept()");
            continue;
        }

        printf("client connected\n");
        fflush(stdout);

        if(actual_client_fd != -1){
            printf("client denied [the slot is busy]\n");
            fflush(stdout);
            close(client_fd);
            continue;
        }

        actual_client_fd = client_fd;

        pthread_t client_tid;
        struct args____handle_client *a = malloc(sizeof(struct args____handle_client));

        a->client_fd = &client_fd;

        int creation = pthread_create(&client_tid, NULL, handle_client, (void *)a);
        if (creation < 0)
        {
            perror("error creating handle_client() thread");
            free(a);
        }
    }
}
