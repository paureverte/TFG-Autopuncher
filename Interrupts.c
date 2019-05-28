/********************************************************************
 * FileName:		Interrupts.c									*
 * Dependencies:	Interrupts.h									*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Fitxer per administració i control de les interrupcions		*
 *		del sistema.												*	
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		24/10/18		Versió inicial	 				*
 * 																	*
 ********************************************************************/
 
#include "main.h"

/************** Variables locals *******************/

volatile unsigned long old_cylinder_pin_state;
volatile unsigned long old_holder_pin_state;
volatile unsigned long old_zero_pin_state;
volatile unsigned long old_end_pin_state;
volatile unsigned long old_door_pin_state;
volatile unsigned long old_input7_pin_state;
volatile unsigned long old_input8_pin_state;
volatile unsigned long old_input9_pin_state;

volatile unsigned char Interrupt_State_Holder; 							// Flag per saber si la interrupció esta enabled o disabled.
volatile unsigned char Interrupt_State_Zero;
volatile unsigned char Interrupt_State_Cylinder;
volatile unsigned char Interrupt_State_End;
volatile unsigned char Interrupt_State_Door;
volatile unsigned char Interrupt_State_Input7;
volatile unsigned char Interrupt_State_Input8;
volatile unsigned char Interrupt_State_Input9;



/************** Variables externes *****************/

extern unsigned long pressure; 
extern volatile unsigned long counter_read_keyboard; 
extern volatile unsigned char flag_int_emergency; 
extern volatile unsigned char flag_int_holder;
extern volatile unsigned char flag_int_electrovalve; 
extern volatile unsigned char flag_int_secdoor; 
extern volatile unsigned char flag_int_endswitch; 
extern volatile unsigned char flag_int_start;
extern volatile unsigned char flag_show_modifying_value;
extern unsigned char flag_screen_refresh;
extern volatile type_State State;  
extern volatile type_positioning positioning_state;
extern volatile unsigned long pwm_steps; 
extern volatile unsigned long pwm_steps_total;
extern volatile unsigned long pwm_steps_start_decelerate;
extern volatile type_acceleration_state acceleration_state; 
extern volatile unsigned long steps_for_deceleration;
extern volatile unsigned long counter_time_welcome_screen;
extern volatile unsigned long counter_time_variable_modify; 
extern volatile unsigned long counter_time_error_blink; 
extern volatile unsigned long counter_time_three_sec;
extern volatile unsigned long counter_time_test;
extern volatile unsigned long counter_time_enable_password;
extern volatile unsigned long counter_time_positioning; 
extern volatile unsigned long counter_time_cap_read;
extern volatile unsigned long steps_for_aceleration;
volatile unsigned long counter_T4; 
volatile unsigned long counter_T5;
extern volatile unsigned long test_time_counter;
extern volatile unsigned long random_test_counter; 
extern volatile unsigned long counter_time_autotest_blink;
extern volatile unsigned long counter_time_error_beep; 
extern volatile unsigned long counter_time_autotest_read;

/*************** Declaracio subrutines ***************/

/********************************************************************
 * Function:	CN_Init()											*
 * Definition:	CN Initialitation.									*
 ********************************************************************/
void CN_Init(void)
{
	CNCON = 0x8000; 														// Enable module
	CNEN = 0x1004F3; 													// Pins que donem enable (0, 1, 4, 5, 6, 7, 10, 20)
	//CNEN = 0x101412;
	CNPUE = 0x1004F3;
	//CNPUE = 0x101412;

	old_cylinder_pin_state = PORTD & (1<<14);
	old_holder_pin_state = PORTG & (1<<8);
	old_zero_pin_state = PORTB & (1<<2);
	old_end_pin_state = PORTC & (1<<14);
	//old_end_pin_state = PORTB & (1<<15);
	old_door_pin_state = PORTC & (1<<13);
	old_input7_pin_state = PORTB & (1<<5);
	old_input8_pin_state = PORTB & (1<<4);
	old_input9_pin_state = PORTB & (1<<3);

	IPC6SET = 0xF0000;													// Priority 3, Subpriority 3
	IFS1CLR = 0x0001; 													// Clear interrupt flag

	old_cylinder_pin_state = PORTD & (1<<14);
	old_holder_pin_state = PORTG & (1<<8);
	old_zero_pin_state = PORTB & (1<<2);
	old_end_pin_state = PORTC & (1<<14);
	//old_end_pin_state = PORTB & (1<<15);
	old_door_pin_state = PORTC & (1<<13);
	old_input7_pin_state = PORTB & (1<<5);
	old_input8_pin_state = PORTB & (1<<4);
	old_input9_pin_state = PORTB & (1<<3);

	IEC1SET = 0x0001; 													// Interrupt Enable

}

