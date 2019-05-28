/********************************************************************
 * FileName:		Delay.h 										*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrer�a per Delay.c											*
 *																	*
 * Change History:			Versi� 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Revert�		19/10/18		Versio inicial.					*
 *																	*
 ********************************************************************/

#ifndef DELAY_H
#define DELAY_H


/***************** Definici� de subrutines usades *******************/

void DelayMs(unsigned long delay_time_ms);
void DelayUs(unsigned long delay_time_us);

#endif
