/********************************************************************
 * FileName:		GUI.c											*
 * Dependencies:	GUI.h											*
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
 * P.Reverté		30/10/18		Versio inicial 					*
 * 																	*
 ********************************************************************/
// #include "main.h"
#include "GUI.h"


/***************** Variables locals *************************/

volatile unsigned char flag_gui_KEY_AA;
volatile unsigned char flag_gui_KEY_AB;
volatile unsigned char flag_gui_KEY_START;
volatile unsigned char flag_gui_KEY_STOP;
volatile unsigned char flag_gui_KEY_MENU;
volatile unsigned char flag_gui_KEY_MENU_3S;
volatile unsigned char flag_gui_KEY_ENTER; 
volatile unsigned char flag_gui_KEY_ENTER_3S;
volatile unsigned char flag_gui_KEY_RESET; 
volatile unsigned char flag_gui_KEY_AAAB;
volatile unsigned char flag_gui_KEY_SECRET;
volatile unsigned char flag_gui_KEY_NUMBER;
volatile unsigned char flag_gui_AAAB_mode = 0;
volatile unsigned char flag_gui_KEY_ESC;
volatile unsigned char flag_gui_KEY_BELT;
volatile unsigned char flag_gui_KEY_STEP;
volatile unsigned char flag_gui_KEY_PUNCH;


volatile unsigned char flag_gui_sec_holder = 0; 
volatile unsigned char flag_gui_sec_cilinder = 0;
volatile unsigned char flag_gui_sec_start = 0; 
volatile unsigned char flag_gui_sec_emergency = 0;
volatile unsigned char flag_gui_sec_end = 0; 
volatile unsigned char flag_gui_sec_door = 0;


volatile unsigned char flag_first_time_state; 
volatile unsigned char flag_data_updated;
volatile unsigned char flag_modifying_parameter_changed;
volatile unsigned char flag_GUI_Set_MainMenuModifying = 0;
volatile unsigned char flag_password_menu_locked;
volatile unsigned char flag_submenu_parameter_changed;
volatile unsigned char flag_GUI_Set_SubmenuModifying = 0;
volatile unsigned char flag_GUI_Set_Submenu2Modifying = 0;
volatile unsigned char flag_submenu2_parameter_changed;
volatile unsigned char flag_password_parameter_changed;
volatile unsigned char flag_error_reset_available = 0; 
volatile unsigned char flag_mainmenu_start_enabled = 1; 
volatile unsigned char flag_show_three_sec_message = 1; 
volatile unsigned char flag_GUI_error_start_detected = 0;
volatile unsigned char flag_curtain_detecting = 0;
volatile unsigned char flag_manual_stopped;
volatile unsigned char flag_mainmenu_door_status = 0;


volatile unsigned char flag_autotest_KEY_AA = 0; 
volatile unsigned char flag_autotest_KEY_AB = 0; 
volatile unsigned char flag_autotest_KEY_START = 0; 
volatile unsigned char flag_autotest_KEY_STOP = 0; 
volatile unsigned char flag_autotest_KEY_RESET = 0; 
volatile unsigned char flag_autotest_KEY_MENU = 0; 
volatile unsigned char flag_autotest_KEY_ESC = 0;
volatile unsigned char flag_autotest_KEY_NUMBER = 0;
volatile unsigned char flag_autotest_KEY_ENTER = 0; 
volatile unsigned char flag_autotest_key_value = 0;
volatile unsigned char flag_autotest_KEY_0 = 0;
volatile unsigned char flag_autotest_KEY_1 = 0;
volatile unsigned char flag_autotest_KEY_2 = 0;
volatile unsigned char flag_autotest_KEY_3 = 0;
volatile unsigned char flag_autotest_KEY_4 = 0;
volatile unsigned char flag_autotest_KEY_5 = 0;
volatile unsigned char flag_autotest_KEY_6 = 0;
volatile unsigned char flag_autotest_KEY_7 = 0;
volatile unsigned char flag_autotest_KEY_8 = 0;
volatile unsigned char flag_autotest_KEY_9 = 0;
volatile unsigned char flag_autotest_KEY_BELT = 0;
volatile unsigned char flag_autotest_KEY_STEP = 0;
volatile unsigned char flag_autotest_KEY_PUNCH = 0;

volatile unsigned char flag_first_time_test = 0;
volatile unsigned char flag_first_time_test_door = 0;
volatile unsigned char flag_first_time_test_emergency = 0;
volatile unsigned char flag_first_time_test_cylinder = 0;
volatile unsigned char flag_first_time_test_holder = 0;
volatile unsigned char flag_first_time_test_start = 0;
volatile unsigned char flag_first_time_test_end = 0;
volatile unsigned char flag_first_time_test_8 = 0;
volatile unsigned char flag_first_time_test_9 = 0;
volatile unsigned char flag_first_time_test_curtain = 0;
volatile unsigned char flag_GUI_first_time_3s_main_menu = 0;
volatile unsigned char flag_GUI_first_time_main_menu = 0; 
			
volatile unsigned char flag_GUI_autotest_door_error = 0;
volatile unsigned char flag_GUI_autotest_emergency_error = 0;
volatile unsigned char flag_GUI_autotest_cylinder_error = 0;
volatile unsigned char flag_GUI_autotest_holder_error = 0;
volatile unsigned char flag_GUI_autotest_start_error = 0;
volatile unsigned char flag_GUI_autotest_end_error = 0;		
volatile unsigned char flag_GUI_autotest_curtain_error = 0;
volatile unsigned char flag_GUI_autotest_8_error = 0;
volatile unsigned char flag_GUI_autotest_9_error = 0;
volatile unsigned char flag_autotest_already_pressed_reset = 0;
volatile unsigned char flag_autotest_already_pressed_aa = 0;
volatile unsigned char flag_autotest_already_pressed_ab = 0;
volatile unsigned char flag_autotest_already_pressed_stop = 0;
volatile unsigned char flag_autotest_already_pressed_start = 0;
volatile unsigned char flag_autotest_already_pressed_menu = 0;
volatile unsigned char flag_autotest_already_pressed_enter = 0;
volatile unsigned char flag_autotest_already_pressed_esc = 0;
volatile unsigned char flag_autotest_already_pressed_belt = 0;
volatile unsigned char flag_autotest_already_pressed_step = 0;
volatile unsigned char flag_autotest_already_pressed_punch = 0;
volatile unsigned char flag_autotest_already_pressed_0 = 0;
volatile unsigned char flag_autotest_already_pressed_1 = 0;
volatile unsigned char flag_autotest_already_pressed_2 = 0;
volatile unsigned char flag_autotest_already_pressed_3 = 0;
volatile unsigned char flag_autotest_already_pressed_4 = 0;
volatile unsigned char flag_autotest_already_pressed_5 = 0;
volatile unsigned char flag_autotest_already_pressed_6 = 0;
volatile unsigned char flag_autotest_already_pressed_7 = 0;
volatile unsigned char flag_autotest_already_pressed_8 = 0;
volatile unsigned char flag_autotest_already_pressed_9 = 0;

volatile unsigned long flag_show_autotest_key = 0;
volatile unsigned long counter_time_autotest_blink = 0;

volatile unsigned char contador_autotest_reset = 0;
volatile unsigned char contador_autotest_aa = 0;	
volatile unsigned char contador_autotest_ab = 0;
volatile unsigned char contador_autotest_stop = 0;
volatile unsigned char contador_autotest_start = 0;
volatile unsigned char contador_autotest_menu = 0;
volatile unsigned char contador_autotest_enter = 0;
volatile unsigned char contador_autotest_esc = 0;
volatile unsigned char contador_autotest_number = 0;
volatile unsigned char contador_autotest_belt = 0;
volatile unsigned char contador_autotest_step = 0;
volatile unsigned char contador_autotest_punch = 0;
volatile unsigned char contador_autotest_0 = 0;
volatile unsigned char contador_autotest_1 = 0;
volatile unsigned char contador_autotest_2 = 0;
volatile unsigned char contador_autotest_3 = 0;
volatile unsigned char contador_autotest_4 = 0;
volatile unsigned char contador_autotest_5 = 0;
volatile unsigned char contador_autotest_6 = 0;
volatile unsigned char contador_autotest_7 = 0;
volatile unsigned char contador_autotest_8 = 0;
volatile unsigned char contador_autotest_9 = 0;
volatile unsigned long counter_time_autotest_read = 0;

volatile unsigned char flag_GUI_wait_start_enabled = 1;
volatile unsigned char flag_GUI_ab_closed_positioning = 0;
volatile unsigned char flag_GUI_ab_closed_zero_positioning = 0;
volatile unsigned char flag_gui_end_movement_stopped = 0;

volatile unsigned long counter_time_three_sec = 0; 

volatile unsigned char flag_came_from_autotest = 0;
volatile unsigned char flag_change_door_main_message = 0;


volatile type_mainmenu_screen mainmenu_screen = 0;
volatile type_wait_screen wait_screen = 0;

/************************* Auxiliars ************************/

/***************** Variables externes ***********************/

extern unsigned char bridge; 
extern volatile unsigned char flag_came_from_final_movement_stop;
extern volatile unsigned char flag_end_movement_stop;
extern volatile unsigned char flag_at_autotest_led;
extern volatile type_acceleration_state acceleration_state; 
extern volatile type_operation_mode operation_mode;
extern volatile type_values_to_modify value_to_modify; 
extern volatile type_State State;  
extern volatile type_submenu_parameter_to_modify submenu_parameter_to_modify; 
extern volatile type_error error_state; 
extern volatile type_stop_values_to_modify stop_values_to_modify;
extern volatile type_motor_movement motor_movement_state;
extern volatile type_door_error_state door_error_state; 

/********************************************************************
 * Function:	GUI_Initialize()									*
 * Definition:	Inicialitzacio del GUI.								*
 ********************************************************************/
void GUI_Initialize(void)
{
	Keyboard_SetMyCallback(&GUI_Callback);
}

/********************************************************************
 * Function:	GUI_ChangeState()									*
 * Definition:	Canviar d'estat la màquina.							*
 ********************************************************************/
void GUI_ChangeState(type_State state)
{
	State = state;
	flag_first_time_state = 1; 
}
/********************************************************************
 * Function:	GUI_DataActualization()								*
 * Definition:	Flag s'han actualutzat les dades.					*
 ********************************************************************/