/********************************************************************
 * Function:	Config_Ext_Int(Int_To_Config)						*
 * Definition:	Configura las interrupciones externas.				*
 ********************************************************************/
unsigned int flush_port;
void Config_Ext_Int(unsigned char Int_To_Config)
{
	switch (Int_To_Config)
	{
		case 0:						// Emergencia.

			if (EMSTSW == 1)
			{
				INTCONbits.INT1EP = 0;	// Falling edge if at start it is on 1.
			}
			else 
			{
				INTCONbits.INT1EP = 1;	// Rising edge.
			}
			IPC1bits.INT1IP = 4;		// Interrupt priority 4.
			IPC1bits.INT1IS	= 0;	// Interrupt subpriority 0.
			IFS0bits.INT1IF = 0;		// Clear interrupt flag.
			IEC0bits.INT1IE = 1;		// Enable interrupt.
		break;
		case 1:						// Pisador.
			CN_Init();
			Interrupt_State_Holder = 1;
		break;
		case 2:						// ElectrovAlvula.
			CN_Init();
			Interrupt_State_Cylinder = 1;
		break;
		case 3:						// Puerta.
			CN_Init();
			Interrupt_State_Door= 1;
		break;
		case 4:						// Fin de carrera.
			CN_Init();
			Interrupt_State_End = 1;
		break;

		case 5:						// START.
			CN_Init();
			Interrupt_State_Zero = 1;
		break;

		case 6: 
			IEC0bits.I2C1MIE = 1;		// Enable master interrupt
			IEC0bits.I2C1BIE = 1;		// Bus Collision	
			IFS0bits.I2C1MIF = 0;		// Clear interrupt flags 
			IFS0bits.I2C1BIF = 0;		// Clear interrupt flags
			IPC6bits.I2C1IP = 7;		// Interrupt priority 7.
			IPC6bits.I2C1IS = 0;		// Interrupt subpriority 0. 
		break;
		case 7: 
			INTCONbits.INT0EP = 0;	// Falling edge.
			IPC0bits.INT0IP = 4;	// Interrupt priority 4.
			IPC0bits.INT0IS	= 0;	// Interrupt subpriority 0.
			IFS0bits.INT0IF = 0;	// Clear interrupt flag.
			IEC0bits.INT0IE = 1;	// Enable interrupt.
		break;

		case 8:
			CN_Init();
			Interrupt_State_Input7 = 1;
		break;

		case 9:
			CN_Init();
			Interrupt_State_Input8 = 1;
		break;

		case 10:
			CN_Init();
			Interrupt_State_Input9 = 1;
		break;
		default:
			
			flag_screen_refresh = 0;
			State = ERROR;
			
		break;
	}
}

/* Interrupciones externas */ 



/********************************************************************
 * Function:	CN_Interrupt_ISR()									*
 * Definition:	ISR de change interrupt.							*
 ********************************************************************/

