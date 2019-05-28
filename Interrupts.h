/********************************************************************
 * FileName:		Interrupts.h									*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per Interrupts.c									*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		24/10/18		Versio inicial.					*
 *																	*
 ********************************************************************/

#ifndef INTERRUPTS_H
#define INTERRUPTS_H
/***************** Definició de subrutines usades *******************/

void Config_Ext_Int(unsigned char Int_To_Config);

/***************** Types externs *****************/ 



/**************** Definicions ********************/

// Variables pel moment de configurar les interrupcions, enlloc d'escriure un numero millor escriure la paraula, es mes intuitiu

#define INT_EMERGENCY			0
#define INT_HOLDER	 			1
#define INT_ELECTROVALVE		2
#define INT_DOOR				3
#define INT_ENDSWITCH			4
#define INT_START 				5
#define INT_I2C					6
#define INT_TCA4595				7
#define INT_INPUT7				8
#define INT_INPUT8				9
#define INT_INPUT9				10

#endif 
