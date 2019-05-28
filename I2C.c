/********************************************************************
 * FileName:		I2C.c											*
 * Dependencies:	I2C.h 											*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Control del I2C.								 				*
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		21/01/19		Versio inicial 					*
 * 																	*
 ********************************************************************/
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

#define MAX_QUEUE_ELEMENTS 16
#define MAX_BUFFER_SIZE 8
#define QUEUE_EMPTY (-1UL)

typedef enum
{
	start,
	address,
	byte,
	ack,
	stop,
	repeated_start,
	idle
	
}i2c_isr_state_t;

typedef enum
{
	I2C_INIT = 0,
	I2C_WAITING,
	I2C_READY,
	I2C_START_TRANSACTION,
	I2C_BUS_COLLISION_DETECTED,
	I2C_BUS_COLLISION_FAILED_RESET,
}i2c_state_t;

typedef enum
{
	Transmit = 0,
	Receive, 
	TransmitReceive
	
} i2c_transaction_type_t;

typedef struct 
{
	bool in_use;
	i2c_transaction_type_t type;
	unsigned char number_of_bytes_tx;
	unsigned char number_of_bytes_rx;
	unsigned long slave_address;
	unsigned char * data_buffer_rx;
	unsigned char data_buffer_tx[MAX_BUFFER_SIZE];
	unsigned char index;
	i2c_callback_t callback;

}i2c_transaction_t;

typedef struct
{
	i2c_isr_state_t isr_state;
	i2c_state_t state;
	i2c_transaction_t ct[MAX_QUEUE_ELEMENTS]; /* this means ct = current_transaction */
	unsigned long current_transaction_index;

} i2c_peripheral_info_t;

/* private */
bool I2C_IsFree(void);
i2c_response_t I2C_Transaction(i2c_transaction_type_t type, unsigned char number_of_bytes_tx, unsigned char number_of_bytes_rx, unsigned long slave_address, uint8_t * tx_buffer, uint8_t * rx_buffer, i2c_callback_t callback);
void I2C_ResetCurrentTransactionData(unsigned long index);
bool I2C_IsCurrentTransactionComplete(void);
void I2C_ISR_Tasks(void);
void I2C_ProcessNextByte(void);
bool I2C_IsMoreDataPending(void);
unsigned long I2C_GetNextFreeIndexInQueue(void);
void I2C_UpdateCurrentTransactionIndex(void);
void I2C_SetBusCollisionDetected(void);
unsigned char I2C_ResetBus(void);
unsigned long I2C_GetFirstNonFreeIndexInQueue(void);

static i2c_peripheral_info_t i2c;

bool I2C_IsFree(void)
{
	return (i2c.state == I2C_READY);
}

