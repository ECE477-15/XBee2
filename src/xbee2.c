/*
 * xbee2.c
 *
 *  Created on: Apr 19, 2021
 *      Author: grantweiss
 */

#include "xbee2.h"
#include "main.h"

void xbee_send_at(char * str, bool check);

void xbee_setup() {
	// Enter into AT Command Mode
	HAL_Delay(1100);
	send_simple_command(XBEE_AT_ENTERCMD, true);
	HAL_Delay(1100);

	xbee_send_at(XBEE_AT_RESTORE	"\r", 		true);	// Reset settings, expect OK
	xbee_send_at(XBEE_AT_APIMODE	" 1\r", 	true);	// Set to API Mode 1, expect OK
	xbee_send_at(XBEE_AT_NETID		" 0x7FFF\r",true);	// Set Network ID, expect OK
	xbee_send_at(XBEE_AT_PREAMBLEID	" 0x0\r", 	true);	// Set Preamble ID, expect OK
	xbee_send_at(XBEE_AT_POWLEVEL	" 0x0\r", 	true);	// Set Power Level, expect OK

	xbee_send_at(XBEE_AT_WRITE	"\r", true);	// Write changes, expect OK
	xbee_send_at(XBEE_AT_EXITCMD"\r", true);	// Exit command mode, expect OK
}

void xbee_send_at(char * str, bool check) {
	// Clear the buffer
	buf_clear(uart2_rx_buffer);

	// Make sure receiving is enabled
	uart2_receive();

	// Set flag when received '\r'
	uart2_update_match('\r');

	// Send the command
	uart2_transmit(str);

	// wait for carriage return
	while(uartFlag == 0);
	uartFlag = 0;

	// check for good response
	if(check) {
		if(!buf_ok(uart2_rx_buffer)) {
			error(__LINE__);	// error
		}
	}

	// Clear the buffer
	buf_clear(uart2_rx_buffer);
}

void xbee_send_message(uint16_t payloadLength, char *payload, uint32_t addrH, uint32_t addrL) {
	// Clear buffer
	buf_clear(uart2_rx_buffer);

	// Set uartFlag to trigger on START_BYTE
	uart2_update_match(XBEE_CTRL_START);

	// Send packet to XBee over UART
	// TODO

	// wait for start of frame (START_BYTE)
	while(uartFlag == 0);
	uartFlag = 0;

	// Format it as a response frame
	start_of_frame_t * response = (start_of_frame_t *)(uart2_rx_buffer->buffer);

	// wait for frame type and frameId information to come in
	while(BUF_USED(uart2_rx_buffer) < 5);

	// check to make sure it's a tx_status frame and matches frameID sent earlier
	if(response->frameType != XBEE_FRAME_TX_STAT || response->frameId != frameID) {
		error(__LINE__);
	}

	// Wait for the rest of the packet to come in
	uint32_t targetLen = response->length + 4;
	while(BUF_USED(uart2_rx_buffer) < targetLen);


}

void network_discovery() {

}
