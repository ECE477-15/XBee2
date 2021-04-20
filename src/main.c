/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32l0xx.h"
#include "stm32l0538_discovery.h"
#include "ringBuf.h"
//#include "xbee.h"
#include "xbee2.h"
#include "uart.h"
#include "main.h"

int main(void)
{
	HAL_Init();
	uart2_init();
	xbee_setup();

	tx_req_frame_t txReq = {
			.addrH = ENDIAN_SWAP32(0x0),
			.addrL = ENDIAN_SWAP32(0xFFFF),
	};
	char payload[] = "HELLOTEST";
	xbee_msg->payload = (uint8_t *)payload;
	xbee_msg->payloadLen = strlen(payload);
	xbee_send_message(&txReq);


	// be prepared for incoming xbee message
	uart2_update_match(XBEE_CTRL_START);
	uart2_receive();

	uint16_t xbee_status = 0;
	uint32_t xbee_length = 0;

	while(1) {
		if(uartFlag != 0) {
			xbee_status = 1; // xbee frame started
			uartFlag = 0;
		}
		if(xbee_status > 0) {
			if(xbee_status == 1 && BUF_USED(uart2_rx_buffer) >= 4) {
				if(BUF_GET_AT(uart2_rx_buffer, (uart2_rx_buffer->tail + 3)) != XBEE_FRAME_RX_PACKET) {
					error(__LINE__);
				}
				xbee_length = (BUF_GET_AT(uart2_rx_buffer, (uart2_rx_buffer->tail + 1)) << 8) | BUF_GET_AT(uart2_rx_buffer, (uart2_rx_buffer->tail + 2));
				xbee_status = 2;	// xbee frame length available
			} else if(xbee_status == 2 && BUF_USED(uart2_rx_buffer) == (xbee_length + 4)) {
				xbee_status = 3;
			} else if(xbee_status == 3) {
				// packet complete
				xbee_rx_complete(xbee_length);
				xbee_status = 0;
			}
		}
	}
}



void error(uint32_t source) {
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;	// GPIOB Clock enable

	GPIOB->MODER &= ~(GPIO_MODER_MODE4);
	GPIOB->MODER |= GPIO_MODER_MODE4_0;
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_4);

	GPIOB->BSRR = GPIO_BSRR_BS_4;

	while(1);
}

void HardFault_Handler(void) {
	while(1);
}
