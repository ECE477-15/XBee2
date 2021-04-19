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

static char* const commandList[] = {"AT\r", "ATND\r"};


int main(void)
{
	HAL_Init();
	uart2_init();
	sendGenericMessage();
	return 1;
	xbee_setup();

	char payload2[] = "HELLO";
	send_message(sizeof(payload2)-1, payload2, 0x13A200, 0x41A1D6AF);

	network_discovery();

	return 1;

	uint16_t commandIndex = 0;
	uart2_transmit(commandList[commandIndex]);

	while(1) {
		if(uartFlag != 0) {
			// received a newline
			if(buf_ok(uart2_rx_buffer) == 1) {
//				buf_clear(uart2_rx_buffer);

				if(++commandIndex < 2) {
					uart2_transmit(commandList[commandIndex]);
				}
			} else {
				error(__LINE__);
			}
			uartFlag = 0;
		}
		HAL_Delay(1);
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
