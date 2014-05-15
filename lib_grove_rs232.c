/** \file lib_grove_rs232.c
 *  \brief Grove devices support library 
 */

/**
\addtogroup Grove devices
@{
 **************************************************************************																					
 *                                OpenPicus                 www.openpicus.com
 *                                                            italian concept
 * 
 *            openSource wireless Platform for sensors and Internet of Things	
 * **************************************************************************
 *  FileName:        lib_grove_rs232.c
 *  Dependencies:    OpenPicus libraries
 *  Module:          FlyPort WI-FI - FlyPort ETH
 *  Compiler:        Microchip C30 v3.12 or higher
 *
 *  Author               Rev.    Date              Comment
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Simone Marra	     1.0     15/05/2014		   First release  
 *  
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  Software License Agreement
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  This is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License (version 2) as published by 
 *  the Free Software Foundation AND MODIFIED BY OpenPicus team.
 *  
 *  ***NOTE*** The exception to the GPL is included to allow you to distribute
 *  a combined work that includes OpenPicus code without being obliged to 
 *  provide the source code for proprietary components outside of the OpenPicus
 *  code. 
 *  OpenPicus software is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details. 
 * 
 * 
 * Warranty
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * WE ARE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 **************************************************************************/

#include "taskFlyport.h"
#include "grovelib.h"
#include "lib_grove_rs232.h"

struct Rs232
{
	const void *class;
	struct Interface *inter;
	BYTE uart_module;
	BYTE uart_interface;
	BYTE baud_rate;
};

struct Interface *attachSensorToUartBus(void *,int,int,BYTE,BYTE);

/**
 * static void *Rs232_ctor (void * _self, va_list *app)- Rs232 grove device Constructor  
 * \param *_self - pointer to the Rs232 grove device class.
 * \param *app 
 * \		1- uart module
* \return - Pointer to the Rs232 devices instantiated
*/
static void *Rs232_ctor (void * _self, va_list *app)
{
	struct Rs232 *self = _self;
	self->uart_module =  va_arg(*app, BYTE);
	switch(self->uart_module)
	{
		case 2 :
		{
			self->uart_interface = 7;
			break;
		}
		case 3 :
		{
			self->uart_interface = 9;
			break;
		}
		case 4 :
		{
			self->uart_interface = 11;
			break;
		}			
	}
	self->inter 	= NULL;

	return self;
}	


/**
 * static void Rs232_dtor (void * _sensor) - Rs232 grove device Destructor  
 * \param *_sensor - pointer to the Rs232 grove device class.
 * \return - None
*/
static void Rs232_dtor (void * _sensor)
{
	struct Rs232 *sensor = _sensor;
	if(sensor->inter)
	{
		free(sensor->inter->port);
		free(sensor->inter);
	}
}	


/**
 * static void *Rs232_attach (void * _board,void *_sensor,int port) - attach a Rs232 grove device to the GroveNest DIG port  
 * \param *_board - pointer to the GroveNest 
 * \param *_sensor - pointer to the Rs232 grove device class.
 * \param port -  which DIG port the device is connected to
  * \return - The status of the operation
 <UL>
	<LI><Breturn = Pointer to the DIG interface created:</B> the operation was successful.</LI> 
	<LI><B>return = NULL:</B> the operation was unsuccessful.</LI> 
 </UL>
 */
static void *Rs232_attach (void * _board,void *_sensor,int port)
{
	struct Rs232 *sensor = _sensor;
	sensor->inter = attachSensorToUartBus(_board,port,19200,sensor->uart_module,sensor->uart_interface);
	UARTInit(sensor->uart_module,19200);
	return sensor->inter;
}	

static const struct SensorClass _Rs232 =
{	
	sizeof(struct Rs232),
	Rs232_ctor,
	Rs232_dtor,
	Rs232_attach,
};

const void *Rs232 = &_Rs232;
