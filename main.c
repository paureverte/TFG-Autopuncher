/********************************************************************
 * FileName:		main.c 											*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Software de la troqueladora.									*
 *																	*
 *														P.Reverté	*
 ********************************************************************/

#include "main.h"

// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1, OSCIOFNC = OFF
#if !defined(__DEBUG)
	#pragma config CP = ON, BWP = OFF, PWP = OFF, FSOSCEN = OFF, FCKSM = CSECME, DEBUG = OFF // Programar.
#else
	#pragma config CP = OFF, BWP = OFF, PWP = OFF, FSOSCEN = OFF, FCKSM = CSECME			// Debugar.
#endif

/********************* Declaració de variables *********************/
/* Variables generales */

/* Auxiliares */
volatile unsigned long wide_cm; 

/* Flags interrupciones */
volatile unsigned char flag_int_emergency; 
volatile unsigned char flag_int_holder;
volatile unsigned char flag_int_electrovalve; 
volatile unsigned char flag_int_secdoor; 
volatile unsigned char flag_int_endswitch; 
volatile unsigned char flag_int_start; 


/* Variables dels valors principals introduits per l'usuari */

unsigned long TON = TON_FACTORY;							// Variable on es guarda el valor de TON 
unsigned long TOFF = TOFF_FACTORY;							// Variable on es guarda el valor de TOFF
unsigned long TOFF_MAX = TOFF_MAX_FACTORY;					// Variable on es guarda el valor maxim de TOFF
unsigned long TOFF_MIN = TOFF_MIN_FACTORY; 					// Variable on es guarda el valor minim de TOFF 
unsigned long accelerate_constant = acc_const_FACTORY; 		// Variable on es guarda la constant d'acceleration.
unsigned long accelerate_constant_MAX = acc_const_MAX;
unsigned long accelerate_constant_MIN = acc_const_MIN;
unsigned long decelerate_constant = dec_const_FACTORY; 		// Variable on es guarda la constant de deceleracio. 
unsigned long decelerate_constant_MAX = dec_const_MAX;
unsigned long decelerate_constant_MIN = dec_const_MIN;
unsigned long decelerate_positioning_constant = dec_positioning_constant_FACTORY;
unsigned long distance_limit_to_start = distance_limit_to_start_FACTORY;
unsigned long step = step_FACTORY;							// Variable STEP que es mostra en pantalla PASO. 
unsigned long step_MAX = step_MAX_FACTORY;
unsigned long step_MIN = step_MIN_FACTORY;
volatile unsigned long necessary_steps_for_change = necessary_steps_for_change_FACTORY; 
unsigned long MAX_WIDE = wide_MAX_FACTORY;
unsigned long wide = wide_FACTORY; 							// Variable wide total de corte. 
unsigned long wide_MAX = wide_MAX_FACTORY;					// Variable del wide maxim
unsigned long wide_MIN = wide_MIN_FACTORY;
unsigned long position = position_FACTORY;
unsigned long pressure = pressure_FACTORY;
unsigned char bridge = bridge_FACTORY; 						// Estat de puente. 0 = ABIERTO, 1 = CERRADO
volatile unsigned long pressure_MAX = pressure_MAX_FACTORY;
volatile unsigned long pressure_MIN = pressure_MIN_FACTORY;
unsigned long speed = speed_FACTORY;
unsigned long speed_MAX = speed_MAX_FACTORY; 
unsigned long speed_MIN = speed_MIN_FACTORY;
unsigned long reset_speed = reset_speed_FACTORY;
unsigned long submenu2_turns_number = 10; 
volatile unsigned char mainlanguage = 1; 
volatile unsigned long random_test_counter = 0;
volatile unsigned long counter_time_cap_read = 0;

volatile unsigned long zero_value = zero_value_FACTORY;		// Variable de la poisicio del punt zero. 
volatile unsigned long end_limit = end_limit_FACTORY;		// Variable del límit final de la màquina, fins al punt de final de carrera.

unsigned char password_try_thousands = 0;					// Valors que entra l'usuari intentant encertar la password
unsigned char password_try_hundreds = 0;
unsigned char password_try_tens = 0;
unsigned char password_try_units = 0; 

/* Comptadors */

/* Variables generals */
unsigned long dies_number;
 
/* FLAGS */
unsigned char flag_screen_refresh; 												// Flag para determinar si se refresca la pantalla 

/*********************************************************************
 *********************************************************************
 ** Function:		MAIN()											**
 ** Description:	PROGRAMA PRINCIPAL.								**
 *********************************************************************
 *********************************************************************/
 
//#define TESTS
#if defined(TESTS)
	// #define I2C_TEST
	// #define CN_TEST
	/* other tests */
#else
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

	/* Externes */
	extern volatile type_State State;												// Variable per determinar l'estat en que es troba l'aparell
	extern volatile type_positioning positioning_state;								// Variable per determinar l'estat en que es troba el posicionament
	extern volatile type_motor_movement motor_movement_state;
	extern volatile type_operation_mode operation_mode;								// Variable del mode de funcionament de l'aparell.
	extern volatile unsigned char flag_first_time_state;
#endif

volatile unsigned long variable = 0;
volatile unsigned long variable_to_compare_with = 10000;

int main(void)
{
		Config_System();
		Config_Ports();
		Init_Reg();
		Config_Timer1();
		Config_Timer2(); 
		Config_Timer3();
		Config_Ext_Int(INT_EMERGENCY);
		Config_Ext_Int(INT_ELECTROVALVE);
		Config_Ext_Int(INT_ENDSWITCH);
		Config_Ext_Int(INT_START);
		Config_Ext_Int(INT_HOLDER);
		Config_Ext_Int(INT_DOOR);
		Config_Ext_Int(INT_I2C);
		Config_Ext_Int(INT_TCA4595);
		Config_Ext_Int(INT_INPUT7);
		Config_Ext_Int(INT_INPUT8);
		Config_Ext_Int(INT_INPUT9);
		Keyboard_Initialize();
		GUI_Initialize();
		BEEP = 0; 
		Control_Shine(6);
		Control_Contrast(7);
		TCA9545_Initialize();
		flag_first_time_state = 1;
		lcd_init();
		clean_screen(ALL);
		GUI_ChangeState(PRESENTATION);
		OUT_5 = 0;
		OUT_6 = 0;
		OUT_7 = 0;
			
		while(1)
		{
			Autopuncher_tasks();
		}
	#endif
}

/****************************** EOF *********************************/
