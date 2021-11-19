
#include "utils_ringbuffer_extension.h"
#if __has_include("utils_ringbuffer.h")

#include "utils_ringbuffer.h"


/**
 * \brief Get one byte from ringbuffer
 *
 */
int32_t ringbuffer_peek(struct ringbuffer *const rb, uint8_t *data)
{
	ASSERT(rb && data);

	if (rb->write_index != rb->read_index) {
		*data = rb->buf[rb->read_index & rb->size];
		return ERR_NONE;
	}

	return ERR_NOT_FOUND;
}

/**
 * \brief Get one byte from ringbuffer
 *
 */
int32_t ringbuffer_peekMany(struct ringbuffer *const rb, uint8_t* data, uint32_t count)
{
	ASSERT(rb && data);
	
	uint32_t num = ringbuffer_num(rb);
	
	if (rb->write_index != rb->read_index) 
	{
		uint32_t index = rb->read_index;
		int i;
		for(i = 0; i < count && i < num; i++)
		{
			data[i] = rb->buf[index++ & rb->size];
		}
		return i;
	}

	return 0;
}

#endif