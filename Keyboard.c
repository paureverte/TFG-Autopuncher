/********************************************************************
 * FileName:		keyboard.c										*
 * Dependencies:	keyboard.h										*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions de control del teclat.								*
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		30/10/18		Versió inicial 					*
 * 																	*
 ********************************************************************/
#include "main.h"

typedef enum
{
	UNPRESSED = 0,
	PRESSED,
} key_state_t;


/***************** Variables locals *************************/

volatile myCallbackType keyboard_myCallback = NULL;
volatile type_StateKeyboardRead StateKeyboardRead  = 0;

/********************* Auxiliars ****************************/
volatile unsigned char counter_key_aa = 0;
volatile unsigned char counter_key_ab = 0;
volatile unsigned char counter_key_start = 0; 
volatile unsigned char counter_key_stop = 0; 
volatile unsigned char counter_key_menu = 0; 
volatile unsigned char counter_key_enter = 0;
volatile unsigned char counter_key_reset = 0; 
volatile unsigned char counter_key_esc = 0;
volatile unsigned long counter_key_secret = 0;
volatile unsigned long counter_read_keyboard = 0;
volatile unsigned long counter_key_aaab = 0;
volatile unsigned long counter_key_n0 = 0;
volatile unsigned long counter_key_n1 = 0;
volatile unsigned long counter_key_n2 = 0;
volatile unsigned long counter_key_n3 = 0;
volatile unsigned long counter_key_n4 = 0;
volatile unsigned long counter_key_n5 = 0;
volatile unsigned long counter_key_n6 = 0;
volatile unsigned long counter_key_n7 = 0;
volatile unsigned long counter_key_n8 = 0;
volatile unsigned long counter_key_n9 = 0;
volatile unsigned long counter_key_belt = 0;
volatile unsigned long counter_key_step = 0;
volatile unsigned long counter_key_punch = 0;

volatile char flag_enable_key_aa = 1;
volatile char flag_enable_key_ab = 1;
volatile char flag_enable_key_start = 1;
volatile char flag_enable_key_stop = 1;
volatile char flag_enable_key_menu = 1;
volatile char flag_enable_key_reset = 1;
volatile char flag_enable_key_wide = 1;
volatile char flag_enable_key_step = 1;
volatile char flag_enable_key_punch = 1;
volatile char flag_enable_key_esc = 1;
volatile char flag_enable_key_enter = 1;
volatile char flag_enable_key_0 = 1;
volatile char flag_enable_key_1 = 1;
volatile char flag_enable_key_2 = 1;
volatile char flag_enable_key_3 = 1;
volatile char flag_enable_key_4 = 1;
volatile char flag_enable_key_5 = 1;
volatile char flag_enable_key_6 = 1;
volatile char flag_enable_key_7 = 1;
volatile char flag_enable_key_8 = 1;
volatile char flag_enable_key_9 = 1;

volatile unsigned char flag_punch_led_blocked = 0;
volatile unsigned char flag_at_autotest_led = 0;

volatile unsigned char flag_key_not_funct = 0;
volatile unsigned char flag_some_key_pressed = 0;


extern volatile type_door_error_state door_error_state;

/***************** Variables externes ***********************/

/********************************************************************
 * Function:	Keyboard_SetMyCallback()							*
 * Definition:	Assignacio de la direccio del callback.				*
 ********************************************************************/
void Keyboard_SetMyCallback(myCallbackType callback)
{
	keyboard_myCallback = callback;																		// Assignem callback. Guardem la direccio a la que s'hauran d'enviar les dades (funcio).
}	

/********************************************************************
 * Function:	Keyboard_Initialize()								*
 * Definition:	Inicialitzacio del teclat. 							*
 ********************************************************************/
void Keyboard_Initialize(void)
{
	keyboard_myCallback = NULL;
}

/********************************************************************
 * Function:	Keyboard_Read()										*
 * Definition:	En funcio dels pins transmeteix unes dades o		* 
 *              unes altres al callback del teclat.					*
 ********************************************************************/
