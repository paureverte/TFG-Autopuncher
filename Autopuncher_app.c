/********************************************************************
 * FileName:		Autopuncher_app.c								*
 * Dependencies:	Autopuncher_app.h							*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Control de la funcionalitat de l'autopuncher. 				*
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverte		23/10/18		Versio inicial 					*
 * 																	*
 ********************************************************************/
#include "main.h"

/***************** Variables locals *************************/
volatile type_State State;								// Variable per determinar l'estat en que es troba l'aparell
volatile type_operation_mode operation_mode;			// Variable del mode de funcionament de l'aparell.
volatile type_values_to_modify value_to_modify;
volatile type_password_numbering_to_modify password_numbering_to_modify = 0;
volatile type_submenu_parameter_to_modify submenu_parameter_to_modify = 0; 
volatile type_error error_state; 
volatile type_submenu2_parameter_to_modify submenu2_parameter_to_modify = 0;
volatile type_stop_values_to_modify stop_values_to_modify = 0;

volatile unsigned long value_to_apply = 0;
volatile unsigned long counter_time_welcome_screen = 0; 
volatile unsigned long temporal_value_modify = 0;
volatile unsigned long old_value_modify = 0;
volatile unsigned char flag_welcome_screen_time = 0; 
volatile unsigned char flag_positioning_completed = 0;
volatile unsigned char flag_prepositioning_completed = 0; 
volatile unsigned char flag_menu_modifying = 0; 
volatile unsigned char flag_menu_password = 0;
volatile unsigned char flag_menu_start = 0;
volatile unsigned char flag_main_menu_esc = 0; 
volatile unsigned char flag_main_menu_menu = 0;
volatile unsigned char flag_main_menu_ok = 0; 
volatile unsigned char flag_main_menu_number = 0;
volatile unsigned char flag_main_menu_belt = 0;
volatile unsigned char flag_main_menu_step = 0;
volatile unsigned char flag_main_menu_punch = 0;
volatile unsigned char flag_mainmenu_first_time_modifying = 1;
volatile unsigned char flag_exiting_end_completed = 0;
volatile unsigned char flag_password_menu = 0; 
volatile unsigned char flag_password_ok = 0; 
volatile unsigned char flag_password_number = 0;
volatile unsigned char flag_show_modifying_value = 0; 
volatile unsigned long counter_time_variable_modify = 0;
volatile unsigned long counter_time_enable_password = 0; 
volatile unsigned char flag_submenu_menu = 0; 
volatile unsigned char flag_submenu_esc = 0;
volatile unsigned char flag_submenu_number = 0;
volatile unsigned char flag_submenu_ok = 0; 
volatile unsigned char flag_submenu_3sok = 0;
volatile unsigned char flag_submenu_3smenu = 0;
volatile unsigned char flag_submenu_first_time_modifying = 1;
volatile unsigned char flag_submenu2_menu = 0; 
volatile unsigned char flag_submenu2_esc = 0; 
volatile unsigned char flag_submenu2_number = 0; 
volatile unsigned char flag_submenu2_ok = 0; 
volatile unsigned char flag_submenu2_3sok = 0;
volatile unsigned char flag_submenu2_start = 0;
volatile unsigned char flag_submenu2_3smenu = 0;
volatile unsigned char flag_submenu2_first_time_modifying = 1;
volatile unsigned char flag_autotest_motor_done = 0; 
volatile unsigned char flag_stopped_start = 0; 
volatile unsigned char flag_stopped_number = 0;
volatile unsigned char flag_stopped_esc = 0;
volatile unsigned char flag_stopped_ok = 0;
volatile unsigned char flag_stopped_belt = 0;
volatile unsigned char flag_stopped_step = 0;
volatile unsigned char flag_stopped_punch = 0;
volatile unsigned char flag_stopped_first_time_modifying = 1;
volatile unsigned char flag_disable_stopped_restart = 0;
volatile unsigned char flag_disable_stopped_modify;
volatile unsigned char flag_mainmenu_status_modifying = 0;
volatile unsigned char flag_submenu_status_modifying = 0;
volatile unsigned char flag_submenu2_status_modifying = 0;
volatile unsigned char flag_stopped_status_modifying = 0;
volatile unsigned char flag_end_movement_stop = 0;

/***************** Variables externes **********************/
extern unsigned long step;							
extern unsigned long step_MAX;
extern unsigned long step_MIN;
extern unsigned long wide; 						
extern unsigned long wide_MAX;				
extern unsigned long wide_MIN;
extern unsigned long MAX_WIDE;
extern unsigned long position;
extern unsigned long pressure;
extern volatile unsigned long pressure_MAX;
extern volatile unsigned long pressure_MIN;
extern unsigned long TON;
extern unsigned long TOFF;
extern unsigned long TOFF_MIN;
extern unsigned long TOFF_MAX;
extern unsigned long speed;
extern unsigned long speed_MAX;
extern unsigned long speed_MIN;
extern unsigned char bridge;
extern unsigned long reset_speed;
extern unsigned long accelerate_constant;
extern unsigned long accelerate_constant_MAX;
extern unsigned long accelerate_constant_MIN;
extern unsigned long decelerate_constant;
extern unsigned long decelerate_constant_MAX;
extern unsigned long decelerate_constant_MIN;
extern unsigned long distance_limit_to_start;
extern unsigned long submenu2_turns_number;
extern volatile unsigned long necessary_steps_for_change;
extern volatile unsigned char mainlanguage; 
extern volatile unsigned long zero_value;
extern volatile unsigned long end_limit;

extern unsigned char password_try_thousands;
extern unsigned char password_try_hundreds;
extern unsigned char password_try_tens;
extern unsigned char password_try_units; 

