/********************************************************************
 * FileName:		Control_Shine_Contrast.c						*
 * Dependencies:	Control_Shine_Contrast.h						*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions de control de brillantor i contrast per				*
 *		la pantalla LCD												*	
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		20/10/18		Versió inicial	 				*
 * 																	*
 ********************************************************************/
#include "main.h"

/***************** Variables locals *************************/

/********************************************************************
 * Function:	Control_Shine(brill)								*
 * Definition:	Configura i controla el shine.						*
 ********************************************************************/
void Control_Shine(unsigned int shine)
{
	switch (shine)
	{
		case 1:	shine = 0x04C9;		break;	// 1225
		case 2:	shine = 0x044C;		break;	// 1100
		case 3:	shine = 0x03CF;		break;	//  975
		case 4:	shine = 0x0352;		break;	//  850
		case 5:	shine = 0x02D5;		break;	//  725
		case 6:	shine = 0x0258;		break;	//  600
		case 7:	shine = 0x01DB;		break;	//  475
		case 8:	shine = 0x015E;		break;	//  350
		case 9:	shine = 0x00E1;		break;	//  225
		case 10:shine = 0x0064;		break;	//  100	
		default:shine = 0x02D5;		break;	// Por defecto a 5.
	}
	
	// Per al PWM utilitzarem el timer 3
	Config_Timer3();
	
	// Enable OC | 16 bit Mode  | Timer3 selected | Continuous O/P, S Compare value, Compare value.
	OpenOC3(OC_ON | OC_TIMER_MODE16| OC_TIMER3_SRC | OC_CONTINUE_PULSE, T1_TICK, shine);	// Configura duty cycle en funció de la variable shine
}

/********************************************************************
 * Function:	Control_Contrast(Contrs)							*
 * Definition:	Configura i controla el contrast.					*
 ********************************************************************/
void Control_Contrast(unsigned int Contrs)
{
	switch (Contrs)
	{
		case 1:	Contrs = 0x0997;		break;	// 2455	
		case 2:	Contrs = 0x08CA;		break;	// 2250
		case 3:	Contrs = 0x07D0;		break;	// 2000
		case 4:	Contrs = 0x06D6;		break;	// 1750
		case 5:	Contrs = 0x05DC;		break;	// 1500
		case 6:	Contrs = 0x04E2;		break;	// 1250
		case 7:	Contrs = 0x03E8;		break;	// 1000
		case 8:	Contrs = 0x02EE;		break;	//  750
		case 9:	Contrs = 0x01F4;		break;	//  500
		case 10:Contrs = 0x00FA;		break;	//  250	// No llega a ser el tope....
		default:Contrs = 0x05DC;		break;	// Por defecto a 5.
	}
	
	// Per al PWM utilitzarem el timer 3
	Config_Timer3();
		
	// Enable OC | 16 bit Mode  | Timer2 selected | Continuous O/P, S Compare value, Compare value.
	OpenOC2(OC_ON | OC_TIMER_MODE16| OC_TIMER3_SRC | OC_CONTINUE_PULSE, T1_TICK, Contrs);	// Aquí pones el duty cycle.
}
	
/****************************** EOF *********************************/
