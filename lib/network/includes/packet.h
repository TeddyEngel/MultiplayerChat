#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#include "constants.h"
#include "packet_type.h"

typedef struct {
    enum PacketType type;       // packet type
    uint16_t length;    // payload length (bytes)
    char payload[MAX_PAYLOAD]; // message or timestamp
} Packet;

#endif