void __ISR(_CHANGE_NOTICE_VECTOR, ipl3) CN_Interrupt_ISR(void)
{
	if (Interrupt_State_Cylinder == 1)
	{
		if (((PORTD & (1<<14)) != old_cylinder_pin_state) && (old_cylinder_pin_state != 0)) /* old is 0, so interrupt is falling edge */
		{
			Error_Cylinder_Change_State();
			motor_reset_flag_cilindre();
			old_cylinder_pin_state = PORTD & (1<<14);
		}
		else if (((PORTD & (1<<14)) != old_cylinder_pin_state) && (old_cylinder_pin_state != 1)) /* old is 1, so interrupt is rising edge */
		{
			Error_Cylinder_Change_State();
			motor_set_flag_cilindre();
			old_cylinder_pin_state = PORTD & (1<<14);
		}
	}

	if (Interrupt_State_Door == 1)
	{
		if (((PORTC & (1<<13)) != old_door_pin_state) && (old_door_pin_state != 0))
		{
			GUI_DataActualization();
			Error_Door_Change_State();
			old_door_pin_state = PORTC & (1<<13);
		}
		else if (((PORTC & (1<<13)) != old_door_pin_state) && (old_door_pin_state != 1))
		{
			GUI_DataActualization();
			Error_Door_Change_State();
			old_door_pin_state = PORTC & (1<<13);
		}
	}

	if (Interrupt_State_End == 1)
	{
		if (((PORTC & (1<<14)) != old_end_pin_state) && (old_end_pin_state != 0))
		{
			Error_End_Change_State();
			set_not_in_end();
			old_end_pin_state = PORTC & (1<<14);
		}
		else if (((PORTC & (1<<14)) != old_end_pin_state) && (old_end_pin_state != 1))
		{
			Error_End_Change_State();
			motor_set_flag_ficarrera();
			reset_not_in_end();  				// As I am at the end
			old_end_pin_state = PORTC & (1<<14);
		}
	}

	if (Interrupt_State_Zero == 1)
	{
		if ((( PORTB & (1<<2)) != old_zero_pin_state) && (old_zero_pin_state != 0))
		{
			Error_End_Start_Pulsed();
			Error_Start_Change_State();			// Aqui fa sempre el canvi d'estat de l'error de start ja que la interrupcio es en el canvi de 0 a 1 o de 1 a 0 independentment
			positioning_reset_flag_start();			// Sino, el poso a zero. 
			ab_closed_reset_flag_start();
			reset_start_in_end();
			old_zero_pin_state =  PORTB & (1<<2);
		}
		else if ((( PORTB & (1<<2)) != old_zero_pin_state) && (old_zero_pin_state != 1))
		{
			Error_End_Start_Pulsed();
			Error_Start_Change_State();	
			positioning_set_flag_start();			// Si esta a start, activo el flag de start per a posicionamiento
			ab_closed_set_flag_start();
			set_start_in_end();
			old_zero_pin_state =  PORTB & (1<<2);
		}
	}
	if (Interrupt_State_Holder == 1)
	{
		if ((( PORTG & (1<<8)) != old_holder_pin_state) && (old_holder_pin_state != 0))
		{
			Error_Holder_Change_State();
			old_holder_pin_state =  PORTG & (1<<8);
		}
		else if ((( PORTG & (1<<8)) != old_holder_pin_state) && (old_holder_pin_state != 1))
		{
			Error_Holder_Change_State();
			old_holder_pin_state =  PORTG & (1<<8);
		}
	}

	if (Interrupt_State_Input7 == 1) //We'll use this one as the security curtain
	{
		if ((( PORTB & (1<<5)) != old_input7_pin_state) && (old_input7_pin_state != 0)) // Considering this is what's activated when the curtain detects something
		{
			Error_Curtain_Change_State();
			old_input7_pin_state =  PORTB & (1<<5);
		}
		else if ((( PORTB & (1<<5)) != old_input7_pin_state) && (old_input7_pin_state != 1))
		{
			Error_Curtain_Change_State();
			old_input7_pin_state =  PORTB & (1<<5);
		}
	}

	if (Interrupt_State_Input8 == 1)
	{
		if ((( PORTB & (1<<4)) != old_input8_pin_state) && (old_input8_pin_state != 0))
		{
			Error_Input8_Change_State();
			old_input8_pin_state =  PORTB & (1<<4);
		}
		else if ((( PORTB & (1<<4)) != old_input8_pin_state) && (old_input8_pin_state != 1))
		{
			Error_Input8_Change_State();
			old_input8_pin_state =  PORTB & (1<<4);
		}
	}

	if (Interrupt_State_Input9 == 1)
	{
		if ((( PORTB & (1<<3)) != old_input9_pin_state) && (old_input9_pin_state != 0))
		{
			Error_Input9_Change_State();
			old_input9_pin_state =  PORTB & (1<<3);
		}
		else if ((( PORTB & (1<<3)) != old_input9_pin_state) && (old_input9_pin_state != 1))
		{
			Error_Input9_Change_State();
			old_input9_pin_state =  PORTB & (1<<3);
		}
	}

	IFS1CLR = 0x0001;

}


