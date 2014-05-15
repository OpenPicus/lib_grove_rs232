lib_grove_rs232
=========================

OpenPicus Flyport library for rs232 device. This kind of device allows user to interface with RS232 busses. You can find more info on OpePicus wiki: wiki.openpicus.com.<br>
<br>
To use the library inside your Flyport project, just follow these steps:<br>
1) Create a new project from a Grove template.<br>
2) import files inside Flyport IDE using the external libs button.<br>
3) add following code example in FlyportTask.c:

<pre>
#include "taskFlyport.h"
#include "grovelib.h"
#include "lib_grove_rs232.h"

char uBuff[256];
const int rs232PortNum = 2; // UART port that will be used by RS232 device

void FlyportTask()
{
	_dbgwrite("Welcome to GROVE RS232 example\r\n");
		
	// GROVE board
	void *board = new(GroveNest);
	
	// GROVE devices: RS232
	void *rs232 = new(Rs232, rs232PortNum);
	// Attach device to digital port (in this case port DIG4)
	attachToBoard(board, rs232, DIG4);
	
    // Now you can use standard Flyport UART APIs:
	UARTInit(rs232PortNum, 19200); 
	UARTOn(rs232PortNum);
	UARTWrite(rs232PortNum, "RS232 device connected and ready to be used!\r\n");
	
    while(1)
    {
 		// Loopback example: 
		// * each char sent by IDE Serial Monitor tool will be sent to RS232 device;
		// * each char sent from RS232 device will be shown to IDE Serial Monitor tool;
		if(UARTBufferSize(1) > 0)
		{
			int uSize = UARTBufferSize(1);
			UARTRead(1, uBuff, uSize);
			uBuff[uSize] = '\0';
			
			UARTWrite(rs232PortNum, uBuff);
		}
		
		if(UARTBufferSize(rs232PortNum) > 0)
		{
			int uSize2 = UARTBufferSize(rs232PortNum);
			UARTRead(rs232PortNum, uBuff, uSize2);
			uBuff[uSize2] = '\0';
			
			UARTWrite(1, uBuff);
		}
	}
}

</pre>
