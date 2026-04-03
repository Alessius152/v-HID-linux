
#ifndef HID_PROTOCOL_H
#define HID_PROTOCOL_H

#include <inttypes.h>

/*
questa particolare dicitura dice di non
dichiarare una semplice struct e di lasciar
gestire il sistema operativo il layout di 
memoria, ma di codificare esattamente come
descritto gli 8 byte indicati.
*/
struct __attribute__((packed)) hid_packet {
    uint8_t  hid;
    uint16_t key_code;
    uint8_t  action;
    uint8_t  axis;
    int8_t   delta;
    uint16_t  padding;
};

enum Hid {
    HID_KEYBOARD = 0,
    HID_MOUSE_BUTTON = 1,
    HID_MOUSE_MOVEMENT = 2,
};

enum Action {
    ACTION_PRESS = 0,
    ACTION_RELEASE = 1,
};

enum Axis {
    AXIS_X = 0,
    AXIS_Y = 1,
};

#endif