void GUI_DataActualization(void)
{
	flag_data_updated = 1; 
}

/********************************************************************
 * Function:	GUI_flag_keys_reset()								*
 * Definition:	Reseteja els flags de les tecles.					*
 ********************************************************************/
void GUI_flag_keys_reset(void)
{
	 flag_gui_KEY_AA = 0;
	 flag_gui_KEY_AB = 0;
	 flag_gui_KEY_START = 0;
	 flag_gui_KEY_STOP = 0;
	 flag_gui_KEY_RESET = 0;
	 flag_gui_KEY_MENU = 0;
	 flag_gui_KEY_MENU_3S = 0;
	 flag_gui_KEY_SECRET = 0;
	 flag_gui_KEY_AAAB = 0;
	 flag_gui_KEY_ENTER = 0;
	 flag_gui_KEY_ENTER_3S = 0;
	 flag_gui_KEY_NUMBER = 0;
	 flag_gui_KEY_ESC = 0;
	 flag_gui_KEY_BELT = 0;
	 flag_gui_KEY_STEP = 0;
	 flag_gui_KEY_PUNCH = 0;
}

/********************************************************************
 * Function:	GUI_Sec_Flag_Holder()								*
 * Definition:	Flag per mostrar per pantalla aquest error.			*
 ********************************************************************/
void GUI_Sec_Flag_Holder(void)
{
	flag_gui_sec_holder = 1; 
}
/********************************************************************
 * Function:	GUI_Sec_Flag_Cylinder()								*
 * Definition:	Flag per mostrar per pantalla aquest error.			*
 ********************************************************************/
void GUI_Sec_Flag_Cylinder(void)
{
	flag_gui_sec_cilinder = 1; 
}
/********************************************************************
 * Function:	GUI_Sec_Flag_Emergency()							*
 * Definition:	Flag per mostrar per pantalla aquest error.			*
 ********************************************************************/
void GUI_Sec_Flag_Emergency(void)
{
	flag_gui_sec_emergency = 1; 
}
/********************************************************************
 * Function:	GUI_Sec_Flag_Start()								*
 * Definition:	Flag per mostrar per pantalla aquest error.			*
 ********************************************************************/
void GUI_Sec_Flag_Start(void)
{
	flag_gui_sec_start = 1; 
}
/********************************************************************
 * Function:	GUI_Sec_Flag_End()									*
 * Definition:	Flag per mostrar per pantalla aquest error.			*
 ********************************************************************/
void GUI_Sec_Flag_End(void)
{
	flag_gui_sec_end = 1; 
}
/********************************************************************
 * Function:	GUI_Sec_Flag_Door()									*
 * Definition:	Flag per mostrar per pantalla aquest error.			*
 ********************************************************************/
void GUI_Sec_Flag_Door(void)
{
	flag_gui_sec_door = 1; 
}

/********************************************************************
 * Function:	GUI_Error_Available_Reset()							*
 * Definition:	Flag per activar el reset en pantalla d'error.		*
 ********************************************************************/
void GUI_Error_Available_Reset(void)
{
	flag_error_reset_available  = 1;
} 
/********************************************************************
 * Function:	GUI_Modif_Parameter_Changed()						*
 * Definition:	Flag s'ha canviat el parametre a modificar.			*
 ********************************************************************/
void GUI_Modif_Parameter_Changed(void)
{
	flag_modifying_parameter_changed = 1;
}

/********************************************************************
 * Function:	GUI_Password_Parameter_Changed()					*
 * Definition:	Flag s'ha canviat el parametre a modificar.			*
 ********************************************************************/
void GUI_Password_Parameter_Changed(void)
{
	flag_password_parameter_changed = 1;
}

/********************************************************************
 * Function:	GUI_Submenu_Parameter_Changed()						*
 * Definition:	Flag s'ha canviat el parametre a modificar.			*
 ********************************************************************/
void GUI_Submenu_Parameter_Changed(void)
{
	flag_submenu_parameter_changed = 1;
}
/********************************************************************
 * Function:	GUI_Submenu2_Parameter_Changed()					*
 * Definition:	Flag s'ha canviat el parametre a modificar.			*
 ********************************************************************/
void GUI_Submenu2_Parameter_Changed(void)
{
	flag_submenu2_parameter_changed = 1;
}

/********************************************************************
 * Function:	GUI_MainMenu_Reset_Start()							*
 * Definition:	Funcio que no permet el funcionament de la operacio.*
 ********************************************************************/
void GUI_MainMenu_Reset_Start(void)
{
	flag_mainmenu_start_enabled = 0; 
}

/********************************************************************
 * Function:	GUI_MainMenu_Set_Start()							*
 * Definition:	Funcio que permet el funcionament de la operacio.	*
 ********************************************************************/
void GUI_MainMenu_Set_Start(void)
{
	flag_mainmenu_start_enabled = 1; 
}

/********************************************************************
 * Function:	GUI_Wait_Reset_Start()							*
 * Definition:	Funcio que no permet el funcionament de la operacio.*
 ********************************************************************/
void GUI_Wait_Reset_Start(void)
{
	flag_GUI_wait_start_enabled = 0; 
}

/********************************************************************
 * Function:	GUI_Wait_Set_Start()								*
 * Definition:	Funcio que permet el funcionament de la operacio.	*
 ********************************************************************/
void GUI_Wait_Set_Start(void)
{
	flag_GUI_wait_start_enabled = 1; 
}

/********************************************************************
 * Function:	GUI_Change_MainMenu_Screen()						*
 * Definition:	Funcio per determinar quina pantalla del main volem.*
 ********************************************************************/
void GUI_Change_MainMenu_Screen(type_mainmenu_screen mainmenuscreento)
{
	 mainmenu_screen = mainmenuscreento;
}
	
/********************************************************************
 * Function:	GUI_Change_Wait_Screen()							*
 * Definition:	Funcio per determinar quina pantalla del main volem.*
 ********************************************************************/
void GUI_Change_Wait_Screen(type_wait_screen waitscreento)
{
	 wait_screen = waitscreento;
}			 	
/********************************************************************
 * Function:	GUI_Start_Detected()								*
 * Definition:	Detectat l'inici per canvi de pantalla en errors.	*
 ********************************************************************/
void GUI_Start_Detected(void)
{
	flag_GUI_error_start_detected = 1;
}

/********************************************************************
 * Function:	GUI_AutoTest_Set_Door()								*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_Door(void)
{
	flag_GUI_autotest_door_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_Door()							*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_Door(void)
{
	flag_GUI_autotest_door_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_Set_Emergency()						*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_Emergency(void)
{
	flag_GUI_autotest_emergency_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_Emergency()						*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_Emergency(void)
{
	flag_GUI_autotest_emergency_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_Set_Cylinder()							*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_Cylinder(void)
{
	flag_GUI_autotest_cylinder_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_Cylinder()						*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_Cylinder(void)
{
	flag_GUI_autotest_cylinder_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_Set_Holder()							*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_Holder(void)
{
	flag_GUI_autotest_holder_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_Holder()							*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_Holder(void)
{
	flag_GUI_autotest_holder_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_Set_Start()							*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_Start(void)
{
	flag_GUI_autotest_start_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_Start()							*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_Start(void)
{
	flag_GUI_autotest_start_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_Set_End()								*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_End(void)
{
	flag_GUI_autotest_end_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_End()							*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_End(void)
{
	flag_GUI_autotest_end_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_Set_Curtain()							*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_Curtain(void)
{
	flag_GUI_autotest_curtain_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_Curtain()						*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_Curtain(void)
{
	flag_GUI_autotest_curtain_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_Set_8()								*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_8(void)
{
	flag_GUI_autotest_8_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_8()								*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_8(void)
{
	flag_GUI_autotest_8_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_Set_9()								*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Set_9(void)
{
	flag_GUI_autotest_9_error = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_Reset_9()								*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_Reset_9(void)
{
	flag_GUI_autotest_9_error = 0;
}
/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set()						*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set(void)
{
	flag_first_time_test = 1;
}

/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_Holder()					*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_Holder(void)
{
	flag_first_time_test_holder = 1;
}

/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_Emergency()				*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_Emergency(void)
{
	flag_first_time_test_emergency = 1;
}

/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_Cylinder()				*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_Cylinder(void)
{
	flag_first_time_test_cylinder = 1;
}

/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_Door()					*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_Door(void)
{
	flag_first_time_test_door = 1;
}

/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_Start()					*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_Start(void)
{
	flag_first_time_test_start = 1;
}

/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_End()					*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_End(void)
{
	flag_first_time_test_end = 1;
}

/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_8()					*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_8(void)
{
	flag_first_time_test_8 = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_9()					*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_9(void)
{
	flag_first_time_test_9 = 1;
}
/********************************************************************
 * Function:	GUI_AutoTest_FirstTime_Set_Curtain()				*
 * Definition:	Canvi de pantalla en errors.						*
 ********************************************************************/
void GUI_AutoTest_FirstTime_Set_Curtain(void)
{
	flag_first_time_test_curtain = 1;
}

/********************************************************************
 * Function:	GUI_Set_From_Autotest(void)							*
 * Definition:	Flag per saber si es ve d'autotest.					*
 ********************************************************************/
void GUI_Set_From_Autotest(void)
{
	flag_came_from_autotest = 1;
}
/********************************************************************
 * Function:	GUI_Reset_From_Autotest(void)						*
 * Definition:	Flag per saber si es ve d'autotest.					*
 ********************************************************************/
void GUI_Reset_From_Autotest(void)
{
	flag_came_from_autotest = 0;
}
/********************************************************************
 * Function:	GUI_Reset_Allow_Main3s(void)						*
 * Definition:	Flag per no permetre saltar directe a password.		*
 ********************************************************************/
void GUI_Reset_Allow_Main3s(void)
{
	flag_GUI_first_time_main_menu = 1;
	flag_GUI_first_time_3s_main_menu = 1;
}
/********************************************************************
 * Function:	GUI_Set_Allow_Main3s(void)							*
 * Definition:	Flag per permetre saltar directe a password.		*
 ********************************************************************/
void GUI_Set_Allow_Main3s(void)
{
	flag_GUI_first_time_main_menu = 0; 
	flag_GUI_first_time_3s_main_menu = 0;
}  

/********************************************************************
 * Function:	GUI_AB_Closed_Positioning(void)						*
 * Definition:	Flag d'estar posicionant-se al mode AB Closed.		*
 ********************************************************************/
