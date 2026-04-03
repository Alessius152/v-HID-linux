
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "./handle_client.h"
#include "../../protocol/packets-layout.h"
#include "../global_vars.h"

void *handle_client(void *args)
{

    struct args____handle_client *args_ = (struct args____handle_client *)args;
    struct hid_packet pkt;

    while (recv(*args_->client_fd, &pkt, sizeof(pkt), MSG_WAITALL) > 0)
    {
        uint16_t keycode = htons(pkt.key_code);
        uint16_t padding = htons(pkt.padding);

        printf("%d, %d, %d, %d, %d, %d\n", pkt.hid, keycode, pkt.action, pkt.axis, pkt.axis, padding);
        fflush(stdout);

        
    }

    actual_client_fd = -1;
    printf("client disconnected\n");
    fflush(stdout);
    close(*args_->client_fd);

    return NULL;
}
