/********************************************************************
 * FileName:		main.h											*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibreria general												*
 *																	*
 *														P.Reverté	*
 ********************************************************************/
#ifndef MAIN_H
#define MAIN_H

#include <plib.h>
#include <p32xxxx.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "iomap.h"
#include "GenericTypeDefs.h"
#include "LCD_Control.h"
#include "PWM_Control.h"
#include "Timers.h"
#include "Interrupts.h"
#include "Inits.h"
#include "Delay.h"
#include "Control_Shine.h"
#include "Motor_Operation.h"
#include "Keyboard.h"
#include "GUI.h"
#include "Autopuncher_app.h"
#include "Error.h"
#include "Flash_Gestion.h"
#include "I2C.h"
#include "CAP1208.h"

/********** TYPES ***********/


/******************** Definiciones Generales ************************/

/* VALORES DE FACTORY */

#define TON_FACTORY							30
#define TOFF_FACTORY						270
#define TOFF_MAX_FACTORY 					270
#define TOFF_MIN_FACTORY 					71
#define acc_const_FACTORY					5
#define acc_const_MAX						9
#define acc_const_MIN						0
#define dec_const_FACTORY					7	
#define dec_const_MAX						9
#define dec_const_MIN						0
#define dec_positioning_constant_FACTORY	5
#define distance_limit_to_start_FACTORY 	10
#define step_FACTORY						10
#define step_MIN_FACTORY					3
#define step_MAX_FACTORY 					30
#define wide_FACTORY						10
#define wide_MIN_FACTORY					3
#define wide_MAX_FACTORY					500
#define position_FACTORY					0
#define pressure_FACTORY					5
#define pressure_MIN_FACTORY 				3
#define pressure_MAX_FACTORY 				30
#define speed_FACTORY 						240
#define speed_MIN_FACTORY					30
#define speed_MAX_FACTORY					530
#define bridge_FACTORY						0
#define reset_speed_FACTORY					190
#define zero_value_FACTORY 					200
#define end_limit_FACTORY					200
#define password_thousands_sub1				1
#define password_hundreds_sub1				9
#define password_tens_sub1					1
#define password_units_sub1					9
#define password_thousands_sub2				9
#define password_hundreds_sub2				1
#define password_tens_sub2					9
#define password_units_sub2					1
#define password_thousands_test				8
#define password_hundreds_test				5
#define password_tens_test					6
#define password_units_test					9
#define STRING_MAX_LENGTH					32
#define necessary_steps_for_change_FACTORY 	20

/* FUNCIONAMIENTO CILINDRO */

#define RISE 0
#define DESCENT 1

/* FUNCIONAMIENTO PUENTE */

#define OPEN 0
#define CLOSED 1

/* Valores contadores */

#define welcome_wait_time	2000		// Tiempo de espera de la PRESENTATION (ms). 

/* Variables que vull que siguin externes */

// Valores predeterminados NVM
#define NVM_PROGRAM_PAGE 	0xBD07F000					// Adressa de la flash a partir de la cual em reservo. Aqui sera on començare a guardar els valors a la flash. 

#define SYS_FREQ 				(80000000L)
#define GetSystemClock()		(SYS_FREQ)
#define	GetPeripheralClock()	(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define I2C_CLOCK_FREQ			100000

#endif
/****************************** EOF *********************************/