void GUI_AB_Closed_Positioning(void)
{
	flag_GUI_ab_closed_positioning = 1; 
}

/********************************************************************
 * Function:	GUI_AB_Closed_Ended_Positioning(void)				*
 * Definition:	Flag d'estar posicionant-se al mode AB Closed.		*
 ********************************************************************/
void GUI_AB_Closed_Ended_Positioning(void)
{
	flag_GUI_ab_closed_positioning = 0; 
}

/********************************************************************
 * Function:	GUI_AB_Closed_ZeroPoisitioning(void)				*
 * Definition:	Flag d'estar posicionant-se al mode AB Closed.		*
 ********************************************************************/
void GUI_AB_Closed_ZeroPoisitioning(void)
{
	flag_GUI_ab_closed_zero_positioning = 1; 
}

/********************************************************************
 * Function:	GUI_AB_Closed_Ended_ZeroPositioning(void)			*
 * Definition:	Flag d'estar posicionant-se al mode AB Closed.		*
 ********************************************************************/
void GUI_AB_Closed_Ended_ZeroPositioning(void)
{
	flag_GUI_ab_closed_zero_positioning = 0; 
}

/********************************************************************
 * Function:	GUI_Set_MainMenuModifying(void)						*
 * Definition:	Flag d'estar modificant a main menu.				*
 ********************************************************************/
void GUI_Set_MainMenuModifying(void)
{
	flag_GUI_Set_MainMenuModifying = 1; 
}

/********************************************************************
 * Function:	GUI_Reset_MainMenuModifying(void)					*
 * Definition:	Flag d'estar posicionant-se al mode AB Closed.		*
 ********************************************************************/
void GUI_Reset_MainMenuModifying(void)
{
	flag_GUI_Set_MainMenuModifying = 0; 
}

/********************************************************************
 * Function:	GUI_Get_MainMenuModifying(void)						*
 * Definition:	Flag d'estar posicionant-se al mode AB Closed.		*
 ********************************************************************/
unsigned char GUI_Get_MainMenuModifying(void)
{
	return flag_GUI_Set_MainMenuModifying; 
}

/********************************************************************
 * Function:	GUI_Set_SubmenuModifying(void)						*
 * Definition:	Flag d'estar modificant a submenu.	 				*
 ********************************************************************/
void GUI_Set_SubmenuModifying(void)
{
	flag_GUI_Set_SubmenuModifying = 1; 
}

/********************************************************************
 * Function:	GUI_Reset_SubmenuModifying(void)					*
 * Definition:	Flag d'estar modificant a submenu.  	       		*
 ********************************************************************/
void GUI_Reset_SubmenuModifying(void)
{
	flag_GUI_Set_SubmenuModifying = 0; 
}

/********************************************************************
 * Function:	GUI_Get_SubmenuModifying(void)						*
 * Definition:	Flag d'estar modificant a submenu.					*
 ********************************************************************/
unsigned char GUI_Get_SubmenuModifying(void)
{
	return flag_GUI_Set_SubmenuModifying; 
}

/********************************************************************
 * Function:	GUI_Set_Submenu2Modifying(void)						*
 * Definition:	Flag d'estar modificant a submenu2. 				*
 ********************************************************************/
void GUI_Set_Submenu2Modifying(void)
{
	flag_GUI_Set_Submenu2Modifying = 1; 
}

/********************************************************************
 * Function:	GUI_Reset_Submenu2Modifying(void)					*
 * Definition:	Flag d'estar modificant a submenu2. 				*
 ********************************************************************/
void GUI_Reset_Submenu2Modifying(void)
{
	flag_GUI_Set_Submenu2Modifying = 0; 
}	

/********************************************************************
 * Function:	ResetCurtainAdvice(void)							*
 * Definition:	Flag d'estar detectant a la cortina. 				*
 ********************************************************************/
void ResetCurtainAdvice(void)
{
	flag_curtain_detecting = 0; 
}

/********************************************************************
 * Function:	SetCurtainAdvice(void)								*
 * Definition:	Flag d'estar detectant a la cortina. 				*
 ********************************************************************/
void SetCurtainAdvice(void)
{
	flag_curtain_detecting = 1; 
}

/********************************************************************
 * Function:	SetManualStop(void)									*
 * Definition:	Flag d'STOP per manual. 				*
 ********************************************************************/
void SetManualStop(void)
{
	flag_manual_stopped = 1;
	enable_stopped_modify(); 
}
/********************************************************************
 * Function:	ResetManualStop(void)								*
 * Definition:	Flag d'STOP per no manual. 							*
 ********************************************************************/
void ResetManualStop(void)
{
	flag_manual_stopped = 0; 
	disable_stopped_modify();
}
/********************************************************************
 * Function:	ResetManualStop(void)								*
 * Definition:	Flag d'STOP per no manual. 							*
 ********************************************************************/
void SetEndManualStop(void)
{
	flag_manual_stopped = 2; 
	disable_stopped_modify();
}

/********************************************************************
 * Function:	ResetFirstPressedKEYS(void)								*
 * Definition:	Flag d'STOP per no manual. 							*
 ********************************************************************/
void ResetFirstPressedKEYS(void)
{
	flag_autotest_already_pressed_reset = 0;
	flag_autotest_already_pressed_aa = 0;
	flag_autotest_already_pressed_ab = 0;
	flag_autotest_already_pressed_stop = 0;
	flag_autotest_already_pressed_start = 0;
	flag_autotest_already_pressed_menu = 0;
	flag_autotest_already_pressed_enter = 0;
	flag_autotest_already_pressed_esc = 0;
	flag_autotest_already_pressed_belt = 0;
	flag_autotest_already_pressed_step = 0;
	flag_autotest_already_pressed_punch = 0;
	flag_autotest_already_pressed_0 = 0;
	flag_autotest_already_pressed_1 = 0;
	flag_autotest_already_pressed_2 = 0;
	flag_autotest_already_pressed_3 = 0;
	flag_autotest_already_pressed_4 = 0;
	flag_autotest_already_pressed_5 = 0;
	flag_autotest_already_pressed_6 = 0;
	flag_autotest_already_pressed_7 = 0;
	flag_autotest_already_pressed_8 = 0;
	flag_autotest_already_pressed_9 = 0;
}

/********************************************************************
 * Function:	GUI_Get_Submenu2Modifying(void)						*
 * Definition:	Flag d'estar modificant a submenu2. 				*
 ********************************************************************/
unsigned char GUI_Get_Submenu2Modifying(void)
{
	return flag_GUI_Set_Submenu2Modifying; 
}

/********************************************************************
 * Function:	GUI_Callback()										*
 * Definition:	En funcio del que se li ha passat pel callback 		*
 *				activa uns flags o uns altres.						*
 ********************************************************************/
void GUI_Callback(type_key key)
{

	switch(key)
	{
		case KEY_AA:
		{
			flag_gui_KEY_AA = 1;
			break;			
		}
		case KEY_AB:
		{
			flag_gui_KEY_AB = 1;
			break;
		}
		case KEY_START:
		{
			flag_gui_KEY_START = 1;
			break;
		}
		case KEY_STOP:
		{
			flag_gui_KEY_STOP = 1;
			break;
		}
		case KEY_RESET:
		{
			flag_gui_KEY_RESET = 1; 
			break;
		}
		case KEY_MENU:
		{
			flag_gui_KEY_MENU = 1;
			break;			
		}
		case KEY_MENU_3S:
		{
			flag_gui_KEY_MENU_3S = 1;
			break;
		}
		case KEY_AAAB:
		{
			flag_gui_KEY_AAAB = 1;
			break;
		}
		case KEY_ENTER:
		{
			flag_gui_KEY_ENTER = 1; 
			break;
		}
		case KEY_ENTER_3S: 
		{
			flag_gui_KEY_ENTER_3S = 1;
			break;
		}
		case KEY_ESC: 
		{
			flag_gui_KEY_ESC = 1;
			break;
		}

		case KEY_BELT:
		{
			flag_gui_KEY_BELT = 1;
			break;
		}

		case KEY_STEP:
		{
			flag_gui_KEY_STEP = 1;
			break;
		}

		case KEY_PUNCH:
		{
			flag_gui_KEY_PUNCH = 1;
			break;
		}
				
		case KEY_N1:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(1);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 1;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N2:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(2);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 2;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N3:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(3);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 3;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N4:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(4);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 4;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N5:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(5);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 5;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N6:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(6);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 6;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N7:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(7);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 7;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N8:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(8);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 8;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N9:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(9);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 9;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		case KEY_N0:
		{
			flag_gui_KEY_NUMBER = 1;
			set_value_to_apply(0);				// Enviem a autopuncher.c el valor de la tecla que hem polsat per que pugui transmetre-ho si estem modificant.
			flag_autotest_key_value = 0;		// Guardem valor per si estem a l'estat de autotest i el poguem mostrar
			break;
		}
		
	}

	GUI_ProcessKey();
}

/********************************************************************
 * Function:	GUI_ProcessKey()									*
 * Definition:	En funcio que comGUI_AutoTest_FirstTime_Set_Curtain la utilitat de la tecla 		*
 *				en l'estat en que es troba. 	 					*
 ********************************************************************/