i2c_response_t I2C_Transaction(i2c_transaction_type_t type, unsigned char number_of_bytes_tx, unsigned char number_of_bytes_rx, unsigned long slave_address, uint8_t * tx_buffer, uint8_t * rx_buffer, i2c_callback_t callback)
{
	unsigned long freeIndex = 0;

	if(I2C_IsFree() == false)
	{
		return I2C_PERIPHERAL_IS_BUSY;
	}

	if(type == Receive)
	{
		if(rx_buffer == NULL)
		{
			return I2C_PERIPHERAL_NULL_BUFFER;
		}
	}
	else if(type == Transmit)
	{
		if(tx_buffer == NULL)
		{
			return I2C_PERIPHERAL_NULL_BUFFER;
		}
	}
	else if(type == TransmitReceive)
	{			
		if(rx_buffer == NULL)
		{
			return I2C_PERIPHERAL_NULL_BUFFER;
		}
		else if(tx_buffer == NULL)
		{
			return I2C_PERIPHERAL_NULL_BUFFER;
		}
	}
	if(number_of_bytes_tx == 0 && number_of_bytes_rx == 0)
	{
		return I2C_PERIPHERAL_ASKED_FOR_0_DATA;
	}
	
	if(number_of_bytes_tx > MAX_BUFFER_SIZE)
	{
		return I2C_PERIPHERAL_MAX_DATA;
	}

	if((freeIndex = I2C_GetNextFreeIndexInQueue()) >= MAX_QUEUE_ELEMENTS)
	{
		return I2C_QUEUE_FULL;
	}

	i2c.ct[freeIndex].in_use = true;
	i2c.ct[freeIndex].type = type;
	i2c.ct[freeIndex].number_of_bytes_tx = number_of_bytes_tx;
	i2c.ct[freeIndex].number_of_bytes_rx = number_of_bytes_rx;
	i2c.ct[freeIndex].slave_address = slave_address & 0xFE; /* ensure the last bit is 0 */
	i2c.ct[freeIndex].data_buffer_rx = rx_buffer;
	memcpy(i2c.ct[freeIndex].data_buffer_tx, tx_buffer, number_of_bytes_tx);
	i2c.ct[freeIndex].callback = callback;

	if(i2c.current_transaction_index == QUEUE_EMPTY)
	{
		i2c.current_transaction_index = freeIndex;
	}
	
	return I2C_TRANSACTION_QUEUED;
}

i2c_response_t I2C_Transmit(unsigned char number_of_bytes_tx, unsigned long slave_address, unsigned char * tx_buffer, i2c_callback_t callback)
{
	return I2C_Transaction(Transmit, number_of_bytes_tx, 0, slave_address, tx_buffer, NULL, callback);
}

i2c_response_t I2C_Receive(unsigned char number_of_bytes_rx, unsigned long slave_address, unsigned char * rx_buffer, i2c_callback_t callback)
{
	return I2C_Transaction(Receive, 0, number_of_bytes_rx, slave_address, NULL, rx_buffer, callback);
}

i2c_response_t I2C_TransmitReceive(unsigned char number_of_bytes_tx, unsigned char number_of_bytes_rx, unsigned long slave_address, unsigned char * tx_buffer, unsigned char * rx_buffer, i2c_callback_t callback)
{
	return I2C_Transaction(TransmitReceive, number_of_bytes_tx, number_of_bytes_rx, slave_address, tx_buffer, rx_buffer, callback);
}

#define BIT_ON_MASK (1 << 15)

void I2C_Tasks(void)
{
	switch(i2c.state)
	{
		case I2C_INIT:
		{
			I2C1BRG = ( (GetPeripheralClock()/I2C_CLOCK_FREQ)/2 ) - 2;			// I2C Set Frequency
			I2C1CONbits.ON = 1; 													// Enable I2C
			
			i2c.current_transaction_index = I2C_GetFirstNonFreeIndexInQueue();
			
			i2c.state = I2C_READY;
			break;
		}
		case I2C_WAITING:
		{
			if(I2C_IsCurrentTransactionComplete() == true)
			{
				if(i2c.ct[i2c.current_transaction_index].callback != NULL)
				{
					i2c.ct[i2c.current_transaction_index].callback();
				}
				I2C_ResetCurrentTransactionData(i2c.current_transaction_index);
				I2C_UpdateCurrentTransactionIndex();
				i2c.state = I2C_READY;
			}
			break;
		}
		case I2C_READY:
		{
			if(i2c.current_transaction_index != QUEUE_EMPTY)
			{
				i2c.state = I2C_START_TRANSACTION;
			}
			break;
		}
		case I2C_START_TRANSACTION:
		{
			i2c.state = I2C_WAITING;
			I2C1CONbits.SEN = 1; 					// Send START Message. 
			i2c.isr_state = start;		
			break;
		}

		case I2C_BUS_COLLISION_DETECTED:
		{
			if(I2C_ResetBus() == 1)
			{
				i2c.state = I2C_READY;
			}
			else
			{
				i2c.state = I2C_BUS_COLLISION_FAILED_RESET;
			}
			break;
		}

		case I2C_BUS_COLLISION_FAILED_RESET:
		{
			I2C1CONbits.ON = 0;
			i2c.state = I2C_INIT;
			break;
		}
	}
}

