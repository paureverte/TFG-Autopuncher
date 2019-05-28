/********************************************************************
 * FileName:		I2C.h											*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibreria del I2C.c											*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		21/01/09		Versió inicial.					*
 *																	*
 *******************************************************************/

#ifndef I2C_H
#define I2C_H

typedef enum
{
	I2C_PERIPHERAL_IS_BUSY = 0,
	I2C_PERIPHERAL_IS_READY,
	I2C_PERIPHERAL_NULL_BUFFER,
	I2C_PERIPHERAL_ASKED_FOR_0_DATA,
	I2C_PERIPHERAL_MAX_DATA,
	I2C_TRANSACTION_QUEUED,
	I2C_QUEUE_FULL,
}i2c_response_t;

typedef void (*i2c_callback_t)(void);

void I2C_Tasks(void);
i2c_response_t I2C_Transmit(unsigned char number_of_bytes_tx, unsigned long slave_address, unsigned char * tx_buffer, i2c_callback_t callback);
i2c_response_t I2C_Receive(unsigned char number_of_bytes_rx, unsigned long slave_address, unsigned char * rx_buffer, i2c_callback_t callback);
i2c_response_t I2C_TransmitReceive(unsigned char number_of_bytes_tx, unsigned char number_of_bytes_rx, unsigned long slave_address, unsigned char * tx_buffer, unsigned char * rx_buffer, i2c_callback_t callback);

#endif /* I2C_H */