void presentation_set_flag_welcome(void);
void positioning_set_flag_completed(void);
void menu_password_set_flag(void);
void menu_start_set_flag(void);
void main_menu_flag_esc(void);
void main_menu_flag_ok(void);
void main_menu_flag_number(void);
void main_menu_flag_menu(void);
void main_menu_flag_belt(void);
void main_menu_flag_step(void);
void main_menu_flag_punch(void);
void password_flag_menu(void);
void password_flag_ok(void);
void password_flag_number(void);
void password_reset_entered_password(void);
void submenu_flag_menu(void);
void submenu_flag_esc(void);
void submenu_flag_number(void);
void submenu_flag_ok(void);
void submenu_flag_3sok(void);
void submenu2_flag_menu(void);
void submenu2_flag_esc(void);
void submenu2_flag_number(void);
void submenu2_flag_ok(void);
void submenu2_flag_3sok(void);
void submenu2_flag_start(void);
void submenu2_flag_3smenu(void);
void submenu_flag_3smenu(void);
void submenu_key_esc(void);
void submenu_key_number(void);
void autotest_motor_done(void);
void autotest_process_start(void);
void reset_main_password_allowed_timer(void);
void stopped_key_start(void);
void stopped_key_esc(void);
void stopped_key_ok(void);
void stopped_key_number(void);
void set_value_to_apply(unsigned long aux_value_to_apply);
void enable_stopped_start(void);
void disable_stopped_start(void);
void disable_stopped_modify(void);
void enable_stopped_modify(void);
void mainmenu_status_modifying(void);
void mainmenu_status_not_modifying(void);
void stopped_status_modifying(void);
void stopped_status_not_modifying(void);
void submenu_status_modifying(void);
void submenu_status_not_modifying(void);
void submenu2_status_modifying(void);
void submenu2_status_not_modifying(void);

/********************************************************************
 * Function:	Autopuncher_tasks(void)								*
 * Definition:	Estats del Autopuncher.								*
 ********************************************************************/
