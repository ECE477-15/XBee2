/*
 * ringBuf.h
 *
 *  Created on: Apr 14, 2021
 *      Author: grantweiss
 */

#ifndef RINGBUF_H_
#define RINGBUF_H_

#include "stm32l0xx.h"
#include "main.h"

/********************** DEFINES **********************/
#define BUFFER_SIZE 64

#define BUF_USED(buffer) ((buffer->head - buffer->tail + BUFFER_SIZE) % BUFFER_SIZE)
#define BUF_AVAIL(buffer) (BUFFER_SIZE - ((buffer->head - buffer->tail + BUFFER_SIZE) % BUFFER_SIZE) - 1)
#define BUF_GET_AT(BUF, ind) ( BUF->buffer[(((ind) + (BUFFER_SIZE)) % (BUFFER_SIZE))] )

#define BUF_PUSH(c, buf) buf->buffer[buf->head] = c; \
	buf->head = (unsigned int)(buf->head + 1) % BUFFER_SIZE


/********************** STRUCTS **********************/
typedef struct
{
  unsigned char buffer[BUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
  const int len;
} Buffer;

/********************** INLINE FUNCTIONS **********************/
__ALWAYS_INLINE __STATIC_INLINE char buf_consumeByte(Buffer *buffer) {
	char c = (buffer->buffer)[buffer->tail];
	buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;

	return c;
}

__ALWAYS_INLINE __STATIC_INLINE void buf_clear(Buffer *buffer) {
	buffer->head = 0;
	buffer->tail = 0;
}

/********************** FUNCTION DECLARATIONS **********************/
uint16_t buf_writeStr(const char *str, Buffer *buffer);
uint16_t buf_ok(Buffer *buffer);
uint16_t buf_crcr(Buffer *buffer);
void buf_pop(Buffer *buffer, uint16_t len);
uint16_t buf_writeByte(Buffer *buffer, unsigned char c);
uint16_t buf_writeChars(Buffer *buffer, const char *str, size_t strLen);
void buf_pop_tail(Buffer *buffer, uint16_t len);

/********************** VARIABLES **********************/
Buffer *uart2_tx_buffer;
Buffer *uart2_rx_buffer;

#endif /* RINGBUF_H_ */
