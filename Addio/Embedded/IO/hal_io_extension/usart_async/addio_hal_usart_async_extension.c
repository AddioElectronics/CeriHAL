#include "addio_hal_usart_async_extension.h"
#if __has_include("hal_usart_async.h")

#include <utils.h>

#include "../../addio_io.h"
#include "../utils/utils_ringbuffer_extension.h"

static int32_t usart_async_peek(struct io_descriptor *const io_descr);
static int32_t usart_async_peekMany(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length);
static int32_t usart_async_rxReady(struct io_descriptor *const io_descr);
static int32_t usart_async_txReady(struct io_descriptor *const io_descr);

static void usart_tx_complete_cb(const struct usart_async_descriptor *const descr);

//char* buffer[16];

/**
 * \brief Extend usart interface
 */
int32_t addio_usart_async_extend(struct usart_async_descriptor *const descr)
{
	descr->io.peek = usart_async_peek;
	descr->io.peekMany = usart_async_peekMany;
	descr->io.rxReady = usart_async_rxReady;
	descr->io.txReady = usart_async_txReady;
	
	/*
	*	Recommended to either enable both tx_wait_for_complete and tx_check_previous_for_completion,
	*	or to limit the interval to 2ms using tx_min_interval (baud rate 115200 with 48MHz clock).
	*	Only 1 of the 2 options are necessary.
	*
	*	*Limiting the interval limits how many transfers, not how many bytes.
	*
	*	*If you are using standard printf functions instead of Addio/Embedded/IO/Serial/Print,
	*	do not limit the interval as printf sends bytes 1 at a time.
	*/
	descr->io.flags.tx_wait_for_complete = true;
	descr->io.flags.tx_check_previous_for_completion = true;
	descr->io.flags.tx_min_interval = 2000;	//2ms
	descr->io.flags.print_quick = false;
	return ERR_NONE;
}


static int32_t usart_async_peek(struct io_descriptor *const io_descr)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(io_descr, struct usart_async_descriptor, io);

	ASSERT(descr);

	return (int32_t)*(descr->rx.buf + descr->rx.read_index);
}

static int32_t usart_async_peekMany(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(io_descr, struct usart_async_descriptor, io);

	ASSERT(descr && buf && length);

	return ringbuffer_peekMany(&descr->rx, buf, length);
}

static int32_t usart_async_rxReady(struct io_descriptor *const io_descr)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(io_descr, struct usart_async_descriptor, io);

	ASSERT(descr);

	return (int32_t)ringbuffer_num(&descr->rx);
}


static int32_t usart_async_txReady(struct io_descriptor *const io_descr)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(io_descr, struct usart_async_descriptor, io);
	
	ASSERT(descr);	
	
	return usart_async_is_tx_empty(descr);
}


#endif