void Autopuncher_tasks(void)
{
	I2C_Tasks();	
	CAPManager_Tasks();
	TCA9545_Tasks();
	GUI_tasks();
	switch(State)
	{
		case PRESENTATION:
		{
			counter_time_welcome_screen = 0;			// Inicialitzem el valor del comptador de mostra de pantalla
			GUI_ChangeState(WAIT_PRESENTATION);				
			break;
		}
		case WAIT_PRESENTATION:
		{
			if (counter_time_welcome_screen >= welcome_wait_time)
			{
				counter_time_welcome_screen = 0; 
				presentation_set_flag_welcome();
			}
			if (flag_welcome_screen_time == 1)			// Si la interrupcio ha activat el flag de temps passat 
			{
				flag_welcome_screen_time = 0; 			// El posem a zero
				clean_screen(ALL);						// Borrem la pantalla 
				GUI_ChangeState(START);						
			}
			break;
		}
		case START:
		{
			motor_movement_reset();
			positioning_set_start();
			Reset_AAAB_Counter();						// Reset del counter de cops de AA AB.
			GUI_ChangeState(POSITIONING);
			break;
		}
		case POSITIONING:
		{
			positioning_tasks();
			
			if (flag_positioning_completed == 1)
			{
				flag_positioning_completed = 0;
				GUI_Change_MainMenu_Screen(screen_mainmenu_normal);
				GUI_ChangeState(MAIN_MENU);
			}
			break;
		}
		case EXITING_END:
		{

			exiting_end_tasks();	
			
			if (flag_exiting_end_completed == 1)
			{
				flag_exiting_end_completed = 0;
				GUI_ChangeState(START);
			}
		
			break;
		}
		case MAIN_MENU:
		{
			if (counter_time_variable_modify >= 500)		// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
			{
				counter_time_variable_modify = 0;
				GUI_DataActualization();
		
				if (flag_show_modifying_value == 1)
				{
					flag_show_modifying_value = 0;				// Si estava a 0 el posem a 1 i viceversa
					change_flag_blink_value();
				}
				else 
				{
					flag_show_modifying_value = 1;
					change_flag_blink_value();
				}
			}

			if (counter_time_enable_password >= 1000)		// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
			{
				counter_time_enable_password = 0;
				GUI_Set_Allow_Main3s();							// Passat un segon ja permetem entrar a password. Es fa per tal de no saltar directe quan es ve de submenu2.
			}

			if (flag_menu_password == 1)
			{
				flag_menu_password = 0;
				if (GUI_Get_MainMenuModifying() == 0)
				{
					GUI_ChangeState(PASSWORD);
				}	
			}

			if (flag_menu_start == 1)
			{
				flag_menu_start = 0; 
				if (GUI_Get_MainMenuModifying() == 0)
				{
					GUI_ChangeState(RUN);
				}	
			}

			if (flag_main_menu_belt == 1)
			{
				flag_main_menu_belt = 0; 
				if (GUI_Get_MainMenuModifying() == 0)
				{
					GUI_Modif_Parameter_Changed();
					value_to_modify = modify_wide; 
				}
			}

			if (flag_main_menu_step == 1)
			{
				flag_main_menu_step = 0; 
				if (GUI_Get_MainMenuModifying() == 0)
				{
					GUI_Modif_Parameter_Changed();
					value_to_modify = modify_step; 
				}
			}
			
			if (flag_main_menu_punch == 1)
			{
				flag_main_menu_punch = 0; 
				if (GUI_Get_MainMenuModifying() == 0)
				{
					GUI_Modif_Parameter_Changed();
					value_to_modify = modify_pressure; 
				}		
			}
			
			if (flag_main_menu_number == 1)
			{
				flag_main_menu_number = 0;
				GUI_Set_MainMenuModifying();
				mainmenu_status_modifying();

				switch (value_to_modify)
				{	
					case modify_wide:
					{
						if (flag_mainmenu_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_mainmenu_first_time_modifying = 0;
							old_value_modify = wide;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%1000;
						wide = temporal_value_modify;
						GUI_DataActualization();
						break;
					}
					case modify_step:
					{
						if (flag_mainmenu_first_time_modifying == 1)
						{
							flag_mainmenu_first_time_modifying = 0;
							old_value_modify = step;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%100;
						step = temporal_value_modify;
						GUI_DataActualization();
						break;
					}
					case modify_pressure:
					{
						if (flag_mainmenu_first_time_modifying == 1)
						{
							flag_mainmenu_first_time_modifying = 0;
							old_value_modify = pressure;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%100;							// Dividim entre 100 i ens quedem amb el resto. 
						pressure = temporal_value_modify;						
						GUI_DataActualization();
						break;
					}
					case modify_none:			//We don't want to be editing if we are at none.
					{
						mainmenu_status_not_modifying();
						GUI_Reset_MainMenuModifying();
						break;
					}
				}

			}
			if (flag_main_menu_esc == 1)
			{
				flag_main_menu_esc = 0;

				if (flag_mainmenu_status_modifying == 1)
				{
					flag_mainmenu_status_modifying = 0;
					switch (value_to_modify)
					{	
						case modify_wide:
						{
							wide = old_value_modify;
							flag_mainmenu_first_time_modifying = 1;
							break;
						}
						case modify_step:
						{
							step = old_value_modify;
							flag_mainmenu_first_time_modifying = 1;
							break;
						}
						case modify_pressure:
						{
							pressure = old_value_modify;
							flag_mainmenu_first_time_modifying = 1;						
							break;
						}
					}
					Flash_Write();
					temporal_value_modify = 0;
					old_value_modify = 0;
					value_to_apply = 0;
					clean_screen(TEXT);
					GUI_Reset_MainMenuModifying();
					mainmenu_status_not_modifying();
				}
				value_to_modify = modify_none; 
			}
			if (flag_main_menu_menu == 1)
			{
				flag_main_menu_menu = 0;
			}

			if (flag_main_menu_ok == 1)
			{
				flag_main_menu_ok = 0;
				if (flag_mainmenu_status_modifying == 1)  // Sols volem aplicar els efectes de OK i ESC en cas de que estem modificant el valor. Si no l'estem modificat, no volem que la tecla faci res. 
				{
					flag_mainmenu_status_modifying = 0;
					switch (value_to_modify)
					{	
						case modify_wide:
						{
							if (temporal_value_modify > MAX_WIDE)
							{
								temporal_value_modify = MAX_WIDE;
							}
							else if (temporal_value_modify < wide_MIN)
							{
								temporal_value_modify = wide_MIN;
							}
							wide = temporal_value_modify;
							flag_mainmenu_first_time_modifying = 1;
							break;
						}
						case modify_step:
						{
							if (temporal_value_modify > step_MAX)
							{
								temporal_value_modify = step_MAX;
							}
							else if (temporal_value_modify < step_MIN)
							{
								temporal_value_modify = step_MIN;
							}
							step = temporal_value_modify;
							flag_mainmenu_first_time_modifying = 1;
							break;
						}
						case modify_pressure:
						{
							if (temporal_value_modify > pressure_MAX)
							{
								temporal_value_modify = pressure_MAX;
							}
							else if (temporal_value_modify < pressure_MIN)
							{
								temporal_value_modify = pressure_MIN;
							}
							pressure = temporal_value_modify;	
							flag_mainmenu_first_time_modifying = 1;					
							break;
						}
					}
					Flash_Write();
					temporal_value_modify = 0;
					old_value_modify = 0;
					value_to_apply = 0;
					clean_screen(TEXT);
					GUI_Reset_MainMenuModifying();
					mainmenu_status_not_modifying();
				}
				value_to_modify = modify_none; 
			}

			break;
		}
		case RUN: 
		{
			motor_movement_start();							// Inicia el motor para el principio del troquelado
			GUI_ChangeState(RUNNING);
			break;
		}
		case RUNNING:
		{
			motor_movement_tasks();
			break;
		}
		case STOPPED:
		{
			if (flag_stopped_start == 1)
			{
				flag_stopped_start = 0;

				if (flag_end_movement_stop == 1)						// En cas de AB Closed i que estigui posicionant-se, mostrarem "POSICIONANDO"
				{
					flag_end_movement_stop = 0;
					clean_screen(TEXT);	
					GUI_ChangeState(WAIT);
				}
				else if (flag_disable_stopped_restart == 0)
				{
					clean_screen(TEXT);
					GUI_ChangeState(RUNNING);
				}
			}
			if (flag_stopped_esc == 1)
			{
				flag_stopped_esc = 0;

				if (flag_stopped_status_modifying == 1)
				{
					flag_stopped_status_modifying = 0;
					pressure = old_value_modify;
					flag_stopped_first_time_modifying = 1;
	
					Flash_Write();
					temporal_value_modify = 0;
					value_to_apply = 0;
					clean_screen(TEXT);
					GUI_DataActualization();
					stopped_status_not_modifying();
				}
				stop_values_to_modify = modify_stop_none;
				GUI_DataActualization();
				Unblock_PunchLED();
			}

			if (flag_stopped_punch == 1)
			{
				flag_stopped_punch = 0;
				stop_values_to_modify = modify_stop_pressure; 
				GUI_DataActualization();
				Block_PunchLED(); //Bloquear el LED del punch para que no se apague
			}

			if (flag_stopped_ok == 1)
			{
				flag_stopped_ok = 0;

				if (flag_stopped_status_modifying == 1)
				{
					flag_stopped_status_modifying = 0;
					if (temporal_value_modify > pressure_MAX)
					{
						temporal_value_modify = pressure_MAX;
					}
					else if (temporal_value_modify < pressure_MIN)
					{
						temporal_value_modify = pressure_MIN;
					}
					pressure = temporal_value_modify;
					flag_stopped_first_time_modifying = 1;
	
					Flash_Write();
					temporal_value_modify = 0;
					old_value_modify = 0;
					value_to_apply = 0;
					clean_screen(TEXT);
					GUI_DataActualization();
					stopped_status_not_modifying();
				}
				stop_values_to_modify = modify_stop_none;
				GUI_DataActualization();
				Unblock_PunchLED();
			}

			if (flag_stopped_number == 1)
			{
				flag_stopped_number = 0;

				if (flag_disable_stopped_modify == 0)
				{
					switch (stop_values_to_modify)
					{
						case modify_stop_pressure:
						{
							if (flag_stopped_first_time_modifying == 1)
							{
								flag_stopped_first_time_modifying = 0;
								old_value_modify = pressure;
							}
							temporal_value_modify = temporal_value_modify*10 + value_to_apply;
							temporal_value_modify = temporal_value_modify%100;							// Dividim entre 100 i ens quedem amb el resto. 
							pressure = temporal_value_modify;						
							GUI_DataActualization();
							stopped_status_modifying();
							break;
						}
						case modify_stop_none:
						{
							stopped_status_not_modifying();
							GUI_DataActualization();
							break;
						}
					}
				}			
			}

			break;
		}
		case WAIT:
		{
			enable_key_start();
			motor_movement_tasks();
			break;
		}
		case PASSWORD:
		{
			// Comptador per parpadeig de la variable.
			if (counter_time_variable_modify >= 500)		// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
			{
				counter_time_variable_modify = 0;
				GUI_DataActualization();
		
				if (flag_show_modifying_value == 1)
				{
					flag_show_modifying_value = 0;				// Si estava a 0 el posem a 1 i viceversa
					change_flag_blink_value();
				}
				else 
				{
					flag_show_modifying_value = 1;
					change_flag_blink_value();
				}
			}

			if (flag_password_number == 1)
			{	
				flag_password_number = 0; 
				
				switch (password_numbering_to_modify)
				{	
					case password_modify_thousands:
					{
						password_try_thousands = value_to_apply;
						if ((password_try_thousands == password_thousands_sub1) && (password_try_hundreds == password_hundreds_sub1) && (password_try_tens == password_tens_sub1) && (password_try_units == password_units_sub1))
						{
							GUI_ChangeState(SUBMENU);				
						}
						else if ((password_try_thousands == password_thousands_sub2) && (password_try_hundreds == password_hundreds_sub2) && (password_try_tens == password_tens_sub2) && (password_try_units == password_units_sub2))
						{
							GUI_ChangeState(SUBMENU2);
						}
						else if ((password_try_thousands == password_thousands_test) && (password_try_hundreds == password_hundreds_test) && (password_try_tens == password_tens_test) && (password_try_units == password_units_test))
						{
							clean_screen(TEXT);
							flag_autotest_motor_done = 1; // Al principi no volem que faci els moviments del motor. 
							GUI_Reset_From_Autotest();
							GUI_ChangeState(AUTOTEST);
							ResetFirstPressedKEYS();
						}
						else
						{
							password_numbering_to_modify = password_modify_hundreds;
							GUI_Password_Parameter_Changed();
						}
						GUI_DataActualization();
						
						break;
					}
					case password_modify_hundreds:
					{
						password_try_hundreds = value_to_apply;
						if ((password_try_thousands == password_thousands_sub1) && (password_try_hundreds == password_hundreds_sub1) && (password_try_tens == password_tens_sub1) && (password_try_units == password_units_sub1))
						{
							GUI_ChangeState(SUBMENU);				
						}
						else if ((password_try_thousands == password_thousands_sub2) && (password_try_hundreds == password_hundreds_sub2) && (password_try_tens == password_tens_sub2) && (password_try_units == password_units_sub2))
						{
							GUI_ChangeState(SUBMENU2);
						}
						else if ((password_try_thousands == password_thousands_test) && (password_try_hundreds == password_hundreds_test) && (password_try_tens == password_tens_test) && (password_try_units == password_units_test))
						{
							clean_screen(TEXT);
							flag_autotest_motor_done = 1; // Al principi no volem que faci els moviments del motor. 
							GUI_Reset_From_Autotest();
							GUI_ChangeState(AUTOTEST);
							ResetFirstPressedKEYS();
						}
						else
						{
							password_numbering_to_modify = password_modify_tens;
							GUI_Password_Parameter_Changed();
						}
						GUI_DataActualization();
						break;
					}
					case password_modify_tens:
					{
						password_try_tens = value_to_apply;
						if ((password_try_thousands == password_thousands_sub1) && (password_try_hundreds == password_hundreds_sub1) && (password_try_tens == password_tens_sub1) && (password_try_units == password_units_sub1))
						{
							GUI_ChangeState(SUBMENU);				
						}
						else if ((password_try_thousands == password_thousands_sub2) && (password_try_hundreds == password_hundreds_sub2) && (password_try_tens == password_tens_sub2) && (password_try_units == password_units_sub2))
						{
							GUI_ChangeState(SUBMENU2);
						}
						else if ((password_try_thousands == password_thousands_test) && (password_try_hundreds == password_hundreds_test) && (password_try_tens == password_tens_test) && (password_try_units == password_units_test))
						{
							clean_screen(TEXT);
							flag_autotest_motor_done = 1; // Al principi no volem que faci els moviments del motor. 
							GUI_Reset_From_Autotest();
							GUI_ChangeState(AUTOTEST);
							ResetFirstPressedKEYS();
						}
						else
						{
							password_numbering_to_modify = password_modify_units;
							GUI_Password_Parameter_Changed();
						}
						GUI_DataActualization();
						break;
					}
					case password_modify_units:
					{
						password_try_units = value_to_apply;
						if ((password_try_thousands == password_thousands_sub1) && (password_try_hundreds == password_hundreds_sub1) && (password_try_tens == password_tens_sub1) && (password_try_units == password_units_sub1))
						{
							GUI_ChangeState(SUBMENU);				
						}
						else if ((password_try_thousands == password_thousands_sub2) && (password_try_hundreds == password_hundreds_sub2) && (password_try_tens == password_tens_sub2) && (password_try_units == password_units_sub2))
						{
							GUI_ChangeState(SUBMENU2);
						}
						else if ((password_try_thousands == password_thousands_test) && (password_try_hundreds == password_hundreds_test) && (password_try_tens == password_tens_test) && (password_try_units == password_units_test))
						{
							clean_screen(TEXT);
							flag_autotest_motor_done = 1; // Al principi no volem que faci els moviments del motor. 
							GUI_Reset_From_Autotest();
							GUI_ChangeState(AUTOTEST);
							ResetFirstPressedKEYS();
						}
						else
						{
							password_numbering_to_modify = password_modify_thousands;
							GUI_Password_Parameter_Changed();
						}
						GUI_DataActualization();
						break;
					}
				}
			}
			
			if (flag_password_menu == 1)
			{
				flag_password_menu = 0;  
			}
		
			if (flag_password_ok == 1)
			{
				flag_password_ok = 0;
			}			

			break;
		}
		case SUBMENU :
		{
			if (counter_time_variable_modify >= 500)		// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
			{
				counter_time_variable_modify = 0;
				GUI_DataActualization();
		
				if (flag_show_modifying_value == 1)
				{
					flag_show_modifying_value = 0;				// Si estava a 0 el posem a 1 i viceversa
					change_flag_blink_value();
				}
				else 
				{
					flag_show_modifying_value = 1;
					change_flag_blink_value();
				}
			}

			if (flag_submenu_number == 1)
			{
				flag_submenu_number = 0;
				GUI_Set_SubmenuModifying();
				submenu_status_modifying();
				switch (submenu_parameter_to_modify)
				{	
					case submenu_bridge:
					{ 
						if (flag_submenu_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu_first_time_modifying = 0;
							old_value_modify = bridge;
						}
						if ((value_to_apply == 8)||(value_to_apply == 2))
						{
							if (bridge == 1)
							{
								bridge = 0; 
							}
							else 
							{
								bridge = 1; 
							}
							GUI_DataActualization();
						}
						break;
					}

					case submenu_max_width:
					{
						if (flag_submenu_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu_first_time_modifying = 0;
							old_value_modify = MAX_WIDE;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%1000;
						MAX_WIDE = temporal_value_modify;
						GUI_DataActualization();
						break;
					}
					case submenu_language: 
					{
						if (flag_submenu_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu_first_time_modifying = 0;
							old_value_modify = mainlanguage;
						}
						if (value_to_apply == 8)
						{
							mainlanguage++;
							if (mainlanguage >= LANGUAGE)
							{
								mainlanguage = 0; 
							}
						}
						else if (value_to_apply == 2)
						{
							mainlanguage--;
							
							if (mainlanguage >= LANGUAGE)
							{
								mainlanguage = LANGUAGE - 1; 
							}
						}
						
						clean_screen(TEXT);	
						print_software_version_submenu();
						modifying_submenu_text();
						GUI_DataActualization();
						break;
					}
					case submenu_zero_value:
					{	
						if (flag_submenu_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu_first_time_modifying = 0;
							old_value_modify = zero_value;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%1000;
						zero_value = temporal_value_modify;
						GUI_DataActualization();
						break;
					}
					case submenu_limit_value:
					{
						if (flag_submenu_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu_first_time_modifying = 0;
							old_value_modify = end_limit;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%1000;
						end_limit = temporal_value_modify;
						GUI_DataActualization();
						break;
					}
				}
			}
			
			if (flag_submenu_esc == 1)
			{	
				flag_submenu_esc = 0; 

				if (flag_submenu_status_modifying == 1)
				{
					flag_submenu_status_modifying = 0;
					switch (submenu_parameter_to_modify)
					{	
						case submenu_bridge:
						{ 
							bridge = old_value_modify;
							flag_submenu_first_time_modifying = 1;
							GUI_DataActualization();
							break;
						}
	
						case submenu_max_width:
						{
							MAX_WIDE = old_value_modify;
							flag_submenu_first_time_modifying = 1;
							GUI_DataActualization();
							break;
						}
						case submenu_language: 
						{
							mainlanguage = old_value_modify;
							flag_submenu_first_time_modifying = 1;						
							clean_screen(TEXT);	
							print_software_version_submenu();
							modifying_submenu_text();
							GUI_DataActualization();
							break;
						}
						case submenu_zero_value:
						{
							zero_value = old_value_modify;
							flag_submenu_first_time_modifying = 1;
							GUI_DataActualization();
							break;
						}
						case submenu_limit_value:
						{
							end_limit = old_value_modify;
							flag_submenu_first_time_modifying = 1;
							GUI_DataActualization();
							break;
						}
					}
					GUI_Reset_SubmenuModifying();
					temporal_value_modify = 0;
					old_value_modify = 0;
					value_to_apply = 0;
					submenu_status_not_modifying();
				}
			}

			if (flag_submenu_ok == 1)
			{
				flag_submenu_ok = 0;

				if (flag_submenu_status_modifying == 1)
				{
					flag_submenu_status_modifying = 0;
					switch (submenu_parameter_to_modify)
					{	
						case submenu_bridge:
						{ 
							bridge = bridge;
							flag_submenu_first_time_modifying = 1;
							GUI_DataActualization();
							break;
						}
	
						case submenu_max_width:
						{
							if (temporal_value_modify > wide_MAX)
							{
								temporal_value_modify = wide_MAX;
							}
							else if (temporal_value_modify < wide_MIN)
							{
								temporal_value_modify = wide_MIN;
							}
							MAX_WIDE = temporal_value_modify;
							flag_submenu_first_time_modifying = 1;
							GUI_DataActualization();
							break;
						}
						case submenu_language: 
						{
							mainlanguage = mainlanguage;
							flag_submenu_first_time_modifying = 1;						
							clean_screen(TEXT);	
							print_software_version_submenu();
							modifying_submenu_text();
							GUI_DataActualization();
							break;
						}
						case submenu_zero_value:
						{
							if (temporal_value_modify > 999)
							{
								temporal_value_modify = 999;
							}
							else if (temporal_value_modify < 50)
							{
								temporal_value_modify = 50;
							}
							zero_value = temporal_value_modify;
							flag_submenu_first_time_modifying = 1;
							GUI_DataActualization();
							break;
						}
						case submenu_limit_value:
						{
							if (temporal_value_modify > 999)
							{
								temporal_value_modify = 999;
							}
							else if (temporal_value_modify < 50)
							{
								temporal_value_modify = 50;
							}
							end_limit = temporal_value_modify;
							flag_submenu_first_time_modifying = 1;
							GUI_DataActualization();
							break;
						}
					}
					GUI_Reset_SubmenuModifying();
					temporal_value_modify = 0;
					old_value_modify = 0;
					value_to_apply = 0;
					submenu_status_not_modifying();
				}
			}

			if (flag_submenu_3sok == 1)
			{
				flag_submenu_3sok = 0;
				if (GUI_Get_SubmenuModifying() == 0)
				{
					Init_Values();													// Com no volem guardar els valors modificats, carreguem els valors previs a les modificacions
					GUI_Reset_Allow_Main3s();
					reset_main_password_allowed_timer();
					GUI_Change_MainMenu_Screen(screen_mainmenu_normal);
					GUI_ChangeState(MAIN_MENU);	
				}
			}	

			if(flag_submenu_menu == 1)
			{
				flag_submenu_menu = 0;
				if (GUI_Get_SubmenuModifying() == 0)
				{
					GUI_Submenu_Parameter_Changed();
					switch(submenu_parameter_to_modify)
					{
						case submenu_bridge: 
						{
							submenu_parameter_to_modify = submenu_max_width;
							break;
						}
																
						case submenu_max_width: 
						{
							submenu_parameter_to_modify = submenu_language;
							break;
						}
						
						case submenu_language: 
						{
							submenu_parameter_to_modify = submenu_zero_value;
							break;
						}
						
						case submenu_zero_value: 
						{
							submenu_parameter_to_modify = submenu_limit_value;
							break;
						}
						
						case submenu_limit_value: 
						{
							submenu_parameter_to_modify = submenu_bridge;
							break;
						}
	
					} 
				}			
			}

			if (flag_submenu_3smenu == 1)
			{
				flag_submenu_3smenu = 0;
				if (GUI_Get_SubmenuModifying() == 0)
				{
					Flash_Write();
					GUI_Reset_Allow_Main3s();
					reset_main_password_allowed_timer();
					GUI_Change_MainMenu_Screen(screen_mainmenu_normal);
					GUI_ChangeState(MAIN_MENU);	
				}
			}	

			break;
		}
		case SUBMENU2 :
		{
			if (counter_time_variable_modify >= 500)		// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
			{
				counter_time_variable_modify = 0;
				GUI_DataActualization();
		
				if (flag_show_modifying_value == 1)
				{
					flag_show_modifying_value = 0;				// Si estava a 0 el posem a 1 i viceversa
					change_flag_blink_value();
				}
				else 
				{
					flag_show_modifying_value = 1;
					change_flag_blink_value();
				}
			}

			if (flag_submenu2_number == 1)
			{	
				flag_submenu2_number = 0; 
				GUI_Set_Submenu2Modifying();

				switch (submenu2_parameter_to_modify)
				{	
					case submenu2_ton:
					{
						if (flag_submenu2_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu2_first_time_modifying = 0;
							old_value_modify = TON;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%1000;
						TON = temporal_value_modify;
						GUI_DataActualization();
						break;
					}

					case submenu2_toffmin:
					{
						if (flag_submenu2_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu2_first_time_modifying = 0;
							old_value_modify = TOFF_MIN;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%1000;
						TOFF_MIN = temporal_value_modify;
						GUI_DataActualization();
						break;
					}
					case submenu2_toffmax: 
					{
						if (flag_submenu2_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu2_first_time_modifying = 0;
							old_value_modify = TOFF_MAX;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%10000;
						TOFF_MAX = temporal_value_modify;
						GUI_DataActualization();
						break;
					}

					case submenu2_stepspdchange: 
					{
						if (flag_submenu2_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu2_first_time_modifying = 0;
							old_value_modify = necessary_steps_for_change;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%1000;
						necessary_steps_for_change = temporal_value_modify;
						GUI_DataActualization();
						break;
					}

					case submenu2_acel: 
					{
						if (flag_submenu2_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu2_first_time_modifying = 0;
							old_value_modify = accelerate_constant;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%10;
						accelerate_constant = temporal_value_modify;
						GUI_DataActualization();
						break;
					}

					case submenu2_decel: 
					{
						if (flag_submenu2_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu2_first_time_modifying = 0;
							old_value_modify = decelerate_constant;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%10;
						decelerate_constant = temporal_value_modify;
						GUI_DataActualization();
						break;
					}

					case submenu2_longini: 
					{
						if (flag_submenu2_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu2_first_time_modifying = 0;
							old_value_modify = distance_limit_to_start;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%10;
						distance_limit_to_start = temporal_value_modify;
						GUI_DataActualization();
						break;
					}

					case submenu2_turns: 
					{
						if (flag_submenu2_first_time_modifying == 1)  //This way, we'll only update the old value the first time you touch a number.
						{
							flag_submenu2_first_time_modifying = 0;
							old_value_modify = submenu2_turns_number;
						}
						temporal_value_modify = temporal_value_modify*10 + value_to_apply;
						temporal_value_modify = temporal_value_modify%10;
						submenu2_turns_number = temporal_value_modify;
						GUI_DataActualization();
						break;
					}	
				}
				submenu2_status_modifying();
			}
				
			if (flag_submenu2_menu == 1)
			{
				flag_submenu2_menu = 0;
				if (GUI_Get_Submenu2Modifying() == 0)
				{
					GUI_Submenu2_Parameter_Changed();
					switch (submenu2_parameter_to_modify)
					{	
						case submenu2_ton:
						{
							submenu2_parameter_to_modify = submenu2_toffmin;
							break;
						}
	
						case submenu2_toffmin:
						{
							submenu2_parameter_to_modify = submenu2_toffmax;
							break;
						}
						case submenu2_toffmax: 
						{
		
							submenu2_parameter_to_modify = submenu2_stepspdchange;
							break;
						}
	
						case submenu2_stepspdchange: 
						{
							submenu2_parameter_to_modify = submenu2_acel;
							break;
						}
	
						case submenu2_acel: 
						{
	
							submenu2_parameter_to_modify = submenu2_decel;
							break;
						}
	
						case submenu2_decel: 
						{
	
							submenu2_parameter_to_modify = submenu2_longini;
							break;
						}
	
						case submenu2_longini:
						{
							submenu2_parameter_to_modify = submenu2_turns;
							break;
						}
	
						case submenu2_turns: 
						{
							submenu2_parameter_to_modify = submenu2_ton;
							break;
						}	
					}
				}	
			}
		
			if (flag_submenu2_ok == 1)
			{
				flag_submenu2_ok = 0; 

				if (flag_submenu2_status_modifying == 1)
				{
					flag_submenu2_status_modifying = 0;
					switch (submenu2_parameter_to_modify)
					{	
						case submenu2_ton:
						{
						if (temporal_value_modify > 999)
						{
							temporal_value_modify = 999;
						}
						else if (temporal_value_modify < 5)
						{
							temporal_value_modify = 5;
						}
						TON = temporal_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
						}
	
						case submenu2_toffmin:
						{
						if (temporal_value_modify > 999)
						{
							temporal_value_modify = 999;
						}
						else if (temporal_value_modify < 5)
						{
							temporal_value_modify = 5;
						}
						TOFF_MIN = temporal_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
						}
						case submenu2_toffmax: 
						{
						if (temporal_value_modify > 9999)
						{
							temporal_value_modify = 9999;
						}
						else if (temporal_value_modify < 5)
						{
							temporal_value_modify = 5;
						}
						TOFF_MAX = temporal_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
						}
	
						case submenu2_stepspdchange: 
						{
						if (temporal_value_modify > 999)
						{
							temporal_value_modify = 999;
						}
						else if (temporal_value_modify < 1)
						{
							temporal_value_modify = 1;
						}
						necessary_steps_for_change = temporal_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
						}
	
						case submenu2_acel: 
						{
						if (temporal_value_modify > 9)
						{
							temporal_value_modify = 9;
						}
						else if (temporal_value_modify < 1)
						{
							temporal_value_modify = 1;
						}
						accelerate_constant = temporal_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
						}
	
						case submenu2_decel: 
						{
						if (temporal_value_modify > 9)
						{
							temporal_value_modify = 9;
						}
						else if (temporal_value_modify < 1)
						{
							temporal_value_modify = 1;
						}
						decelerate_constant = temporal_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
						}
	
						case submenu2_longini: 
						{
						if (temporal_value_modify > 20)
						{
							temporal_value_modify = 20;
						}
						else if (temporal_value_modify < 1)
						{
							temporal_value_modify = 1;
						}
						distance_limit_to_start = temporal_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
						}
	
						case submenu2_turns: 
						{
						if (temporal_value_modify > 10)
						{
							temporal_value_modify = 10;
						}
						else if (temporal_value_modify < 1)
						{
							temporal_value_modify = 1;
						}
						submenu2_turns_number = temporal_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
						}	
					}
					GUI_Reset_Submenu2Modifying();
					old_value_modify = 0;
					value_to_apply = 0;
					temporal_value_modify = 0;
					submenu2_status_not_modifying();
				}
			}	

			if (flag_submenu2_esc == 1)
			{	
				flag_submenu2_esc = 0; 

				if (flag_submenu2_status_modifying == 1)
				{
					flag_submenu2_status_modifying = 0;
					switch (submenu2_parameter_to_modify)
					{	
					case submenu2_ton:
					{
						TON = old_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
					}

					case submenu2_toffmin:
					{
						TOFF_MIN = old_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
					}
					case submenu2_toffmax: 
					{
						TOFF_MAX = old_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
					}

					case submenu2_stepspdchange: 
					{
						necessary_steps_for_change = old_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
					}

					case submenu2_acel: 
					{
						accelerate_constant = old_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
					}

					case submenu2_decel: 
					{
						decelerate_constant = old_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
					}

					case submenu2_longini: 
					{
						distance_limit_to_start = old_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
					}

					case submenu2_turns: 
					{
						submenu2_turns_number = old_value_modify;
						flag_submenu2_first_time_modifying = 1;
						GUI_DataActualization();
						break;
					}	
	
	
					}
					GUI_Reset_Submenu2Modifying();
					old_value_modify = 0;
					value_to_apply = 0;
					temporal_value_modify = 0;
					submenu2_status_not_modifying();
				}
			}	

			if (flag_submenu2_3sok == 1)
			{
				flag_submenu2_3sok = 0;
				if (GUI_Get_Submenu2Modifying() == 0)
				{
					Init_Values();													// Com no volem guardar els valors modificats, carreguem els valors previs a les modificacions
					GUI_Reset_Allow_Main3s();
					reset_main_password_allowed_timer();
					GUI_Change_MainMenu_Screen(screen_mainmenu_normal);
					GUI_ChangeState(MAIN_MENU);	
				}
			}

			if (flag_submenu2_3smenu == 1)
			{
				flag_submenu2_3smenu = 0;
				if (GUI_Get_Submenu2Modifying() == 0)
				{
					Flash_Write();
					GUI_Reset_Allow_Main3s();
					reset_main_password_allowed_timer();
					GUI_Change_MainMenu_Screen(screen_mainmenu_normal);
					GUI_ChangeState(MAIN_MENU);	
				}
			}

			if (flag_submenu2_start == 1)
			{
				flag_submenu2_start = 0; 
				if (GUI_Get_Submenu2Modifying() == 0)
				{
					autotest_mode_motor();
					motor_test_reset();
					motor_test_came_from_submenu2();
					GUI_ChangeState(MOTOR_TEST);
				}
			}

			break;
		}
		case AUTOTEST: 
		{
			if (flag_autotest_motor_done == 0)
			{
				motor_test_came_from_autotest();
				GUI_ChangeState(MOTOR_TEST);
			}
			break;
		}
		case MOTOR_TEST: 
		{
			motor_test_tasks();
			break;
		}
				
		case ERROR :
		{												// Si entrem en error, primer que res pararem el motor. 
			OUT_EVCIL = RISE;							// Pujem el cilindre en cas d'error. 
			break;
		}
		case SAVE:
		{
			break;
		}
	}
	Error_tasks();
	
}

void presentation_set_flag_welcome(void)
{
	flag_welcome_screen_time = 1;
}	

void positioning_set_flag_completed(void)
{
	flag_positioning_completed = 1;
}	

void menu_password_set_flag(void)
{
	flag_menu_password = 1;
}	
void menu_start_set_flag(void)
{
	flag_menu_start = 1;
}	

void main_menu_flag_esc(void)
{
	flag_main_menu_esc = 1;
}
void main_menu_flag_ok(void)
{
	flag_main_menu_ok = 1;
}

void main_menu_flag_number(void)
{
	flag_main_menu_number = 1;
}

void main_menu_flag_menu(void)
{
	flag_main_menu_menu = 1;
}

void main_menu_flag_belt(void)
{
	flag_main_menu_belt = 1;
}

void main_menu_flag_step(void)
{
	flag_main_menu_step = 1;
}

void main_menu_flag_punch(void)
{
	flag_main_menu_punch = 1;
}

void password_flag_menu(void)
{
	flag_password_menu = 1;
}

void password_flag_ok(void)
{
	flag_password_ok = 1;
}

void password_flag_number(void)
{
	flag_password_number = 1;
}

void password_reset_entered_password(void)
{
	password_numbering_to_modify = 0;								// Volem que quan inicie torni a començar pels milers 
	password_try_thousands = 0;
	password_try_hundreds = 0;
	password_try_tens = 0;
	password_try_units = 0; 
}

void submenu_flag_menu(void)
{
	flag_submenu_menu = 1;
}

void submenu_flag_esc(void)
{
	flag_submenu_esc = 1;
}

void submenu_flag_number(void)
{
	flag_submenu_number = 1;
}

void submenu_flag_ok(void)
{
	flag_submenu_ok = 1;
}

void submenu_flag_3sok(void)
{
	flag_submenu_3sok = 1;
}

void submenu2_flag_menu(void)
{
	flag_submenu2_menu = 1;
}

void submenu2_flag_esc(void)
{
	flag_submenu2_esc = 1;
}

void submenu2_flag_number(void)
{
	flag_submenu2_number = 1;
}

void submenu2_flag_ok(void)
{
	flag_submenu2_ok = 1;
}

void submenu2_flag_3sok(void)
{
	flag_submenu2_3sok = 1;
}

void submenu2_flag_start(void)
{
	flag_submenu2_start = 1;
}

void submenu2_flag_3smenu(void)
{
	flag_submenu2_3smenu = 1;
}

void submenu_flag_3smenu(void)
{
	flag_submenu_3smenu = 1;
}

void submenu_key_esc(void)
{
	flag_submenu_esc = 1;
}

void submenu_key_number(void)
{
	flag_submenu_number = 1;
}

void autotest_motor_done(void)
{
	flag_autotest_motor_done = 1;
}

void autotest_process_start(void)
{
	flag_autotest_motor_done = 0;
}

void reset_main_password_allowed_timer(void)
{
	counter_time_enable_password = 0;
}

void stopped_key_start(void)
{
	flag_stopped_start = 1;
}

void stopped_key_esc(void)
{
	flag_stopped_esc = 1;
}

void stopped_key_ok(void)
{
	flag_stopped_ok = 1;
}

void stopped_key_belt (void)
{
	flag_stopped_belt = 1;
}

void stopped_key_step (void)
{
	flag_stopped_step = 1;
}

void stopped_key_punch (void)
{
	flag_stopped_punch = 1;
}

void stopped_key_number(void)
{
	flag_stopped_number = 1;
}

void set_value_to_apply(unsigned long aux_value_to_apply)
{
	value_to_apply = aux_value_to_apply;
}

void enable_stopped_start(void)
{
	flag_disable_stopped_restart = 0;
}

void disable_stopped_start(void)
{
	flag_disable_stopped_restart = 1;
}

void disable_stopped_modify(void)
{
	flag_disable_stopped_modify = 1;
}

void enable_stopped_modify(void)
{
	flag_disable_stopped_modify = 0;
}

void mainmenu_status_modifying(void)
{
	flag_mainmenu_status_modifying = 1;
}

void mainmenu_status_not_modifying(void)
{
	flag_mainmenu_status_modifying = 0;
}

void stopped_status_modifying(void)
{
	flag_stopped_status_modifying = 1;
}

void stopped_status_not_modifying(void)
{
	flag_stopped_status_modifying = 0;
}

void submenu_status_modifying(void)
{
	flag_submenu_status_modifying = 1;
}

void submenu_status_not_modifying(void)
{
	flag_submenu_status_modifying = 0;
}

void submenu2_status_modifying(void)
{
	flag_submenu2_status_modifying = 1;
}

void submenu2_status_not_modifying(void)
{
	flag_submenu2_status_modifying = 0;
}

void exiting_end_completed (void)
{
	flag_exiting_end_completed = 1;
}
