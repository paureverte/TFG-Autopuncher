/********************************************************************
 * FileName:		CAPManager.c									*
 * Dependencies:	CAPManager.h									*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions del CAPManager.										*
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		15/02/19		Versio inicial 					*
 * 																	*
 ********************************************************************/
#include "CAPManager.h"
#include "TCA9545.h"
#include <stddef.h>

typedef enum
{
	CAPMANAGER_INITIALIZE = 0,
	CAPMANAGER_INITIALIZING_CAPS,
	CAPMANAGER_READY,
	CAPMANAGER_WAITING_FLAG,
} CAPManager_states_t;

typedef struct
{
	unsigned char flag;
	CAPManager_states_t state;
	unsigned char channel;
} CAPManager_t;

void CAPManager_Init(void);

CAPManager_t CAPManager;
CAP1208_t CAP1;
CAP1208_t CAP2;
CAP1208_t CAP3;
CAP1208_t * caps[3];

void CAPManager_Tasks(void)
{
	CAPManager.channel = TCA9545_GetChannel();
	switch(CAPManager.state)
	{
		case CAPMANAGER_INITIALIZE:
		{
			CAPManager_Init();
			break;
		}

		case CAPMANAGER_INITIALIZING_CAPS:
		case CAPMANAGER_READY:
		{
			if(TCA9545_GetChannel() != 0xFF) 	//Assegurem agafar-ne un correcte
			{
				if(CAPManager.channel < NUMBER_OF_CAPS)	//Menor que el nombre màxim dels caps
				{
					if(CAP1208_Tasks(caps[CAPManager.channel]) == CAP1208_READY)	//Si està preparat per funcionar
					{
						CAPManager.channel++;										//Canvi de canal
						if(CAPManager.channel >= NUMBER_OF_CAPS)
						{
							CAPManager.channel = 0;
							CAPManager.state = CAPMANAGER_WAITING_FLAG;				//Espera flag per començar

							Keyboard_Read();										//Lectura del teclat
						}
						TCA9545_SetChannel(CAPManager.channel);
						CAP1208_SetCurrentCAP(caps[CAPManager.channel]);
					}
				}
			}
			break;
		}

		case CAPMANAGER_WAITING_FLAG:
		{
			if(CAPManager.flag == 1)
			{
				CAPManager.flag = 0;
				CAPManager.state = CAPMANAGER_READY;
				CAP1208_ProgramRead(caps[0]);
				CAP1208_ProgramRead(caps[1]);
				CAP1208_ProgramRead(caps[2]);
			}
			break;
		}

		default:
		{
			break;
		}
	}	
}

void CAPManager_Init(void)
{
	CAPManager.flag = 0;
	CAPManager.state = CAPMANAGER_INITIALIZING_CAPS;

	caps[0] = &CAP1;
	caps[1] = &CAP2;
	caps[2] = &CAP3;

	CAP1208_SetCurrentCAP(caps[0]);
}

void CAPManager_SetFlag(void)
{
	CAPManager.flag = 1;
}

unsigned char CAPManager_GetCAPIndexInputStatus(unsigned char index)
{
	if(index < NUMBER_OF_CAPS)
	{
		return caps[index]->input_status;
	}

	return 0;
}