#define START_MASK (1 << 3)
#define START_CAP_INDEX 2
#define STOP_MASK (1 << 4)
#define STOP_CAP_INDEX 2
#define AA_MASK (1 << 0)
#define AA_CAP_INDEX 2
#define SECRET_MASK (1 << 2)
#define SECRET_CAP_INDEX 2
#define AB_MASK (1 << 5)
#define AB_CAP_INDEX 2
#define MENU_MASK (1 << 1)
#define MENU_CAP_INDEX 2
#define RESET_MASK (1 << 6)
#define RESET_CAP_INDEX 2
#define BELT_MASK (1 << 0)
#define BELT_CAP_INDEX 1
#define STEP_MASK (1 << 1)
#define STEP_CAP_INDEX 1
#define PUNCH_MASK (1 << 7)
#define PUNCH_CAP_INDEX 2
#define ESC_MASK (1 << 7)
#define ESC_CAP_INDEX 1
#define N0_MASK (1 << 5)
#define N0_CAP_INDEX 1
#define ENTER_MASK (1 << 2)
#define ENTER_CAP_INDEX 1
#define N1_MASK (1 << 0)
#define N1_CAP_INDEX 0
#define N4_MASK (1 << 2)
#define N4_CAP_INDEX 0
#define N7_MASK (1 << 5)
#define N7_CAP_INDEX 0
#define N2_MASK (1 << 6)
#define N2_CAP_INDEX 1
#define N5_MASK (1 << 4)
#define N5_CAP_INDEX 1
#define N8_MASK (1 << 3)
#define N8_CAP_INDEX 1
#define N3_MASK (1 << 1)
#define N3_CAP_INDEX 0
#define N6_MASK (1 << 3)
#define N6_CAP_INDEX 0
#define N9_MASK (1 << 4)
#define N9_CAP_INDEX 0

