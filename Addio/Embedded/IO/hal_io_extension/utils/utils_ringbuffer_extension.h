
#ifndef _UTILS_RINGBUFFER_EXTENSION_H_INCLUDED
#define _UTILS_RINGBUFFER_EXTENSION_H_INCLUDED
#if __has_include("utils_ringbuffer.h")

#include <utils_ringbuffer.h>

#ifdef __cplusplus
extern "C" {
#endif




/**
 * \brief Peeks one byte from ring buffer, the user needs to handle the concurrent
 * access on buffer via put/get/flush
 *
 * \param[in] rb The pointer to a ring buffer structure instance
 * \param[in] data One byte space to store the read data
 *
 * \return ERR_NONE on success, or an error code on failure.
 */
int32_t ringbuffer_peek(struct ringbuffer* const rb, uint8_t* data);


/**
 * \brief Peeks n bytes from ring buffer, the user needs to handle the concurrent
 * access on buffer via put/get/flush
 *
 * \param[in] rb The pointer to a ring buffer structure instance
 * \param[in] data One byte space to store the read data
 *
 * \return count of how many bytes were read.
 */
int32_t ringbuffer_peekMany(struct ringbuffer* const rb, uint8_t* data, uint32_t count);

/**@}*/

#ifdef __cplusplus
}
#endif
#endif /*__has_include("utils_ringbuffer.h")*/
#endif /* _UTILS_RINGBUFFER_H_INCLUDED */
