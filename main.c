/*
*	CeriHAL demo.
*
*	Contains Arduino like Serial print and reading functions/macros.
*	Replaces "hal_io" and "hal_stdio_io," with extended versions "addio_io" and "addio_stdio_io."
*/

#include <atmel_start.h>
#include <stdio_io.h>
#include <usb_start.h>

//Requires adding "Addio/using" to project's included directories.
#include <using_Addio.Universal.Standard.h>
#include <using_Addio.Embedded.IO.h>
#include <using_Addio.GeNETiCC.Embedded.IO.h>
#include <using_Addio.Embedded.Time.h>

#include "Addio/Embedded/IO/hal_io_extension/usart_async/addio_hal_usart_async_extension.h"


#define USB_CDC_IO_PORT_ID			0
#define USART_EBDG_IO_PORT_ID		1

void usb_cdc_rx_cb(const uint16_t length);
void usart_rx_cb(const struct usart_async_descriptor *const descr);


typedef enum {
	RX_IDLE,
	RX_ADDR,
	RX_LENGTH,
	RX_LINE_LENGTH,
	RX_LABELS,
	RX_TEXT
}rx_states_t;

typedef struct 
{
	char* addr;
	int length;
	int line_length;
	bool labels;
	bool text;
}rx_parameters_t;

rx_states_t usb_states;
rx_parameters_t usb_parameters;

void rx_state_machine(rx_states_t* rx_state, rx_parameters_t* rx_params);

uint32_t usb_transfer_count = 0;
uint32_t usart_transfer_count = 0;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	//Extend the HAL USART async to use addio_io.h instead of stdio_io.h
	//Usart connected to Atmel Embedded Debugger on Samd21j Xplained Pro
	addio_usart_async_extend(&USART_EBDG);
	
	//Initiate USB CDC for use with stdio
	cdc_stdio_init();	
	
	usart_async_register_callback(&USART_EBDG, USART_ASYNC_RXC_CB, usart_rx_cb);
	
	//Enable USART.
	usart_async_enable(&USART_EBDG);
	
	/* 
		Initialize USB CDC and HAL USART for use with the Serial library.
		
		*Last one initialized is the active IO port.
		 All Serial functions call into the active port.
		 To change active port use "Serial(port_id),"
		 If not using GeNETiCC, use "serial_set_port(port_id)"
	*/
	Serial_Init(&USB_CDC_IO, USB_CDC_IO_PORT_ID);
	Serial_Init(&USART_EBDG, USART_EBDG_IO_PORT_ID);

	/*
		Initialize system timer for millis().
		If you are using the system timer for something else, you will need to create your own millis() function.
		millis() prototype located in "Addio\Embedded\Time\Timing\timing.h"
		The option to use the RTC or a regular timer will be added in a future update.
	*/
	system_timer_init();
	
	//Register RX callback for USB CDC
	usb_cdc_stdio_register_callback(USB_CDC_RX_DATA, (FUNC_PTR)usb_cdc_rx_cb);
	
	//Wait for the DTR signal 
	while(!cdc_data_terminal_ready()){}
	
	
	//Prints to UART, last IO descriptor initialized was USART_EBDG.
	Println("Initialized");
	
	//Set active IO to USB
	Serial(0); //USB_CDC_IO_PORT_ID = 0
	
	//Prints to USB
	Println("Initialized");
	
	/* Replace with your application code */
	while (1) {
		

		//Set USB CDC as active I/O descriptor.
		Serial(USB_CDC_IO_PORT_ID);
	
		if(Serial_Available())
		{
			rx_state_machine(&usb_states, &usb_parameters);
		}

		//Set Embedded Debugger USART as active I/O descriptor.
		Serial(USART_EBDG_IO_PORT_ID);
		
		if(Serial_Available())
		{
			//Warning : string_t must be freed when done using "cstring_delete(string_t* string)."
			string_t* uartString = Serial_ReadString();
			
			 if(string_contains_charp(uartString, "%TCOUNT", 0, false))
			 {
				 Printfln("USART Transfer Count : %d", usart_transfer_count);
			 }
			 else
			 {
				 //Echo
				 PrintlnString(uartString);
			 }
			
			//Free uartString's buffer and structure from memory.
			string_delete(uartString);
		}

	}
}


bool is_string_hex_chars(string_t* string)
{
	for(int i = 0; i < string->length; i++)
	{
		char c = string->buf[i];
		if(c < '0' ||
		(c > '9' && c < 'A' )||
		(c > 'F' && c < 'a' )||
		c > 'f')
		return false;
	}
	return true;
}

bool is_string_digits(string_t* string)
{
	for(int i = 0; i < string->length; i++)
	{
		char c = string->buf[i];
		if(c < '0' || c > '9')
		return false;
	}
	return true;
}

