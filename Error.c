/********************************************************************
 * FileName:		Error.c											*
 * Dependencies:	Error.h											*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions del Guide User Interface.							*
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverte		10/12/18		Versio inicial 					*
 * 																	*
 ********************************************************************/
#include "main.h"


/***************** Variables locals *************************/

extern volatile type_State State;  
extern volatile type_error error_state; 

volatile type_holder_error_state holder_error_state; 
volatile type_cylinder_error_state cylinder_error_state;
volatile type_emergency_error_state emergency_error_state;
volatile type_start_error_state start_error_state;
volatile type_end_error_state end_error_state;
volatile type_door_error_state door_error_state; 
volatile type_curtain_error_state curtain_error_state;
volatile type_8_error_state error_8_state;
volatile type_9_error_state error_9_state;
volatile type_sensors_error_state error_sensors_state;

volatile char flag_already_shown_error = 0;
volatile char flag_already_shown_reset = 0; 
volatile char flag_show_error_blink = 0;
volatile char flag_error_end_reset_pulsed = 0; 
volatile char flag_error_end_start_pulsed = 0; 
volatile char flag_mainmenu_holder_ocurred = 0; 
volatile char flag_mainmenu_door_ocurred = 0; 
volatile char flag_mainmenu_emergency_ocurred = 0;
volatile char flag_wait_door_ocurred = 0;
volatile char flag_wait_holder_ocurred = 0;
volatile char flag_autotest_first_door = 0;
volatile char flag_autotest_first_holder = 0;
volatile char flag_autotest_first_emergency = 0;
volatile char flag_autotest_first_cylinder = 0;
volatile char flag_autotest_first_start = 0;
volatile char flag_autotest_first_end = 0;
volatile char flag_autotest_first_curtain = 0;
volatile char flag_autotest_first_8 = 0;
volatile char flag_autotest_first_9 = 0;
volatile char flag_end_error_necessary = 1;
volatile char flag_first_time_curtain_detected = 1;
volatile char flag_first_time_curtain_not_detected = 1;
volatile char flag_came_from_stopped_detected_state = 0;
volatile char flag_came_from_running_detected_state = 0;
volatile char flag_mainmenu_curtain_ocurred = 0;
volatile char flag_end_error_first_beep = 1;
volatile char flag_error_emergency_solved = 0;
volatile char flag_error_door_solved = 0;
volatile char flag_error_holder_solved = 0;
volatile char flag_error_cylinder_solved = 0;
volatile char flag_error_start_solved = 0;

volatile unsigned long counter_time_error_blink = 0; 
volatile unsigned long counter_time_error_beep = 0;

extern volatile unsigned char flag_key_not_funct;
extern volatile unsigned char flag_some_key_pressed;