/***** I2C INTERRUPTS *****/

void __ISR(_I2C_1_VECTOR , IPL7SOFT) I2C1Handler(void)
{
	if(IFS0bits.I2C1MIF == 1)
	{
		/* master */
		IFS0bits.I2C1MIF = 0;
		I2C_ISR_Tasks();
	}
	if(IFS0bits.I2C1BIF == 1)
	{
		/* bus collision */
		IFS0bits.I2C1BIF = 0;
		I2C_SetBusCollisionDetected();
	}
}

/***** EMERGENCY STOP ******/

/********************************************************************
 * Function:	Ext0Handler()										*
 * Definition:	ISR de interrupción externa 0 para comunicaciones.	*
 ********************************************************************/
void __ISR(_EXTERNAL_0_VECTOR , IPL4SOFT) Ext0Handler(void)	// Interrupció pels CAP1208
{
	//Procés per començar la lectura de tots els CAP.
	CAPManager_SetFlag();
	IFS0bits.INT0IF = 0;	// Clear interrupt flag.
	//IEC0bits.INT0IE = 0;	// Disable interrupt.
}

/********************************************************************
 * Function:	Ext1_Polarity_Change()								*
 * Definition:	Canviar l'edge de la interrupcio.					*
 ********************************************************************/  
  void Ext1_Polarity_Change(void)
  {
  	if (INTCONbits.INT1EP == 1)
  	{
  		INTCONbits.INT1EP = 0; 
  	}
  	else 
  	{
  		INTCONbits.INT1EP = 1;
  	}
  }
/********************************************************************
 * Function:	Ext1Handler()										*
 * Definition:	ISR de interrupción externa 1 para comunicaciones.	*
 ********************************************************************/
void __ISR(_EXTERNAL_1_VECTOR , IPL4SOFT) Ext1Handler(void)	// Paro de emergencia
{
	IFS0bits.INT1IF = 0;	// Clear interrupt flag.

	Error_Emergency_Change_State();
	Ext1_Polarity_Change();
}

/********************************************************************
 * Function:	Holder_Interrupt_Disable()							*
 * Definition:	Desactivar l'interru´pció del holder.				*
 ********************************************************************/
void Holder_Interrupt_Disable(void)	// Pisador arriba.
{
	Interrupt_State_Holder = 0;
}
/********************************************************************
 * Function:	Holder_Interrupt_Enable()							*
 * Definition:	Reactivar l'interru´pció del holder.				*
 ********************************************************************/
void Holder_Interrupt_Enable(void)	// Pisador arriba.
{
	Interrupt_State_Holder = 1;
}

/* Interrupciones Timers */ 

/********************************************************************
 * Function:	Timer1Handler()										*
 * Definition:	ISR del Timer1. Cada 1ms. General.					*
 ********************************************************************/
void __ISR(_TIMER_1_VECTOR, ipl1) Timer1Handler(void)
{
	mT1ClearIntFlag();		// Clear the interrupt flag.
	
	counter_read_keyboard++;
	
	counter_time_welcome_screen++;
	
	random_test_counter++;
	
	counter_time_variable_modify++;

	counter_time_error_blink++;

	counter_time_three_sec++;

	test_time_counter++;

	counter_time_test++;

	counter_time_enable_password++;

	counter_time_positioning++;

	counter_time_cap_read++;

	counter_time_autotest_blink++;

	counter_time_error_beep++;
	
	counter_time_autotest_read++;

	// Codigo deseado
}

/********************************************************************
 * Function:	Timer3Handler()										*
 * Definition:	ISR del Timer3. Cada 100ms. Para error cil pisador.	*
 ********************************************************************/
void __ISR(_TIMER_3_VECTOR, ipl2) Timer3Handler(void)
{
	mT3ClearIntFlag();		// Clear the interrupt flag.
	// Codigo deseado
}

/********************************************************************
 * Function:	Timer4Handler()										*
 * Definition:	ISR del Timer4. Cada 100ms. Para pisador.			*
 ********************************************************************/
