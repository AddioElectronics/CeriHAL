#ifndef ADDIO_HAL_USART_SYNC_EXTENSION_H_
#define ADDIO_HAL_USART_SYNC_EXTENSION_H_
#if __has_include("hal_usart_sync.h")

#include <hal_usart_sync.h>

/*
*	Extends the hal_usart_async to use the addio_io.h IO descriptor.
*/
int32_t addio_usart_sync_extend(struct usart_sync_descriptor *const descr);

#endif
#endif /* ADDIO_HAL_USART_SYNC_EXTENSION_H_ */