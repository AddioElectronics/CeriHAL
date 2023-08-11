# CeriHAL
#### `V0.1.3`

C library for extending and redirecting the HAL IO drivers, and provides arduino like serial functions for printing and reading.

 
## Usage (Atmel Start)

- Run `git clone https://github.com/AddioElectronics/CeriHAL.git`
- Run `git submodule update --init --recursive`
- Create a project with Atmel Start.
  - Add the `Middleware/Utilities/STDIO Redirect` component.
  - USB
	- Add the `Middleware/USB Stack/USB Device CDC ACM` component.
	- Configure proper clock settings for USB.
  - USART
	- Add the `Drivers/USART` component, or use the "Target_IO" from "STDIO Redirect".
	- Under Component Settings, change Driver: to "HAL:Driver:USART_Async" or "HAL:Driver:USART_Sync"
  - Generate your project
- Move/Copy the CeriHAL folder to your project. *1
- In your Atmel Studio project properties, include each CeriHAL\submodules\* path in "ARM/GNU C Compiler->Directories."
- _(Optional)_ Edit the multiple "_config" files.
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
  - Call `system_timer_init()` *2 *3
- USB
  - Call `cdc_stdio_init()`
  - Register your desired callbacks using `usb_cdc_stdio_register_callback`
  - Initialize Serial IO descriptor using `Serial_Init()`
- USART
  - Call `addio_usart_async_extend()` *4
  - Register your desired callbacks using `usart_async_register_callback`
  - Initialize Serial IO descriptor using `Serial_Init()`
- You can now use `printf`, `stdio_io_write`, `stdio_io_read`, `Print`, `Println`, and much more.

**1** : If you wish to use the original "hal_io.h" and "stdio_io.h" delete the "hal" and "stdio_redirect" folders before copying into your project.
Some Serial functions/macros will not be able to be used with the original drivers.

**2** : If the system timer is not available. You will need to write your own millis() function, which returns how many milliseconds have elapsed since program start.
Create a source file and include "Addio/Embedded/Time/System_Timer/system_timer.h", which contains the millis() prototype.`

**3** : If you are using a new MCU or Core, it may not be supported yet. You can issue a bug report and I will add it asap. [If you wish to add support for an MCU or Core, there are short tutorials here.](https://github.com/AddioElectronics/AS-HAL-USB-CDC-STDIO-Redirect#How-to-Add-Support-for-a-Device)

**4** : You do not have to use the extended IO descriptors, although some Serial functions will not work. More info coming soon.


### Example
Example located in [main.c](https://github.com/AddioElectronics/CeriHAL/blob/main/main.c)

Data will be echoed back, unless certain commands are sent.

#### Commands
`Commands are not apart of CeriHAL, they are specific to the example and simply used to display the CeriHAL functions.` 

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
 
 ## Included Repos
 
 ##### SubModules
- [AS-HAL-USB-CDC-STDIO-Redirect](https://github.com/AddioElectronics/AS-HAL-USB-CDC-STDIO-Redirect) ***1**
- [GeNETiCC-Barebones](https://github.com/AddioElectronics/GeNETiCC/tree/GeNETiCC_Barebones_SubModule)
 
 1. Only compatible with Atmel Start

## License

CeriHAL is released under the [MIT License](http://www.opensource.org/licenses/MIT).

## Author

- Author : Addio from Addio Electronics (Canada)
- Website : www.Addio.io
