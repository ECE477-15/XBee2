/*
 * xbee2.h
 *
 *  Created on: Apr 19, 2021
 *      Author: grantweiss
 */

#ifndef XBEE2_H_
#define XBEE2_H_

#include <stdbool.h>
#include "uart.h"
#include "String.h"

/********************** DEFINES **********************/
/* XBee Control Bytes */
#define XBEE_CTRL_START 0x7e

/* XBee AT Transparent Mode Commands */
#define XBEE_AT_ENTERCMD "+++"
#define XBEE_AT_EXITCMD "ATCN"

#define XBEE_AT_RESTORE "ATRE"
#define XBEE_AT_WRITE "ATWR"

#define XBEE_AT_APIMODE "ATAP"
#define XBEE_AT_NETID "ATID"
#define XBEE_AT_PREAMBLEID "ATHP"
#define XBEE_AT_POWLEVEL "ATPL"

/* XBee Frames */
#define XBEE_FRAME_TX_REQ 0x10
#define XBEE_FRAME_TX_STAT 0x8B
#define XBEE_FRAME_AT_CMD 0x08
#define XBEE_FRAME_AT_CMD_RESP 0x88

/********************** STRUCTS **********************/
typedef struct __attribute__((__packed__)) {
	uint8_t startByte;
	uint16_t length;
	uint8_t frameType;
	uint8_t frameId;
} start_of_frame_t;

/********************** FUNCTIONS **********************/
void xbee_setup();
void send_message(uint16_t payloadLength, char *payload, uint32_t addrH, uint32_t addrL);
void network_discovery();

#endif /* XBEE2_H_ */