void Keyboard_Read(void)
{
	if (flag_key_not_funct == 1)
	{
		if (door_error_state == door_CLOSED)
		{
			flag_some_key_pressed = 1;
		}
	}
	else
	{
		if((CAPManager_GetCAPIndexInputStatus(START_CAP_INDEX) & START_MASK) != UNPRESSED)
	{
		if (flag_enable_key_start == 1)
		{
			counter_key_start++;
		}
		if (flag_at_autotest_led == 0)
		{
			LED_START = 1;
		}	
	}
	else
	{
		if(counter_key_start >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_START);
			}
		}

		counter_key_start = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_START = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(STOP_CAP_INDEX) & STOP_MASK) != UNPRESSED)
	{
		if (flag_enable_key_stop == 1)
		{
			counter_key_stop++;
		}
		if (flag_at_autotest_led == 0)
		{
			LED_STOP = 1;
		}
	}
	else
	{
		if(counter_key_stop >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_STOP);
			}
		}

		counter_key_stop = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_STOP = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(AA_CAP_INDEX) & AA_MASK) != UNPRESSED)
	{
		if (flag_enable_key_aa == 1)
		{
			counter_key_aa++;
		}
		if (flag_at_autotest_led == 0)
		{
			LED_AA = 1;
		}
	}
	else
	{
		if(counter_key_aa >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_AA);
			}
		}

		counter_key_aa = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_AA = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(SECRET_CAP_INDEX) & SECRET_MASK) != UNPRESSED)
	{
		counter_key_secret++;
	}
	else
	{
		if(counter_key_secret >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_SECRET);
			}
		}
			counter_key_secret = 0;
	}
		if((CAPManager_GetCAPIndexInputStatus(AB_CAP_INDEX) & AB_MASK) != UNPRESSED)
	{
		if (flag_enable_key_ab == 1)
		{	
			counter_key_ab++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_AB = 1;
		}
	}
	else
	{
		if(counter_key_ab >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_AB);
			}
		}

		counter_key_ab = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_AB = 0;
		}		
	}
	if(((CAPManager_GetCAPIndexInputStatus(AA_CAP_INDEX) & AA_MASK) != UNPRESSED) && ((CAPManager_GetCAPIndexInputStatus(AB_CAP_INDEX) & AB_MASK) != UNPRESSED))
	{
		counter_key_aaab++;
		if(counter_key_aaab >= KEYBOARD_LONG_PRESS_KEYBOARD_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_AAAB);
			}
		}
	}
	else
	{
		counter_key_aaab = 0;
	}
		if((CAPManager_GetCAPIndexInputStatus(MENU_CAP_INDEX) & MENU_MASK) != UNPRESSED)
	{
		
		if(flag_enable_key_menu == 1)
		{
			counter_key_menu++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_MENU = 1;
		}

		if(counter_key_menu >= KEYBOARD_LONG_PRESS_KEYBOARD_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_MENU_3S);
			}
		}
	}
	else
	{
		if((counter_key_menu >= KEYBOARD_SHORT_PRESS_TICKS) && (counter_key_menu < KEYBOARD_LONG_PRESS_KEYBOARD_TICKS) )
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_MENU);
			}
		}

		counter_key_menu = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_MENU = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(RESET_CAP_INDEX) & RESET_MASK) != UNPRESSED)
	{
		if (flag_enable_key_reset == 1)
		{
			counter_key_reset++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_RESET = 1;
		}
	}
	else
	{
		if(counter_key_reset >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_RESET);
			}
		}

		counter_key_reset = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_RESET = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(BELT_CAP_INDEX) & BELT_MASK) != UNPRESSED)
	{
		if  (flag_enable_key_wide == 1)
		{
			counter_key_belt++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_BELT = 1;
		}
	}
	else
	{
		if(counter_key_belt >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_BELT);
			}
		}

		counter_key_belt = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_BELT = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(STEP_CAP_INDEX) & STEP_MASK) != UNPRESSED)
	{
		if(flag_enable_key_step == 1)
		{
			counter_key_step++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_STEP = 1;
		}
	}
	else
	{
		if(counter_key_step >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_STEP);
			}
		}

		counter_key_step = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_STEP = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(PUNCH_CAP_INDEX) & PUNCH_MASK) != UNPRESSED)
	{
		if(flag_enable_key_punch == 1)
		{
			counter_key_punch++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_PUNCH = 1;
		}
	}
	else
	{
		if(counter_key_punch >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_PUNCH);
			}
		}

		counter_key_punch = 0;

		if (flag_punch_led_blocked == 0)  //Si el LED no esta bloquejat per algun estat, l'apaguem
		{
			if (flag_at_autotest_led == 0)
			{

				LED_PUNCH = 0;			
			}	
		}
	}
	if((CAPManager_GetCAPIndexInputStatus(ESC_CAP_INDEX) & ESC_MASK) != UNPRESSED)
	{
		if (flag_enable_key_esc == 1)
		{
			counter_key_esc++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_ESC = 1;
		}	
	}
	else
	{
		if(counter_key_esc >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_ESC);
			}
		}

		counter_key_esc = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_ESC = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N0_CAP_INDEX) & N0_MASK) != UNPRESSED)
	{
		if(flag_enable_key_0 == 1)
		{
			counter_key_n0++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_N0 = 1;
		}	
	}
	else
	{
		if(counter_key_n0 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N0);
			}
		}

		counter_key_n0 = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_N0 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(ENTER_CAP_INDEX) & ENTER_MASK) != UNPRESSED)
	{
		if (flag_enable_key_enter == 1)
		{
			counter_key_enter++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_ENTER = 1;
		}

		if(counter_key_enter >= KEYBOARD_LONG_PRESS_KEYBOARD_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_ENTER_3S);
			}
		}
	}
	else
	{
		if(counter_key_enter >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_ENTER);
			}
		}

		counter_key_enter = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_ENTER = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N1_CAP_INDEX) & N1_MASK) != UNPRESSED)
	{
		if (flag_enable_key_1 == 1)
		{
			counter_key_n1++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_N1 = 1;
		}	
	}
	else
	{
		if(counter_key_n1 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N1);
			}
		}

		counter_key_n1 = 0;
		
		if (flag_at_autotest_led == 0)
		{
			LED_N1 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N4_CAP_INDEX) & N4_MASK) != UNPRESSED)
	{
		if (flag_enable_key_4 == 1)
		{
			counter_key_n4++;
		}

		if (flag_at_autotest_led == 0)
		{	
			LED_N4 = 1;		
		}
	}
	else
	{
		if(counter_key_n4 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N4);
			}
		}

		counter_key_n4 = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_N4 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N7_CAP_INDEX) & N7_MASK) != UNPRESSED)
		{
		if (flag_enable_key_7 == 1)
		{			
			counter_key_n7++;	
		}

		if (flag_at_autotest_led == 0)
		{
			LED_N7 = 1;
		}	
	}
	else
	{
		if(counter_key_n7 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N7);
			}
		}

		counter_key_n7 = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_N7 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N2_CAP_INDEX) & N2_MASK) != UNPRESSED)
	{
		if (flag_enable_key_2 == 1)
		{
			counter_key_n2++;
		}

		if (flag_at_autotest_led == 0)
		{	
			LED_N2 	= 1;		
		}
	}
	else
	{
		if(counter_key_n2 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N2);
			}
		}

		counter_key_n2 = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_N2 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N5_CAP_INDEX) & N5_MASK) != UNPRESSED)
	{
		if (flag_enable_key_5 == 1)
		{
			counter_key_n5++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_N5 = 1;
		}	
	}
	else
	{
		if(counter_key_n5 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N5);
			}
		}

		counter_key_n5 = 0;

		if (flag_at_autotest_led == 0)
		{
			LED_N5 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N8_CAP_INDEX) & N8_MASK) != UNPRESSED)
	{
		if (flag_enable_key_8 == 1)
		{
			counter_key_n8++;
		}

		if (flag_at_autotest_led == 0)
		{
			LED_N8 = 1;
		}
	
	}
	else
	{
		if(counter_key_n8 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N8);
			}
		}

		counter_key_n8 = 0;
		
		if (flag_at_autotest_led == 0)
		{
			LED_N8 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N3_CAP_INDEX) & N3_MASK) != UNPRESSED)
	{
		if (flag_enable_key_3 == 1)
		{
			counter_key_n3++;
		}
		
		if (flag_at_autotest_led == 0)
		{
			LED_N3 = 1;
		}
		
	}
	else
	{
		if(counter_key_n3 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N3);
			}
		}
		
		counter_key_n3 = 0;
		
		if (flag_at_autotest_led == 0)
		{
			LED_N3 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N6_CAP_INDEX) & N6_MASK) != UNPRESSED)
	{
		if (flag_enable_key_6 == 1)
		{
			counter_key_n6++;
		}
		
		if (flag_at_autotest_led == 0)
		{
			LED_N6 = 1;
		}
	
	}
	else
	{
		if(counter_key_n6 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N6);
			}
		}
		
		counter_key_n6 = 0;
		
		if (flag_at_autotest_led == 0)
		{
			LED_N6 = 0;
		}		
	}
	if((CAPManager_GetCAPIndexInputStatus(N9_CAP_INDEX) & N9_MASK) != UNPRESSED)
	{
		if (flag_enable_key_9 == 1)
		{
			counter_key_n9++;
		}
		
		if (flag_at_autotest_led == 0)
		{
			LED_N9 = 1;
		}
		
	}
	else
	{
		if(counter_key_n9 >= KEYBOARD_SHORT_PRESS_TICKS)
		{
			if(keyboard_myCallback != NULL)
			{
				keyboard_myCallback(KEY_N9);
			}
		}
			counter_key_n9 = 0;
		if (flag_at_autotest_led == 0)
		{
			LED_N9 = 0;
		}		
	}

	}

}
/********************************************************************
 * Function:	Keyboard_Tasks()									*
 * Definition:	Tasks del teclat. Usats per al comptador i fer 		*
 *				lectura. 				 							*
 ********************************************************************/