/*
*	Collects parameters for a function, and finally calls the function.
*	The function prints memory in the format of a hex editor.
*
*	*Calls PrintDataHexEditor macro which calls serial_print_data_hex_addr
*
*	**Data Expected**
*	1. start			: %HEX			- Start the state machine, will begin looking for address.
*	2. address			: 0x00000000	- The starting location to display
*	3. length			: 8-infinity	- How many bytes to display
*	4. line length		: 8, 16, 32, 64	- How many bytes per line to display. *Must be less than or equal to length.
*	5. display labels	: 0, 1			- Display column labels?
*	6. display text		: 0, 1			- Display a text representation in the right most column.
*
*	After step 6, the data will be printed to the active IO descriptor (USB CDC).
*/
void rx_state_machine(rx_states_t* rx_state, rx_parameters_t* rx_params)
{
	//Warning : string_t must be freed when done using "cstring_delete(string_t* string)."
	string_t* string = NULL;

	switch(*rx_state)
	{
		case RX_IDLE:
		{
			string = Serial_ReadString();
			
			if(string_startsWith_charp(string, "%HEX", 0, false))
			{
				Println("Begin RX State Machine");
				*rx_state = RX_ADDR;
				Println("Waiting for Address(32bit hex)...");
			}
			else if(string_contains_charp(string, "%TCOUNT", 0, false))
			{
				Printfln("USB Transfer Count : %d", usb_transfer_count);
			}
			else
			{
				//Echo
				PrintlnString(string);
			}
		}		
		break;
		case RX_ADDR:
		{
			string = Serial_ReadString();
			
			if(string_startsWith_charp(string, "0x", 0, false))
			{
				string_t* address = string_subString(string, 2, 8);
				
				if(is_string_hex_chars(address))
				{
					rx_params->addr = (char*)strtol(address->buf, NULL, 16);
					Print("Address Accepted : 0x");
					PrintlnDataBase(&rx_params->addr, 4);
					*rx_state = RX_LENGTH;
					Println("Waiting for Length(8 to )...");
					string_delete(address);
					break;
				}
			}
	
			Println("Address Invalid");
			Println("Waiting for Address(32-bit hex (0x________)...");
		}
		break;
		case RX_LENGTH:
		{
			rx_params->length = Serial_ParseInt();
			
			if(rx_params->length < 8 /*|| rx_params->length > 1024*/)
			{
				Println("Length Invalid");
				Println("Waiting for Length(8 to )...");
				rx_params->length = 0;
				break;
			}
			Print("Length Accepted : ");
			Println(rx_params->length);
			Println("Waiting for Line Length(8, 16, 32, 64)...");
			*rx_state = RX_LINE_LENGTH;
		}		
		break;
		case RX_LINE_LENGTH:
		{
			rx_params->line_length = Serial_ParseInt();
			
			if(rx_params->line_length >= 8 && rx_params->line_length % 8 == 0 && rx_params->line_length <= 64 && rx_params->line_length <= rx_params->length)
			{
				Print("Line Length Accepted : ");
				Println(rx_params->line_length);
				Println("Waiting for Show Labels(0, 1)...");
				*rx_state = RX_LABELS;
				
				break;
			}
			Println("Line Length Invalid");
			
			if(rx_params->line_length >= rx_params->length)
			{
				Print("Length can not be smaller than line length. Length : ");
				Println(rx_params->line_length);
			}
			
			Println("Waiting for Line Length(8, 16, 32, 64)...");
			rx_params->line_length = 0;
		}		
		break;
		case RX_LABELS:
		{
			rx_params->labels = (bool)Serial_ParseInt();
			if(rx_params->labels != 0 && rx_params->labels != 1)
			{
				Println("Length Invalid");
				Println("Waiting for Show Labels(0, 1)...");
				rx_params->labels = 0;
				break;
			}
			Print("Show Labels Accepted : ");
			Println((bool)rx_params->labels);
			Println("Waiting for Show Text(0, 1)...");
			*rx_state = RX_TEXT;
		}
		break;
		case RX_TEXT :
		{
			rx_params->text = (bool)Serial_ParseInt();
			if(rx_params->text != 0 && rx_params->text != 1)
			{
				Println("Show Text Invalid");
				Println("Waiting for Show Text(0, 1)...");
				rx_params->labels = 0;
				break;
			}
			Print("Show Text Accepted : ");
			Println((bool)rx_params->labels);
			*rx_state = RX_IDLE;
			
			//Print memory like a hex editor using all the values we collected.
			PrintDataHexEditor(rx_params->addr, rx_params->length, rx_params->line_length, rx_params->labels, rx_params->text);
		}
		break;
	}
	
	//Free the string's buffer and structure from memory.
	string_delete(string);
	
	//Flush any newline characters from the buffer.
	Serial_FlushRx();
	
	delay_ms(100);
}

void usb_cdc_rx_cb(const uint16_t length)
{
	//No need to read data in callback, data is put in a ring buffer during the interrupt.
	
	/*
		When receiving a USB transfer larger than 64 bytes in the callback,
		and the callback contains a write, the COM port will freeze.
		I am currently looking for a fix.
	*/
	
	usb_transfer_count++;
}

void usart_rx_cb(const struct usart_async_descriptor *const descr)
{
	//No need to read data in callback, data is put in a ring buffer during the interrupt.
	
	usart_transfer_count++;
}

