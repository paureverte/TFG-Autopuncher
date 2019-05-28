 /********************************************************************
 * FileName:		Inits.c											*
 * Dependencies:	Inits.h											*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions de inicialització del micro i perifèrics 			*												*	
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		23/10/18		Versió inicial	 				*
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


/***************** Definicio de subrutines *************************/


/********************************************************************
 * Function:	Config_System()										*
 * Description:	Configura el oscilador del sistema.					*
 ********************************************************************/
void Config_System(void)
{
	DDPCONbits.JTAGEN = 0;				// Habilitar al programar.
	SYSTEMConfigPerformance(80000000);
	INTEnableSystemMultiVectoredInt();
}

/********************************************************************
 * Function:	Config_Ports()										*
 * Description:	Configura els ports I/O.							*
 ********************************************************************/
void Config_Ports(void)
{
	/* Pins a nivell determinat a l'inici */
	
	RST_KBD = 1;

	LED_RUN = 0;
	LED_AB = 0;
	LED_AA = 0;
	LED_START = 0;
	LED_STOP = 0;
	BEACON_STOP = 0;
	BEACON_START = 0;
	LED_ENTER = 0;
	LED_ESC = 0;
	LED_PUNCH = 0;
	LED_STEP = 0;
	LED_BELT = 0;
	LED_RESET = 0;
	LED_MENU = 0;
	LED_N0 = 0;
	LED_N1 = 0;
	LED_N2 = 0;
	LED_N3 = 0;
	LED_N4 = 0;
	LED_N5 = 0;
	LED_N6 = 0;
	LED_N7 = 0;
	LED_N8 = 0;
	LED_N9 = 0;
	OUT_EVCIL = 0;
	
	// PUERTO A
	mPORTASetPinsDigitalIn (BIT_0 |BIT_9 | BIT_10);			
	mPORTASetPinsDigitalOut(BIT_1 | BIT_2 | BIT_3 | BIT_4 |	BIT_5 | BIT_6 | BIT_7 | BIT_14 | BIT_15);						 
	
	// PUERTO B
	mPORTBSetPinsDigitalIn (BIT_2 | BIT_3 | BIT_4 |	BIT_5 | BIT_6 | BIT_7 | BIT_8 | BIT_9 |	BIT_10 | BIT_11  /*| BIT_15*/ );			
	mPORTBSetPinsDigitalOut(BIT_0 | BIT_1 |	BIT_12 | BIT_13 | BIT_14 | BIT_15 );	

	// PUERTO C
	mPORTCSetPinsDigitalIn (BIT_12 | BIT_13 | BIT_14 );			
	mPORTCSetPinsDigitalOut(BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_15);				

	// PUERTO D
	mPORTDSetPinsDigitalIn (BIT_0 | BIT_10 | BIT_14 );							
	mPORTDSetPinsDigitalOut(BIT_1 |	BIT_2 | BIT_3 |	BIT_4 | BIT_5 | BIT_6 | BIT_7 | BIT_8 |	BIT_9 |	BIT_11 | BIT_12 | BIT_13 | BIT_15);		

	// PUERTO E
	mPORTESetPinsDigitalIn (BIT_8);								
	mPORTESetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 |		
							BIT_5 | BIT_6 | BIT_7 | BIT_9 );						
	// PUERTO F
	mPORTFSetPinsDigitalIn (BIT_2 |	BIT_4 |	BIT_6 |	BIT_7 |	BIT_12 );						
	mPORTFSetPinsDigitalOut(BIT_0 | BIT_1 | BIT_3 | BIT_5 |	BIT_8 | BIT_13); 
				
	// PUERTO G
	mPORTGSetPinsDigitalIn (BIT_2 | BIT_3 | BIT_8 );								
	mPORTGSetPinsDigitalOut(BIT_0 | BIT_1 | BIT_6 | BIT_7 | BIT_9 |	BIT_12 | BIT_13 | BIT_14 | BIT_15);	

	AD1PCFG = 0xFFFF;	// Analog inputs in digital mode.

}
/********************************************************************
 * Function:	Init_Values()										*
 * Description:	Inicializa valors.									*
 ********************************************************************/