void Keyboard_Tasks(void)
{
	switch (StateKeyboardRead)
	{
		case KEYBOARD_INIT: 
		{
			counter_read_keyboard = 0;
			StateKeyboardRead = KEYBOARD_WAIT;
			break;
		}
		case KEYBOARD_WAIT: 
		{
			if (counter_read_keyboard >= READ_KEYBOARD_EVERY_MS)
			{
				counter_read_keyboard = 0; 
				StateKeyboardRead = KEYBOARD_DONE;
			}
			break;
		}
		case KEYBOARD_DONE:
		{
			Keyboard_Read();
			StateKeyboardRead = KEYBOARD_INIT;
			break;
		}
	}
}

void enable_key_aa(void)
{
	flag_enable_key_aa = 1;
}
void enable_key_ab(void)
{
	flag_enable_key_ab = 1;
}
void enable_key_start(void)
{
	flag_enable_key_start = 1;
}
void enable_key_stop(void)
{
	flag_enable_key_stop = 1;
}
void enable_key_menu(void)
{
	flag_enable_key_menu = 1;
}
void enable_key_reset(void)
{
	flag_enable_key_reset = 1;
}
void enable_key_wide(void)
{
	flag_enable_key_wide = 1;
}
void enable_key_step(void)
{
	flag_enable_key_step = 1;
}
void enable_key_punch(void)
{
	flag_enable_key_punch = 1;
}
void enable_key_esc(void)
{
	flag_enable_key_esc = 1;
}
void enable_key_enter(void)
{
	flag_enable_key_enter = 1;
}
void enable_key_0(void)
{
	flag_enable_key_0 = 1;
}
void enable_key_1(void)
{
	flag_enable_key_1 = 1;
}
void enable_key_2(void)
{
	flag_enable_key_2 = 1;
}
void enable_key_3(void)
{
	flag_enable_key_3 = 1;
}
void enable_key_4(void)
{
	flag_enable_key_4 = 1;
}
void enable_key_5(void)
{
	flag_enable_key_5 = 1;
}
void enable_key_6(void)
{
	flag_enable_key_6 = 1;
}
void enable_key_7(void)
{
	flag_enable_key_7 = 1;
}
void enable_key_8(void)
{
	flag_enable_key_8 = 1;
}
void enable_key_9(void)
{
	flag_enable_key_9 = 1;
}

