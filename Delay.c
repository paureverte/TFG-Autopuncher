/********************************************************************
 * FileName:		Delay.c											*
 * Dependencies:	Delay.h											*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions d'espera per temps 						 			*													
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		19/10/18		Versió inicial	 				*
 * 																	*
 ********************************************************************/
#include "main.h"


/********************************************************************
 * Function:	DelayMs(delay_time)									*
 * Description:	Delays execution on time specified in ms.			*
 ********************************************************************/
void DelayMs(unsigned long delay_time_ms)
{
	unsigned int int_status;
	int_status = INTDisableInterrupts();
	while(delay_time_ms--)
	{
		OpenCoreTimer(80000000ul / 2000);     // core timer is at 1/2 system clock
		mCTClearIntFlag();
		while(!mCTGetIntFlag());
	}
	mCTClearIntFlag();
	INTRestoreInterrupts(int_status);
}

/********************************************************************
 * Function:	DelayUs(delay_time)									*
 * Description:	Delays execution on time specified in us.			*
 ********************************************************************/
void DelayUs(unsigned long delay_time_us)
{
    unsigned int int_status;
    int_status = INTDisableInterrupts();
    while(delay_time_us--)
    {
		OpenCoreTimer(80000000ul / 2000000);    // core timer is at 1/2 system clock
        mCTClearIntFlag();
        while(!mCTGetIntFlag());
    }
    mCTClearIntFlag();
    INTRestoreInterrupts(int_status);
}