void I2C_ResetCurrentTransactionData(unsigned long index)
{
	i2c.ct[index].in_use = false;
	i2c.ct[index].type = 0;
	i2c.ct[index].number_of_bytes_tx = 0;
	i2c.ct[index].number_of_bytes_rx = 0;
	i2c.ct[index].slave_address = 0;
	i2c.ct[index].data_buffer_rx = NULL;
	memset(i2c.ct[index].data_buffer_tx, 0x00, sizeof(i2c.ct[index].data_buffer_tx));
	i2c.ct[index].index = 0;
	i2c.ct[index].callback = NULL;
}

bool I2C_IsCurrentTransactionComplete(void)
{
	return (i2c.isr_state == idle);
}

void I2C_ISR_Tasks(void)
{
	switch(i2c.isr_state)
	{
		case start:
		{
			i2c.isr_state = address;
			if(i2c.ct[i2c.current_transaction_index].type == Receive)
			{
				I2C1STATbits.R_W = 1;
				I2C1ADD = i2c.ct[i2c.current_transaction_index].slave_address + 1;
				I2C1TRN = i2c.ct[i2c.current_transaction_index].slave_address + 1; /* R/~W bit to 1 because it is a read operation */
			}
			else
			{
				I2C1STATbits.R_W = 0;
				I2C1ADD = i2c.ct[i2c.current_transaction_index].slave_address;
				I2C1TRN = i2c.ct[i2c.current_transaction_index].slave_address;
			}
			break;
		}
		case address:
		{
			if(i2c.ct[i2c.current_transaction_index].type == Transmit)
			{
				i2c.isr_state = byte;
				I2C_ProcessNextByte();
			}
			else if(i2c.ct[i2c.current_transaction_index].type == Receive)
			{
				if(I2C_IsMoreDataPending() == true)
				{
					if(I2C1STATbits.ACKSTAT == 1) /* NACK */
					{
						/* el slave NO esta present al bus, NO ens ha donat ACK a la seva ADDR */
						i2c.isr_state = stop;
						I2C1CONbits.PEN = 1; /* generate stop sequence */
					}
					else /* ACK */
					{
						/* el slave esta present al bus, ens ha donat ACK a la seva ADDR */
						i2c.isr_state = byte;			
						I2C1CONbits.RCEN = 1; /* next byte is meant to be received */
					}
				}
				else
				{
					i2c.isr_state = stop;
					I2C1CONbits.PEN = 1; /* generate stop sequence */
				}
			}
			else if(i2c.ct[i2c.current_transaction_index].type == TransmitReceive)
			{
				i2c.isr_state = byte;
				if(i2c.ct[i2c.current_transaction_index].index == (i2c.ct[i2c.current_transaction_index].number_of_bytes_tx + 1))
				{
					I2C1CONbits.RCEN = 1; /* next byte is meant to be received */
				}
				else
				{
					I2C_ProcessNextByte();
				}
			}
			break;
		}
		case byte:
		{
			if(i2c.ct[i2c.current_transaction_index].type == Receive)
			{
				/* receiving */
				i2c.isr_state = ack;
				I2C_ProcessNextByte();
			}
			else
			{
				/* transmitting */
				if(I2C1STATbits.ACKSTAT == 1) /* NACK */
				{
					/* el slave NO esta present al bus, NO ens ha donat ACK a la seva ADDR */
					i2c.isr_state = stop;
					I2C1CONbits.PEN = 1; /* generate stop sequence */
				}
				else /* ACK */
				{
					/* el slave esta present al bus, ens ha donat ACK a la seva ADDR */
					i2c.isr_state = byte;			
					I2C_ProcessNextByte();		
				}
			}
			break;
		}
		case ack: /* this is supposed to arrive only during a reception */
		{
			if(I2C_IsMoreDataPending() == true)
			{
				i2c.isr_state = byte;
				I2C1CONbits.RCEN = 1; /* next byte is meant to be received */
			}
			else
			{
				i2c.isr_state = stop;
				I2C1CONbits.PEN = 1; /* generate stop sequence */
			}
			break;
		}
		case stop:
		{
			i2c.isr_state = idle;
			break;
		}
		case repeated_start:
		{
			i2c.isr_state = address;
			I2C1STATbits.R_W = 1;
			I2C1ADD = i2c.ct[i2c.current_transaction_index].slave_address + 1;
			I2C1TRN = i2c.ct[i2c.current_transaction_index].slave_address | 0x1;
			break;
		}
		case idle:
		{
			break;
		}
	}
}

