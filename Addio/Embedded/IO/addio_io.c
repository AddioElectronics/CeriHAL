#include "addio_io.h"

#include <utils_assert.h>

#include "Addio/Universal/Time/timing.h"



//If the Addio Serial component is available, use its timeout.
#if __has_include("Serial/serial_config.h")
#include "Serial/serial_config.h"
extern unsigned long serial_timeout;
#define TIMEOUT serial_timeout
#else
#define TIMEOUT 1000
#endif


unsigned long previous_write_timestamp;

#if ADDIO_IO_USE_ADDITIONAL_VERIFICATION

/**
 * \brief I/O write interface
 */
int32_t io_write(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length)
{
	uint64_t start_time;
	
	ASSERT(io_descr && buf);
	
	//Check to see if the previous write has finished.
	if(io_descr->flags.tx_check_previous_for_completion)
	{
		start_time = millis();
		while(!io_descr->txReady(io_descr))
		{
			if(has_time_elapsed_ms(TIMEOUT, start_time))
			{
				return 0;
			}
		}
	}
	
	if(io_descr->flags.tx_min_interval > 0)
	{
		//Wait until the minimum amount of microseconds have elapsed since the last transfer.
		while(micros() - previous_write_timestamp < io_descr->flags.tx_min_interval){}
	}
		
	//Send the data to the current IO descriptor.
	int32_t result = io_descr->write(io_descr, buf, length);
	
	//Mark timestamp for previous write.
	if(io_descr->flags.tx_min_interval > 0)
	previous_write_timestamp = micros();
	
	//Wait for the write to finish sending.
	if(io_descr->flags.tx_wait_for_complete)
	{
		start_time = millis();
		while(!io_descr->txReady(io_descr))
		{
			if(has_time_elapsed_ms(TIMEOUT, start_time))
			{
				return 0;
			}
		}
	}
		
	return result;
}

/**
 * \brief I/O read interface
 */
int32_t io_read(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length)
{
	uint64_t start_time;
	
	ASSERT(io_descr && buf);
	
	if(io_descr->flags.rx_timed_read)
	{
		start_time = millis();
		while(!io_rxReady(io_descr))
		{
			if(has_time_elapsed_ms(TIMEOUT, start_time))
			{
				return -1;
			}
		}
	}
	
	return io_descr->read(io_descr, buf, length);
}

/**
 * \brief I/O peek interface
 */
int32_t io_peek(struct io_descriptor *const io_descr)
{
	uint64_t start_time;
	
	ASSERT(io_descr);
	
	if(io_descr->flags.rx_timed_read)
	{
		start_time = millis();
		while(!io_rxReady(io_descr))
		{
			if(has_time_elapsed_ms(TIMEOUT, start_time))
			{
				return -1;
			}
		}
	}
	
	return io_descr->peek(io_descr);
}

/**
 * \brief I/O peekMany interface
 */
int32_t io_peekMany(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length)
{
	uint64_t start_time;
	
	ASSERT(io_descr && buf);
	
	if(io_descr->flags.rx_timed_read)
	{
		start_time = millis();
		while(!io_rxReady(io_descr))
		{
			if(has_time_elapsed_ms(TIMEOUT, start_time))
			{
				return -1;
			}
		}
	}
	
	return io_descr->peekMany(io_descr, buf, length);
}

#else

/**
 * \brief I/O write interface
 */
int32_t io_write(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length)
{
	ASSERT(io_descr && buf);
	return io_descr->write(io_descr, buf, length);
}

/**
 * \brief I/O read interface
 */
int32_t io_read(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length)
{
	ASSERT(io_descr && buf);
	return io_descr->read(io_descr, buf, length);
}

/**
 * \brief I/O peek interface
 */
int32_t io_peek(struct io_descriptor *const io_descr)
{
	ASSERT(io_descr);
	return io_descr->peek(io_descr);
}

/**
 * \brief I/O peekMany interface
 */
int32_t io_peekMany(struct io_descriptor *const io_descr, const uint8_t* buf, const uint16_t length)
{
	ASSERT(io_descr && buf);
	return io_descr->peekMany(io_descr, buf, length);
}

#endif

/**
 * \brief I/O rxLength interface
 */
int32_t io_rxReady(struct io_descriptor *const io_descr)
{
	ASSERT(io_descr);
	return io_descr->rxReady(io_descr);
}


/**
 * \brief I/O txCapacity interface
 */
int32_t io_txReady(struct io_descriptor *const io_descr)
{
	ASSERT(io_descr);
	return io_descr->txReady(io_descr);
}


/**
 * \brief I/O flushRx interface
 */
int32_t io_flushRx(struct io_descriptor *const io_descr)
{
	ASSERT(io_descr);
	return io_descr->flushRx(io_descr);
}