void disable_key_aa(void)
{
	flag_enable_key_aa = 0;
}
void disable_key_ab(void)
{
	flag_enable_key_ab = 0;
}
void disable_key_start(void)
{
	flag_enable_key_start = 0;
}
void disable_key_stop(void)
{
	flag_enable_key_stop = 0;
}
void disable_key_menu(void)
{
	flag_enable_key_menu = 0;
}
void disable_key_reset(void)
{
	flag_enable_key_reset = 0;
}
void disable_key_wide(void)
{
	flag_enable_key_wide = 0;
}
void disable_key_step(void)
{
	flag_enable_key_step = 0;
}
void disable_key_punch(void)
{
	flag_enable_key_punch = 0;
}
void disable_key_esc(void)
{
	flag_enable_key_esc = 0;
}
void disable_key_enter(void)
{
	flag_enable_key_enter = 0;
}
void disable_key_0(void)
{
	flag_enable_key_0 = 0;
}
void disable_key_1(void)
{
	flag_enable_key_1 = 0;
}
void disable_key_2(void)
{
	flag_enable_key_2 = 0;
}
void disable_key_3(void)
{
	flag_enable_key_3 = 0;
}
void disable_key_4(void)
{
	flag_enable_key_4 = 0;
}
void disable_key_5(void)
{
	flag_enable_key_5 = 0;
}
void disable_key_6(void)
{
	flag_enable_key_6 = 0;
}
void disable_key_7(void)
{
	flag_enable_key_7 = 0;
}
void disable_key_8(void)
{
	flag_enable_key_8 = 0;
}
void disable_key_9(void)
{
	flag_enable_key_9 = 0;
}
void disable_numbers(void)
{
	disable_key_0();
	disable_key_1();
	disable_key_2();
	disable_key_3();
	disable_key_4();
	disable_key_5();
	disable_key_6();
	disable_key_7();
	disable_key_8();
	disable_key_9();
}
void enable_numbers(void)
{
	enable_key_0();
	enable_key_1();
	enable_key_2();
	enable_key_3();
	enable_key_4();
	enable_key_5();
	enable_key_6();
	enable_key_7();
	enable_key_8();
	enable_key_9();
}
void disable_all_keys (void)
{
	disable_key_aa();
	disable_key_ab();
	disable_key_start();
	disable_key_stop();
	disable_key_menu();
	disable_key_reset();
	disable_key_wide();
	disable_key_step();
	disable_key_punch();
	disable_key_esc();
	disable_key_enter();
	disable_key_0();
	disable_key_1();
	disable_key_2();
	disable_key_3();
	disable_key_4();
	disable_key_5();
	disable_key_6();
	disable_key_7();
	disable_key_8();
	disable_key_9();
}

void enable_all_keys (void)
{
	enable_key_aa();
	enable_key_ab();
	enable_key_start();
	enable_key_stop();
	enable_key_menu();
	enable_key_reset();
	enable_key_wide();
	enable_key_step();
	enable_key_punch();
	enable_key_esc();
	enable_key_enter();
	enable_key_0();
	enable_key_1();
	enable_key_2();
	enable_key_3();
	enable_key_4();
	enable_key_5();
	enable_key_6();
	enable_key_7();
	enable_key_8();
	enable_key_9();
}

/********************************************************************
 * Function:	Block_PunchLED(void)								*
 * Definition:	Funcio per bloquejar l'estat del LED de punch.		*
 ********************************************************************/
void Block_PunchLED(void)
{
	flag_punch_led_blocked = 1;
}
/********************************************************************
 * Function:	Unblock_PunchLED(void)								*
 * Definition:	Funcio per desbloquejar l'estat del LED de punch.	*
 ********************************************************************/
void Unblock_PunchLED(void)
{
	flag_punch_led_blocked = 0;
}
