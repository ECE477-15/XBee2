/*
 * xbee.c
 *
 *  Created on: Apr 14, 2021
 *      Author: grantweiss
 */
#if 0
#include "xbee.h"
#include "ringBuf.h"
#include "main.h"
#include "string.h"

/********************** FUNCTION DECLARATIONS **********************/
void send_payload(frame_t *frame, char *payload, uint16_t payloadLength);
void sendByte(uint8_t b, bool escape);

/********************** VARIABLES **********************/
frame_t frame = {
	.startByte = XBEE_CTRL_START,
	.reserved = 0xFEFF,
	.broadcastRadius = 0x0,
	.opts = 0xC0
};

uint8_t frameID = 0x1;
packet_builder_t packet;

/********************** FUNCTION DEFINITIONS **********************/
void send_64_tx(uint16_t payloadLength, char *payload, uint32_t addrH, uint32_t addrL, uint8_t frameID) {
	FRAME_SET_LEN(frame, payloadLength + 14);
	FRAME_SET_TYPE(frame, XBEE_FRAME_TX_REQ);
	FRAME_SET_ID(frame, frameID);
	FRAME_SET_ADDRH(frame, addrH);
	FRAME_SET_ADDRL(frame, addrL);

	send_payload(&frame, payload, payloadLength);
}

void send_payload(frame_t *frame, char *payload, uint16_t payloadLength) {
	uint8_t checksum = 0;

	sendByte(((uint8_t *)frame)[0], false);

	size_t i = 1;
	for(; i < 3; ++i) {
		sendByte(((uint8_t *)frame)[i], true);
	}

	for(; i < sizeof(frame_t); ++i) {
		sendByte(((uint8_t *)frame)[i], true);
		checksum += ((uint8_t *)frame)[i];
	}

	for(size_t i = 0; i < payloadLength; ++i) {
		sendByte(payload[i], true);
		checksum += (uint8_t)payload[i];
	}

	// perform 2s complement
	checksum = 0xff - checksum;

	sendByte(checksum, true);

	// Enable the Transmit Data Register Empty interrupt
	SET_BIT(USART2->CR1, USART_CR1_TXEIE);
}

void write(uint8_t b) {
	buf_writeByte(b, uart2_tx_buffer);
}

void sendByte(uint8_t b, bool escape) {
	if(escape && (b == XBEE_CTRL_START || b == XBEE_CTRL_ESCAPE || b == XBEE_CTRL_XON || b == XBEE_CTRL_XOFF)) {
		write(XBEE_CTRL_ESCAPE);
		write(b ^ 0x20);
	} else {
		write(b);
	}
}

void xbee_setup() {
	HAL_Delay(1100);
	send_simple_command(XBEE_AT_ENTERCMD, true);
	HAL_Delay(1100);
//
	send_simple_command(XBEE_AT_RESTORE"\r", true);	// Reset settings
	XBEE_SEND(XBEE_AT_APIMODE, 1);
//	XBEE_SEND(XBEE_AT_APIMODE);
//	XBEE_SEND(XBEE_AT_ROUTEMODE); // coordinator/router/etc

	XBEE_SEND(XBEE_AT_NETID, 0x7FFF);
//	XBEE_SEND(XBEE_AT_NETID);
	XBEE_SEND(XBEE_AT_PREAMBLEID, 0x0);
	XBEE_SEND(XBEE_AT_POWLEVEL, 0x0);
//	XBEE_SEND(XBEE_AT_TXOPTS, 0xC0);
//	XBEE_SEND(XBEE_AT_TXOPTS);

	send_simple_command(XBEE_AT_WRITE"\r", true);	// Write changes
	send_simple_command(XBEE_AT_EXITCMD"\r", true);	// Exit command mode
}

void send_simple_command(char * str, bool check) {
	uart2_receive();
	uart2_transmit(str);

	while(uartFlag == 0); // wait for carriage return
	uartFlag = 0;

	if(check) {
		if(buf_ok(uart2_rx_buffer)) {
			buf_pop(uart2_rx_buffer, 3); // remove "OK\r"
		} else {
			error(__LINE__);	// error
		}
	}
}

void network_discovery() {


	return;

	HAL_Delay(1100);
	send_simple_command("+++", true);
	HAL_Delay(1100);

	send_simple_command("AT\r", true);
	send_simple_command("ATAP 2\r", true);

	// Allow receiving
	uart2_receive();

	uint16_t startOfMsg = uart2_rx_buffer->head;

	uart2_transmit("ATND\r");

	while(1) {
		if(uartFlag) {
			if(buf_crcr(uart2_rx_buffer)) {
				break;
			}
			uartFlag = 0;
		}
	}

	uint32_t SH = 0;
	memcpy(&SH, &(uart2_rx_buffer->buffer[startOfMsg]), sizeof(SH));

	uint32_t SL = 0;
	memcpy(&SL, &(uart2_rx_buffer->buffer[startOfMsg]), sizeof(SL));

	unsigned char DB[4] = {0};
	memcpy(DB, &(uart2_rx_buffer->buffer[startOfMsg]), sizeof(DB)/sizeof(DB[0]));

//	SH; // 4 bytes
//	SL; // 4 bytes
//	DB; // (Contains the detected signal strength of the response in negative dBm units)
//	NI; // (variable, 0-20 bytes plus 0x00 character)
//	dev_type; //(1 byte: 0 = Coordinator, 1 = Router, 2 = End Device)
//	status; // (1 byte: reserved)
//	prof_id; // 2 bytes
//	man_id; // 2 bytes
//	digi_type; // 4 bytes
//	rssi_of_last_hop; // 1 byte
}