/********************************************************************
 * Function:	Error_Holder_Change_State()							*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Holder_Change_State(void)
{
	if (PISW == 0)
	{
		holder_error_state = holder_DOWN;
	}
	else 
	{
		holder_error_state = holder_UP;
	}
}

/********************************************************************
 * Function:	Error_Cylinder_Change_State()						*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Cylinder_Change_State(void)
{
	if (CIDESSW == 1)
	{
		cylinder_error_state = cylinder_DOWN;
	}
	else 
	{
		cylinder_error_state = cylinder_UP;
	}
}

/********************************************************************
 * Function:	Error_Emergency_Change_State()						*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Emergency_Change_State(void)
{
	if (EMSTSW == 1)
	{
		emergency_error_state = emergency_ON;
	}
	else 
	{
		emergency_error_state = emergency_OFF;
	}
}

/********************************************************************
 * Function:	Error_Start_Change_State()							*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Start_Change_State(void)
{
	if (ZESW == 1)
	{
		start_error_state = start_ON;
	}
	else 
	{
	
		start_error_state = start_OFF;
	}
}

/********************************************************************
 * Function:	Error_End_Change_State()							*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_End_Change_State(void)
{
	if (FISW == 1)
	{
		end_error_state = end_ON;
	}
	else 
	{
		end_error_state = end_OFF;
	}
}

/********************************************************************
 * Function:	Error_Door_Change_State()							*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Door_Change_State(void)
{
	if (SEDOSW == 1)
	{
		door_error_state = door_OPEN;
	}
	else 
	{
		door_error_state = door_CLOSED;
	}
}

/********************************************************************
 * Function:	Error_Curtain_Change_State()						*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Curtain_Change_State(void)
{
	if (INPUT7 == 1)
	{
		curtain_error_state = curtain_DETECTED;
	}
	else 
	{
		curtain_error_state = curtain_NOT_DETECTED;
	}
}

/********************************************************************
 * Function:	Error_Input8_Change_State()						*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Input8_Change_State(void)
{
	if (INPUT8 == 1)
	{
		error_8_state = I8_DETECTED;
	}
	else 
	{
		error_8_state = I8_NOT_DETECTED;
	}
}

/********************************************************************
 * Function:	Error_Input9_Change_State()						*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Input9_Change_State(void)
{
	if (INPUT9 == 1)
	{
		error_9_state = I9_DETECTED;
	}
	else 
	{
		error_9_state = I9_NOT_DETECTED;
	}
}

/********************************************************************
 * Function:	Error_End_Reset_Pulsed()							*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_End_Reset_Pulsed(void)
{
	flag_error_end_reset_pulsed  = 1; 
}
/********************************************************************
 * Function:	Error_End_Reset_Pulsed()							*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_End_Start_Pulsed(void)
{
	flag_error_end_start_pulsed  = 1; 
}

/********************************************************************
 * Function:	Error_End_Reset_Necessary()							*
 * Definition:	Habilita o no que salti l'error de end.				*
 ********************************************************************/
void Error_End_Reset_Necessary(void)
{
	flag_end_error_necessary  = 0; 
}
/********************************************************************
 * Function:	Error_End_Set_Necessary()							*
 * Definition:	Habilita o no que salti l'error de end.				*
 ********************************************************************/
void Error_End_Set_Necessary(void)
{
	flag_end_error_necessary  = 1; 
}


/********************************************************************
 * Function:	Error_Change_State()								*
 * Definition:	Canvi de l'estat de l'error.						*
 ********************************************************************/
void Error_Change_State(type_error change_to_error)
{
	error_state = change_to_error;
	flag_already_shown_error = 0;
}

/********************************************************************
 * Function:	Error_tasks()										*
 * Definition:	Tasks d'error,			 							*
 ********************************************************************/