void __ISR(_TIMER_4_VECTOR, ipl3) Timer4Handler(void)
{

	mT4ClearIntFlag();		// Clear the interrupt flag.
	counter_T4++;
	if (counter_T4 >= pressure)
	{
		counter_T4 = 0;
		pressure_completed_set_flag();  // Activamos el flag de pression de cilindro completada. 
		CloseTimer4();		// Cierro Timer4.
	}
}

/********************************************************************
 * Function:	Timer5Handler()										*
 * Definition:	ISR del Timer5. Cada 1us. Para pasos motor.			*
 ********************************************************************/
void __ISR(_TIMER_5_VECTOR, ipl3) Timer5Handler(void)
{
	mT5ClearIntFlag();		// Clear the interrupt flag.
	counter_T5++;
	//LED_AB = 1; 
	if (counter_T5 >= (20 + pressure))	// Más de 2 segundos + tiempo de pressure sin volver.
	{
		counter_T5 = 0;
		GUI_ChangeState(ERROR);
		Error_Change_State(error_cylinder);
		CloseTimer5();		// Cierro Timer5.	
	}
	//LED_AB = 0; 
}

/********************************************************************
 * Function:	reset_counter_t5()									*
 * Definition:	Reset del comptador del t5.							*
 ********************************************************************/
void reset_counter_t5(void)
{
	counter_T5 = 0; 
}

/* Interrupciones OutputCompare */

/********************************************************************
 * Function:	OC4_Handler()										*
 * Definition:	ISR del OC4. En funcio del TON i TOFF. Per control  *
 *				del motor pas-a-pas. 								*
 ********************************************************************/
void __ISR(_OUTPUT_COMPARE_4_VECTOR, ipl7) OC4_Handler(void)
{
	IFS0CLR = 1<<18;		// Clear the interrupt flag.
	// Miro si ja s'ha arribat al numero de passos per decelerar
	if ((State != POSITIONING) || (positioning_state == SEARCHING_ZERO))   				// Quan estigui posicionant no sabem quan es decelerara. Fem que acceleri i quan arribi al maxim es mantingui constant. Si que voldrem que deceleri com toca quan busqui el punt zero.
	{
		if (pwm_steps >= pwm_steps_start_decelerate && acceleration_state != STOP)	
		{
			acceleration_state = DECELERATE; 	// Si ja s'ha arribat, comença a decelerar. 
		}
		else if (pwm_steps >= steps_for_aceleration && acceleration_state != STOP)				// Si ja ha fet el total de passos de accelerar, es mantendrà constant.
		{
			acceleration_state == STEADY;
		}
	}	
	StepMotor();					// Codi a realitzar depenent de l'estat d'acceleration
}

//	Exception handler:
  static enum {
  	EXCEP_IRQ = 0,			// interrupt
  	EXCEP_AdEL = 4,			// address error exception (load or ifetch)
  	EXCEP_AdES,				// address error exception (store)
  	EXCEP_IBE,				// bus error (ifetch)
  	EXCEP_DBE,				// bus error (load/store)
  	EXCEP_Sys,				// syscall
  	EXCEP_Bp,				// breakpoint
  	EXCEP_RI,				// reserved instruction
  	EXCEP_CpU,				// coprocessor unusable
  	EXCEP_Overflow,			// arithmetic overflow
  	EXCEP_Trap,				// trap (possible divide by zero)
  	EXCEP_IS1 = 16,			// implementation specfic 1
  	EXCEP_CEU,				// CorExtend Unuseable
  	EXCEP_C2E				// coprocessor 2
  } _excep_code;

  static unsigned int _excep_addr;

  // this function overrides the normal _weak_ generic handler
  void _general_exception_handler(void)
  {
  	asm volatile("mfc0 %0,$13" : "=r" (_excep_code));
  	asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

  	_excep_code = (_excep_code & 0x0000007C) >> 2;
  	 	while (1) {
  		// Examine _excep_code to identify the type of exception
  		// Examine _excep_addr to find the address that caused the exception
  		Nop();
  		Nop();
  		Nop();
   	}
  }//	End of exception handler
  