bool xbee_check_response(frame_tx_status_t * response) {
	uint8_t checksum = 0;
	for(uint8_t * responseBytes = ((uint8_t *)&(response->frameType)); responseBytes < &(response->checksum); responseBytes++) {
		checksum += *responseBytes;
	}
	if((0xFF - checksum) != response->checksum || response->deliveryStatus != RESPONSE_OK) { // bad checksum or message not delivered
		return false;
	}
	return true;
}


void send_at_frame() {
	// Clear buffers
	buf_clear(uart2_tx_buffer);
	buf_clear(uart2_rx_buffer);

	// Set uartFlag to trigger on START_BYTE
	uart2_update_match(XBEE_CTRL_START);

	// Send packet to XBee over UART
	// TODO

	// wait for start of frame (START_BYTE)
	while(uartFlag == 0);
	uartFlag = 0;

	// Format it as a response frame
	frame_tx_status_t * response = (frame_tx_status_t *)(uart2_rx_buffer->buffer);

	// wait for frame type and frameId information to come in
	while(BUF_USED(uart2_rx_buffer) < 5);

	// check to make sure it's a at_response frame and matches frameID sent earlier
	if(response->frameType != XBEE_FRAME_AT_CMD_RESP || response->frameId != frameID) {
		error(__LINE__);
	}

	// Wait for the rest of the packet to come in
	uint16_t packetLength = ENDIAN_SWAP16(response->length) + 4; // packet length according to start of frame, add start delim (1 byte) length (2 byte) and checksum (1 byte)
	while(BUF_USED(uart2_rx_buffer) < packetLength);

	/********************* TODO --- COMBINE THIS FUNCTION WITH ONE BELOW, HAVE EVERYTHING RELATIVE TO FRAME REPORTED LENGTH --- TODO ********************/

	// Increment frameID for next time
	frameID++;
	if(frameID == 0x0) {
		frameID = 0x1;
	}
}

void send_message(uint16_t payloadLength, char *payload, uint32_t addrH, uint32_t addrL) {
	// Clear buffers
	buf_clear(uart2_tx_buffer);
	buf_clear(uart2_rx_buffer);

	// Set uartFlag to trigger on START_BYTE
	uart2_update_match(XBEE_CTRL_START);

	// Send packet to XBee over UART
	send_64_tx(payloadLength, payload, addrH, addrL, frameID);

	// wait for start of frame (START_BYTE)
	while(uartFlag == 0);
	uartFlag = 0;

	// Format it as a response frame
	frame_tx_status_t * response = (frame_tx_status_t *)(uart2_rx_buffer->buffer);

	// wait for frame type and frameId information to come in
	while(BUF_USED(uart2_rx_buffer) < 5);

	// check to make sure it's a tx_status frame and matches frameID sent earlier
	if(response->frameType != XBEE_FRAME_TX_STAT || response->frameId != frameID) {
		error(__LINE__);
	}

	// Wait for the rest of the packet to come in
	while(BUF_USED(uart2_rx_buffer) < 11);

	// Ensure valid checksum and make sure information was received by target
	if(xbee_check_response(response) == false) {
		error(__LINE__);
	}

	// Done with it now
	buf_clear(uart2_rx_buffer);

	// Increment frameID for next time
	frameID++;
	if(frameID == 0x0) {
		frameID = 0x1;
	}
}

void sendGenericMessage() {
	packet.length = 12;
	packet.addr_h = 0x0;
	packet.addr_l = 0xFFFF;


	// Clear buffers
	buf_clear(uart2_tx_buffer);
	buf_clear(uart2_rx_buffer);

	// Set uartFlag to trigger on START_BYTE
	uart2_update_match(XBEE_CTRL_START);

	// make sure buffer has enough space
	if ((packet.length + 4) > BUF_AVAIL(uart2_rx_buffer)) {
		error(__LINE__);
	}

	uint8_t checksum = 0;

	// write character to buffer and add to checksum
	#define BUF_WR_CHECK(CH) BUF_PUSH((CH), uart2_rx_buffer); \
		checksum += (CH)

	// Build packet in UART Buffer
	buf_writeByte(XBEE_CTRL_START, 			uart2_rx_buffer);		// START
	buf_writeByte((packet.length >> 8), 	uart2_rx_buffer);		// LENGTH_H
	buf_writeByte(packet.length, 	uart2_rx_buffer);		// LENGTH_L
	BUF_WR_CHECK(packet.frameType);		// FRAME_TYPE
	BUF_WR_CHECK(packet.frameId);		// FRAME_ID
	uint8_t test = packet.addr_h >> 24;
	test = packet.addr_h >> 16;
	test = packet.addr_h >> 8;
	test = packet.addr_h;

	test = packet.addr_l >> 24;
	test = packet.addr_l >> 16;
	test = packet.addr_l >> 8;
	test = packet.addr_l;

}
#endif