void GUI_ProcessKey(void)
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
		case START:
		{
			break;
		}
		case POSITIONING:
		{
			break;
		}
		case MAIN_MENU:
		{
			LED_STOP = 1; 
			BEACON_STOP = 1;
			LED_START = 0; 
			BEACON_START = 0;

			if (flag_gui_KEY_AA == 1)
			{
				operation_mode = AA;
				GUI_ChangeState(START);
				Flash_Write();
			}
			if (flag_gui_KEY_AB == 1)
			{
				operation_mode = AB;
				GUI_ChangeState(START);
				Flash_Write();
			}
			if (flag_gui_KEY_AAAB == 1)
			{
				operation_mode = AA_AB;
				GUI_ChangeState(START);
				Flash_Write();
			}
			if (flag_gui_KEY_START == 1)
			{
				if (flag_mainmenu_start_enabled == 1)
				{
					menu_start_set_flag();
				}
				else 															// Casos de no poder començar a funcionar l'aparell per un error. Mostra durant uns segons. 
				{
					if (error_state == error_door)
					{
						GUI_Change_MainMenu_Screen(screen_mainmenu_door_error);
					}
					if (error_state == error_holder)
					{
						GUI_Change_MainMenu_Screen(screen_mainmenu_holder_error);
					}
					if (error_state == error_emergency)
					{
						GUI_Change_MainMenu_Screen(screen_mainmenu_emergency_error);
					}
					if (error_state == error_curtain)
					{
						GUI_Change_MainMenu_Screen(screen_mainmenu_curtain_error);
					}
					counter_time_three_sec = 0; 							// Inicialitzem el comptador
					flag_first_time_state = 1;						 		// Volem que faci la neteja inicial de la pantalla 
					flag_show_three_sec_message = 1; 						// Activem el flag perque mostri el missatge de l'error durant els 3 segons 
					GUI_DataActualization();
				}
			}
			if (flag_gui_KEY_MENU == 1)
			{
				if (flag_GUI_first_time_main_menu == 0)						// Evitem que, venint de submenu2, es salti directament a modifying. 
				{	
					main_menu_flag_menu();
				}
			}
			if (flag_gui_KEY_ENTER == 1)
			{
				main_menu_flag_ok();
			}
			if (flag_gui_KEY_BELT == 1)
			{
				main_menu_flag_belt();
			}
			if (flag_gui_KEY_STEP == 1)
			{
				main_menu_flag_step();
			}
			if (flag_gui_KEY_PUNCH == 1)
			{
				main_menu_flag_punch();
			}
			if (flag_gui_KEY_ESC == 1)
			{
				main_menu_flag_esc();
			}
			if (flag_gui_KEY_NUMBER == 1)
			{
				main_menu_flag_number();
			}	
			if (flag_gui_KEY_MENU_3S == 1)
			{
				if (flag_GUI_first_time_3s_main_menu == 0)
				{
					menu_password_set_flag();
					flag_password_menu_locked = 1;							// Al canviar de menu bloquejem la tecla menu, de forma que al estar mantenint el botó per canviar no afecti al seu funcionament. Sino, saltava directament a centenes. 
				}
			}
			if (flag_gui_KEY_RESET == 1)
			{
				GUI_ChangeState(START);
			}
			break;
		}
		case RUN:
		{
			break;
		}
		case RUNNING:
		{
			if (flag_gui_KEY_STOP == 1)
			{
				SetStopRunning();
				SetManualStop();
			}
			break;
		}
		case STOPPED: 
		{
			if (flag_gui_KEY_START == 1)
			{
				stopped_key_start();
			}
			if (flag_gui_KEY_ESC == 1)
			{
				stopped_key_esc();
			}
			if (flag_gui_KEY_ENTER == 1)
			{
				stopped_key_ok();
			}
			if (flag_gui_KEY_NUMBER == 1)
			{
				stopped_key_number();
			}
			if (flag_gui_KEY_RESET == 1)
			{
				GUI_ChangeState(START);
			}
			if (flag_gui_KEY_BELT == 1)
			{
				stopped_key_belt();
			}
			if (flag_gui_KEY_STEP == 1)
			{
				stopped_key_step();
			}
			if (flag_gui_KEY_PUNCH == 1)
			{
				stopped_key_punch();
			}
			break;
		}
		case WAIT:
		{
			if (flag_gui_KEY_START == 1)
			{
				if (flag_GUI_wait_start_enabled == 1)
				{
					motor_set_flag_start();
					GUI_ChangeState(RUNNING);
				}
				else 															// Casos de no poder començar a funcionar l'aparell per un error. Mostra durant uns segons. 
				{
					if (error_state == error_holder)
					{
						GUI_Change_Wait_Screen(screen_wait_holder_error);
					}

					if (error_state == error_door)
					{
						GUI_Change_Wait_Screen(screen_wait_door_error);
					}

					counter_time_three_sec = 0; 							// Inicialitzem el comptador
					flag_first_time_state = 1;						 		// Volem que faci la neteja inicial de la pantalla 
					flag_show_three_sec_message = 1; 						// Activem el flag perque mostri el missatge de l'error durant els 3 segons 
					GUI_DataActualization();
				}
			}
			if (flag_gui_KEY_RESET == 1)
			{
				GUI_ChangeState(START);
			}
			if (flag_gui_KEY_STOP == 1)
			{
				if (flag_gui_end_movement_stopped == 1)
				{
					flag_gui_end_movement_stopped = 0;
					flag_came_from_final_movement_stop = 1;
					flag_end_movement_stop = 1;
					clean_screen(TEXT);
					StopMotor();
					SetManualStop();
					motor_movement_state = FINAL_MOVEMENT_RETURN_B_CLOSED;
					GUI_ChangeState(STOPPED);
					GUI_DataActualization();

				}
			}
			break;
		}
		case PASSWORD:
		{
			if (flag_gui_KEY_NUMBER == 1)
			{
				flag_password_menu_locked = 0;
				password_flag_number();
			}	
			if (flag_gui_KEY_MENU == 1)
			{
				if(flag_password_menu_locked == 0)					// Quan s'haurà modificat un paràmetre, ja si es podrà usar el boto menu.
				{
					password_flag_menu();
				}
			}
			if (flag_gui_KEY_ENTER == 1)
			{
				password_flag_ok();
			}
			if (flag_gui_KEY_RESET == 1)
			{
				GUI_ChangeState(START);
			}
			break;
		}
		case SUBMENU:
		{
			
			if (flag_gui_KEY_MENU == 1)
			{
				submenu_flag_menu();
			}
			if (flag_gui_KEY_MENU_3S == 1)
			{
				submenu_flag_3smenu();
			}
			if (flag_gui_KEY_ENTER == 1)
			{
				submenu_flag_ok();
			}
			if (flag_gui_KEY_ESC == 1)
			{
				submenu_key_esc();
			}
			if (flag_gui_KEY_NUMBER == 1)
			{
				submenu_key_number();
			}
			if (flag_gui_KEY_ENTER_3S == 1)
			{
				submenu_flag_3sok();
			}
			if (flag_gui_KEY_RESET == 1)
			{
				GUI_ChangeState(START);
			}
			break;
		}
		case SUBMENU2:
		{
			if (flag_gui_KEY_MENU == 1)
			{
				submenu2_flag_menu();
			}
			if (flag_gui_KEY_MENU_3S == 1)
			{
				submenu2_flag_3smenu();
			}
			if (flag_gui_KEY_ENTER == 1)
			{
				submenu2_flag_ok();
			}
			if (flag_gui_KEY_ESC == 1)
			{
				submenu2_flag_esc();
			}
			if (flag_gui_KEY_NUMBER == 1)
			{
				submenu2_flag_number();
			}
			if (flag_gui_KEY_ENTER_3S == 1)
			{
				submenu2_flag_3sok();
			}
			if (flag_gui_KEY_RESET == 1)
			{
				GUI_ChangeState(START);
			}
			if (flag_gui_KEY_START == 1)
			{
				submenu2_flag_start();
			}
			break;
		}
		case AUTOTEST:
		{
			flag_at_autotest_led = 1; //We show that we are at autotest in order not to put our leds at 0 while keyboard_read

			if (flag_gui_KEY_AA == 1)
			{
				flag_autotest_already_pressed_aa = 1;
				flag_autotest_KEY_AA = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_aa == 0)
				{
					contador_autotest_aa = 1;
				}
				else 
				{
					contador_autotest_aa = 0;	
				}
			}

			if (flag_gui_KEY_AB == 1)
			{
				flag_autotest_already_pressed_ab = 1;
				flag_autotest_KEY_AB = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_ab == 0)
				{
					contador_autotest_ab = 1;
				}
				else 
				{
					contador_autotest_ab = 0;	
				}
			}

			if (flag_gui_KEY_START == 1)
			{
				flag_autotest_already_pressed_start = 1;
				flag_autotest_KEY_START = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_start == 0)
				{
					contador_autotest_start = 1;
				}
				else 
				{
					contador_autotest_start = 0;	
				}
			}
	
			if (flag_gui_KEY_STOP == 1)
			{
				flag_autotest_already_pressed_stop = 1;
				flag_autotest_KEY_STOP = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_stop == 0)
				{
					contador_autotest_stop = 1;
				}
				else 
				{
					contador_autotest_stop = 0;	
				}
			}

			if (flag_gui_KEY_RESET == 1)
			{
				flag_autotest_already_pressed_reset = 1;
				flag_autotest_KEY_RESET = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_reset == 0)
				{
					contador_autotest_reset = 1;
				}
				else 
				{
					contador_autotest_reset = 0;	
				}
			}

			if (flag_gui_KEY_ESC == 1)
			{
				flag_autotest_already_pressed_esc = 1;
				flag_autotest_KEY_ESC = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_esc == 0)
				{
					contador_autotest_esc = 1;
				}
				else 
				{
					contador_autotest_esc = 0;	
				}
			}

			if (flag_gui_KEY_NUMBER == 1)
			{
				flag_autotest_KEY_NUMBER = 1; 
				flag_first_time_test = 1;

				if (flag_autotest_key_value == 0)
				{	
					flag_autotest_already_pressed_0 = 1;
					flag_autotest_KEY_0 = 1;
					if (contador_autotest_0 == 0)
					{
						contador_autotest_0 = 1;
					}
					else 
					{
						contador_autotest_0 = 0;	
					}
				}
				else if (flag_autotest_key_value == 1)
				{	
					flag_autotest_already_pressed_1 = 1;
					flag_autotest_KEY_1 = 1;
					if (contador_autotest_1 == 0)
					{
						contador_autotest_1 = 1;
					}
					else 
					{
						contador_autotest_1 = 0;	
					}
				}
				else if (flag_autotest_key_value == 2)
				{	
					flag_autotest_already_pressed_2 = 1;
					flag_autotest_KEY_2 = 1;
					if (contador_autotest_2 == 0)
					{
						contador_autotest_2 = 1;
					}
					else 
					{
						contador_autotest_2 = 0;	
					}
				}
				else if (flag_autotest_key_value == 0)
				{	
					flag_autotest_already_pressed_0 = 1;
					flag_autotest_KEY_0 = 1;
					if (contador_autotest_0 == 0)
					{
						contador_autotest_0 = 1;
					}
					else 
					{
						contador_autotest_0 = 0;	
					}
				}
				else if (flag_autotest_key_value == 3)
				{	
					flag_autotest_already_pressed_3 = 1;
					flag_autotest_KEY_3 = 1;
					if (contador_autotest_3 == 0)
					{
						contador_autotest_3 = 1;
					}
					else 
					{
						contador_autotest_3 = 0;	
					}
				}
				else if (flag_autotest_key_value == 4)
				{	
					flag_autotest_already_pressed_4 = 1;
					flag_autotest_KEY_4 = 1;
					if (contador_autotest_4 == 0)
					{
						contador_autotest_4 = 1;
					}
					else 
					{
						contador_autotest_4 = 0;	
					}
				}
				else if (flag_autotest_key_value == 5)
				{	
					flag_autotest_already_pressed_5 = 1;
					flag_autotest_KEY_5 = 1;
					if (contador_autotest_5 == 0)
					{
						contador_autotest_5 = 1;
					}
					else 
					{
						contador_autotest_5 = 0;	
					}
				}
				else if (flag_autotest_key_value == 6)
				{	
					flag_autotest_already_pressed_6 = 1;
					flag_autotest_KEY_6 = 1;
					if (contador_autotest_6 == 0)
					{
						contador_autotest_6 = 1;
					}
					else 
					{
						contador_autotest_6 = 0;	
					}
				}
				else if (flag_autotest_key_value == 7)
				{	
					flag_autotest_already_pressed_7 = 1;
					flag_autotest_KEY_7 = 1;
					if (contador_autotest_7 == 0)
					{
						contador_autotest_7 = 1;
					}
					else 
					{
						contador_autotest_7 = 0;	
					}
				}
				else if (flag_autotest_key_value == 8)
				{	
					flag_autotest_already_pressed_8 = 1;
					flag_autotest_KEY_8 = 1;
					if (contador_autotest_8 == 0)
					{
						contador_autotest_8 = 1;
					}
					else 
					{
						contador_autotest_8 = 0;	
					}
				}
				else if (flag_autotest_key_value == 9)
				{	
					flag_autotest_already_pressed_9 = 1;
					flag_autotest_KEY_9 = 1;
					if (contador_autotest_9 == 0)
					{
						contador_autotest_9 = 1;
					}
					else 
					{
						contador_autotest_9 = 0;	
					}
				}
			}
			if (flag_gui_KEY_MENU == 1)
			{
				flag_autotest_already_pressed_menu = 1;
				flag_autotest_KEY_MENU = 1;
				flag_first_time_test = 1; 
				if (contador_autotest_menu == 0)
				{
					contador_autotest_menu = 1;
				}
				else 
				{
					contador_autotest_menu = 0;	
				}
			}
		
			if (flag_gui_KEY_ENTER == 1)
			{
				flag_autotest_already_pressed_enter = 1;
				flag_autotest_KEY_ENTER = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_enter == 0)
				{
					contador_autotest_enter = 1;
				}
				else 
				{
					contador_autotest_enter = 0;	
				}
			}

			if (flag_gui_KEY_BELT == 1)
			{
				flag_autotest_already_pressed_belt = 1;
				flag_autotest_KEY_BELT = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_belt == 0)
				{
					contador_autotest_belt = 1;
				}
				else 
				{
					contador_autotest_belt = 0;	
				}
			}
			if (flag_gui_KEY_STEP == 1)
			{
				flag_autotest_already_pressed_step = 1;
				flag_autotest_KEY_STEP = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_step == 0)
				{
					contador_autotest_step = 1;
				}
				else 
				{
					contador_autotest_step = 0;	
				}
			}
			if (flag_gui_KEY_PUNCH == 1)
			{
				flag_autotest_already_pressed_punch = 1;
				flag_autotest_KEY_PUNCH = 1; 
				flag_first_time_test = 1;
				if (contador_autotest_punch == 0)
				{
					contador_autotest_punch = 1;
				}
				else 
				{
					contador_autotest_punch = 0;	
				}
			}
			break;

		}
		case ERROR:
		{
			if (flag_gui_KEY_RESET == 1)
			{
				if (flag_error_reset_available == 1)
				{
					if (State == ERROR && error_state == error_end)
					{
						Error_End_Reset_Pulsed();
					}
					
					else
					{
						flag_error_reset_available = 0; 
						GUI_ChangeState(START);
					}
				}
			}
			break;
		}
	}
	GUI_flag_keys_reset();								// Fem reset de tots els flags de tecles un cop ja hem llegit les que ens interessen.

}
/********************************************************************
 * Function:	GUI_tasks(void)										*
 * Definition:	Estats del GUI. 									*
 ********************************************************************/
