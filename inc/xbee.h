/*
 * xbee.h
 *
 *  Created on: Apr 14, 2021
 *      Author: grantweiss
 */

#ifndef XBEE_H_
#define XBEE_H_

#include "stm32l0xx.h"
#include <stdbool.h>
#include "uart.h"
#include "String.h"

/********************** DEFINES **********************/
/* XBee Control Bytes */
#define XBEE_CTRL_START 0x7e
#define XBEE_CTRL_ESCAPE 0x7d
#define XBEE_CTRL_XON 0x11
#define XBEE_CTRL_XOFF 0x13

/* XBee Frames */
#define XBEE_FRAME_TX_REQ 0x10
#define XBEE_FRAME_TX_STAT 0x8B
#define XBEE_FRAME_AT_CMD 0x08
#define XBEE_FRAME_AT_CMD_RESP 0x88

/* XBee AT Transparent Mode Commands */
#define XBEE_AT_ENTERCMD "+++"
#define XBEE_AT_EXITCMD "ATCN"

#define XBEE_AT_RESET "ATFR"
#define XBEE_AT_RESTORE "ATRE"
#define XBEE_AT_APPLY "ATAC"
#define XBEE_AT_WRITE "ATWR"

#define XBEE_AT_APIMODE "ATAP"
#define XBEE_AT_ROUTEMODE "ATCE"
#define XBEE_AT_TXOPTS "ATTO"
#define XBEE_AT_POWLEVEL "ATPL"
#define XBEE_AT_NETID "ATID"
#define XBEE_AT_PREAMBLEID "ATHP"

/* XBee API Constants */
#define RESPONSE_OK 0x0

/* Function Helpers */
#define XBEE_SEND(KIND, ...) sizeof(#__VA_ARGS__)==1 ? send_simple_command(KIND "\r", false) : send_simple_command(KIND " " #__VA_ARGS__ "\r", true)

#define ENDIAN_SWAP16(VAL) (((VAL) >> 8) | ((VAL) << 8))
#define ENDIAN_SWAP32(VAL) ((((VAL)>>24) & 0xFF) | (((VAL)>>8) & 0xFF00) | (((VAL)<<8) & 0xFF0000) | (((VAL)<<24) & 0xFF000000))

#define FRAME_SET_LEN(FR, PL) FR.length = ENDIAN_SWAP16(PL)
#define FRAME_SET_TYPE(FR, TY) (FR.frameType = TY)
#define FRAME_SET_ID(FR, ID) (FR.frameId = ID)
#define FRAME_SET_ADDRH(FR, ADDR) FR.addrH = ENDIAN_SWAP32(ADDR)
#define FRAME_SET_ADDRL(FR, ADDR) FR.addrL = ENDIAN_SWAP32(ADDR)


/********************** STRUCTS **********************/
typedef struct __attribute__((__packed__)) {
	uint8_t startByte;
	uint16_t length;
	uint8_t frameType;
	uint8_t frameId;
	uint32_t addrH;
	uint32_t addrL;
	uint16_t reserved;
	uint8_t broadcastRadius;
	uint8_t opts;
} frame_t;

typedef struct __attribute__((__packed__)) {
	uint8_t startByte;
	uint16_t length;
	uint8_t frameType;
	uint8_t frameId;
	uint16_t reserved;
	uint8_t retryCount;
	uint8_t deliveryStatus;
	uint8_t discoveryStatus;
	uint8_t checksum;
} frame_tx_status_t;

typedef struct {
	uint16_t length;
	uint8_t frameType;
	uint8_t frameId;
	uint32_t addr_h;
	uint32_t addr_l;
} packet_builder_t;

/********************** FUNCTIONS **********************/
void send_64_tx(uint16_t payloadLength, char *payload, uint32_t addrH, uint32_t addrL, uint8_t frameID);
void xbee_setup();
void send_simple_command(char * str, bool check);
void network_discovery(void);
bool xbee_check_response(frame_tx_status_t *);

/********************** VARIABLES **********************/

#endif /* XBEE_H_ */
