
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>

#include "./handle_client.h"
#include "../../protocol/packets-layout.h"
#include "../global_vars.h"
#include "../../packet-processing/hid-interaction/processing.h"

void *handle_client(void *args)
{

    struct args____handle_client *args_ = (struct args____handle_client *)args;
    const size_t pkt_size = sizeof(struct hid_packet);

    size_t len = 0;
    uint8_t bfr[4096];

    while (1) {
        ssize_t r = read(*args_->client_fd, bfr + len, sizeof(bfr) - len);
        
        if(r <= 0) break;

        bool isFull = (sizeof(bfr) - (len+r)) == 0;
        
        if(isFull) break;

        len += r;

        while(len >= pkt_size){
            struct hid_packet pkt;

            memcpy(&pkt, bfr, pkt_size);
            printf("packet arrived!\n");
            memmove(bfr, bfr + pkt_size, len - pkt_size);
            process_packet____hid_interaction(&pkt);

            len -= pkt_size;
        }
    }

    actual_client_fd = -1;
    printf("client disconnected\n");
    close(*args_->client_fd);

    return NULL;
}
