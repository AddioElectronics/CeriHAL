
#include <atmel_start.h>
#include <stdio_io.h>
#include <usb_start.h>
#include <stdio.h>
#include <hal_delay.h>

#include <using_Addio.Universal.Standard.h>
#include <using_Addio.Embedded.IO.h>
#include <using_Addio.GeNETiCC.Embedded.IO.h>
#include <using_Addio.Embedded.Time.h>

#include "Addio/Embedded/IO/hal_io_extension/usart_async/addio_hal_usart_async_extension.h"


#define USB_CDC_IO_PORT 0
#define USART_QBUG_IO_PORT 1

uint8_t rx_buffer[USB_CDC_RX_BUF_SIZE+1];
uint8_t tx_buffer[USB_CDC_TX_BUF_SIZE+1];

#if CDC_TX_RETRY == false
int interval = 0;
#else
int interval = 10000;
#endif

int count;
int lastCount;
bool firstTime;

void DataReceived(const uint16_t length);


#define typename(x) _Generic((x),        /* Get the name of a type */             \
\
_Bool: "_Bool",                  unsigned char: "unsigned char",          \
const unsigned char: "unsigned char",          \
const char: "char",                     const signed char: "signed char",            \
char: "char",                     signed char: "signed char",            \
short int: "short int",         unsigned short int: "unsigned short int",     \
int: "int",                     unsigned int: "unsigned int",           \
long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
float: "float",                         double: "double",                 \
long double: "long double",                   char *: "pointer to char",        \
void *: "pointer to void",                int *: "pointer to int",         \
default: "other")


size_t test_vprintf_(const char* format, ...)
{
va_list ap;
va_start(ap, format);

size_t total = vprintlnf_(format, ap);
va_end(ap);
return total;
}

void DataSent(const uint16_t length)
{

}

bool receivedData;

//extern struct usart_sync_descriptor USART_QBUG;

#include "Addio/Embedded/Time/timing/timing.h"

char arr[64];
char rxbuf[16];

void tx_test1();
void tx_test2();

void rx_test1();

void usart_rx_cb(const struct usart_async_descriptor *const descr)
{
	int count =serial_readBytes(rxbuf, 16);	
		
	Serial_Write(rxbuf, count);
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	addio_usart_async_extend(&USART_EBDG);
	
	cdc_stdio_init();
	
	
	//usart_async_register_callback(&USART_EBDG, USART_ASYNC_RXC_CB, usart_rx_cb);
	
	usart_async_enable(&USART_EBDG);
	

	
	Serial_Init(&USB_CDC_IO, USB_CDC_IO_PORT);
	Serial_Init(&USART_EBDG, USART_QBUG_IO_PORT);
	
	//Serial(USART_QBUG_IO_PORT);
	
	system_timer_init();
	
	usb_cdc_stdio_register_callback(USB_CDC_RX_DATA, (FUNC_PTR)DataReceived);
	
	
	while(!cdc_data_terminal_ready()){}

	
	Println("Initialized");
	

	
	
	strcpy(arr, "BOOBIES");
	
	/* Replace with your application code */
	while (1) {
		
		//tx_test1();
		//tx_test2();
		rx_test1();
		
		//
		//if(Serial_Available())
		//{
			//
			//char peek = Serial_Peek();
			//
			//string_t* string = Serial_ReadString();
			//
			//Serial_Write(string->buf, string->length);
//
		//}
	

		
	}
}



void rx_test1()
{
	
	if(Serial_ActivePort() == USB_CDC_IO_PORT)
	Serial(USART_QBUG_IO_PORT);
	else
	Serial(USB_CDC_IO_PORT);
	
	
	
	if(Serial_Available() || usart_async_is_rx_not_empty(&USART_EBDG))
	{
		int count =serial_readBytes((char*)rxbuf, 16);	
		
		Serial_Write(rxbuf, count);
	}
}


void tx_test1()
{
	unsigned long ms = millis();
	while(1)
	{
		
		if(has_time_elapsed_ms(2500, ms))
		{
			Serial(1); //Uart
			
			Print("Millis : ");
			Println(millis());
			
			PrintDataHexEditor(&arr, 64);
			//PrintDataHexEditor(&arr, 64, 16);
			//PrintDataHexEditor(&arr, 64, 32);
			
			
			Serial(0); //USB
			
			Print("Millis : ");
			Println(millis());
			
			PrintDataHexEditor(&arr, 64);
			//PrintDataHexEditor(&arr, 64, 16);
			//PrintDataHexEditor(&arr, 64, 32);
			break;
		}
	}
}


void tx_test2()
{
	if(receivedData)
	{
	receivedData = false;
	
	if(Serial_ActivePort() == USB_CDC_IO_PORT)
	Serial(USART_QBUG_IO_PORT);
	else
	Serial(USB_CDC_IO_PORT);
	
	//uint32_t rxCount = stdio_io_read(&rx_buffer, USB_CDC_RX_BUF_SIZE);
	
	printfln("Should be int : %s", typename(10));
	printfln("Should be bool : %s", typename(false));
	char c = 'c';
	printfln("Should be char : %s", typename((char)'c'));
	printfln("Should be char : %s", typename(c));
	
	////char c = 'c';
	char arr[64];
	strcpy(arr, "BOOBIES");
	//typename(10);
	//typename(arr);
	//printf(typename(arr));
	//println_str();
	//println_char('c');
	//println((const char*)"BOOBIES");
	//
	//Println(10);
	//Println(arr);
	//printlnf_("This string should say test : %s", "Test");
	//Printfln(0xaaaa, 16);
	//Println(10);
	write(&arr, 7);
	
	
	test_vprintf_("%s, 0x%02x, %d", "test_vprintf_ : ", 0xad, 169);
	
	printf_("%s", "printf_");
	println_();
	print_data_hex_addr(&arr, 64, 8, true, true);
	print_data_hex_addr(&arr, 64, 16, true, true);
	print_data_hex_addr(&arr, 64, 32, true, true);
	println_data_base_sep(&arr, 8, 2, 4, ' ');
	println_data_base_sep(&arr, 8, 8, 4, ' ');
	println_data_base_sep(&arr, 8, 10, 4, ' ');
	println_data_base_sep(&arr, 8, 16, 8, ' ');
	println_data_base_sep(&arr, 8, 64, 16, ' ');
	//println_data_hex_sep(&arr, 64, 8, ' ');
	println_data_base64_sep(&arr, 64, 16, ' ');
	
	Println(11);
	Println((char)'c');
	Println(arr);
	Println(-2.5d);
	Println(2.5f);
	
	_Bool b = false;
	bool balls = true;
	
	Println(b);
	Println(balls);
	Println((bool)false);
	Println((bool)true);
	}
}


void DataReceived(const uint16_t length)
{
	
	receivedData = true;
	
	//uint32_t rxCount = io_read(&USB_CDC_IO, rx_buffer, USB_CDC_RX_BUF_SIZE);
	//
	//memcpy(tx_buffer, rx_buffer, rxCount);
	//
	//io_write(&USB_CDC_IO,tx_buffer, rxCount);

}
