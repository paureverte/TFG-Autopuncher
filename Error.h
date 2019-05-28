/********************************************************************
 * FileName:		Error.h											*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per Error.c											*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		10/12/18		Versió inicial.					*
 *																	*
 ********************************************************************/
#ifndef ERROR_H
#define ERROR_H

#include "main.h"

void Error_Holder_Change_State(void);
void Error_Cylinder_Change_State(void);
void Error_Emergency_Change_State(void);
void Error_Start_Change_State(void);
void Error_End_Change_State(void);
void Error_Door_Change_State(void);
void Error_End_Reset_Pulsed(void);
void Error_End_Start_Pulsed(void);
void Error_End_Reset_Necessary(void);
void Error_End_Set_Necessary(void);
void Error_Change_State(type_error change_to_error);
void Error_tasks(void);


typedef enum type_holder_error_state
{
	holder_UP,
	holder_DOWN

} type_holder_error_state;

typedef enum type_cylinder_error_state
{
	cylinder_UP,
	cylinder_DOWN
	
} type_cylinder_error_state;

typedef enum type_emergency_error_state
{
	emergency_ON,
	emergency_OFF
	
} type_emergency_error_state;

typedef enum type_start_error_state
{
	start_ON,
	start_OFF
	
} type_start_error_state;

typedef enum type_end_error_state
{
	end_ON,
	end_OFF
	
} type_end_error_state;

typedef enum type_door_error_state
{
	door_OPEN,
	door_CLOSED
	
} type_door_error_state;

typedef enum type_curtain_error_state
{
	curtain_DETECTED,
	curtain_NOT_DETECTED
	
} type_curtain_error_state;

typedef enum type_8_error_state
{
	I8_DETECTED,
	I8_NOT_DETECTED
	
} type_8_error_state;

typedef enum type_9_error_state
{
	I9_DETECTED,
	I9_NOT_DETECTED
	
} type_9_error_state;

typedef enum type_sensors_error_state
{
	error_sensors_ON,
	error_sensors_OFF
	
} type_sensors_error_state;

#endif