void I2C_ProcessNextByte(void)
{
	if(I2C_IsMoreDataPending() == false && (i2c.ct[i2c.current_transaction_index].type == Transmit))
	{
		i2c.isr_state = stop;
		I2C1CONbits.PEN = 1; /* generate stop sequence */
		return;
	}

	switch(i2c.ct[i2c.current_transaction_index].type)
	{
		case Transmit:
		{
			I2C1TRN = i2c.ct[i2c.current_transaction_index].data_buffer_tx[i2c.ct[i2c.current_transaction_index].index];
			i2c.ct[i2c.current_transaction_index].index++;
			break;
		}
		case Receive:
		{
			/* need to know whether it is first byte being sent (address) or next bytes (meant to be received) */
			i2c.ct[i2c.current_transaction_index].data_buffer_rx[i2c.ct[i2c.current_transaction_index].index] = I2C1RCV;
			i2c.ct[i2c.current_transaction_index].index++;
			if(I2C_IsMoreDataPending() == false)
			{
				I2C1CONbits.ACKDT = 1; /* NACK */
			}
			else
			{
				I2C1CONbits.ACKDT = 0; /* ACK */
			}
			I2C1CONbits.ACKEN = 1; /* generate ACK event from master to slave */
			break;
		}
		case TransmitReceive:
		{		
			if(i2c.ct[i2c.current_transaction_index].index < i2c.ct[i2c.current_transaction_index].number_of_bytes_tx)
			{
				/* still in transmit phase */
				I2C1TRN = i2c.ct[i2c.current_transaction_index].data_buffer_tx[i2c.ct[i2c.current_transaction_index].index];
				i2c.ct[i2c.current_transaction_index].index++;
			}
			else if(i2c.ct[i2c.current_transaction_index].index == i2c.ct[i2c.current_transaction_index].number_of_bytes_tx)
			{
				if(I2C_IsMoreDataPending() == true)
				{
					i2c.isr_state = repeated_start;
					I2C1CONbits.RSEN = 1; /* issue repeated start to slave */
					i2c.ct[i2c.current_transaction_index].index++;
				}
				else
				{
					i2c.isr_state = stop;
					I2C1CONbits.PEN = 1; /* generate stop sequence */
				}
			}
			else if(i2c.ct[i2c.current_transaction_index].index > i2c.ct[i2c.current_transaction_index].number_of_bytes_tx)
			{
				/* now in receive phase */
				i2c.ct[i2c.current_transaction_index].data_buffer_rx[i2c.ct[i2c.current_transaction_index].index-i2c.ct[i2c.current_transaction_index].number_of_bytes_tx - 1] = I2C1RCV; /* -1 to return to indexes [0-number_of_bytes_rx) */
				i2c.ct[i2c.current_transaction_index].index++;
				if(I2C_IsMoreDataPending() == false)
				{
					I2C1CONbits.ACKDT = 1; /* NACK */
				}
				else
				{
					I2C1CONbits.ACKDT = 0; /* ACK */
				}
				i2c.isr_state = ack;
				I2C1CONbits.ACKEN = 1; /* generate ACK event from master to slave */
			}
			break;
		}
	}
}

