/********************************************************************
 * FileName:		PWM_Control.c									*
 * Dependencies:	PWM_Control.h									*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions de control del periferic Output Compare del micro	*
 *		per realitzar un PWM del motor pas-a-pas.					*	
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		19/11/18		Versio inicial 					*
 * 																	*
 ********************************************************************/
#include "main.h"

/***************** Variables externes ***********************/

extern volatile type_acceleration_state acceleration_state; 
extern volatile type_State State;  
extern unsigned long step; 
extern unsigned long wide;
extern unsigned long wide_MAX; 
extern unsigned char TON;
extern unsigned char TOFF;
extern unsigned char TOFF_MAX;
extern unsigned char TOFF_MIN; 
extern unsigned char accelerate_constant; 
extern unsigned char decelerate_constant; 
extern volatile unsigned long dies_counter;
extern volatile unsigned long end_limit;
extern volatile unsigned long dies_number;
extern volatile unsigned long wide_cm; 
extern volatile unsigned long zero_value; 
extern volatile unsigned long pwm_steps; 													// Variable comptadora dels passos que ha realitzat el pwm durant una operacio
extern volatile unsigned long pwm_steps_total; 											// Variable auxiliar dels passos totals que ha de fer el pwm per complir amb "step"
extern volatile unsigned long steps_for_deceleration; 										// Variable per calcular els passos necessaris ha fer durant la deceleracio
extern volatile unsigned char flag_calculating_decelerating_step; 									// Variable booleana per saber si s'esta buscant el pas inicial de deceleracio
extern volatile unsigned long pwm_steps_start_decelerate;									// Variable fixa per determinar el pas al qual es comenca la deceleracio
extern volatile unsigned long necessary_steps_for_change; 										// Variable de passos als quals fer un canvi de velocitat amb el pwm
extern volatile unsigned long pwm_steps_done;												// Variable auxiliar per determinar el valor de pasos per comencar la deceleracio
extern volatile unsigned long motor_steps; 												// Variable comptadora per comparar amb els de canvi de velocitat

/***************** Interrupcions externes ********************/
extern volatile unsigned char flag_int_electrovalve; 


/********************************************************************
 * Function:	InitOutputCompare()									*
 * Definition:	Inicialitzacio Output Compare per realitzacio PWM.	*
 ********************************************************************/
void InitOutputCompare(void)
{
	OC4CON = 0x0000; 			// Valores a cero.
	OC4CON = 0x0005; 			// OC Not Enabled, Continue in Stop in the Idle, 16 bits, no fault condition, Timer2, Contiuous output pulses.

	// Registres de comparacio
	OC4RS = 0x00 * CONV_FACT_T2_OC;				// A nivell alt al instant zero. 
	OC4R = TON * CONV_FACT_T2_OC; 				// Es posara  a nivell baix un cop hagi passat el valor de TON.
	PR2 = (TON + TOFF) * CONV_FACT_T2_OC; 		// El periode inicial vindra  donat pels valors de TON i TOFF. Al llarg del programa sera TOFF el que s'anira modificant per variar aixi el PWM.
	
	// Interrupcio
	IFS0CLR = 1<<18;		// Neteja flag interrupcio OC4
	IEC0SET = 1<<18;		// Enable Interrupcio OC4
	IPC4SET = 7<<18; 		// Estableix prioritat 7 (maxima) a la interrupcio OC4
	IPC4SET = 3<<16; 		// Estableix subprioritat 3 (maxima) a la interrupcio OC4		

	// Activa Output Compare
	OC4CONSET = 0x8000; 			// OC Enable
}
/********************************************************************
 * Function:	StopOutputCompare()									*
 * Definition:	Parada de Output Compare en funcionament de PWM.	*
 ********************************************************************/
void StopOutputCompare(void)
{
	OC4CON = 0x0000; 								// Valores a cero.
	PR2 = (TON + TOFF) * CONV_FACT_T2_OC; 			// El periode inicial vindra donat pels valors de TON i TOFF. Al llarg del programa sera  TOFF el que s'anira  modificant per variar aixi el PWM.
}

