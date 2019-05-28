/********************************************************************
 * FileName:		Autopuncher_app.h    							*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibreria per Autopuncher_app.c								*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverte		23/10/18		Versie inicial.					*
 *																	*
 ********************************************************************/

#ifndef AUTOPUNCHERAPP_H
#define AUTOPUNCHERAPP_H


/* Definicio de funcions */
void positioning_set_flag_completed(void);
void presentation_set_flag_welcome(void);
void reset_main_password_allowed_timer(void);
void autotest_process_start(void);
void Autopuncher_tasks(void);
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
void stopped_key_start(void);
void stopped_key_esc(void);
void stopped_key_number(void);
void set_value_to_apply(unsigned long aux_value_to_apply);


/* Types */

typedef enum type_State
{
	PRESENTATION,
	WAIT_PRESENTATION,
	START, 
	POSITIONING,
	EXITING_END,
	MAIN_MENU,
	RUN,
	RUNNING,
	STOPPED,
	WAIT,
	PASSWORD,
	SUBMENU, 
	SUBMENU2,
	MOTOR_TEST,
	AUTOTEST,
	ERROR, 
	SAVE
	
} type_State;

typedef enum type_operation_mode
{
	AA,
	AB,
	AA_AB,
	
} type_operation_mode; 


typedef enum type_values_to_modify
{
	modify_none = 0,
	modify_wide = 1,
	modify_step = 2,
	modify_pressure = 3
	
} type_values_to_modify;

typedef enum type_stop_values_to_modify
{
	modify_stop_none = 0,
	modify_stop_pressure = 1
	
} type_stop_values_to_modify;


typedef enum type_password_numbering_to_modify
{
	password_modify_thousands = 0,
	password_modify_hundreds = 1,
	password_modify_tens = 2,
	password_modify_units = 3
	
} type_password_numbering_to_modify;

typedef enum type_submenu_parameter_to_modify
{
	submenu_bridge,
	submenu_max_width,
	submenu_language,
	submenu_zero_value,
	submenu_limit_value

} type_submenu_parameter_to_modify;

typedef enum type_submenu2_parameter_to_modify
{
	submenu2_ton = 0,
	submenu2_toffmin,
	submenu2_toffmax,
	submenu2_stepspdchange,
	submenu2_acel,
	submenu2_decel,
	submenu2_longini,
	submenu2_turns

} type_submenu2_parameter_to_modify;

typedef enum type_error
{
	error_holder,
	error_cylinder,
	error_emergency,
	error_start,
	error_end,
	error_door,
	error_curtain,
	error_sensors

} type_error; 

#endif
