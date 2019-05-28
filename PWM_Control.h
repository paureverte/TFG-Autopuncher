/********************************************************************
 * FileName:		PWM_Control.h									*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per PWM_Control.c									*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		19/11/18		Versió inicial.					*
 *																	*
 ********************************************************************/

#ifndef PWM_H
#define PWM_H
/***************** Definició de subrutines usades *******************/

void InitOutputCompare(void);
void StopOutputCompare(void);

/***************** Types *****************/ 

typedef enum
{
	ACCELERATE = 0,
	DECELERATE = 1,
	DECELERATE_POSITIONING = 2,
	STOP = 3, 
	STEADY = 4,
		
}type_acceleration_state;					// Type para la variable de seleccionar tipo de aceleracion 

/***************** Definicions de variables **************************/

// Comandes al motor

#define MOTOR_ON 			0			// Enable sortida motor
#define MOTOR_OFF			1			// Disable sortida motor
#define RIGHT			  	0			// Direccio = Dreta  
#define LEFT			1			// Direccio = Esquerra

// Variables 

#define CONV_FACT_T2_OC		80			// Relacio entre polsos del SYSCLK i el que vull que llegeixi el OC4

#endif 
