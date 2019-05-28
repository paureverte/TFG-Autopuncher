/********************************************************************
 * FileName:		TCA9545.c										*
 * Dependencies:	TCA9545.h										*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions del TCA9545.											*
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		15/02/19		Versio inicial 					*
 * 																	*
 ********************************************************************/
#include "TCA9545.h"
#include "I2C.h"
#include <stddef.h>

typedef struct
{
	unsigned char current_channel;
	unsigned char last_channel;
	unsigned char tx_buffer;
	unsigned char transmit_in_progress;
} tca9545_t;

tca9545_t multiplexer;

void TCA9545_Callback(void);

void TCA9545_Initialize(void)
{
	multiplexer.current_channel = 0;
	multiplexer.last_channel = 0xFF;
	multiplexer.tx_buffer = 0;
	multiplexer.transmit_in_progress = 0;
}

void TCA9545_Tasks(void)
{
	if(multiplexer.current_channel != multiplexer.last_channel && multiplexer.transmit_in_progress == 0)
	{
		multiplexer.tx_buffer = (1 << multiplexer.current_channel);
		if(I2C_Transmit(1, TCA9545_ADDRESS, &multiplexer.tx_buffer, TCA9545_Callback) == I2C_TRANSACTION_QUEUED)
		{
			multiplexer.transmit_in_progress = 1;
		}
	}
}

unsigned char TCA9545_GetChannel(void)
{
	return multiplexer.last_channel;
}

void TCA9545_SetChannel(unsigned char channel)
{
	if(channel < NUMBER_OF_CHANNELS)
	{
		multiplexer.current_channel = channel;
	}
}

void TCA9545_Callback(void)
{
	multiplexer.last_channel = multiplexer.current_channel;
	multiplexer.transmit_in_progress = 0;
}
