/********************************************************************
 * FileName:		CAPManager.h									*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per CAPManager.c									*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		15/02/19		Versio inicial.					*
 *																	*
 ********************************************************************/
#ifndef CAPMANAGER_H
#define CAPMANAGER_H

#include "CAP1208.h"

#define NUMBER_OF_CAPS 3

void CAPManager_Tasks(void);
void CAPManager_Init(void);
void CAPManager_SetFlag(void);
unsigned char CAPManager_GetCAPIndexInputStatus(unsigned char index);

#endif /* CAPMANAGER_H */
