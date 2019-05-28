/********************************************************************
 * FileName:		TCA9545.h									*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per TCA9545.c									*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		15/02/19		Versio inicial.					*
 *																	*
 ********************************************************************/
#ifndef TCA9545_H
#define TCA9545_H

#define TCA9545_ADDRESS 0xE0
#define NUMBER_OF_CHANNELS 4

unsigned char TCA9545_GetChannel(void);
void TCA9545_SetChannel(unsigned char channel);
void TCA9545_Tasks(void);

#endif /* TCA9545_H */