void Init_Values(void)
{
	unsigned char flag_write_flash_necessary = 0;
	wide = *(int *)(NVM_PROGRAM_PAGE);
	if ((wide > wide_MAX)||(MAX_WIDE < wide_MIN))
	{
		wide = wide_FACTORY;
		flag_write_flash_necessary = 1;
	}

	step = *(int *)(NVM_PROGRAM_PAGE + 4);
	if ((step > step_MAX)||(step < step_MIN))
	{
		step = step_FACTORY;
		flag_write_flash_necessary = 1;
	}

	pressure = *(int *)(NVM_PROGRAM_PAGE + 8);
	if ((pressure > pressure_MAX)||(pressure < pressure_MIN))
	{
		pressure = pressure_FACTORY;
		flag_write_flash_necessary = 1;
	}

	bridge = *(int *)(NVM_PROGRAM_PAGE + 12);
	if (bridge > 1)
	{
		bridge = 1; 
	}

	MAX_WIDE = *(int *)(NVM_PROGRAM_PAGE + 16);
	if ((MAX_WIDE > wide_MAX)||(MAX_WIDE < wide_MIN))
	{
		MAX_WIDE = wide_MAX;
		flag_write_flash_necessary = 1;
	}

	mainlanguage = *(int *)(NVM_PROGRAM_PAGE + 20);
	if (mainlanguage > 1)
	{
		mainlanguage = 0; 
	}

	zero_value = *(int *)(NVM_PROGRAM_PAGE + 24);
	if ((zero_value < 50)||(zero_value > 999))
	{
		zero_value = zero_value_FACTORY;
		flag_write_flash_necessary = 1;
	}

	end_limit = *(int *)(NVM_PROGRAM_PAGE + 28);
	if ((end_limit < 50)||(end_limit > 999))
	{
		end_limit = end_limit_FACTORY;
		flag_write_flash_necessary = 1;
	}

	TON = *(int *)(NVM_PROGRAM_PAGE + 32);
	if (TON < 5 || TON > 999)
	{
		TON = TON_FACTORY;
		flag_write_flash_necessary = 1;
	}

	TOFF_MIN = *(int *)(NVM_PROGRAM_PAGE + 36);
	if (TOFF_MIN < 5  || TOFF_MIN > 999)
	{
		TOFF_MIN = TOFF_MIN_FACTORY;
		flag_write_flash_necessary = 1;
	}

	TOFF_MAX = *(int *)(NVM_PROGRAM_PAGE + 40);
	if (TOFF_MAX < 5 || TOFF_MAX > 9999)
	{
		TOFF_MAX = TOFF_MAX_FACTORY;
		flag_write_flash_necessary = 1;
	}

	necessary_steps_for_change = *(int *)(NVM_PROGRAM_PAGE + 44);
	if (necessary_steps_for_change < 1 || necessary_steps_for_change > 999)
	{
		necessary_steps_for_change = necessary_steps_for_change_FACTORY;
		flag_write_flash_necessary = 1;
	}

	accelerate_constant = *(int *)(NVM_PROGRAM_PAGE + 48);
	if ((accelerate_constant > acc_const_MAX)||(accelerate_constant < acc_const_MIN))
	{
		accelerate_constant = acc_const_FACTORY;
		flag_write_flash_necessary = 1;
	}

	decelerate_constant = *(int *)(NVM_PROGRAM_PAGE + 52);
	if ((decelerate_constant > dec_const_MAX)||(decelerate_constant < dec_const_MIN))
	{
		decelerate_constant = dec_const_FACTORY;
		flag_write_flash_necessary = 1;
	}

	submenu2_turns_number = *(int *)(NVM_PROGRAM_PAGE + 56);
	if ((submenu2_turns_number < 1)||(submenu2_turns_number > 10))
	{
		submenu2_turns_number = 10;
		flag_write_flash_necessary = 1;
	}

	distance_limit_to_start = *(int *)(NVM_PROGRAM_PAGE + 60);
	if ((distance_limit_to_start < 1)||(distance_limit_to_start > 20))
	{
		distance_limit_to_start = 5;
		flag_write_flash_necessary = 1;
	}

	operation_mode = *(int *)(NVM_PROGRAM_PAGE + 64);
	if ((operation_mode != AA) && (operation_mode != AB) && (operation_mode != AA_AB))
	{
		operation_mode = AA;
		flag_write_flash_necessary = 1;
	}

	if(flag_write_flash_necessary)
	{
		Flash_Write();
	}
}

/********************************************************************
 * Function:	Init_Reg()											*
 * Description:	Inicializa registres y variables.					*
 ********************************************************************/
void Init_Reg(void)
{
	Init_Values();
	LED_STOP = 0; 
	LED_START = 0;
	BEACON_START = 0;
	BEACON_STOP = 0;
	Error_Holder_Change_State(); 			// Mira l'estat del pisador. 
	Error_Cylinder_Change_State();			// Mira l'estat del cilindre.
	Error_Emergency_Change_State();			// Mira l'estat del polsador d'emergencia
	Error_Start_Change_State();				// Mira l'estat del limit d'inicio
	Error_End_Change_State();
	Error_Door_Change_State();
	Error_Curtain_Change_State();
}

