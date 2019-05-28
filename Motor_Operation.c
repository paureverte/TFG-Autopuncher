/********************************************************************
 * FileName:		Motor_Operation.c								*
 * Dependencies:	Motor_Operation.h								*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions per al correcte funcionament del motor.				*
 *	  Inclou funcions per detetminar la forma de funcionar.			*	
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		20/11/18		Versio inicial 					*
 * 																	*
 ********************************************************************/
#include "main.h"


/***************** Variables locals *************************/
volatile unsigned long pwm_steps = 0; 											// Variable comptadora dels passos que ha realitzat el pwm durant una operacio
volatile unsigned long pwm_steps_total = 0; 									// Variable auxiliar dels passos totals que ha de fer el pwm per complir amb "step"
volatile unsigned long steps_for_deceleration = 0; 								// Variable per calcular els passos necessaris ha fer durant la deceleracio
volatile unsigned char flag_calculating_decelerating_step; 								// Variable booleana per saber si s'esta buscant el pas inicial de deceleracio
volatile unsigned long pwm_steps_start_decelerate;								// Variable fixa per determinar el pas al qual es comenca la deceleracio
extern volatile unsigned long necessary_steps_for_change; 							// Variable de passos als quals fer un canvi de velocitat amb el pwm
volatile unsigned long pwm_steps_done = 0;										// Variable auxiliar per determinar el valor de pasos per comencar la deceleracio
volatile unsigned long motor_steps = 0; 										// Variable comptadora per comparar amb els de canvi de velocitat
volatile type_motor_movement motor_movement_state;
volatile type_acceleration_state acceleration_state; 
volatile type_positioning positioning_state;
volatile type_motor_test motor_test_state = 0;
volatile type_exitingend exiting_end_state = 0;
volatile unsigned long dies_counter;
volatile unsigned char flag_first_cut;
volatile unsigned char flag_going_movement;
volatile unsigned char flag_return_movement;
volatile unsigned char flag_start_motor = 0;
volatile unsigned char flag_start_ab_closed = 0;
volatile unsigned char flag_cylinder_motor = 0;
volatile unsigned char flag_endswitch_motor = 0; 
volatile unsigned char flag_start_positioning = 0; 
volatile unsigned char flag_pressure_completed = 0; 
volatile unsigned char flag_state_came_from; 
volatile unsigned long test_time_counter = 0; 
volatile unsigned char counter_dd_times = 0; 
volatile unsigned long counter_time_test  = 0;
volatile unsigned long counter_time_positioning = 0;
volatile unsigned char autotest_process_mode;
volatile unsigned long pwm_to_end_counter = 0;
volatile unsigned long obtained_pwm_to_end_counter = 0;
volatile unsigned long pwm_gone_counter = 0;
volatile unsigned long obtained_pwm_gone_counter = 0;
volatile unsigned char flag_stop_running = 0;
volatile unsigned long steps_for_aceleration = 0;
volatile unsigned char flag_came_from_final_movement_stop = 0;
volatile unsigned char flag_not_in_end;
volatile unsigned char flag_start_end_scaping; 

/***************** Variables externes ***********************/


extern volatile type_State State;  
extern volatile type_acceleration_state acceleration_state; 
extern volatile type_operation_mode operation_mode;
extern volatile unsigned char flag_gui_end_movement_stopped;
extern unsigned long step; 
extern unsigned long wide;
extern unsigned long wide_MAX; 
extern unsigned long TON;
extern unsigned long TOFF;
extern unsigned long TOFF_MAX;
extern unsigned long TOFF_MIN; 
extern unsigned long position;
extern unsigned long pressure;
extern unsigned char bridge; 				
extern unsigned long accelerate_constant; 
extern unsigned long decelerate_constant; 
extern unsigned long decelerate_positioning_constant;
extern unsigned long distance_limit_to_start;
extern unsigned long submenu2_turns_number;
extern volatile unsigned long end_limit;
extern volatile unsigned long dies_number;
extern volatile unsigned long wide_cm; 
extern volatile unsigned long zero_value; 

/********************************************************************
 * Function:	CalculoPasoDeceleracion()							*
 * Definition:	Funcio per calcular el pas inicial per decelerar	*
 ********************************************************************/