/* true = more data left, false = no more data left */
bool I2C_IsMoreDataPending(void)
{
	#warning no estic segur del =
	return ((i2c.ct[i2c.current_transaction_index].number_of_bytes_tx + i2c.ct[i2c.current_transaction_index].number_of_bytes_rx) > i2c.ct[i2c.current_transaction_index].index);
}

unsigned long I2C_GetNextFreeIndexInQueue(void)
{
	unsigned long i = 0;

	/* if current_transaction_index is QUEUE_EMPTY will not loop at all, so return the first index */
	if(i2c.current_transaction_index != QUEUE_EMPTY)
	{
		for(i = i2c.current_transaction_index; i < MAX_QUEUE_ELEMENTS; i++)
		{
			if(i2c.ct[i].in_use == false)
			{
				return i; /* found free index, return index value */
			}
		}

		/* loop from 0 to current_transaction_index to wrap around the whole queue */
		for(i = 0; i < i2c.current_transaction_index; i++)
		{
			if(i2c.ct[i].in_use == false)
			{
				return i; /* found free index, return index value */
			}
		}

		return MAX_QUEUE_ELEMENTS; /* queue is full */
	}
	else
	{
		return 0; /* queue is empty */
	}
}

unsigned long I2C_GetFirstNonFreeIndexInQueue(void)
{
	unsigned long i = 0;

	for(i = 0; i < MAX_QUEUE_ELEMENTS; i++)
	{
		if(i2c.ct[i].in_use == true)
		{
			return i; /* found non free index, return index value */
		}
	}

	return QUEUE_EMPTY;
}

void I2C_UpdateCurrentTransactionIndex(void)
{
	unsigned long i = 0;

	for(i = i2c.current_transaction_index; i < MAX_QUEUE_ELEMENTS; i++)
	{
		if(i2c.ct[i].in_use == true)
		{
			i2c.current_transaction_index = i; /* found next non-free index, set current index value */
			return;
		}
	}

	/* loop from 0 to current_transaction_index to wrap around the whole queue */
	for(i = 0; i < i2c.current_transaction_index; i++)
	{
		if(i2c.ct[i].in_use == true)
		{
			i2c.current_transaction_index = i; /* found next non-free index, set current index value */
			return;
		}
	}

	i2c.current_transaction_index = QUEUE_EMPTY; /* if none had been found, queue is empty */
}	

void I2C_SetBusCollisionDetected(void)
{
	i2c.state = I2C_BUS_COLLISION_DETECTED;
}

unsigned char I2C_ResetBus(void)
{
	unsigned long i = 0;
	unsigned char ret_value = 0; /* 0 = reset failed, 1 = reset successful */
	unsigned long number_of_clocks = 256;	
	unsigned long scl_tris_backup = TRISA;
	unsigned long sda_tris_backup = TRISA;

	I2C1CONbits.ON = 0; // Disable I2C.
	SCL_1_TRIS = 0; /* set as output */
	SDA_1_TRIS = 1; /* set as input */

	for (i = 0; i < number_of_clocks * 2; i++) /* *2 because these are state changes, and not clock edges */
	{
		if (SDA_1_PORT == 0)
		{
			SCL_1 = ~SCL_1; /* change state */
			DelayUs(5); /* more or less the same frequency as the normal operation */
		}
		else
		{
			ret_value = 1;
		}
	}

	SCL_1 = 1; /* set high */
	SCL_1_TRIS = 1; /* set as input again */
	I2C1CONbits.ON = 1; // Enable I2C.

	/* for now they are the same register but leaving it in for reference anyway */
	TRISA = sda_tris_backup;
	TRISA = scl_tris_backup;

	return ret_value;
}
