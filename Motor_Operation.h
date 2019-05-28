/********************************************************************
 * FileName:		Motor_Operation.h								*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per Motor_Operation.c 								*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		20/11/18		Versió inicial.					*
 *																	*
 ********************************************************************/

#ifndef MOTORFUNC_H
#define MOTORFUNC_H

void positioning_set_flag_start(void);
void positioning_reset_flag_start(void);
void ab_closed_set_flag_start(void);
void ab_closed_reset_flag_start(void);


/* Types */

typedef enum 
{
	START_EXITING_END = 0,
	WAIT_END_EXITED,
	END_EXITED_COMPLETE,
	
} type_exitingend;


/* ESTATS PER QUAN EL DISPOSITIU ES POSICIONA AL PUNT 0 */
typedef enum
{
	PRE_POSITIONING,
	START_SEARCH_STARTPOINT,
	EXIT_STARTPOINT,
	EXITING_STARTPOINT,
	SCAPED_FROM_STARTPOINT,
	SEARCHING_STARTPOINT,
	STARTPOINT_FOUND,
	SEARCH_DECELERATION_POSITION,
	START_EXIT_FROM_START_AGAIN,
	WAIT_EXIT_FROM_START_AGAIN,
	WAIT_START_SEARCH_ZEROPOINT,
	START_SEARCH_ZEROPOINT, 
	SEARCHING_ZERO,
	ZEROPOINT_FOUND,
	
} type_positioning; 

/* ESTATS PER QUAN EL DISPOSITIU FA L'ANADA TIPUS A */
typedef enum
{
	START_GOING_A,
	DESCENT_CYLINDER,
	WAIT_DESCENT_CYLINDER,
	WAIT_TIME_RISE_CYLINDER,
	RISE_CYLINDER,
	WAIT_RISE_CYLINDER,
	STEP_TROQUEL_GOING_A,
	WAIT_MOVEMENT_GOING_A,
	STOP_MOTOR_GOING_A,
	GONE_DONE, 
	START_RETURN_A_CLOSED,
	START_RETURN_A_OPEN,
	START_RETURN_B_CLOSED,
	FINAL_MOVEMENT_RETURN_B_CLOSED,
	WAIT_FINAL_MOVEMENT_RETURN_B_CLOSED,
	STEP_DIE_RETURN_B,
	HALF_STEP_RETURN_A_CLOSED,
	WAIT_HALF_STEP_RETURN_A_CLOSED,
	MOVEMENT_LIMITPLUSHALF_RETURN_B_CLOSED,
	WAIT_MOVEMENT_LIMITPLUSHALF_RETURN_B_CLOSED,
	STEP_DIE_RETURN,
	WAIT_MOVEMENT_RETURN,
	WAIT_LAST_HALF_STEP_AA_CLOSED,
	LAST_HALF_STEP_CLOSED_AA,
	WAIT_STATE_AA_CLOSED,
	WAIT_STATE_AB_CLOSED,
	ENDSWITCH_FOUND,
	WAIT_FOR_DECELERATING_POSITION,
	TIME_WAIT_LIMITPLUSHALF,
	CHANGE_STEP_AAAB,
	WAIT_HALF_STEP_AAAB,
	STOP_MOTOR_RETURN,
	START_FINAL_POSITIONING_AB_CLOSED,
	WAIT_STARTPOINT_POSITIONING_AB,
	STARTPOINT_AB_CLOSED_FOUND,
	SEARCH_DECERATE_POSITION,
	WAIT_SEARCH_ZEROPOINT,
	START_SEARCH_ZEROPOINT_AB_CLOSED,
	SEARCHING_ZERO_AB_CLOSED,
	RETURN_COMPLETED,
	DROPPING_DONE,
	
} type_motor_movement; 


typedef enum
{
	MOVEMENT_TYPE_ZEROPOINT,
	MOVEMENT_TYPE_STARTPOINT,
	MOVEMENT_TYPE_STEP,
	MOVEMENT_TYPE_HALF_STEP,
	MOVEMENT_TYPE_END_RETURN_B_CLOSED,
	MOVEMENT_TYPE_HALFSTEP_LIMIT, 
	MOVEMENT_TYPE_TEST_MOTOR,
	MOVEMENT_TYPE_POSITIONING_DECELERATE,
	MOVEMENT_TYPE_ENDSWITCH_DECELERATE,
	MOVEMENT_TYPE_AB_CLOSED_ZEROPOINT,
	
} type_movement;

typedef enum
{
	START_TURN_A,
	WAIT_TURN_A,
	START_TURN_B,
	WAIT_TURN_B,
	END_TEST_MOTOR,
	
} type_motor_test; 

/***************** Definicio de subrutines usades *******************/

void CalculePWMSteps(type_movement movement_type);
void StartMotor(unsigned char start_turn_direction, type_movement movement_type);
void StopMotor(void);
void StepMotor(void);
void DiesCalcule(void);
void motor_movement_start(void);
void positioning_tasks(void);
void motor_movement_tasks(void);
void motor_set_flag_start(void);
void motor_reset_dies_counter (void);
void motor_stop_operating (void);
void motor_set_flag_cilindre(void);
void motor_reset_flag_cilindre(void);
void motor_set_flag_ficarrera(void);



#endif
