/********************************************************************
 * FileName:		CAP1208.c										*
 * Dependencies:	CAP1208.h										*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions del CAP1208.											*
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		11/02/19		Versio inicial 					*
 * 																	*
 ********************************************************************/
#include "main.h"

unsigned long rx_cap1208_buffer = 0;
unsigned char register_saved_manufacturerid = 0;


void CAP1208_Callback(void);

CAP1208_t * current_pointer = NULL;

/********************************************************************
 * Function:	Write_CAP1208(register, data)						*
 * Description:	Funció per escriure un byte a un registre del CAP.	*
 ********************************************************************/
i2c_response_t Write_CAP1208(unsigned char reg, unsigned char data)
{
	if(current_pointer != NULL)
	{
		current_pointer->txbuffer[0] = reg;
		current_pointer->txbuffer[1] = data;
		return I2C_Transmit(2, CAP1208_Address, current_pointer->txbuffer, CAP1208_Callback);
	}

	return I2C_PERIPHERAL_NULL_BUFFER;
}

/********************************************************************
 * Function:	Read_CAP1208(register_to_read, register_to_save)	*
 * Description:	Funció per llegir un byte a un registre del CAP.	*
 ********************************************************************/
i2c_response_t Read_CAP1208(unsigned char register_to_read, unsigned char number_of_registers_to_read)
{
	if(current_pointer != NULL)
	{
		current_pointer->txbuffer[0] = register_to_read;
		return I2C_TransmitReceive(1, number_of_registers_to_read+1, CAP1208_Address, current_pointer->txbuffer, current_pointer->rxbuffer, CAP1208_Callback);   //Escribim el registre que volem llegir i a continuació el llegim i guardem a un registre desitjat. 
	}

	return I2C_PERIPHERAL_NULL_BUFFER;	
}

/********************************************************************
 * Function:	Init_CAP1208(manufacturerid, register_to_save)		*
 * Description:	Funció per inicialitzar CAP1208.					*
 ********************************************************************/
i2c_response_t Init_CAP1208(void)
{
	if(current_pointer != NULL)
	{
		current_pointer->txbuffer[0] = MANID;
		current_pointer->rxbuffer[0] = 0;

		current_pointer->input_status = 0;

		return I2C_TransmitReceive(1, 1, CAP1208_Address, current_pointer->txbuffer, current_pointer->rxbuffer, CAP1208_Callback);   //Escribim el registre que volem llegir i a continuació el llegim i guardem a un registre desitjat. 
	}

	return I2C_PERIPHERAL_NULL_BUFFER;
}

MAX_DUR_t max_dur = MAX_DUR_10080ms;
RPT_RATE_t rpt_rate = RPT_RATE_175ms;
DELTA_SENSE_t delta_sense = DELTA_SENSE_32x;
BASE_SHIFT_t base_shift = BASE_SHIFT_256x;

/********************************************************************
 * Function:	CAP1208_Tasks()										*
 * Description:	Tasks del CAP1208.									*
 ********************************************************************/
CAP1208_state_t CAP1208_Tasks(CAP1208_t * cap)
{
	if(cap == NULL)
	{
		return -1;
	}

	switch (cap->state)
	{
		case CAP1208_INITIALIZE:
		{
			cap->expected_i2c_ready = 0;
			if (
				(Init_CAP1208() == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(INPUT_ENABLE, 0xFF) == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(MULT_TOUCH, 0x02) == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(SENSIV_CONF, (((delta_sense << DELTA_SENSE_LSHIFT) & DELTA_SENSE_MASK) | ((base_shift << BASE_SHIFT_LSHIFT) & BASE_SHIFT_MASK))) == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(CONFIGURATION, 0x20) == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(CONFIGURATION_2, 0x40) == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(INTERRUPT_ENABLE, 0xFF) == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(REPEAT_RATE_ENABLE, 0xFF) == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(INPUT_CONFIGURATION, 0xF0) == I2C_TRANSACTION_QUEUED) &&
				(Write_CAP1208(MAIN_CONTROL_REGISTER, 0x00) == I2C_TRANSACTION_QUEUED)
				)
			{
				cap->i2c_ready = 0;
				cap->expected_i2c_ready = 10;
				cap->state = CAP1208_WAITING_INITIALIZE;
			}
			break;
		}
		case CAP1208_WAITING_INITIALIZE:
		{
			if(cap->i2c_ready == 1)
			{
				cap->manufacturer_id = cap->rxbuffer[0];
				
				if (cap->rxbuffer[0] != 0x5D)
				{
					/* NOTE: do something */
				}
			}
			else if(cap->i2c_ready == cap->expected_i2c_ready)
			{
				cap->i2c_ready = 0;
				cap->expected_i2c_ready = 0;
				cap->state = CAP1208_READ;
			}
			break;
		}
		
		case CAP1208_READ: 
		{
			if (Read_CAP1208(MAIN_CONTROL_REGISTER, 4) == I2C_TRANSACTION_QUEUED) /* read 4 bytes from address 0x00 and up to 0x03 (inclusive) */
			{
				cap->state = CAP1208_WAITING_I2C;
			}
			break;
		}
		case CAP1208_WAITING_I2C:
		{
			if (cap->i2c_ready == 1)
			{
				cap->i2c_ready = 0;	
				/*Guardar els valors que s'han llegit del cap-> En aquest punt, s'ha realitzat la transacció i està guardat a cap->rxbuffer. */
				if((cap->rxbuffer[0] & 0x1) == 1) /* check INT bit int MAIN CONTROL REGISTER */
				{
					cap->state = CAP1208_RESTORE_INT;
				}
				else
				{
					cap->state = CAP1208_READY;
				}
				cap->input_status = cap->rxbuffer[3];
			}
			break;
		}
		case CAP1208_RESTORE_INT:
		{
			if (Write_CAP1208(MAIN_CONTROL_REGISTER, ((cap->rxbuffer[0]) & 0xFE)) == I2C_TRANSACTION_QUEUED) /* leave all bits untouched except bit 0, set to 0 */
			{
				cap->state = CAP1208_WAITING_RESTORE_INT;
			}
			break;
		}
		case CAP1208_WAITING_RESTORE_INT:
		{
			if (cap->i2c_ready == 1)
			{
				cap->i2c_ready = 0;	
				#if 0
				cap->state = CAP1208_READY;
				#else
				cap->state = CAP1208_READ;
				#endif
			}
			break;
		}
		case CAP1208_READY:
		{
			break;
		}
	}

	return cap->state;
}

void CAP1208_SetCurrentCAP(CAP1208_t * pointer)
{
	if(pointer != NULL)
	{
		current_pointer = pointer;
	}
}

void CAP1208_Callback(void)
{
	if(current_pointer != NULL)
	{
		current_pointer->i2c_ready++;
	}
}

void CAP1208_ProgramRead(CAP1208_t * pointer)
{
	if(pointer != NULL)
	{
		pointer->state = CAP1208_READ;
	}
}
