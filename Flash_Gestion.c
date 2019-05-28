/********************************************************************
 * FileName:		Flash_Gestion.c									*
 * Dependencies:	Flash_Gestion.h									*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions de gestió de la memòria FLASH.						*
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		2/1/19		Versió inicial	 					*
 * 																	*
 ********************************************************************/
#include "main.h"

/* Variables Externes */
extern unsigned long TON;					
extern unsigned long TOFF;					
extern unsigned long TOFF_MAX;			
extern unsigned long TOFF_MIN; 			
extern unsigned long accelerate_constant;
extern unsigned long accelerate_constant_MIN;
extern unsigned long decelerate_constant;
extern unsigned long decelerate_constant_MAX;
extern unsigned long decelerate_constant_MIN;
extern unsigned long distance_limit_to_start;
extern unsigned long step;					
extern unsigned long step_MAX;
extern unsigned long step_MIN;
extern volatile unsigned long necessary_steps_for_change;
extern unsigned long MAX_WIDE;
extern unsigned long wide; 					
extern unsigned long wide_MAX;			
extern unsigned long wide_MIN;
extern unsigned long position;
extern unsigned long pressure;
extern unsigned char bridge; 				
extern volatile unsigned long pressure_MAX;
extern volatile unsigned long pressure_MIN;
extern unsigned long speed;
extern unsigned long speed_MAX; 
extern unsigned long speed_MIN;
extern unsigned long submenu2_turns_number; 
extern volatile unsigned char mainlanguage; 
extern volatile unsigned long zero_value;
extern volatile unsigned long end_limit;
extern volatile type_operation_mode operation_mode;

/********************************************************************
 * Function:	Flash_Write()										*
 * Definition:	Graba valors de programa a la memoria flash.		*
 ********************************************************************/
void Flash_Write (void)
{
	unsigned int status;

	status = INTDisableInterrupts();								// Desactiva les interrupcions

	NVMErasePage((void *)NVM_PROGRAM_PAGE);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE), wide);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 4), step);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 8), pressure);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 12), bridge);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 16), MAX_WIDE);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 20), mainlanguage);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 24), zero_value);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 28), end_limit);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 32), TON);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 36), TOFF_MIN);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 40), TOFF_MAX);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 44), necessary_steps_for_change);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 48), accelerate_constant);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 52), decelerate_constant);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 56), submenu2_turns_number);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 60), distance_limit_to_start);
	DelayMs(2);
	NVMWriteWord((void*)(NVM_PROGRAM_PAGE + 64), operation_mode);
	DelayMs(75);
	INTRestoreInterrupts(status);									// Torna les interrupcions a l'estat anterior
}


