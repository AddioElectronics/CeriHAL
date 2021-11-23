#ifndef SERIAL_CONFIG_H_
#define SERIAL_CONFIG_H_



/*
*	How many IO ports are available.
*/
#define SERIAL_IO_PORTS 2

/*
*	How many milliseconds will the read/write functions wait before timeout.
*/
#define SERIAL_TIMEOUT 100


///*
//*	Default transfer limit in milliseconds.
//*
//*	*Only used if the I/O descriptor has the tx_limit_rate flag checked,
//*	*and the tx_rate is 0, it will use the default value.
//*/
//#define SERIAL_DEFAULT_TX_RATE 5


#endif /* SERIAL_CONFIG_H_ */