void Error_tasks(void)
{
	switch(State)
	{
		case PRESENTATION:
		{
			break;
		}
		case WAIT_PRESENTATION:
		{
			break;
		}
		case START :
		{
			break;
		}
		case POSITIONING:
		{
			switch (cylinder_error_state)
			{
				case cylinder_DOWN:
				{
					StopMotor();
					GUI_ChangeState(ERROR);
					Error_Change_State(error_cylinder);
					break;
				}
			}

			switch (emergency_error_state)
			{
				case emergency_ON:
				{
					StopMotor();
					GUI_ChangeState(ERROR);
					Error_Change_State(error_emergency);
					break;
				}
			}
			switch (end_error_state)
			{
				case end_ON:
				{
					StopMotor();
					GUI_ChangeState(ERROR);
					Error_Change_State(error_end);
					break;
				}
			}
			switch (door_error_state)
			{
				case door_OPEN:
				{
					StopMotor();
					GUI_ChangeState(ERROR);
					Error_Change_State(error_door);
					break;
				}
			}
			break;
		}
		case MAIN_MENU:
		{
			switch (door_error_state)
			{
				case door_OPEN:
				{
					Error_Change_State(error_door);
					disable_all_keys();
					if (flag_mainmenu_door_ocurred == 0)
					{
						GUI_ChangeState(MAIN_MENU);
						GUI_Change_MainMenu_Screen(screen_mainmenu_door_error);  
						GUI_DataActualization();
						flag_mainmenu_door_ocurred = 1;
						flag_key_not_funct = 1;
					}

					break;
				}
				case door_CLOSED:
				{
					if (flag_some_key_pressed == 1)
					{
						flag_some_key_pressed = 0;
						if (flag_mainmenu_door_ocurred == 1)			// Sols tornem a activar si previament el mateix error l'ha desactivat.
						{
							flag_key_not_funct = 0;
							flag_mainmenu_door_ocurred = 0; 
							GUI_ChangeState(MAIN_MENU);
							GUI_Change_MainMenu_Screen(screen_mainmenu_normal);  // Tornarem a la pantalla normal
							enable_all_keys();
							GUI_DataActualization();
						}
					}
					flag_some_key_pressed = 0;					
					break;
				}
			}
			switch (holder_error_state)
			{
				case holder_UP:
				{
					Error_Change_State(error_holder);
					GUI_MainMenu_Reset_Start();
					flag_mainmenu_holder_ocurred = 1;
					break;
				}
				case holder_DOWN:
				{
					if (flag_mainmenu_holder_ocurred == 1)
					{
						flag_mainmenu_holder_ocurred = 0;
						GUI_MainMenu_Set_Start();
					}
					break;
				}
			}
			switch (emergency_error_state)
			{
				case emergency_ON:
				{
					Error_Change_State(error_emergency);
					GUI_MainMenu_Reset_Start();
					flag_mainmenu_emergency_ocurred = 1;
					break;
				}
				case emergency_OFF:
				{
					if (flag_mainmenu_emergency_ocurred == 1)
					{
						flag_mainmenu_emergency_ocurred = 0;
						GUI_MainMenu_Set_Start();
					}
					break;
				}
			}
			switch (curtain_error_state)
			{
				case curtain_DETECTED:
				{
					Error_Change_State(error_curtain);
					GUI_MainMenu_Reset_Start();
					flag_mainmenu_curtain_ocurred = 1;
					break;
				}
				case curtain_NOT_DETECTED:
				{
					if (flag_mainmenu_curtain_ocurred == 1)			// Sols tornem a activar si previament el mateix error l'ha desactivat.SS
					{
						flag_mainmenu_curtain_ocurred = 0; 
						GUI_MainMenu_Set_Start();
					}
					break;
				}
			}
			break;
		}
		case RUN:
		{
			break;
		}
		case RUNNING:
		{
			switch (holder_error_state)
			{
				case holder_UP: 
				{
					StopMotor();
					GUI_ChangeState(ERROR);
					Error_Change_State(error_holder);
					break;
				}
			}
			switch (emergency_error_state)
			{
				case emergency_ON:
				{
					StopMotor();
					GUI_ChangeState(ERROR);
					Error_Change_State(error_emergency);
					break;
				}
			}
			switch (end_error_state)
			{				
				case end_ON:
				{
					if (flag_end_error_necessary == 1)
					{
						StopMotor();
						GUI_ChangeState(ERROR);
						Error_Change_State(error_end);
					}
					break;
				}
			}
			switch (door_error_state)
			{
				case door_OPEN:
				{
					StopMotor();
					GUI_ChangeState(ERROR);
					Error_Change_State(error_door);
					break;
				}
			}
			switch (start_error_state)
			{
				case start_ON: 
				{			
					StopMotor();
					GUI_ChangeState(ERROR);
					Error_Change_State(error_start);
					break;
				}
			}
			switch (curtain_error_state)
			{
				case curtain_DETECTED:
				{
					if ((flag_first_time_curtain_detected == 1)||(flag_came_from_stopped_detected_state == 1))
					{	
						flag_came_from_stopped_detected_state = 0;
						flag_first_time_curtain_detected = 0;
						flag_first_time_curtain_not_detected = 1;
						SetStopRunning();
						ResetManualStop();
						SetCurtainAdvice();
						disable_stopped_start();
						GUI_DataActualization();
						flag_came_from_running_detected_state = 1;
					}
					break;
				}

			}
			break;
		}
		case STOPPED:
		{
			switch (curtain_error_state)
			{
				case curtain_NOT_DETECTED:
				{
					if (flag_first_time_curtain_not_detected == 1)
					{
						BEEP = 0;
						flag_first_time_curtain_not_detected = 0;
						flag_first_time_curtain_detected = 1;
						ResetCurtainAdvice();
						
						enable_stopped_start();
						GUI_DataActualization();
					}
					break;
				}
				
				case curtain_DETECTED:
				{
					if ((flag_first_time_curtain_detected == 1)||(flag_came_from_running_detected_state == 1))
					{	
						flag_came_from_running_detected_state = 0;
						flag_first_time_curtain_detected = 0;
						flag_first_time_curtain_not_detected = 1;
						SetStopRunning();
						ResetManualStop();
						SetCurtainAdvice();
						disable_stopped_start();
						GUI_DataActualization();
						flag_came_from_stopped_detected_state = 1;
					}
					break;
				}
			}
			break;
		}
		case WAIT:
		{
			switch (holder_error_state)
			{
				case holder_UP:
				{
					Error_Change_State(error_holder);
					GUI_Wait_Reset_Start();
					flag_wait_holder_ocurred = 1;
					break;
				}
				case holder_DOWN:
				{
					if (flag_wait_holder_ocurred == 1)			// Sols tornem a activar si previament el mateix error l'ha desactivat.SS
					{
						flag_wait_holder_ocurred = 0; 
						GUI_Wait_Set_Start();
					}
					break;
				}
			}
			switch (emergency_error_state)
			{
				case emergency_ON:
				{
					GUI_ChangeState(ERROR);
					Error_Change_State(error_emergency);
					break;
				}
			}
			switch (door_error_state)
			{
				case door_OPEN:
				{
					Error_Change_State(error_door);
					GUI_Wait_Reset_Start();
					flag_wait_door_ocurred = 1;
					break;
				}
				case door_CLOSED:
				{
					if (flag_wait_door_ocurred == 1)			// Sols tornem a activar si previament el mateix error l'ha desactivat.SS
					{
						flag_wait_door_ocurred = 0; 
						GUI_Wait_Set_Start();
					}
					break;
				}
			}
			break;
		}
		case PASSWORD:
		{
			break;
		}
		case SUBMENU :
		{
			break;
		}
		case MOTOR_TEST:
		{
		}
		case AUTOTEST: 
		{
			switch (door_error_state)
			{
				case door_OPEN:
				{
					if (flag_autotest_first_door == 1)
					{
						flag_autotest_first_door = 0; 
						GUI_AutoTest_FirstTime_Set_Door();
						GUI_AutoTest_Set_Door();
					}
					break;
				}
				case door_CLOSED:
				{
					flag_autotest_first_door = 1;
					GUI_AutoTest_FirstTime_Set_Door();
					GUI_AutoTest_Reset_Door();
					break;
				}
			}
			switch (holder_error_state)
			{
				case holder_UP:
				{
					if (flag_autotest_first_holder == 1)
					{
						flag_autotest_first_holder = 0; 
						GUI_AutoTest_FirstTime_Set_Holder();
						GUI_AutoTest_Set_Holder();
					}
					break;
				}
				case holder_DOWN:
				{
					flag_autotest_first_holder = 1;
					GUI_AutoTest_FirstTime_Set_Holder();
					GUI_AutoTest_Reset_Holder();
					break;
				}
			}
			switch (emergency_error_state)
			{
				case emergency_ON:
				{
					if (flag_autotest_first_emergency == 1)
					{
						flag_autotest_first_emergency = 0; 
						GUI_AutoTest_FirstTime_Set_Emergency();
						GUI_AutoTest_Set_Emergency();
					}
					break;
				}
				case emergency_OFF:
				{
					flag_autotest_first_emergency = 1;
					GUI_AutoTest_FirstTime_Set_Emergency();
					GUI_AutoTest_Reset_Emergency();
					break;
				}
			}
			switch (cylinder_error_state)
			{
				case cylinder_DOWN: 
				{
					if (flag_autotest_first_cylinder == 1)
					{
						flag_autotest_first_cylinder = 0; 
						GUI_AutoTest_FirstTime_Set_Cylinder();
						GUI_AutoTest_Set_Cylinder();
					}
					break;
				}
				case cylinder_UP: 
				{
					flag_autotest_first_cylinder = 1;
					GUI_AutoTest_FirstTime_Set_Cylinder();
					GUI_AutoTest_Reset_Cylinder();
					break;
				}
			}
			switch (start_error_state)
			{
				case start_ON: 
				{
					if (flag_autotest_first_start == 1)
					{
						flag_autotest_first_start = 0; 
						GUI_AutoTest_FirstTime_Set_Start();
						GUI_AutoTest_Set_Start();
					}
					break;
				}
				case start_OFF: 
				{
					flag_autotest_first_start = 1;
					GUI_AutoTest_FirstTime_Set_Start();
					GUI_AutoTest_Reset_Start();
					break;
				}
			}
			switch (end_error_state)
			{
				case end_ON: 
				{
					if (flag_autotest_first_end == 1)
					{
						flag_autotest_first_end = 0; 
						GUI_AutoTest_FirstTime_Set_End();
						GUI_AutoTest_Set_End();
					}
					break;
				}
				case end_OFF: 
				{
					flag_autotest_first_end = 1;
					GUI_AutoTest_FirstTime_Set_End();
					GUI_AutoTest_Reset_End();
					break;
				}
			}
			switch (curtain_error_state)
			{
				case curtain_DETECTED:
				{
					if (flag_autotest_first_curtain == 1)
					{
						flag_autotest_first_curtain = 0;
						GUI_AutoTest_FirstTime_Set_Curtain();
						GUI_AutoTest_Set_Curtain();
					}
					break;
				}
				case curtain_NOT_DETECTED: 
				{
					flag_autotest_first_curtain = 1;
					GUI_AutoTest_FirstTime_Set_Curtain();
					GUI_AutoTest_Reset_Curtain();
					break;
				}
			}
			switch (error_8_state)
			{
				case I8_DETECTED:
				{
					if (flag_autotest_first_8 == 1)
					{
						flag_autotest_first_8 = 0;
						GUI_AutoTest_FirstTime_Set_8();
						GUI_AutoTest_Set_8();
					}
					break;
				}
				case I8_NOT_DETECTED: 
				{
					flag_autotest_first_8 = 1;
					GUI_AutoTest_FirstTime_Set_8();
					GUI_AutoTest_Reset_8();
					break;
				}
			}
			switch (error_9_state)
			{
				case I9_DETECTED:
				{
					if (flag_autotest_first_9 == 1)
					{
						flag_autotest_first_9 = 0;
						GUI_AutoTest_FirstTime_Set_9();
						GUI_AutoTest_Set_9();
					}
					break;
				}
				case I9_NOT_DETECTED: 
				{
					flag_autotest_first_9 = 1;
					GUI_AutoTest_FirstTime_Set_9();
					GUI_AutoTest_Reset_9();
					break;
				}
			}
			break;
		}
		case ERROR :
		{
			CloseTimer5();
			switch (error_state)
			{
				case error_holder: 
				{
					switch (holder_error_state)
					{
						case holder_UP: 
						{
							if (flag_already_shown_error == 0)
							{
								flag_already_shown_error = 1;
								error_show_particular_message();
								GUI_DataActualization();
								counter_time_error_blink = 0;
								BEEP = 1;
								counter_time_error_beep = 0;
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_error_holder_solved == 1)
							{
								flag_error_holder_solved = 0;
								clean_screen(TEXT);
								error_show_particular_message();
								GUI_DataActualization();
							}
							
							break;
						}
						case holder_DOWN: 
						{
							flag_error_holder_solved = 1;

							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}

							break;
						}
					}
					break;
				}
				case error_emergency: 
				{
					switch (emergency_error_state)
					{
						case emergency_ON: 
						{

							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (flag_already_shown_error == 0)
							{
								clean_screen(TEXT);
								flag_already_shown_error = 1;
								error_show_particular_message();
								GUI_DataActualization();
								BEEP = 1;
								counter_time_error_beep = 0;
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}

							counter_time_error_blink = 0;
							break;
						}
						case emergency_OFF: 
						{
							flag_error_emergency_solved = 1;
							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}
							break;
						}
					}
					break;
				}
				case error_start: 
				{
					switch (start_error_state)
					{
						case start_ON: 
						{
							if (flag_already_shown_error == 0)
							{
								clean_screen(TEXT);
								flag_already_shown_error = 1;
								error_show_particular_message();
								GUI_DataActualization();
								BEEP = 1;
								counter_time_error_beep = 0;
							}
							
							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}
							flag_already_shown_reset = 0;
							break;
						}
						case start_OFF: 
						{							
							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}
							flag_already_shown_reset = 0;
							break;
						}
					}
					break;
				}
				case error_end: 
				{
					switch(end_error_state)
					{
						case end_ON:
						{
							if (flag_already_shown_error == 0)
							{
								clean_screen(TEXT);
								flag_already_shown_error = 1;
								error_show_particular_message();
								GUI_DataActualization();
								BEEP = 1;
								counter_time_error_beep = 0;
							}

							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}
							// Polsat Reset, Movem a inicio
							if (flag_error_end_reset_pulsed == 1)
							{
								MOTOR_EN = MOTOR_ON;
								flag_error_end_reset_pulsed = 0;
								GUI_ChangeState(EXITING_END);
							}

							flag_already_shown_reset = 0;
							break;
						}

						case end_OFF:
						{
							if (flag_already_shown_error == 0)
							{
								clean_screen(TEXT);
								flag_already_shown_error = 1;
								error_show_particular_message();
								GUI_DataActualization();
								BEEP = 1;
								counter_time_error_beep = 0;
							}

							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}
							// Polsat Reset, Movem a inicio
							if (flag_error_end_reset_pulsed == 1)
							{
								MOTOR_EN = MOTOR_ON;
								flag_error_end_reset_pulsed = 0;
								GUI_ChangeState(EXITING_END);
							}

							if (flag_error_end_start_pulsed == 1)				// Un cop ha polsat start, es reinicia
							{
								flag_error_end_start_pulsed = 0; 
							//	StopMotor();
							//	GUI_ChangeState(START);
							}

							flag_already_shown_reset = 0;
							break;
						}
					}								

					break;
				}
				case error_door: 
				{
					switch (door_error_state)
					{
						case door_OPEN: 
						{
							if (flag_already_shown_error == 0)
							{
								flag_already_shown_error = 1;
								error_show_particular_message();
								GUI_DataActualization();
								BEEP = 1;
								counter_time_error_beep = 0;
							}
							
							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_error_door_solved == 1)
							{
								flag_error_door_solved = 0;
								clean_screen(TEXT);
								error_show_particular_message();
								GUI_DataActualization();
							}
							counter_time_error_blink = 0;
							break;
						}
						case door_CLOSED: 
						{
							flag_error_door_solved = 1;

							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}
						
							break;
						}
					}
					break;
				}
				case error_cylinder: 
				{	
					switch (cylinder_error_state)
					{
						case cylinder_DOWN: 
						{
							if (flag_already_shown_error == 0)
							{
								flag_already_shown_error = 1;
								error_show_particular_message();
								GUI_DataActualization();
								BEEP = 1;
								counter_time_error_beep = 0;
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_error_cylinder_solved == 1)
							{
								flag_error_cylinder_solved = 0;
								clean_screen(TEXT);
								error_show_particular_message();
								GUI_DataActualization();
							}
							counter_time_error_blink = 0;
							break;
						}
						case cylinder_UP: 
						{
							flag_error_cylinder_solved = 1;

							if (counter_time_error_blink >= 1000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
							{
								counter_time_error_blink = 0;
								GUI_DataActualization();
						
								if (flag_show_error_blink == 1)
								{
									flag_show_error_blink = 0;				// Si estava a 0 el posem a 1 i viceversa
								}
								else 
								{
									flag_show_error_blink = 1;
								}
							}

							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
								GUI_Error_Available_Reset();
							}

							if (flag_show_error_blink == 0)
							{
								error_show_particular_message();			// Mostrem error concret
							}
							else 
							{
								error_show_general_reset_message();			// Mostrem missatge de RESET
							}

							break;
						}
					}
					break;
				}
				case error_sensors:
				{
					switch (error_sensors_state)
					{
						case error_sensors_ON:
						{
							if (flag_already_shown_error == 0)
							{
								flag_already_shown_error = 1;
								error_show_particular_message();
								GUI_DataActualization();
								BEEP = 1;
								counter_time_error_beep = 0;
							}
							if (counter_time_error_beep >= 3000)
							{
								BEEP = 0;
							}

							break;
						}
					}
					break;
				}	
			}
			break;
		}
		case SAVE:
		{
			break;
		}
	}
}
