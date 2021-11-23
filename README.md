# CeriHAL
#### `V0.1.0`

C library for extending and redirecting the HAL IO drivers, and provides arduino like serial functions for printing and reading.

`Only tested using Atmel ARM MCU's with Atmel Start. May not be compatible with other MCU brands.`
 
 Contains [AS-HAL-USB-CDC-STDIO-Redirect](https://github.com/AddioElectronics/AS-HAL-USB-CDC-STDIO-Redirect).
 
 Contains part of [GeNETiCC](https://github.com/AddioElectronics/GeNETiCC).
 
## Usage

`More and better info coming soon` 

You may be better off looking at the [Example](https://github.com/AddioElectronics/CeriHAL/blob/main/main.c).

- Create a project with Atmel Start.
  - Add the `Middleware/Utilities/STDIO Redirect` component.
  - USB
	- Add the `Middleware/USB Stack/USB Device CDC ACM` component.
	- Configure proper clock settings for USB.
  - USART
	- Add the `Drivers/USART` component, or use the "Target_IO" from "STDIO Redirect".
	- Under Component Settings, change Driver: to "HAL:Driver:USART_Async" or "HAL:Driver:USART_Sync"
  - Generate your project
- Import the Addio folder and its contents to your project. *1
- _(Optional)_ Edit the multiple "_config" files to your liking.
- _(Optional)_In `atmel_start.c`, comment out `stdio_redirect_init();`
- Include headers
  - `#include "Addio/Embedded/IO/Serial/serial.h"`
  - `#include "Addio/GeNETiCC/Embedded/IO/Serial/serial_geneticc.h"`
  - `#include "Addio/Embedded/Time/System_Timer/system_timer.h"`
  - USB
    - `#include "Addio/Embedded/IO/Atmel Start/cdc_stdio_redirect/usb_cdc_stdio.h"`
  - USART
     - `#include "Addio/Embedded/IO/hal_io_extension/usart_async/addio_hal_usart_async_extension.h"`
- Initialization
  - Call `system_timer_init()` *2 *3 *4
- USB
  - Call `cdc_stdio_init()`
  - Register your desired callbacks using `usb_cdc_stdio_register_callback`
  - Initialize Serial IO descriptor using `Serial_Init()`
- USART
  - Call `addio_usart_async_extend()` *5
  - Register your desired callbacks using `usart_async_register_callback`
  - Initialize Serial IO descriptor using `Serial_Init()`
- You can now use `printf`, `stdio_io_write`, `stdio_io_read`, `Print`, `Println`, and much more.

**1** : If you wish to use the original "hal_io.h" and "stdio_io.h" delete the "hal" and "stdio_redirect" folders before copying into your project.
Some Serial functions/macros will not be able to be used with the original drivers.

**2** : If the system timer is not available. You will need to write your own millis() function, which returns how many milliseconds have elapsed since program start.
Create a source file and include "Addio\Embedded\Time\Timing\timing.h", which contains the millis() prototype.`

**3** : If you are not using the Samd21, you will need to add includes to your IC in the `system_timer_atmelstart_cm0plus.c,` like the example below. In future versions more MCU's will be supported out of the box.

**4** : If you are not using a cm0plus, you will need to add an include for that. As long as they use the same macros/functions/registers as cm0plus, if you choose to you can modify `system_timer_atmelstart_cm0plus.c,` or better yet create a new file for the CPU type.  In future versions more CPU's will be supported out of the box.

**5** : You do not have to use the extended IO descriptors, although some Serial functions will not work. More info coming soon.

__Adding new IC/CPU to system timer__
``` C
/*
*	Include IC header
*/
#if defined(__SAMD21J18A__)
#include <samd21j18a.h>

#elif //Add your IC here.

#else
#error unsupported
#endif

#include <core_cm0plus.h> //Requires IC header.
```

### Example

Example located in [main.c](https://github.com/AddioElectronics/CeriHAL/blob/main/main.c)

Data will be echoed back, unless certain commands are sent.

#### Commands
 - %TXCOUNT : Returns the amount of tranfers received from the host.
 - %HEX 	: Starts waiting for a sequence of commands.
 
 
##### HEX Command

Collects a sequence of parameters sent from the host, and calls a function when all parameters have been received.
The function prints memory in the format of a HEX editor.

###### Data Expected __(In order)__
<table>
  <tr> 
  <th>Step #</th>
  <th>Name</th>
  <th>Command/Format</th>
  <th>Description</th>
 </tr>
 <tr> 
  <th>1.</th>
  <td>Start</td>
  <td>%HEX</td>
  <td>Start the state machine, will begin looking for address.</td>
 </tr>
 <tr> 
  <th>2.</th>
  <td>Address</td>
  <td>0x00000000</td>
  <td>The starting location to display./td>
 </tr>
  <tr> 
  <th>3.</th>
  <td>Length</td>
  <td>8-infinity</td>
  <td>How many bytes to display./td>
 </tr>
  <tr> 
  <th>4.</th>
  <td>Line Length</td>
  <td>8, 16, 32, 64</td>
  <td>How many bytes per line to display. *Must be less than or equal to length./td>
 </tr>
  <tr> 
  <th>5.</th>
  <td>Labels</td>
  <td>0, 1</td>
  <td>Display column labels?/td>
 </tr>
  <tr> 
  <th>6.</th>
  <td>Text Column</td>
  <td>0, 1</td>
  <td>Display a text representation in the right most column./td>
 </tr>
 </table>

## License

CeriHAL is released under the [MIT License](http://www.opensource.org/licenses/MIT).

## Author

- Author : Addio from Addio Electronics (Canada)
- Website : www.Addio.io
