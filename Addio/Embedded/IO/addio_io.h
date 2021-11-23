/*
*	Extending hal_io.h designed for "stream" buffers.
*/

#warning If you are using this with regular Atmel Start libraries, you will need to create the missing functions, (get, peek, peekMany, rxLength, txCapacity) \
if you use functions that make use of them \
example in addio/embedded/io/hal_io_extension/usart_async.

#ifndef ADDIO_IO_H_
#define ADDIO_IO_H_

#include <compiler.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
*	Use functions that check the io_descriptor control flags,
*	and perform the corresponding checks.
*
*	*Without the additional verifications, the data may be sent too fast, and result in lost data.
*	*Certain libraries do not require this, such as hal_usart_sync, where its sibling hal_usart_async does.
*/
#define ADDIO_IO_USE_ADDITIONAL_VERIFICATION true

typedef union{
	struct{
		bool tx_check_previous_for_completion : 1;	//Check to see if the previous tx has completed before a write.
		bool tx_wait_for_complete : 1;				//Wait for transfer to complete immediately after a write.
		bool rx_timed_read : 1;						//On read, check if rx is ready. If rx is not ready, wait until timeout.
		bool print_quick : 1;						//If using Serial/print, safety checks will be skipped and its io_write function will be called directly.
		//bool tx_limit_rate : 1;					//Should the transfer rate be limited?
		uint16_t tx_min_interval : 14;				//The minimum interval between transfer. (Microseconds) | Max = 16383 microseconds
		};	
	uint16_t flags;
}addio_io_control_t;


/**
 * \brief I/O descriptor
 *
 * The I/O descriptor forward declaration.
 */
struct io_descriptor;

/**
 * \brief I/O write function pointer type
 */
typedef int32_t (*io_write_t)(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length);

/**
 * \brief I/O read function pointer type
 */
typedef int32_t (*io_read_t)(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length);

/**
 * \brief I/O read function pointer type
 */
typedef int32_t (*io_peek_t)(struct io_descriptor *const io_descr);

/**
 * \brief I/O read function pointer type
 */
typedef int32_t (*io_peekMany_t)(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length);

/**
 * \brief I/O read function pointer type
 */
typedef int32_t (*io_rxReady_t)(struct io_descriptor *const io_descr);

/**
 * \brief I/O read function pointer type
 */
typedef int32_t (*io_txReady_t)(struct io_descriptor *const io_descr);

/**
 * \brief I/O read function pointer type
 */
typedef int32_t (*io_flushRx_t)(struct io_descriptor *const io_descr);

/**
 * \brief I/O descriptor
 */
struct io_descriptor {
	io_write_t write;
	io_read_t read;
	io_peek_t peek;
	io_peekMany_t peekMany;			//Optional
	io_rxReady_t rxReady;
	io_txReady_t txReady;			//Optional, if the io_write_t function handles it internally.
	io_flushRx_t flushRx;			//Optional, if using a buffered system.
	addio_io_control_t flags;
};

/**
 * \brief I/O write interface
 *
 * This function writes up to \p length of bytes to a given I/O descriptor.
 * It returns the number of bytes actually write.
 *
 * \param[in] descr  An I/O descriptor to write
 * \param[in] buf    The buffer pointer to store the write data
 * \param[in] length The number of bytes to write
 *
 * \return The number of bytes written
 */
int32_t io_write(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length);

/**
 * \brief I/O read interface
 *
 * This function reads up to \p length bytes from a given I/O descriptor, and
 * stores it in the buffer pointed to by \p buf. It returns the number of bytes
 * actually read.
 *
 * \param[in] descr  An I/O descriptor to read
 * \param[in] buf    The buffer pointer to store the read data
 * \param[in] length The number of bytes to read
 *
 * \return The number of bytes actually read. This number can be less than the
 *         requested length. E.g., in a driver that uses ring buffer for
 *         reception, it may depend on the availability of data in the
 *         ring buffer.
 */
int32_t io_read(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length);


///**
 //* \brief I/O get interface
 //*
 //* This function reads 1 byte from a given I/O descriptor, and returns it.
 //* If the buffer is empty, it will return -1.
 //*
 //* \param[in] descr  An I/O descriptor to read
 //*
 //* \return The first byte in the buffer, or -1 if the buffer is empty.
 //*/
//int32_t io_get(struct io_descriptor *const io_descr);

/**
 * \brief I/O get interface
 *
 * This function reads 1 byte from a given I/O descriptor, and returns it without decrementing the buffer's size.
 *
 * \param[in] descr  An I/O descriptor to read
 *
 * \return The first byte in the buffer, or -1 if the buffer is empty.
 */
int32_t io_peek(struct io_descriptor *const io_descr);

/**
 * \brief I/O read interface
 *
 * This function reads up to \p length bytes from a given I/O descriptor, and
 * stores it in the buffer pointed to by \p buf. It returns the number of bytes
 * actually read. It will not remove the data from the buffer or decrement the size.
 *
 * \param[in] descr  An I/O descriptor to peek
 * \param[in] buf    The buffer pointer to store the peek data
 * \param[in] length The number of bytes to peek
 *
 * \return The number of bytes actually read. This number can be less than the
 *         requested length. E.g., in a driver that uses ring buffer for
 *         reception, it may depend on the availability of data in the
 *         ring buffer.
 */
int32_t io_peekMany(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length);

/**
 * \brief I/O get interface
 *
 * This function checks if any bytes have been received. For asynchronous(buffered) systems, it will return how many bytes have been received.
 *
 * \param[in] descr  An I/O descriptor to get information from.
 *
 * \return If any bytes have been received, or how many bytes have been received.
 */
int32_t io_rxReady(struct io_descriptor *const io_descr);


/**
 * \brief I/O get interface
 *
 * This function checks to see if an I/O descriptor is accepting new writes.
 * For systems that use a ring buffer (or similar), it will return how many bytes are empty in the TX buffer.
 *
 * \param[in] descr  An I/O descriptor to get information from.
 *
 * /return True or false depending on if the I/O descriptor is ready to write, or how many empty bytes are in the buffer.
 */
int32_t io_txReady(struct io_descriptor *const io_descr);

/**
 * \brief I/O get interface
 *
 * This function will clear the RX buffer, if using a buffered system.
 *
 * \param[in] descr  An I/O descriptor to get information from.
 *
 * /return A count of how many bytes were flushed from the buffer.
 */
int32_t io_flushRx(struct io_descriptor *const io_descr);

#ifdef __cplusplus
}
#endif
#endif /* ADDIO_IO_H_ */