void CalculePWMSteps(type_movement movement_type)
{
		pwm_steps = 0; 																						// Inicialitzem els passos que el pwm ha realitzat en el proces

		acceleration_state = ACCELERATE; 																	// Auxiliar per buscar el pas al que comencar la deceleracio
		switch(movement_type)
		{
			case MOVEMENT_TYPE_STARTPOINT:
			{
				pwm_steps_total = wide_MAX_FACTORY * 20000;
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;		
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)								// Si el espai total no es necessari per fer la seqüència, donarem la meitat a aceleracio i la meitat a deceleració.
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_ZEROPOINT:
			{
				pwm_steps_total = (zero_value * 20)	+ 200 * distance_limit_to_start; 									// Punt zero més distancia de frenada. 
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_STEP:
			{
				pwm_steps_total = step * 200; 																			// Calculem els passos necessaris que haura de fer el PWM en funcio de "paso". 200 relaciona el pas entre els talls de la maquina i els passos que hauraÂ  de fer el pwm per arribar-hi. 2000 "passos" es una volta. 																// Calculem els passos que haura de fer el PWM per arribar de START a punt zero.												
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_HALF_STEP:
			{
				pwm_steps_total = step * 100; 																			// Els pasos del pwm hauran de ser per realitzar mig pas.
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_END_RETURN_B_CLOSED:
			{
				pwm_steps_total = wide_MAX * 50000; 
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 		
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_HALFSTEP_LIMIT: 
			{
				pwm_steps_total = (( (end_limit * 20)-(step * 100)) + (200 * distance_limit_to_start));														// DesplaÃ§ar-se desde el punt de frenada fins el limit final menys mig pas.
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_TEST_MOTOR:
			{
				pwm_steps_total = 2000 * submenu2_turns_number;
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_POSITIONING_DECELERATE:
			{
				pwm_steps_total = 200 * distance_limit_to_start;
				acceleration_state = DECELERATE;
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_positioning_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_ENDSWITCH_DECELERATE:
			{
				pwm_steps_total = 200 * distance_limit_to_start;
				acceleration_state = DECELERATE;
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_positioning_constant)*necessary_steps_for_change;		// Calculem els passos de deceleracio que en seran necessaris per parar. 
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)											
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}
			case MOVEMENT_TYPE_AB_CLOSED_ZEROPOINT:
			{
				pwm_steps_total = obtained_pwm_to_end_counter - ((end_limit*20)-(step*100));
				acceleration_state = ACCELERATE;
				steps_for_deceleration = (TOFF_MAX - TOFF_MIN) / (decelerate_positioning_constant)*necessary_steps_for_change;
				steps_for_aceleration = (TOFF_MAX - TOFF_MIN) / (accelerate_constant)*necessary_steps_for_change;
				if ((steps_for_aceleration + steps_for_deceleration) >= pwm_steps_total)
				{
					steps_for_deceleration = pwm_steps_total / 2;
					steps_for_aceleration = pwm_steps_total / 2;
				}
				break;
			}

		}
		
		pwm_steps_start_decelerate = pwm_steps_total -  steps_for_deceleration; 
}


/********************************************************************
 * Function:	StartMotor()										*
 * Definition:	Funcio per inicialitzar i posar en marxa un motor	*
 ********************************************************************/
void StartMotor(unsigned char start_turn_direction, type_movement movement_type)
{
	MOTOR_EN = MOTOR_ON;					// Donem enable al motor
	MOTOR_DIR = start_turn_direction;		// Indiquem al direccio de gir del motor. (RIGHT / LEFT)
	acceleration_state = ACCELERATE; 		// Al ser l'inici ha de comenÃƒÂ§ar accelerant si o siÂ­. 
	CalculePWMSteps(movement_type);
	TOFF = TOFF_MAX;
	InitOutputCompare();					// Inicialitzem i comencem el Output Compare
}
/********************************************************************
 * Function:	StartDeceleratePositioning()						*
 * Definition:	Funcio per decelerar en posicionament				*
 ********************************************************************/
void StartDeceleratePositioning(void)
{
	MOTOR_EN = MOTOR_ON;
	MOTOR_DIR = LEFT;		// Indiquem al direccio de gir del motor. (RIGHT / LEFT)
	motor_steps = 0;
	CalculePWMSteps(MOVEMENT_TYPE_POSITIONING_DECELERATE);
	TOFF = TOFF_MAX;
	InitOutputCompare();					// Inicialitzem i comencem el Output Compare
}

/********************************************************************
 * Function:	StartDecelerateEndswitch()							*
 * Definition:	Funcio per decelerar a l'endswitch					*
 ********************************************************************/
void StartDecelerateEndswitch(void)
{
	MOTOR_EN = MOTOR_ON;
	MOTOR_DIR = RIGHT;		// Indiquem al direccio de gir del motor. (RIGHT / LEFT)
	motor_steps = 0;
	CalculePWMSteps(MOVEMENT_TYPE_POSITIONING_DECELERATE);
	TOFF = TOFF_MAX;
	InitOutputCompare();					// Inicialitzem i comencem el Output Compare
}
/********************************************************************
 * Function:	StopMotor()											*
 * Definition:	Funcio per parar el motor  							*
 ********************************************************************/
void StopMotor(void)
{
	TOFF = TOFF_MAX;
	StopOutputCompare();					// Disable al Output Compare
}

/****************************************************************************
 * Function:	StepMotor()													*
 * Definition:	Funcio per fer funcionar el motor. Equival a 1 pas del pwm.	*
 ****************************************************************************/
void StepMotor(void) 
{
	switch (acceleration_state)										// En funcio de l'estat de l'acceleration es fara un funcionament determinat
	{
		case ACCELERATE:											// En cas d'estar accelerant 						
		{
			if (motor_steps >= necessary_steps_for_change) 			// S'han fet els passos necessaris per realitzar un canvi de velocitat	
			{
				motor_steps = 0;									// Posem a zero el numero de passos per calcular un nou canvi
				TOFF = TOFF - accelerate_constant;					// Modifiquem el valor de TOFF per variar aixi el PWM

				if (TOFF <= TOFF_MIN)								// Si el TOFF ja ha arribat al seu minim el deixem aixi
				{		
					TOFF = TOFF_MIN;
					acceleration_state = STEADY; 					// Un cop ja estem al minim de TOFF en situem en estat d'estable
				}

			}

			break; 	
		}
		case DECELERATE:											// En cas d'estar desaccelerant 						
		{
			if (motor_steps >= necessary_steps_for_change) 			// S'han fet els passos necessaris per realitzar un canvi de velocitat	
			{

				motor_steps = 0;									// Posem a zero el numero de passos per calcular un nou canvi
				TOFF = TOFF + decelerate_constant;					// Modifiquem el valor de TOFF per variar aixi el PWM
				if (TOFF >= TOFF_MAX)								// Si el TOFF ja ha arribat al seu maxim el deixem aixi
				{		
					TOFF = TOFF_MAX;
				}
			}
			if (pwm_steps >= pwm_steps_total){
				acceleration_state = STOP; 							// Un cop ja estem al maxim de TOFF (deceleracio maxima)i hem arribat a comptar els passos totals del pwm, el motor ha de parar.
				StopMotor(); 										// Crida la funcio per deixar d'usar el PWM. Deixa d'estar en enable i, per tant, no es donen polsos al motor i aquest no funciona
			}

			break; 		
		}
		case DECELERATE_POSITIONING:											// En cas d'estar desaccelerant 						
		{
			if (motor_steps >= necessary_steps_for_change) 			// S'han fet els passos necessaris per realitzar un canvi de velocitat	
			{
				motor_steps = 0;									// Posem a zero el numero de passos per calcular un nou canvi
				TOFF = TOFF + decelerate_positioning_constant;					// Modifiquem el valor de TOFF per variar aixi el PWM
				if (TOFF >= TOFF_MAX)								// Si el TOFF ja ha arribat al seu maxim el deixem aixi
				{		
					TOFF = TOFF_MAX;
				}
			}
			if (pwm_steps >= pwm_steps_total){
				acceleration_state = STOP; 							// Un cop ja estem al maxim de TOFF (deceleracio maxima)i hem arribat a comptar els passos totals del pwm, el motor ha de parar.
				StopMotor(); 										// Crida la funcio per deixar d'usar el PWM. Deixa d'estar en enable i, per tant, no es donen polsos al motor i aquest no funciona
			}

			break; 		
		}	
		case STOP: 													// En cas de deixar d'haver de parar el motor. 
		{
			break; 
		}	
		case STEADY: 												// En cas d'estar ESTABLE no fem cap modificacio
		default:
		break;



	}
	motor_steps++;													// Augmentem en una unitat els passos realitzats
	PR2 = (TON + TOFF) * CONV_FACT_T2_OC;							// Modifiquem el valor del periode del Output Compare, corresponent a la suma de TON i TOFF.
	pwm_steps++;													// Augmentem en una unitat els passos que ha fet el PWM
	pwm_to_end_counter++;
}
/********************************************************************
 * Function:	DiesCalcule()										*
 * Definition:	Funcio per calcular el nombre de talls a fer.		*
 ********************************************************************/
void DiesCalcule(void)
{
	dies_number = 0;
	wide_cm = wide * 10;
	while (wide_cm >= step)
	{
		wide_cm = wide_cm - step; 
		dies_number++;	
	}
	if (wide_cm > 0)
	{
		dies_number++;
	}
	dies_number = dies_number + 3; 

	// Per a AA_AB
	if ((operation_mode == AA_AB)&&(counter_dd_times == 1))
	{
		dies_number = dies_number + 1;					// La 3a i 4a tenen 1 pas més que la resta.}
	}	
}

/********************************************************************
 * Function:	motor_movement_start()						*
 * Definition:	Funcio per començar a funcionar el motor.			*
 ********************************************************************/
void motor_movement_start(void)
{
	motor_movement_state = START_GOING_A;
	acceleration_state = ACCELERATE;
}
/********************************************************************
 * Function:	motor_reset_dies_counter()							*
 * Definition:	Funcio per resetejar el comptador de troquels.		*
 ********************************************************************/
void motor_reset_dies_counter (void)
{
	dies_counter = 0;  
}
/********************************************************************
 * Function:	motor_stop_operating()					*
 * Definition:	Funcio per finalitzar el proces de troquel.			*
 *				Prepara per a l'inici següent						*
 ********************************************************************/
void motor_stop_operating (void) 
{
	motor_reset_dies_counter();
	flag_return_movement = 0;
	flag_going_movement = 1; 	
}
/********************************************************************
 * Function:	positioning_set_flag_start()						*
 * Definition:	Funcio per activar el flag d'inici de posicionament.*
 ********************************************************************/
void positioning_set_flag_start(void)
{
	flag_start_positioning = 1;
}	

/********************************************************************
 * Function:	positioning_reset_flag_start()					*
 * Definition:	Funcio per desactivar el flag d'inici de 			*
 *				posicionament.										*
 ********************************************************************/
void positioning_reset_flag_start(void)
{
	flag_start_positioning = 0;
}
/********************************************************************
 * Function:	ab_closed_set_flag_start()							*
 * Definition:	Funcio per activar el flag d'inici de posicionament.*
 ********************************************************************/
void ab_closed_set_flag_start(void)
{
	flag_start_ab_closed = 1;
}
/********************************************************************
 * Function:	ab_closed_reset_flag_start()						*
 * Definition:	Funcio per activar el flag d'inici de posicionament.*
 ********************************************************************/
void ab_closed_reset_flag_start(void)
{
	flag_start_ab_closed = 0;
}
/********************************************************************
 * Function:	motor_set_flag_cilindre()							*
 * Definition:	Funcio per activar el flag de cilindre del motor.	*
 ********************************************************************/
void motor_set_flag_cilindre(void)
{
	flag_cylinder_motor = 1;
}	

/********************************************************************
 * Function:	motor_reset_flag_cilindre()							*
 * Definition:	Funcio per desactivar el flag de cilindre del motor.*
 ********************************************************************/
void motor_reset_flag_cilindre(void)
{
	flag_cylinder_motor = 0;
}	
/********************************************************************
 * Function:	motor_set_flag_ficarrera()							*
 * Definition:	Funcio per activar el flag de final de carrera		*
 * 				del motor.											*
 ********************************************************************/
void motor_set_flag_ficarrera(void)
{
	flag_endswitch_motor = 1; 
}
		
/********************************************************************
 * Function:	motor_set_flag_start()								*
 * Definition:	Funcio per activar el flag de start del motor.		*
 *				Usat per a fer la tornada. S'activa i es torna a 	*
 *				arrencar.											*
 ********************************************************************/
void motor_set_flag_start(void)
{
	flag_start_motor = 1;
}	
/********************************************************************
 * Function:	positioning_set_start()								*
 * Definition:	Funcio per activar el posicionament en l'inici.		*
 ********************************************************************/
void positioning_set_start(void)
{
	positioning_state = PRE_POSITIONING;
}

void set_not_in_end (void)
{
	flag_not_in_end = 1;
}

void reset_not_in_end (void)
{
	flag_not_in_end = 0;
}

void set_start_in_end (void)
{
	flag_start_end_scaping = 1;
}

void reset_start_in_end (void)
{
	flag_start_end_scaping = 0;
}

void exiting_end_tasks(void)
{
	switch(exiting_end_state)
	{
		case START_EXITING_END:
		{
			StartMotor(LEFT, MOVEMENT_TYPE_STARTPOINT);
			exiting_end_state = WAIT_END_EXITED;
			break;
		}
		case WAIT_END_EXITED:
		{
			if (flag_not_in_end == 1)
			{
				StopMotor();
				exiting_end_state = END_EXITED_COMPLETE;
			}
			if (flag_start_end_scaping == 1)
			{
				StopMotor();
				GUI_ChangeState(ERROR);
				Error_Change_State(error_sensors);
				exiting_end_state = START_EXITING_END;
			}
			break;
		}
		case END_EXITED_COMPLETE:
		{
			exiting_end_completed();
			exiting_end_state = START_EXITING_END;
			break;
		}
	}
}


/********************************************************************
 * Function:	positioning_tasks(void)								*
 * Definition:	Estats del procediment de positioning.  			*
 ********************************************************************/
void positioning_tasks(void)
{
	switch(positioning_state)
	{
		case PRE_POSITIONING:											// State previo al positioning
		{
			if (flag_start_positioning == 1) 												// Desde el principio ya estamos en START			
			{
				positioning_state = EXIT_STARTPOINT;						// Vamos al State de salir del START inicial
			}
			else  // No estamos en START 
			{
				positioning_state = START_SEARCH_STARTPOINT; 		// Vamos a buscar el START.
			}
			break; 
		}
		case EXIT_STARTPOINT:
		{
			StartMotor(RIGHT, MOVEMENT_TYPE_STARTPOINT);
			positioning_state = EXITING_STARTPOINT;
			break;
		}
		case EXITING_STARTPOINT:
		{
			if (flag_start_positioning == 0)
			{
				positioning_state = SCAPED_FROM_STARTPOINT;
			}
			break;
		}
		case SCAPED_FROM_STARTPOINT:
		{
			StopMotor();
			positioning_state = START_SEARCH_STARTPOINT;
			break;
		}
		case START_SEARCH_STARTPOINT: 
		{
			flag_start_positioning = 0;
			StartMotor(LEFT, MOVEMENT_TYPE_STARTPOINT);
			positioning_state = SEARCHING_STARTPOINT;
			break;	
		}
		case SEARCHING_STARTPOINT:
		{
			if (flag_start_positioning == 1)
			{
				positioning_state = STARTPOINT_FOUND; 
			}
			break; 
		}
		case STARTPOINT_FOUND: 
		{
			StartDeceleratePositioning();
			positioning_state = SEARCH_DECELERATION_POSITION;
			break;
		}

		case SEARCH_DECELERATION_POSITION:
		{
			if (acceleration_state == STOP)
			{
				StopMotor(); 
				counter_time_positioning = 0;
				positioning_state = WAIT_START_SEARCH_ZEROPOINT;
			}

			break;
		}

		case WAIT_START_SEARCH_ZEROPOINT:
		{
			if(counter_time_positioning >= 500)
			{
				positioning_state = START_EXIT_FROM_START_AGAIN;
			}
			break;
		}

		case START_EXIT_FROM_START_AGAIN:
		{
			StartMotor(RIGHT, MOVEMENT_TYPE_STARTPOINT);
			positioning_state = WAIT_EXIT_FROM_START_AGAIN;
			break;
		}

		case WAIT_EXIT_FROM_START_AGAIN:
		{
			if (flag_start_positioning == 0)
			{
				positioning_state = START_SEARCH_ZEROPOINT;
			}
			break;
		}

		case START_SEARCH_ZEROPOINT: 
		{
			StartMotor(RIGHT, MOVEMENT_TYPE_ZEROPOINT);
			positioning_state =  SEARCHING_ZERO;
			break;
		}
		case SEARCHING_ZERO: 
		{
			if (acceleration_state == STOP)
			{
				positioning_state = ZEROPOINT_FOUND; 
				positioning_set_flag_completed();
			}
			break; 
		}
		case ZEROPOINT_FOUND: 
		{
			// Ja s'ha completat la sequencia de positioning
			break;
		}
	}
		
}	

/********************************************************************
 * Function:	pressure_completed_set_flag(void)					*
 * Definition:	Funcio per posar el flag de pressio completada.		*
 ********************************************************************/
 void pressure_completed_set_flag(void)
 {
 	flag_pressure_completed = 1; 
 }

/********************************************************************
 * Function:	motor_movement_reset(void)							*
 * Definition:	Funcio per posar a zero el funcionament del motor.	*
 ********************************************************************/
 void motor_movement_reset(void)
 {
 	motor_movement_state = START_GOING_A;
 	OUT_EVCIL = RISE; 
 	dies_counter = 0; 
 	position = 0; 
 }
/********************************************************************
 * Function:	SetStopRunning(void)								*
 * Definition:	Activa el flag del STOP a RUNNING.					*
 ********************************************************************/
 void SetStopRunning(void)
 {
 	flag_stop_running = 1;
 }

/********************************************************************
 * Function:	Reset_AAAB_Counter(void)							*
 * Definition:	Reset del coutner de AA AB 							*
 ********************************************************************/
 void Reset_AAAB_Counter(void)
 {
 	counter_dd_times = 0;
 }



/********************************************************************
 * Function:	motor_movement_tasks(void)							*
 * Definition:	Estats del procediment de funcionament del motor.	*
 ********************************************************************/
void motor_movement_tasks(void)
{
	switch (motor_movement_state)
	{
		case START_GOING_A: 
		{
			Error_End_Set_Necessary();							// Tornem a activar l'error de final per si es dona el cas que estava en OFF per haver fet un AB cerrado
			flag_going_movement = 1;
			flag_first_cut = 1; 
			DiesCalcule();									// Calculem el nombre de talls a realitzar. Sera el mateix per a AA i AB.	
			motor_movement_state = DESCENT_CYLINDER;
			break;
		}

		case DESCENT_CYLINDER: 
		{
			OUT_EVCIL = DESCENT;										// Baixem el cilindre.
			Config_Timer5();
			motor_movement_state = WAIT_DESCENT_CYLINDER;				// Passem a l'estat d'esperar la baixada del cilindre
			break;  
		}

		case WAIT_DESCENT_CYLINDER:
		{
 			if (flag_cylinder_motor == 1)
			{	
				flag_pressure_completed = 0;
				Config_Timer4();
				motor_movement_state = WAIT_TIME_RISE_CYLINDER;
			}
			break; 		
		}

		case WAIT_TIME_RISE_CYLINDER: 
		{
			if (flag_pressure_completed == 1)
			{
				flag_pressure_completed = 0;
				motor_movement_state = RISE_CYLINDER;
			} 			
			break;
		}

		case RISE_CYLINDER:
		{
			OUT_EVCIL = RISE; 
			motor_movement_state = WAIT_RISE_CYLINDER; 
			break; 		
		}

		case WAIT_RISE_CYLINDER: 
		{
			if (flag_going_movement == 1)
			{
				if (flag_cylinder_motor == 0)
				{	
					if (flag_stop_running == 1)
					{
						flag_stop_running = 0;
						reset_counter_t5();
						CloseTimer5();
						GUI_ChangeState(STOPPED);
						GUI_DataActualization();
					}
					else
					{
						reset_counter_t5();
						CloseTimer5();
						if (dies_counter < dies_number - 1 ) // Si encara no hem fet el total de troquels, anem a start motor per fer un altre tall.
						{
							motor_movement_state = STEP_TROQUEL_GOING_A;
							
							if (flag_first_cut == 1) 
							{
								position++;
								GUI_DataActualization();
								flag_first_cut = 0; 
							}
							else 
							{
								position++;
								GUI_DataActualization();
								dies_counter++;
							}
						}
						
						else 											// Si ja hem arribat, pararem el motor. 
						{
							dies_counter++;
							motor_movement_state = STOP_MOTOR_GOING_A;	
						}
					}
				}
			}
			else if (flag_return_movement == 1)
			{
				if (flag_cylinder_motor == 0)
				{
					if (flag_cylinder_motor == 0)
					{	
						if (flag_stop_running == 1)									// S'ha polsat el STOP, esperem a parar a que el cilindre estigui a dalt. 
						{
							flag_stop_running = 0;
							reset_counter_t5();
							CloseTimer5();
							GUI_ChangeState(STOPPED);
						}
						else
						{
							reset_counter_t5();
							CloseTimer5();					
							if (dies_counter < dies_number - 1)
							{
								motor_movement_state = STEP_DIE_RETURN;
								
								if (flag_first_cut == 1)
								{
									position--;
									GUI_DataActualization();
									flag_first_cut = 0;
								}
								else 
								{
									position--;
									GUI_DataActualization();
									dies_counter++;
								}
							}
							
							else 
							{
								dies_counter++;
								motor_movement_state = STOP_MOTOR_RETURN;
							}
						}
					}				
				}
			}
			break; 		
		}

		case STEP_TROQUEL_GOING_A: 
		{
			StartMotor(RIGHT, MOVEMENT_TYPE_STEP); 
			motor_movement_state = WAIT_MOVEMENT_GOING_A;
			break;		
		}

		case WAIT_MOVEMENT_GOING_A:
		{
			if (acceleration_state == STOP)
			{
				motor_movement_state = DESCENT_CYLINDER;
			}
			break;
		}

		case STOP_MOTOR_GOING_A:
		{
			StopMotor();
			motor_movement_state = GONE_DONE;
			GUI_ChangeState(WAIT);
			break;		
		}

		case GONE_DONE: 
		{	
			flag_going_movement = 0; 											// Desactivem flag per saber que estem a la GOING.
			flag_return_movement = 1; 											// Activem flag per saber que estem a la tornada. 
				
			if (operation_mode == AA) 
			{
				if (bridge == CLOSED)
				{
					GUI_ChangeState(RUNNING);
					motor_movement_state = START_RETURN_A_CLOSED;			
				}
				else if (bridge == OPEN)
				{
					if (flag_start_motor == 1)
					{	
						flag_start_motor = 0;
						GUI_ChangeState(RUNNING);
						motor_movement_state = START_RETURN_A_OPEN;
					}
				}
			}
			else if (operation_mode == AB) 
			{
				if (bridge == CLOSED)
				{
					Error_End_Reset_Necessary();						// Desactivem temporalment el error de end ja que amb aquest mode haurem d'arribar al final fisic per posicionar-nos
					disable_key_reset(); 								// Desactivem temporalment el botó de reset.
					motor_movement_state = START_RETURN_B_CLOSED;			
				}
				else if (bridge == OPEN)
				{
					GUI_ChangeState(RUNNING);
					motor_movement_state = START_RETURN_A_CLOSED;  // AB OPEN fa el mateix que AA CLOSED.
				}								
			}
			else if (operation_mode == AA_AB)
			{
				if (flag_start_motor == 1)
				{	
					flag_start_motor = 0;
					GUI_ChangeState(RUNNING);
					// Funcionamiento de doble dedo
					motor_movement_state = START_RETURN_A_OPEN;		// Fa la tornada amb el mateix pas que l'anada. 
					
				}
			}
				
			break; 
		}

		case START_RETURN_A_CLOSED:
		{
			dies_number = dies_number + 1; 							// En lugar de +3, la vuelta es +4.
			dies_counter = 0; 
			flag_first_cut = 1; 			
			motor_movement_state = HALF_STEP_RETURN_A_CLOSED;
			break;
		}

		case HALF_STEP_RETURN_A_CLOSED: 
		{
			StartMotor(RIGHT, MOVEMENT_TYPE_HALF_STEP);
			motor_movement_state = WAIT_HALF_STEP_RETURN_A_CLOSED;
			break;		
		}

		case WAIT_HALF_STEP_RETURN_A_CLOSED: 
		{
			if (acceleration_state == STOP)
			{
				position++;
				GUI_DataActualization();
				motor_movement_state = WAIT_STATE_AA_CLOSED;	
				GUI_ChangeState(WAIT);			
			}
			break;
		}

		case WAIT_STATE_AA_CLOSED:
		{
			if (flag_start_motor == 1)
			{
				GUI_ChangeState(RUNNING);
				flag_start_motor = 0; 
				motor_movement_state = DESCENT_CYLINDER;
			}
			break;
		}

		case START_RETURN_A_OPEN:
		{
			// Aqui, al contrari que al closed, no fem el mig pas, pel qual els talls d'anada seran els mateixos que de tornada. 
			dies_counter = 0; 
			flag_first_cut = 1; 			
			motor_movement_state = DESCENT_CYLINDER;
			break;
		}

		case START_RETURN_B_CLOSED:
		{
			dies_number = dies_number; 
			dies_counter = 0;
			flag_first_cut = 1;
			GUI_AB_Closed_Positioning();															// Aquí volem mostrar a la pantalla "POSITIONING"
			GUI_DataActualization();
			motor_movement_state = FINAL_MOVEMENT_RETURN_B_CLOSED;
			break;		
		}

		case FINAL_MOVEMENT_RETURN_B_CLOSED: 
		{
			GUI_Wait_Reset_Start();
			flag_gui_end_movement_stopped = 1;
			disable_key_reset();
			disable_key_start();
			if (flag_came_from_final_movement_stop == 0)					//Solo haremos reset de este contador si no hemos llegado aquí pulsando el botón START i luego STOP.
			{
				obtained_pwm_to_end_counter = 0;
				pwm_to_end_counter = 0;
			}
			else if (flag_came_from_final_movement_stop == 1)				// Si venimos de pulsar stop i start, no hacemos el reset i desactivamos el flag para que solo se haga una vez. 
			{
				flag_came_from_final_movement_stop = 0;
			}
			StartMotor(RIGHT, MOVEMENT_TYPE_END_RETURN_B_CLOSED);
			motor_movement_state = WAIT_FINAL_MOVEMENT_RETURN_B_CLOSED;
			GUI_DataActualization();
			break;
		}

		case WAIT_FINAL_MOVEMENT_RETURN_B_CLOSED:
		{
			if (flag_endswitch_motor == 1)
			{	
				obtained_pwm_to_end_counter = pwm_to_end_counter;					// Guardem a una variable el numero de passos pwm que hem donat fins al end.
				flag_endswitch_motor = 0; 
				motor_movement_state = ENDSWITCH_FOUND; 
			}
			break;
		}

		case ENDSWITCH_FOUND:
		{
			StartDecelerateEndswitch();
			enable_key_reset();
			motor_movement_state = WAIT_FOR_DECELERATING_POSITION;
			flag_gui_end_movement_stopped = 0;
			break;
		}

		case WAIT_FOR_DECELERATING_POSITION:
		{
			if (acceleration_state == STOP)
			{
				StopMotor();
				counter_time_positioning = 0;
				motor_movement_state = TIME_WAIT_LIMITPLUSHALF;
			}
			break;
		}
		case TIME_WAIT_LIMITPLUSHALF:
		{
			if(counter_time_positioning >= 500)
			{
				motor_movement_state = MOVEMENT_LIMITPLUSHALF_RETURN_B_CLOSED;
			}
			break;
		}
		case MOVEMENT_LIMITPLUSHALF_RETURN_B_CLOSED:
		{
			StartMotor(LEFT, MOVEMENT_TYPE_HALFSTEP_LIMIT); 
			motor_movement_state = WAIT_MOVEMENT_LIMITPLUSHALF_RETURN_B_CLOSED;
			break;
		}

		case WAIT_MOVEMENT_LIMITPLUSHALF_RETURN_B_CLOSED: 
		{
			if (acceleration_state == STOP)
			{
				GUI_AB_Closed_Ended_Positioning();														// Aquí deixem de mostrar "POSITIONING"
				GUI_DataActualization();
				GUI_Wait_Set_Start();
				StopMotor();
				Error_End_Set_Necessary();								// Ja hem arribat al punt invers del zero, tornem a activar la interrupció
				motor_movement_state = WAIT_STATE_AB_CLOSED;
				GUI_ChangeState(WAIT);
			}
			break;
		}

		case WAIT_STATE_AB_CLOSED: 
		{
			if(flag_start_motor == 1)
			{
				GUI_ChangeState(RUNNING);
				flag_start_motor = 0; 
				motor_movement_state = DESCENT_CYLINDER;
			}
			break;
		}

		case STEP_DIE_RETURN: 
		{
			StartMotor(LEFT, MOVEMENT_TYPE_STEP);
			motor_movement_state = WAIT_MOVEMENT_RETURN;
			break; 			
		}

		case WAIT_MOVEMENT_RETURN: 
		{
			if (acceleration_state == STOP)
			{
				motor_movement_state = DESCENT_CYLINDER;
			}
			break;		
		}

		case STOP_MOTOR_RETURN: 
		{
			StopMotor();
			if (operation_mode == AA_AB)
			{
				motor_movement_state = CHANGE_STEP_AAAB;
			}
			else if ((operation_mode == AB)&&(bridge == CLOSED))							// Si hem parat pero estem al mode AB closed bridge, haurem de iniciar el posicionament al punt zero.
			{
				motor_movement_state = START_FINAL_POSITIONING_AB_CLOSED;
			}
			else if (((operation_mode == AA)&&(bridge == CLOSED))||((operation_mode == AB)&&(bridge == OPEN)))
			{
				motor_movement_state = LAST_HALF_STEP_CLOSED_AA;
			}
			else
			{
				motor_movement_state = RETURN_COMPLETED; 
			}
			break;			
		}

		case START_FINAL_POSITIONING_AB_CLOSED: 
		{
			Holder_Interrupt_Disable();														// Desactivem la interrupció del holder, en aquest cas ens interessa poder pujar el pisador
			GUI_AB_Closed_ZeroPoisitioning();												// Buscara el zero, volem que mostri pantalla de buscant zero.
			GUI_DataActualization();
			StartMotor(LEFT, MOVEMENT_TYPE_AB_CLOSED_ZEROPOINT);
			motor_movement_state = WAIT_STARTPOINT_POSITIONING_AB;	
			break;
		}
		case WAIT_STARTPOINT_POSITIONING_AB:
		{
			if (acceleration_state == STOP)														// Trobat el zero de la màquina.
			{
				GUI_AB_Closed_Ended_ZeroPositioning();											// No volem que mostri més "BUSCANDO" zero.
				GUI_DataActualization();
				StopMotor();
				Holder_Interrupt_Enable();													// Tornem a activar la interrupció del holder. 
				motor_movement_state = RETURN_COMPLETED; 
			}
			break;
		}

		case LAST_HALF_STEP_CLOSED_AA:
		{
			StartMotor(RIGHT, MOVEMENT_TYPE_HALF_STEP);
			motor_movement_state = WAIT_LAST_HALF_STEP_AA_CLOSED;
			break;
		}
		case WAIT_LAST_HALF_STEP_AA_CLOSED:
		{
			if (acceleration_state == STOP)
			{
				StopMotor();
				motor_movement_state = RETURN_COMPLETED; 										// Trobat, finalitzem.
			}
			break;
		}
		case CHANGE_STEP_AAAB:
		{
			if (counter_dd_times == 0)
			{
				StartMotor(LEFT, MOVEMENT_TYPE_HALF_STEP);
				motor_movement_state = WAIT_HALF_STEP_AAAB;
			}
			else if (counter_dd_times == 1)
			{
				StartMotor(RIGHT, MOVEMENT_TYPE_HALF_STEP);
				motor_movement_state = WAIT_HALF_STEP_AAAB;
			}
			break;
		}

		case WAIT_HALF_STEP_AAAB: 
		{
			if (acceleration_state == STOP)
			{
				StopMotor();
				counter_dd_times++;
				if (counter_dd_times > 1)
				{
					counter_dd_times = 0;
				}
				motor_movement_state = RETURN_COMPLETED;
				
			}
			break;
		}

		case RETURN_COMPLETED:
		{
			motor_movement_state = DROPPING_DONE;
			motor_stop_operating();	
			GUI_Change_MainMenu_Screen(screen_mainmenu_normal);
			GUI_ChangeState(MAIN_MENU);
			break;	
		}

		case DROPPING_DONE: 
		{
			// Ja s'ha completat el troquelado
			break;
		}
	}
}

/********************************************************************
 * Function:	motor_test_mode_motor(void)							*
 * Definition:	Funcio per canviar el mode de autotest.				*
 ********************************************************************/
 void autotest_mode_motor(void)
 {
 	autotest_process_mode = 0;
 }

/********************************************************************
 * Function:	motor_test_mode_cylinder(void)						*
 * Definition:	Funcio per canviar el mode de autotest.				*
 ********************************************************************/
 void autotest_mode_cylinder(void)
 {
 	autotest_process_mode = 1;
 }
/********************************************************************
 * Function:	motor_test_mode_5(void)								*
 * Definition:	Funcio per canviar el mode de autotest.				*
 ********************************************************************/
 void autotest_mode_5(void)
 {
 	autotest_process_mode = 2;
 }
 /********************************************************************
 * Function:	motor_test_mode_6(void)								*
 * Definition:	Funcio per canviar el mode de autotest.				*
 ********************************************************************/
 void autotest_mode_6(void)
 {
 	autotest_process_mode = 3;
 }
 /********************************************************************
 * Function:	motor_test_mode_7(void)								*
 * Definition:	Funcio per canviar el mode de autotest.				*
 ********************************************************************/
 void autotest_mode_7(void)
 {
 	autotest_process_mode = 4;
 }

/********************************************************************
 * Function:	motor_test_reset(void)								*
 * Definition:	Funcio per posar a zero el funcionament del motor.	*
 ********************************************************************/
 void motor_test_reset(void)
 {
 	motor_test_state = START_TURN_A;
 	pwm_steps = 0;
 }

/********************************************************************
 * Function:	motor_test_came_from_autotest(void)					*
 * Definition:	Flag per marcar que anem de autotest.				*
 ********************************************************************/
 void motor_test_came_from_autotest(void)
 {
 	flag_state_came_from = 0;
 }
/********************************************************************
 * Function:	motor_test_came_from_submenu2(void)					*
 * Definition:	Flag per marcar que anem de submenu2.				*
 ********************************************************************/
 void motor_test_came_from_submenu2(void)
 {
 	flag_state_came_from = 1;
 }

/********************************************************************
 * Function:	motor_test_tasks(void)								*
 * Definition:	Estats del procediment de test del motor.			*
 ********************************************************************/
void motor_test_tasks(void)
{
	switch (motor_test_state)
	{
		case START_TURN_A: 
		{
			BEEP = 1;
			DelayMs(300);
			BEEP = 0;
			if (autotest_process_mode == 0)
			{	
				StartMotor(RIGHT,MOVEMENT_TYPE_TEST_MOTOR);
			}
			else if (autotest_process_mode == 1)
			{
				counter_time_test = 0;
				OUT_EVCIL = DESCENT;
			}
			else if (autotest_process_mode == 2)
			{
				counter_time_test = 0;
				OUT_5 = 0;
			}
			else if (autotest_process_mode == 3)
			{
				counter_time_test = 0;
				OUT_6 = 0;
			}
			else if (autotest_process_mode == 4)
			{
				counter_time_test = 0;
				OUT_7 = 0;
			}
			motor_test_state = WAIT_TURN_A;
			break;
		}
		case WAIT_TURN_A:
		{
			if (autotest_process_mode == 0)
			{	
				if (acceleration_state == STOP)
				{
					StopMotor();
					test_time_counter = 0; 
					motor_test_state = START_TURN_B;
				}
			}
			else if (autotest_process_mode == 1)
			{
				if (counter_time_test >= 2000)
				{
					test_time_counter = 0;
					motor_test_state = START_TURN_B;
				}
			}
			else if (autotest_process_mode == 2)
			{
				if (counter_time_test >= 2000)
				{
					test_time_counter = 0;
					motor_test_state = START_TURN_B;
				}
			}
			else if (autotest_process_mode == 3)
			{
				if (counter_time_test >= 2000)
				{
					test_time_counter = 0;
					motor_test_state = START_TURN_B;
				}
			}
			else if (autotest_process_mode == 4)
			{
				if (counter_time_test >= 2000)
				{
					test_time_counter = 0;
					motor_test_state = START_TURN_B;
				}
			}
			break;
		}
		case START_TURN_B:
		{	
			if (autotest_process_mode == 0)
			{	
				if (test_time_counter >= 1000)
				{	
					StartMotor(LEFT,MOVEMENT_TYPE_TEST_MOTOR);
					pwm_steps = 0;
					test_time_counter = 0; 
					motor_test_state = WAIT_TURN_B;

				}
			}	
			else if (autotest_process_mode == 1)
			{
				counter_time_test = 0;
				OUT_EVCIL = RISE;
				motor_test_state = WAIT_TURN_B;
			}
			else if (autotest_process_mode == 2)
			{
				counter_time_test = 0;
				OUT_5 = 1;
				motor_test_state = WAIT_TURN_B;
			}
			else if (autotest_process_mode == 3)
			{
				counter_time_test = 0;
				OUT_6 = 1;
				motor_test_state = WAIT_TURN_B;
			}
			else if (autotest_process_mode == 4)
			{
				counter_time_test = 0;
				OUT_7 = 1;
				motor_test_state = WAIT_TURN_B;
			}
			break;
		}
		case WAIT_TURN_B:
		{
			if (autotest_process_mode == 0)
			{	
				if (acceleration_state == STOP)
				{
					StopMotor();
					test_time_counter = 0; 
					motor_test_state = END_TEST_MOTOR;
					autotest_motor_done();
					GUI_Set_From_Autotest();					// Flag de venir d'autotest, no vull que es neteji la pantalla
					BEEP = 1;
					DelayMs(300);
					BEEP = 0;
					if (flag_state_came_from == 0)
					{
						GUI_ChangeState(AUTOTEST);
					}
					else if (flag_state_came_from == 1)
					{
						GUI_ChangeState(SUBMENU2);
					}
				
				}
			}
			else if (autotest_process_mode == 1)
			{
				motor_test_state = END_TEST_MOTOR;
				autotest_motor_done();		
				GUI_Set_From_Autotest();					// Flag de venir d'autotest, no vull que es neteji la pantalla
				BEEP = 1;
				DelayMs(300);
				BEEP = 0;
				if (flag_state_came_from == 0)
				{
					GUI_ChangeState(AUTOTEST);
				}
				else if (flag_state_came_from == 1)
				{
					GUI_ChangeState(SUBMENU2);
				}
			}
			else if (autotest_process_mode == 2)
			{
				motor_test_state = END_TEST_MOTOR;
				autotest_motor_done();		
				GUI_Set_From_Autotest();					// Flag de venir d'autotest, no vull que es neteji la pantalla
				BEEP = 1;
				DelayMs(300);
				BEEP = 0;
				if (flag_state_came_from == 0)
				{
					GUI_ChangeState(AUTOTEST);
				}
				else if (flag_state_came_from == 1)
				{
					GUI_ChangeState(SUBMENU2);
				}
			}
			else if (autotest_process_mode == 3)
			{
				motor_test_state = END_TEST_MOTOR;
				autotest_motor_done();		
				GUI_Set_From_Autotest();					// Flag de venir d'autotest, no vull que es neteji la pantalla
				BEEP = 1;
				DelayMs(300);
				BEEP = 0;
				if (flag_state_came_from == 0)
				{
					GUI_ChangeState(AUTOTEST);
				}
				else if (flag_state_came_from == 1)
				{
					GUI_ChangeState(SUBMENU2);
				}
			}
			else if (autotest_process_mode == 4)
			{
				motor_test_state = END_TEST_MOTOR;
				autotest_motor_done();		
				GUI_Set_From_Autotest();					// Flag de venir d'autotest, no vull que es neteji la pantalla
				BEEP = 1;
				DelayMs(300);
				BEEP = 0;
				if (flag_state_came_from == 0)
				{
					GUI_ChangeState(AUTOTEST);
				}
				else if (flag_state_came_from == 1)
				{
					GUI_ChangeState(SUBMENU2);
				}
			}
			break;
		}
		case END_TEST_MOTOR:
		{
			break;
		}
	}
}
