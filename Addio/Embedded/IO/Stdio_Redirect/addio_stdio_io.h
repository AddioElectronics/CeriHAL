#ifndef ADDIO_STDIO_IO_H_
#define ADDIO_STDIO_IO_H_


#include "../addio_io.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *  \brief Initialize STDIO access
 *  \param[in] io Pointer to IO descriptor,
 *                NULL to discard R/W without any error.
 */
void stdio_io_init(struct io_descriptor* io);

/**
 *  \brief Change IO descriptor for terminal to R/W data
 *  \param[in] io Pointer to IO descriptor,
 *                NULL to discard R/W without any error.
 */
void stdio_io_set_io(struct io_descriptor* io);

/**
 *  \brief Read through specified terminal
 *  \param[out] buf Pointer to buffer to place read data
 *  \param[in] len Data length in number of bytes
 *  \return status
 *  \retval >=0 number of bytes read
 *  \retval <0 error
 */
int32_t stdio_io_read(uint8_t* buf, const uint16_t len);

/**
 *  \brief Write through specified terminal
 *  \param[in] buf Pointer to buffer to place data to write
 *  \param[in] len Data length in number of bytes
 *  \return status
 *  \retval >=0 number of bytes read
 *  \retval <0 error
 */
int32_t stdio_io_write(const uint8_t* buf, const uint16_t len);

/**
 *  \brief Peek the first byte in the RX buffer.
 *	
 *  \returns The first byte in the RX buffer, or -1 if the buffer is empty.
 */
int32_t stdio_io_peek();

//int32_t stdio_io_get();

/**
 *  Peeks n length of bytes in the RX buffer, without decrementing the length or removing the data.
 *	
 *	\param[in]	buf	The buffer to copy the peeked data too.
  *	\param[in]	len	The amount of bytes to attempt to peek.
 *
 *  \returns The amount of bytes peeked.
 */
int32_t stdio_io_peekMany(uint8_t* buf, const uint16_t len);

/**
 *  Checks if any bytes have been received, or with buffered systems it will return the amount of bytes received.
 *	
 *  \returns If any bytes have been received, or with buffered systems it will return the amount of bytes received.
 */
int32_t stdio_io_rxReady();


/**
 * \brief I/O get interface
 *
 * This function checks to see if an I/O descriptor is accepting new writes.
 * For systems that use a ring buffer (or similar), it will return how many bytes are empty in the TX buffer.
 *
 * /return True or false depending on if the I/O descriptor is ready to write, or how many empty bytes are in the buffer.
 */
int32_t stdio_io_txReady();

/**
 * \brief I/O get interface
 *
 * This function will clear the RX buffer, if using a buffered system.
 *
 * /return A count of how many bytes were flushed from the buffer.
 */
int32_t stdio_io_flushRx();

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* ADDIO_STDIO_IO_H_ */