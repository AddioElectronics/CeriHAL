#include "addio_hal_usart_sync_extension.h"
#if __has_include("hal_usart_sync.h")

#include <utils.h>
#include <utils_assert.h>

#include "../../addio_io.h"

static int32_t usart_sync_rxReady(struct io_descriptor *const io_descr);
static int32_t usart_sync_txReady(struct io_descriptor *const io_descr);

//char* buffer[16];

/**
 * \brief Extend usart interface
 */
int32_t addio_usart_sync_extend(struct usart_sync_descriptor *const descr)
{
	descr->io.peek = NULL;
	descr->io.peekMany = NULL;
	descr->io.rxReady = usart_sync_rxReady;
	descr->io.txReady = usart_sync_txReady;
	descr->io.flags.tx_wait_for_complete = false;
	descr->io.flags.tx_check_previous_for_completion = false;
	descr->io.flags.tx_min_interval = 0;
	descr->io.flags.print_quick = true;
	return ERR_NONE;
}

static int32_t usart_sync_rxReady(struct io_descriptor *const io_descr)
{
	struct usart_sync_descriptor *descr = CONTAINER_OF(io_descr, struct usart_sync_descriptor, io);

	ASSERT(descr);

	return (int32_t)usart_sync_is_rx_not_empty(descr);
}


static int32_t usart_sync_txReady(struct io_descriptor *const io_descr)
{
	struct usart_sync_descriptor *descr = CONTAINER_OF(io_descr, struct usart_sync_descriptor, io);
	
	ASSERT(descr);	
	
	return usart_sync_is_tx_empty(descr);
	//return descr->tx_buffer_length == 0;
}

#endif