void GUI_tasks(void)
{
	switch(State)
	{
		case PRESENTATION:
		{
			//disable_all_keys();						// Here we don't want any key to funct
			LED_AA = 0;								// LED a 0
			LED_AB = 0;
			LED_START = 0;
			LED_STOP = 0;
			BEACON_STOP = 0;
			BEACON_START = 0;
			weclome_screen();						// Dibuixa pantalla benvinguda
			print_software_version_presentation();
			break;
		}
		case WAIT_PRESENTATION:
		{
			if (flag_first_time_state == 1)
			{
				flag_first_time_state = 0; 
			}
			else
			{
				if (flag_data_updated == 1)
				{
					flag_data_updated = 0;	
				}
			}
			break;
		}
		case START:
		{	
			//disable_all_keys();
			//enable_key_reset();
			if (flag_first_time_state == 1)
			{	
				LED_AA = 0;									
				LED_AB = 0;
				LED_STOP = 0;
				BEACON_STOP = 0;
				flag_first_time_state = 0; 
			}
			else
			{
				if (flag_data_updated == 1)
				{
					flag_data_updated = 0;
				}
			}
			break;
		}
		case POSITIONING:
		{
			if (flag_first_time_state == 1)				// Primer cop que entro
			{	
				screen_clean_submenu_bars();
				screen_clean_modifying_bars();			// Per si vinc de modificacio, elimino les possibles barres d'edicio
				clean_screen(TEXT);
				GUI_DataActualization();				// Activo el flag per actualitzar pantalla
				flag_first_time_state = 0; 				// Desactivo el flag de primer cop
			}
			else
			{
				if (flag_data_updated == 1)			// Si esta activat el flag d'haverse actualitzat alguna dada
				{	
					flag_data_updated = 0;			// Desactivem el flag
					positioning_screen();				// Refresquem la pantalla per mostrar les dades noves								
				}
				LED_START = 1; 
				BEACON_START = 1;							
			}			
			break;
		}
		case MAIN_MENU:
		{
			//enable_all_keys();							// Here we'll need every key
			if (flag_first_time_state == 1)				
			{
				GUI_DataActualization();
				screen_clean_submenu_bars();
				screen_clean_password_bars();
				screen_clean_submenu2_bars();
				clean_screen(TEXT);						// Elimino text per si vinc de posicionando
				flag_first_time_state = 0; 
			}
			else
			{
				if (mainmenu_screen == screen_mainmenu_normal)
				{
					if (flag_data_updated == 1)
					{
						enable_all_keys();
						flag_data_updated = 0;
						main_menu_screen();				// Mostro pantalla de menu principal
						modifying_values_screen();				// Mostrar el valor d'aquesta variable.
						modifying_lines_screen();
					}
					
					if (flag_modifying_parameter_changed == 1)
					{
						flag_modifying_parameter_changed = 0; 	// Si s'ha canviat de variable a modificar, canviarà la ratlla. 
						clean_modifying_lines_screen();
					}
					
					if (operation_mode == AA)				// Depenent del funcionament mostrare un LED activat o un altre
					{
						LED_AA = 1; 
						LED_AB = 0;
					}
					
					else if (operation_mode == AB)
					{
						LED_AA = 0;
						LED_AB = 1;				
					}
					
					else if (operation_mode == AA_AB)
					{
						LED_AA = 1;
						LED_AB = 1;
					}
					
					if (value_to_modify == modify_wide)				//Depenent del valor que es modifica, es manté un LED a 1 o a 0.
					{
						LED_BELT = 1;
						LED_STEP = 0;
						LED_PUNCH = 0;
					}
					
					else if (value_to_modify == modify_step)
					{
						LED_BELT = 0;
						LED_STEP = 1;
						LED_PUNCH = 0;
					}
					
					else if (value_to_modify == modify_pressure)
					{
						LED_BELT = 0;
						LED_STEP = 0;
						LED_PUNCH = 1;
					}
					
					else if (value_to_modify == modify_none)
					{
						LED_BELT = 0;
						LED_STEP = 0;
						LED_PUNCH = 0;
					}

					LED_START = 0;
					LED_STOP = 1; 
					BEACON_STOP = 1;
					BEACON_START = 0;
				}
				else if (mainmenu_screen == screen_mainmenu_door_error)
				{
					if (door_error_state == door_OPEN)
					{
						if (counter_time_three_sec>= 3000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
						{
							counter_time_three_sec = 0;
							//GUI_DataActualization();
	
							if (flag_show_three_sec_message == 1)
							{
								flag_change_door_main_message = 1;
								flag_show_three_sec_message = 0;				// Si estava a 0 el posem a 1 i viceversa
							}	

							else if (flag_show_three_sec_message == 0)
							{
								flag_change_door_main_message = 1;
								flag_show_three_sec_message = 1;				// Si estava a 0 el posem a 1 i viceversa
							}
						}

						if (flag_data_updated == 1)
						{
							if (flag_change_door_main_message == 1)
							{
								flag_change_door_main_message = 0;
								clean_screen(TEXT);
							}
							
							flag_data_updated = 0;
							disable_all_keys();
							clean_modifying_lines_screen();
							if (flag_show_three_sec_message == 0)
							{
								error_show_door_message();
							}
							else if (flag_show_three_sec_message == 1)
							{
								door_remember_screen();				// Mostro pantalla de menu principal amb recordatori de porta
							}
							LED_AA = 0;
							LED_AB = 0;
							LED_BELT = 0;
							LED_STEP = 0;
							LED_PUNCH = 0;
							LED_START = 0;
							LED_STOP = 0;
							BEACON_STOP = 0;
							BEACON_START = 0;
						}
					}
					else if (door_error_state == door_CLOSED)
					{
						if (flag_data_updated == 1)
						{
							flag_data_updated = 0;
							disable_all_keys();
							clean_modifying_lines_screen();
							door_remember_screen();				// Mostro pantalla de menu principal amb recordatori de porta
							LED_AA = 0;
							LED_AB = 0;
							LED_BELT = 0;
							LED_STEP = 0;
							LED_PUNCH = 0;
							LED_START = 0;
							LED_STOP = 0;
							BEACON_STOP = 0;
							BEACON_START = 0;
							flag_change_door_main_message = 1;
							flag_show_three_sec_message = 0;
							counter_time_three_sec = 0;
						}
					}
				}
				else if (mainmenu_screen == screen_mainmenu_holder_error)
				{
					clean_modifying_lines_screen();
					if (counter_time_three_sec>= 3000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
					{
						counter_time_three_sec = 0;
						GUI_DataActualization();

						if (flag_show_three_sec_message == 1)
						{
							flag_show_three_sec_message = 0;				// Si estava a 0 el posem a 1 i viceversa
						}	
					}

					if (flag_show_three_sec_message == 1)
					{
						if (flag_data_updated == 1)
						{
							BEEP = 1;
							flag_data_updated = 0;
							error_show_holder_message();
						}
					}
					else
					{
						BEEP = 0;
						GUI_Change_MainMenu_Screen(screen_mainmenu_normal);  // Tornarem a la pantalla normal
						flag_first_time_state = 1; 							// Volem que al tornar es faci neteja de la pantalla
					}
				}
				else if (mainmenu_screen == screen_mainmenu_emergency_error)
				{
					clean_modifying_lines_screen();
					if (counter_time_three_sec>= 3000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
					{
						counter_time_three_sec = 0;
						GUI_DataActualization();

						if (flag_show_three_sec_message == 1)
						{
							flag_show_three_sec_message = 0;				// Si estava a 0 el posem a 1 i viceversa
						}	
					}

					if (flag_show_three_sec_message == 1)
					{
						if (flag_data_updated == 1)
						{
							BEEP = 1;
							flag_data_updated = 0;
							error_show_emergency_message();
						}
					}
					else
					{
						BEEP = 0;
						GUI_Change_MainMenu_Screen(screen_mainmenu_normal);  // Tornarem a la pantalla normal
						flag_first_time_state = 1; 							// Volem que al tornar es faci neteja de la pantalla
					}
				}
				else if (mainmenu_screen == screen_mainmenu_curtain_error)
				{
					clean_modifying_lines_screen();
					if (counter_time_three_sec>= 3000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
					{
						counter_time_three_sec = 0;
						GUI_DataActualization();

						if (flag_show_three_sec_message == 1)
						{
							flag_show_three_sec_message = 0;				// Si estava a 0 el posem a 1 i viceversa
						}	
					}

					if (flag_show_three_sec_message == 1)
					{
						if (flag_data_updated == 1)
						{
							BEEP = 1;
							flag_data_updated = 0;
							curtain_stop_screen();
						}
					}
					else
					{
						BEEP = 0;
						GUI_Change_MainMenu_Screen(screen_mainmenu_normal);  // Tornarem a la pantalla normal
						flag_first_time_state = 1; 							// Volem que al tornar es faci neteja de la pantalla
					}

				}
			}		
			break;
		}	
		case RUN:
		{
			
			if (flag_first_time_state == 1)			
			{
				//disable_all_keys();
				//enable_key_stop();
				//enable_key_start();
				clean_modifying_lines_screen();
				flag_first_time_state = 0; 
			}
			else
			{	
				if (flag_data_updated == 1)
				{
					flag_data_updated = 0;
					main_menu_screen();			// Si s'ha actualitzat algun valor, el refrescare respecte a la pantalla del menu principal
				}
			}
			break;		

		}
		case RUNNING: 
		{

			if (flag_first_time_state == 1)
			{
				//disable_all_keys();
				//enable_key_stop();
				//enable_key_start();
				if (operation_mode == AA)				// Depenent del funcionament mostrare un LED activat o un altre
				{
					LED_AA = 1; 
					LED_AB = 0;
				}
				else if (operation_mode == AB)
				{
					LED_AA = 0;
					LED_AB = 1;				
				}
				else if (operation_mode == AA_AB)
				{
					LED_AA = 1;
					LED_AB = 1;
				}
				flag_first_time_state = 0; 
			}
			else
			{
				if (flag_data_updated == 1)
				{
					flag_data_updated = 0;
					if ((operation_mode == AB) && (bridge == CLOSED) && (flag_GUI_ab_closed_zero_positioning == 1))				// En cas del AB Cerrado, al buscar el punt zero, mostri pantalla de buscando punto zero. 
					{
						clean_screen(TEXT);		
						positioning_screen();
					}
					else if ((operation_mode == AB) && (bridge == CLOSED) && (flag_GUI_ab_closed_positioning == 1))						// En cas de AB Closed i que estigui posicionant-se, mostrarem "POSICIONANDO"
					{
						clean_screen(TEXT);	
						searching_limit_screen();
					}
					else 
					{
						main_menu_screen();
					}
				} 
				LED_START = 1; 							// Comença moure's: activo LED start i desactivo el de stop.
				LED_STOP = 0;
				BEACON_STOP = 0;
				BEACON_START = 1;

			}		
			break;
		}
		case STOPPED:
		{
			if (operation_mode == AA)				// Depenent del funcionament mostrare un LED activat o un altre
			{
				LED_AA = 1; 
				LED_AB = 0;
			}
			else if (operation_mode == AB)
			{
				LED_AA = 0;
				LED_AB = 1;				
			}
			else if (operation_mode == AA_AB)
			{
				LED_AA = 1;
				LED_AB = 1;
			}
			
			if (stop_values_to_modify == modify_stop_pressure)
			{
				if (flag_data_updated == 1)
				{
					LED_PUNCH = 1;
					LED_STEP = 0;
					LED_BELT = 0;
				}
			}
			else if (stop_values_to_modify == modify_stop_none)
			{
				if (flag_data_updated == 1)
				{
					LED_PUNCH = 0;
					LED_STEP = 0;
					LED_BELT = 0;
				}
			}
			
			LED_START = 0;
			LED_STOP = 1; 
			BEACON_STOP = 1;
			BEACON_START = 0;
			
			if (flag_data_updated == 1)
			{
				flag_data_updated = 0;
				if (flag_manual_stopped == 1) //Stopped by STOP
				{
					//disable_all_keys();
					//enable_key_start();
					//enable_numbers();
					//enable_key_enter();
					//enable_key_esc();
					clean_pressure_value();
					main_menu_screen();
					clean_modifying_lines_screen();
					stopped_lines_screen();
				}
				else if (flag_manual_stopped == 0) // Stopped by curtain
				{
					//disable_all_keys();
					//enable_key_start();
					clean_screen(TEXT);
					clean_modifying_lines_screen();
					stopped_lines_screen();
					if (flag_curtain_detecting == 1)
					{
						curtain_stop_screen();
						BEEP = 1;
						DelayMs(3000);
						BEEP = 0;
					}
					else if (flag_curtain_detecting == 0)
					{
						pulse_start_to_continue_screen();
					}						
				}
			} 
			break;
		}
		case WAIT:
		{
			if (flag_first_time_state == 1)
			{
				//disable_all_keys();
				//enable_key_start();
				//enable_key_reset();
				//enable_key_stop();
				GUI_DataActualization();
				screen_clean_submenu_bars();
				screen_clean_submenu2_bars();
				screen_clean_modifying_bars();		// Per si vinc de modificacio, elimino les possibles barres d'edicio
				clean_screen(TEXT);						// Elimino text per si vinc de posicionando
				flag_first_time_state = 0; 
			}
			else
			{
				if (operation_mode == AA)				// Depenent del funcionament mostrare un LED activat o un altre
				{
					LED_AA = 1; 
					LED_AB = 0;
				}
				else if (operation_mode == AB)
				{
					LED_AA = 0;
					LED_AB = 1;				
				}
				else if (operation_mode == AA_AB)
				{
					LED_AA = 1;
					LED_AB = 1;
				}

				if (wait_screen == screen_wait_normal)
				{
					if (flag_data_updated == 1)
					{
						if ((operation_mode == AB) && (bridge == CLOSED) && (flag_GUI_ab_closed_positioning == 1))						// En cas de AB Closed i que estigui posicionant-se, mostrarem "POSICIONANDO"
						{
							clean_screen(TEXT);	
							searching_limit_screen();
						}
						else
						{	
							clean_screen(TEXT);	
							main_menu_screen();	 
						}

						flag_data_updated = 0;
					}

					LED_START = 0; 
					LED_STOP = 1; 							// Estic parat: mostro LED de stop.
					BEACON_STOP = 1;
					BEACON_START = 0;
					
				}
				else if (wait_screen == screen_wait_holder_error)
				{
					if (counter_time_three_sec>= 3000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
					{
						counter_time_three_sec = 0;
						GUI_DataActualization();

						if (flag_show_three_sec_message == 1)
						{
							flag_show_three_sec_message = 0;				// Si estava a 0 el posem a 1 i viceversa
						}	
					}

					if (flag_show_three_sec_message == 1)
					{
						if (flag_data_updated == 1)
						{
							flag_data_updated = 0;
							BEEP = 1;
							error_show_holder_message();
						}
					}
					else
					{
						BEEP = 0;
						GUI_Change_Wait_Screen(screen_wait_normal);  // Tornarem a la pantalla normal
						flag_first_time_state = 1; 							// Volem que al tornar es faci neteja de la pantalla
					}
				}
				else if (wait_screen == screen_wait_door_error)
				{
					if (counter_time_three_sec>= 3000)			// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
					{
						counter_time_three_sec = 0;
						GUI_DataActualization();

						if (flag_show_three_sec_message == 1)
						{
							flag_show_three_sec_message = 0;				// Si estava a 0 el posem a 1 i viceversa
						}	
					}

					if (flag_show_three_sec_message == 1)
					{
						if (flag_data_updated == 1)
						{
							flag_data_updated = 0;
							BEEP = 1;
							error_show_door_message();
						}
					}
					else
					{
						BEEP = 0;
						GUI_Change_Wait_Screen(screen_wait_normal);  // Tornarem a la pantalla normal
						flag_first_time_state = 1; 							// Volem que al tornar es faci neteja de la pantalla
					}
				}
			}		
			break;
		}
		case PASSWORD:
		{

			if (flag_first_time_state == 1)
			{
				//disable_all_keys();
				//enable_numbers();
				screen_clean_modifying_bars();			// Elimino les barres per venir de modificando
				clean_screen(TEXT);						// Elimino text.
				password_reset_entered_password();		// Posa els valors de la contrasenya a zero 
				GUI_DataActualization();
				password_initial_screen();
				flag_first_time_state = 0; 
				LED_AA = 0;
				LED_AB = 0;
				LED_START = 0;
				BEACON_STOP = 0;
				BEACON_START = 0;
				LED_MENU = 0;
				LED_STOP = 0;
			}
			else
			{
				if (flag_data_updated == 1)
				{
					flag_data_updated = 0;
					modifying_password();
					password_lines_screen();
				}
				if (flag_password_parameter_changed == 1)
				{
					flag_password_parameter_changed = 0;
					screen_clean_password_bars();
				}
			}		
			break;
		}
		case SUBMENU:
		{
			if (flag_first_time_state == 1)
			{
				//disable_all_keys();
				//enable_numbers();
				//enable_key_esc();
				//enable_key_enter();
				//enable_key_menu();
				clean_screen(TEXT);	
				screen_clean_submenu_bars();
				screen_clean_password_bars();
				modifying_submenu_text();
				print_software_version_submenu();
				GUI_DataActualization();
				flag_first_time_state = 0; 
			}
			else
			{
				if  (flag_data_updated == 1)
				{
					modifying_submenu_values();				// Un valor es modifica 
					submenu_lines_screen();					// Canviar el blink de la ratlla.
					flag_data_updated = 0;
				}
				if (flag_submenu_parameter_changed == 1)
				{
					flag_submenu_parameter_changed = 0; 	// Si s'ha canviat de variable a modificar, canviarà la ratlla. 
					screen_clean_submenu_bars();
				}
			}		
			break;
		}
		case SUBMENU2:
		{
			if (flag_first_time_state == 1)
			{
				//disable_all_keys();
				//enable_numbers();
				//enable_key_esc();
				//enable_key_enter();
				//enable_key_menu();
				clean_screen(TEXT);	
				screen_clean_submenu2_bars();
				screen_clean_password_bars();
				modifying_submenu2_text();
				GUI_DataActualization();
				flag_first_time_state = 0; 
			}
			else
			{
				if  (flag_data_updated == 1)
				{
					modifying_submenu2_values();
					submenu2_lines_screen();
					flag_data_updated = 0;
				}
				if (flag_submenu2_parameter_changed == 1)
				{
					flag_submenu2_parameter_changed = 0; 	// Si s'ha canviat de variable a modificar, canviarà la ratlla. 	
					screen_clean_submenu2_bars();
				}
			}		
			break;
		}

		case AUTOTEST:
		{
			flag_at_autotest_led = 1; //We show that we are at autotest in order not to put our leds at 0 while keyboard_read

			if (counter_time_autotest_read >= 30)
			{
				counter_time_autotest_read = 0;
				Keyboard_Read();
			}
			
			if (counter_time_autotest_blink >= 600)		// Mirem si el comptador provoca un canvi en el flag de mostrar el valor que s'esta editant
			{
				counter_time_autotest_blink = 0;
				GUI_DataActualization();
		
				if (flag_show_autotest_key == 1)
				{
					flag_show_autotest_key = 0;				// Si estava a 0 el posem a 1 i viceversa
				}
				else 
				{
					flag_show_autotest_key = 1;
				}
			}

			if (flag_first_time_state == 1)				
			{
				enable_all_keys();
				if (flag_came_from_autotest == 0)
				{
					screen_clean_password_bars();
					clean_screen(TEXT);							// Sols netjo pantalla si no vinc d'autotest. 
				}
				motor_test_reset();
				//print_autotest_title();
				flag_gui_KEY_MENU = 0; 			// Sino, es queda activat al polsar menu per entrar a password
				flag_first_time_state = 0; 
			}

			else
			{
				if (flag_autotest_already_pressed_aa == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_aa();
						LED_AA = 1;
					}
					else 
					{
						print_autotest_aa_empty();
						LED_AA = 0;							
					}
				}
				else if (flag_autotest_already_pressed_aa == 1)
				{
					if (flag_autotest_KEY_AA == 1)
					{
						flag_autotest_KEY_AA = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_aa == 1)
							{
								print_autotest_aa();
								LED_AA = 1;
							}
							else 
							{
								print_autotest_aa_empty();
								LED_AA = 0;							
							}
						}
					} 
				}

				if (flag_autotest_already_pressed_ab == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_ab();
						LED_AB = 1;
					}
					else 
					{
						print_autotest_ab_empty();
						LED_AB = 0;							
					}
				}
				else if (flag_autotest_already_pressed_ab == 1)
				{
					if (flag_autotest_KEY_AB == 1)
					{
						flag_autotest_KEY_AB = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_ab == 1)
							{
								print_autotest_ab();
								LED_AB = 1;
							}
							else 
							{
								print_autotest_ab_empty();
								LED_AB = 0;							
							}
						}
					} 
				}

				if (flag_autotest_already_pressed_start == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_start();
						LED_START = 1;
						BEACON_START = 1;
					}
					else 
					{
						print_autotest_start_empty();
						LED_START = 0;	
						BEACON_START = 0;						
					}
				}
				else if (flag_autotest_already_pressed_start == 1)
				{
					if (flag_autotest_KEY_START == 1)
					{
						flag_autotest_KEY_START = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_start == 1)
							{
								print_autotest_start();
								LED_START = 1;
								BEACON_START = 1;
								autotest_mode_motor();
								motor_test_reset();
								autotest_process_start();
							}
							else 
							{
								print_autotest_start_empty();
								LED_START = 0;	
								BEACON_START = 0;						
							}
						}
					} 
				}

				if (flag_autotest_already_pressed_stop == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_stop();
						LED_STOP = 1;
						BEACON_STOP = 1;
					}
					else 
					{
						print_autotest_stop_empty();
						LED_STOP = 0;		
						BEACON_STOP = 0;					
					}
				}
				else if (flag_autotest_already_pressed_stop == 1)
				{
					if (flag_autotest_KEY_STOP == 1)
					{
						flag_autotest_KEY_STOP = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_stop == 1)
							{
								print_autotest_stop();
								LED_STOP = 1;
								BEACON_STOP = 1;
								autotest_mode_cylinder();
								motor_test_reset();
								autotest_process_start();
							}
							else 
							{
								print_autotest_stop_empty();
								LED_STOP = 0;
								BEACON_STOP = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_menu == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_menu();
						LED_MENU = 1;
					}
					else 
					{
						print_autotest_menu_empty();
						LED_MENU = 0;							
					}
				}
				else if (flag_autotest_already_pressed_menu == 1)
				{
					if (flag_autotest_KEY_MENU == 1)
					{
						flag_autotest_KEY_MENU = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_menu == 1)
							{
								print_autotest_menu();
								LED_MENU = 1;
							}
							else 
							{
								print_autotest_menu_empty();
								LED_MENU = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_reset == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_reset();
						LED_RESET = 1;
					}
					else 
					{
						print_autotest_reset_empty();
						LED_RESET = 0;							
					}
				}
				else if (flag_autotest_already_pressed_reset == 1)
				{
					if (flag_autotest_KEY_RESET == 1)
					{
						flag_autotest_KEY_RESET = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_reset == 1)
							{
								print_autotest_reset();
								LED_RESET = 1;
							}
							else 
							{
								print_autotest_reset_empty();
								LED_RESET = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_belt == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_belt();
						LED_BELT = 1;
					}
					else 
					{
						print_autotest_belt_empty();
						LED_BELT = 0;							
					}
				}
				else if (flag_autotest_already_pressed_belt == 1)
				{
					if (flag_autotest_KEY_BELT == 1)
					{
						flag_autotest_KEY_BELT = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_belt == 1)
							{
								print_autotest_belt();
								LED_BELT = 1;
								autotest_mode_5();
								motor_test_reset();
								autotest_process_start();
							}
							else 
							{
								print_autotest_belt_empty();
								LED_BELT = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_step == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_step();
						LED_STEP = 1;
					}
					else 
					{
						print_autotest_step_empty();
						LED_STEP = 0;							
					}
				}
				else if (flag_autotest_already_pressed_step == 1)
				{
					if (flag_autotest_KEY_STEP == 1)
					{
						flag_autotest_KEY_STEP = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_step == 1)
							{
								print_autotest_step();
								LED_STEP = 1;
								autotest_mode_6();
								motor_test_reset();
								autotest_process_start();
							}
							else 
							{
								print_autotest_step_empty();
								LED_STEP = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_punch == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_punch();
						LED_PUNCH = 1;
					}
					else 
					{
						print_autotest_punch_empty();
						LED_PUNCH = 0;							
					}
				}
				else if (flag_autotest_already_pressed_punch == 1)
				{
					if (flag_autotest_KEY_PUNCH == 1)
					{
						flag_autotest_KEY_PUNCH = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_punch == 1)
							{
								print_autotest_punch();
								LED_PUNCH = 1;
								autotest_mode_7();
								motor_test_reset();
								autotest_process_start();
							}
							else 
							{
								print_autotest_punch_empty();
								LED_PUNCH = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_esc == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_esc();
						LED_ESC = 1;
					}
					else 
					{
						print_autotest_esc_empty();
						LED_ESC = 0;							
					}
				}
				else if (flag_autotest_already_pressed_esc == 1)
				{
					if (flag_autotest_KEY_ESC == 1)
					{
						flag_autotest_KEY_ESC = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_esc == 1)
							{
								print_autotest_esc();
								LED_ESC = 1;
							}
							else 
							{
								print_autotest_esc_empty();
								LED_ESC = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_enter == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_ok();
						LED_ENTER = 1;
					}
					else 
					{
						print_autotest_ok_empty();
						LED_ENTER = 0;							
					}
				}
				else if (flag_autotest_already_pressed_enter == 1)
				{
					if (flag_autotest_KEY_ENTER == 1)
					{
						flag_autotest_KEY_ENTER = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_enter == 1)
							{
								print_autotest_ok();
								LED_ENTER = 1;
							}
							else 
							{
								print_autotest_ok_empty();
								LED_ENTER = 0;							
							}
						}
					} 
				}

				if (flag_autotest_already_pressed_0 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_0();
						LED_N0 = 1;
					}
					else 
					{
						print_autotest_0_empty();
						LED_N0 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_0 == 1)
				{
					if (flag_autotest_KEY_0 == 1)
					{
						flag_autotest_KEY_0 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_0 == 1)
							{
								print_autotest_0();
								LED_N0 = 1;
							}
							else 
							{
								print_autotest_0_empty();
								LED_N0 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_1 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_1();
						LED_N1 = 1;
					}
					else 
					{
						print_autotest_1_empty();
						LED_N1 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_1 == 1)
				{
					if (flag_autotest_KEY_1 == 1)
					{
						flag_autotest_KEY_1 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_1 == 1)
							{
								print_autotest_1();
								LED_N1 = 1;
							}
							else 
							{
								print_autotest_1_empty();
								LED_N1 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_2 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_2();
						LED_N2 = 1;
					}
					else 
					{
						print_autotest_2_empty();
						LED_N2 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_2 == 1)
				{
					if (flag_autotest_KEY_2 == 1)
					{
						flag_autotest_KEY_2 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_2 == 1)
							{
								print_autotest_2();
								LED_N2 = 1;
							}
							else 
							{
								print_autotest_2_empty();
								LED_N2 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_3 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_3();
						LED_N3 = 1;
					}
					else 
					{
						print_autotest_3_empty();
						LED_N3 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_3 == 1)
				{
					if (flag_autotest_KEY_3 == 1)
					{
						flag_autotest_KEY_3 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_3 == 1)
							{
								print_autotest_3();
								LED_N3 = 1;
							}
							else 
							{
								print_autotest_3_empty();
								LED_N3 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_4 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_4();
						LED_N4 = 1;
					}
					else 
					{
						print_autotest_4_empty();
						LED_N4 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_4 == 1)
				{
					if (flag_autotest_KEY_4 == 1)
					{
						flag_autotest_KEY_4 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_4 == 1)
							{
								print_autotest_4();
								LED_N4 = 1;
							}
							else 
							{
								print_autotest_4_empty();
								LED_N4 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_5 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_5();
						LED_N5 = 1;
					}
					else 
					{
						print_autotest_5_empty();
						LED_N5 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_5 == 1)
				{
					if (flag_autotest_KEY_5 == 1)
					{
						flag_autotest_KEY_5 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_5 == 1)
							{
								print_autotest_5();
								LED_N5 = 1;
							}
							else 
							{
								print_autotest_5_empty();
								LED_N5 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_6 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_6();
						LED_N6 = 1;
					}
					else 
					{
						print_autotest_6_empty();
						LED_N6 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_6 == 1)
				{
					if (flag_autotest_KEY_6 == 1)
					{
						flag_autotest_KEY_6 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_6 == 1)
							{
								print_autotest_6();
								LED_N6 = 1;
							}
							else 
							{
								print_autotest_6_empty();
								LED_N6 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_7 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_7();
						LED_N7 = 1;
					}
					else 
					{
						print_autotest_7_empty();
						LED_N7 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_7 == 1)
				{
					if (flag_autotest_KEY_7 == 1)
					{
						flag_autotest_KEY_7 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_7 == 1)
							{
								print_autotest_7();
								LED_N7 = 1;
							}
							else 
							{
								print_autotest_7_empty();
								LED_N7 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_8 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_8();
						LED_N8 = 1;
					}
					else 
					{
						print_autotest_8_empty();
						LED_N8 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_8 == 1)
				{
					if (flag_autotest_KEY_8 == 1)
					{
						flag_autotest_KEY_8 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_8 == 1)
							{
								print_autotest_8();
								LED_N8 = 1;
							}
							else 
							{
								print_autotest_8_empty();
								LED_N8 = 0;							
							}
						}
					} 
				}
				if (flag_autotest_already_pressed_9 == 0)
				{
					if (flag_show_autotest_key == 1)
					{
						print_autotest_9();
						LED_N9 = 1;
					}
					else 
					{
						print_autotest_9_empty();
						LED_N9 = 0;							
					}
				}
				else if (flag_autotest_already_pressed_9 == 1)
				{
					if (flag_autotest_KEY_9 == 1)
					{
						flag_autotest_KEY_9 = 0; 
						if (flag_first_time_test == 1)
						{
							flag_first_time_test = 0; 
							if(contador_autotest_9 == 1)
							{
								print_autotest_9();
								LED_N9 = 1;
							}
							else 
							{
								print_autotest_9_empty();
								LED_N9 = 0;							
							}
						}
					} 
				}
				#if 0 
				if (flag_autotest_KEY_NUMBER == 1)
				{
					flag_autotest_KEY_NUMBER = 0;
					if (flag_first_time_test == 1)
					{
						flag_first_time_test = 0; 

						#if 0
							if(contador_autotest_number == )
							{
								print_autotest_number_empty();
								print_autotest_number(flag_autotest_key_value);
							}
							else
							{
								print_autotest_number_empty();
							}
						#else
							if (flag_autotest_key_value == 0)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_0();
								}
								else 
								{
									print_autotest_0_empty();	
								}
							}
							else if (flag_autotest_key_value == 1)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_1();
								}
								else 
								{
									print_autotest_1_empty();	
								}
							}
							else if (flag_autotest_key_value == 2)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_2();
								}
								else 
								{
									print_autotest_2_empty();	
								}
							}
							else if (flag_autotest_key_value == 3)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_3();
								}
								else 
								{
									print_autotest_3_empty();	
								}
							}
							else if (flag_autotest_key_value == 4)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_4();
								}
								else 
								{
									print_autotest_4_empty();	
								}
							}
							else if (flag_autotest_key_value == 5)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_5();
								}
								else 
								{
									print_autotest_5_empty();	
								}
							}
							else if (flag_autotest_key_value == 6)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_6();
								}
								else 
								{
									print_autotest_6_empty();	
								}
							}
							else if (flag_autotest_key_value == 7)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_7();
								}
								else 
								{
									print_autotest_7_empty();	
								}
							}
							else if (flag_autotest_key_value == 8)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_8();
								}
								else 
								{
									print_autotest_8_empty();	
								}
							}
							else if (flag_autotest_key_value == 9)
							{	
								if (contador_autotest_number == 1)
								{
									print_autotest_number_empty();			// We clean the position if there was any different number painted
									print_autotest_9();
								}
								else 
								{
									print_autotest_9_empty();	
								}
							}
						#endif
					}
				} 
				#endif
	
				if (flag_GUI_autotest_door_error == 1)
				{
					if (flag_first_time_test_door == 1)
					{
						flag_first_time_test_door = 0; 
						print_autotest_door();
					}
				} 
				else 
				{
					if (flag_first_time_test_door == 1)
					{
						flag_first_time_test_door = 0; 
						print_autotest_door_empty();
					}
				}
	
				if (flag_GUI_autotest_emergency_error == 1)
				{
					if (flag_first_time_test_emergency == 1)
					{
						flag_first_time_test_emergency = 0; 
						print_autotest_emergency();
					}
				} 
				else 
				{
					if (flag_first_time_test_emergency == 1)
					{
						flag_first_time_test_emergency = 0; 
						print_autotest_emergency_empty();
					}
				}
	
				if (flag_GUI_autotest_cylinder_error == 1)
				{
					if (flag_first_time_test_cylinder == 1)
					{
						flag_first_time_test_cylinder = 0; 
						print_autotest_cylinder();
					}
				} 
				else 
				{
					if (flag_first_time_test_cylinder == 1)
					{
						flag_first_time_test_cylinder = 0; 
						print_autotest_cylinder_empty();
					}
				}
	
				if (flag_GUI_autotest_holder_error == 1)
				{
					if (flag_first_time_test_holder == 1)
					{
						flag_first_time_test_holder = 0; 
						print_autotest_holder();
					}
				} 
				else 
				{
					if (flag_first_time_test_holder == 1)
					{
						flag_first_time_test_holder = 0; 
						print_autotest_holder_empty();
					}
				}
	
				if (flag_GUI_autotest_start_error == 1)
				{
					if (flag_first_time_test_start == 1)
					{
						flag_first_time_test_start = 0; 
						print_autotest_inicio();
					}
				} 
				else 
				{
					if (flag_first_time_test_start == 1)
					{
						flag_first_time_test_start = 0; 
						print_autotest_inicio_empty();
					}
				}
	
				if (flag_GUI_autotest_end_error == 1)
				{
					if (flag_first_time_test_end == 1)
					{
						flag_first_time_test_end = 0; 
						print_autotest_end();
					}
				} 
				else 
				{
					if (flag_first_time_test_end == 1)
					{
						flag_first_time_test_end = 0; 
						print_autotest_end_empty();
					}
				}

				if (flag_GUI_autotest_curtain_error == 1)
				{
					if (flag_first_time_test_curtain == 1)
					{
						flag_first_time_test_curtain = 0; 
						print_autotest_curtain();
					}
				} 
				else 
				{
					if (flag_first_time_test_curtain == 1)
					{
						flag_first_time_test_curtain = 0; 
						print_autotest_curtain_empty();
					}
				}

				if (flag_GUI_autotest_8_error == 1)
				{
					if (flag_first_time_test_8 == 1)
					{
						flag_first_time_test_8 = 0; 
						print_autotest_i8();
					}
				} 
				else 
				{
					if (flag_first_time_test_8 == 1)
					{
						flag_first_time_test_8 = 0; 
						print_autotest_i8_empty();
					}
				}

				if (flag_GUI_autotest_9_error == 1)
				{
					if (flag_first_time_test_9 == 1)
					{
						flag_first_time_test_9 = 0; 
						print_autotest_i9();
					}
				} 
				else 
				{
					if (flag_first_time_test_9 == 1)
					{
						flag_first_time_test_9 = 0; 
						print_autotest_i9_empty();
					}
				}
			}

			break;
		}		
		case ERROR:
		{
			if (flag_first_time_state == 1)
			{
				//disable_all_keys();
				//enable_key_reset();
				//enable_key_start();
				LED_AA = 0;
				LED_AB = 0;
				LED_START = 0;
				LED_STOP = 0;
				BEACON_STOP = 0;
				BEACON_START = 0;
				screen_clean_submenu_bars();
				screen_clean_modifying_bars();		// Per si vinc de qualsevol lloc, com a molt hi haura text i les barres dels modificants. 
				screen_clean_submenu2_bars();
				clean_screen(TEXT);					// Posant clean GRAPHIC tarda molt més
				GUI_DataActualization();
				flag_first_time_state = 0; 
			}
			if (flag_data_updated == 1)
			{
				flag_data_updated = 0;
				clean_screen(TEXT);
				error_screen();
			}		
			break;
		}



	}


}

