/********************************************************************
 * FileName:		Timers.h										*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per Timers.c										*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		17/10/18		Versió inicial.					*
 *																	*
 ********************************************************************/

#ifndef TIMER_H
#define TIMER_H

/***************** Definició de subrutines usades *******************/

void Config_Timer1(void);
void Config_Timer2(void);
void Config_Timer3(void);
void Config_Timer4(void);
void Config_Timer5(void); 

/*************************** Definicions ****************************/

/* TIMER 1 */

	#define T1_ON	      	                (1 << _T1CON_ON_POSITION)	    /* Timer1 ON */
	#define T1_OFF							(0)

	#define T1_IDLE_STOP			        (1 << _T1CON_SIDL_POSITION)		/* stop during idle */
	#define T1_IDLE_CON						(0)								/* operate during idle */

	#define T1_TMWDIS_ON 					(1 << _T1CON_TMWDIS_POSITION)	/* Asynchronous Write Disable */
	#define T1_TMWDIS_OFF					(0)

	#define T1_GATE_ON		                (1 << _T1CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
	#define T1_GATE_OFF						(0)

	#define T1_PS_1_256                     (3 << _T1CON_TCKPS_POSITION)    /* Prescaler 1:256 */
	#define T1_PS_1_64                      (2 << _T1CON_TCKPS_POSITION)    /*           1:64 */
	#define T1_PS_1_8                       (1 << _T1CON_TCKPS_POSITION)    /*           1:8 */
	#define T1_PS_1_1                       (0)								/*           1:1 */

	#define T1_SYNC_EXT_ON                  (1 << _T1CON_TSYNC_POSITION)    /* Synch external clk input */
	#define T1_SYNC_EXT_OFF					(0)

	#define T1_SOURCE_EXT                   (1 << _T1CON_TCS_POSITION)      /* External clock source */
	#define T1_SOURCE_INT					(0)								/* Internal clock source */
	
	#define T1_INT_ON		            	(1 << 15)
	#define T1_INT_OFF						(0)

	#define T1_INT_PRIOR_7                  (7) // Timer int priority 7
	#define T1_INT_PRIOR_6                  (6) // Timer int priority 6
	#define T1_INT_PRIOR_5                  (5) // Timer int priority 5
	#define T1_INT_PRIOR_4                  (4) // Timer int priority 4
	#define T1_INT_PRIOR_3                  (3) // Timer int priority 3
	#define T1_INT_PRIOR_2                  (2) // Timer int priority 2
	#define T1_INT_PRIOR_1                  (1) // Timer int priority 1
	#define T1_INT_PRIOR_0                  (0) // Timer int priority 0

	#define T1_INT_SUB_PRIOR_3              (3 << 4) // Timer int sub priority 3
	#define T1_INT_SUB_PRIOR_2              (2 << 4) // Timer int sub priority 2
	#define T1_INT_SUB_PRIOR_1              (1 << 4) // Timer int sub priority 1
	#define T1_INT_SUB_PRIOR_0              (0 << 4) // Timer int sub priority 0
	
	#define T1_TICK							1250
	
	
/* TIMER 2 */

	#define T2_ON                           (1 << _T2CON_ON_POSITION)		/* Timer2 ON */
	#define T2_OFF							(0)

	#define T2_IDLE_STOP                    (1 << _T2CON_SIDL_POSITION)		/* stop during idle */
	#define T2_IDLE_CON 					(0)								/* operate during idle */

	#define T2_GATE_ON                      (1 << _T2CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
	#define T2_GATE_OFF						(0)

	#define T2_PS_1_256                     (7 << _T2CON_TCKPS_POSITION)    /* Prescaler 1:256 */
	#define T2_PS_1_64                      (6 << _T2CON_TCKPS_POSITION)    /*           1:64 */
	#define T2_PS_1_32                      (5 << _T2CON_TCKPS_POSITION)    /*           1:32 */
	#define T2_PS_1_16                      (4 << _T2CON_TCKPS_POSITION)    /*           1:16 */
	#define T2_PS_1_8                       (3 << _T2CON_TCKPS_POSITION)    /*           1:8 */
	#define T2_PS_1_4                       (2 << _T2CON_TCKPS_POSITION)    /*           1:4 */
	#define T2_PS_1_2                       (1 << _T2CON_TCKPS_POSITION)    /*           1:2 */
	#define T2_PS_1_1                       (0)								/*           1:1 */

	#define T2_32BIT_MODE_ON                (1 << _T2CON_T32_POSITION)      /* Enable 32-bit mode */
	#define T2_32BIT_MODE_OFF				(0)

	#define T2_SOURCE_EXT                   (1 << _T2CON_TCS_POSITION)      /* External clock source */
	#define T2_SOURCE_INT					(0)								/* Internal clock source */					
	
	#define T2_INT_ON			            (1 << 15)		/* T2 Interrupt Enable */
	#define T2_INT_OFF						(0)

	#define T2_INT_PRIOR_7                  (7)
	#define T2_INT_PRIOR_6                  (6)
	#define T2_INT_PRIOR_5                  (5)
	#define T2_INT_PRIOR_4                  (4)
	#define T2_INT_PRIOR_3                  (3)
	#define T2_INT_PRIOR_2                  (2)
	#define T2_INT_PRIOR_1                  (1)
	#define T2_INT_PRIOR_0                  (0)

	#define T2_INT_SUB_PRIOR_3              (3 << 4)
	#define T2_INT_SUB_PRIOR_2              (2 << 4)
	#define T2_INT_SUB_PRIOR_1              (1 << 4)
	#define T2_INT_SUB_PRIOR_0              (0 << 4)

	#define T2_TICK 						1
	

/* TIMER 3 */

	#define T3_ON                           (1 << _T3CON_ON_POSITION)		/* Timer3 ON */
	#define T3_OFF							(0)

	#define T3_IDLE_STOP                    (1 << _T3CON_SIDL_POSITION)		/* stop during idle */
	#define T3_IDLE_CON 					(0)								/* operate during idle */

	#define T3_GATE_ON                      (1 << _T3CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
	#define T3_GATE_OFF						(0)

	#define T3_PS_1_256                     (7 << _T3CON_TCKPS_POSITION)    /* Prescaler 1:256 */
	#define T3_PS_1_64                      (6 << _T3CON_TCKPS_POSITION)    /*           1:64 */
	#define T3_PS_1_32                      (5 << _T3CON_TCKPS_POSITION)    /*           1:32 */
	#define T3_PS_1_16                      (4 << _T3CON_TCKPS_POSITION)    /*           1:16 */
	#define T3_PS_1_8                       (3 << _T3CON_TCKPS_POSITION)    /*           1:8 */
	#define T3_PS_1_4                       (2 << _T3CON_TCKPS_POSITION)    /*           1:4 */
	#define T3_PS_1_2                       (1 << _T3CON_TCKPS_POSITION)    /*           1:2 */
	#define T3_PS_1_1                       (0)								/*           1:1 */

	#define T3_SOURCE_EXT                   (1 << _T3CON_TCS_POSITION)      /* External clock source */
	#define T3_SOURCE_INT					(0)								/* Internal clock source */

	#define T3_INT_ON			            (1<<15)		/* Interrupt Enable */
	#define T3_INT_OFF						(0)

	#define T3_INT_PRIOR_7                  (7)
	#define T3_INT_PRIOR_6                  (6)
	#define T3_INT_PRIOR_5                  (5)
	#define T3_INT_PRIOR_4                  (4)
	#define T3_INT_PRIOR_3                  (3)
	#define T3_INT_PRIOR_2                  (2)
	#define T3_INT_PRIOR_1                  (1)
	#define T3_INT_PRIOR_0                  (0)

	#define T3_INT_SUB_PRIOR_3              (3 << 4)
	#define T3_INT_SUB_PRIOR_2              (2 << 4)
	#define T3_INT_SUB_PRIOR_1              (1 << 4)
	#define T3_INT_SUB_PRIOR_0              (0 << 4)

	#define T3_TICK 						2500
	
/* TIMER 4 */

	#define T4_ON                           (1 << _T4CON_ON_POSITION)		/* Timer4 ON */
	#define T4_OFF							(0)

	#define T4_IDLE_STOP                    (1 << _T4CON_SIDL_POSITION)		/* stop during idle */
	#define T4_IDLE_CON						(0)								/* operate during idle */
       
	#define T4_GATE_ON                      (1 << _T4CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
	#define T4_GATE_OFF						(0)

	#define T4_PS_1_256                     (7 << _T4CON_TCKPS_POSITION)    /* Prescaler 1:256 */
	#define T4_PS_1_64                      (6 << _T4CON_TCKPS_POSITION)    /*           1:64 */
	#define T4_PS_1_32                      (5 << _T4CON_TCKPS_POSITION)    /*           1:32 */
	#define T4_PS_1_16                      (4 << _T4CON_TCKPS_POSITION)    /*           1:16 */
	#define T4_PS_1_8                       (3 << _T4CON_TCKPS_POSITION)    /*           1:8 */
	#define T4_PS_1_4                       (2 << _T4CON_TCKPS_POSITION)    /*           1:4 */
	#define T4_PS_1_2                       (1 << _T4CON_TCKPS_POSITION)    /*           1:2 */
	#define T4_PS_1_1                       (0)								/*           1:1 */

	#define T4_32BIT_MODE_ON                (1 << _T4CON_T32_POSITION)      /* Enable 32-bit mode */
	#define T4_32BIT_MODE_OFF				(0)

	#define T4_SOURCE_EXT                   (1 << _T4CON_TCS_POSITION)      /* External clock source */
	#define T4_SOURCE_INT					(0)								/* Internal clock source */

	#define T4_INT_ON			            (1<<15)		/* Interrupt Enable */
	#define T4_INT_OFF						(0)

	#define T4_INT_PRIOR_7                  (7)
	#define T4_INT_PRIOR_6                  (6)
	#define T4_INT_PRIOR_5                  (5)
	#define T4_INT_PRIOR_4                  (4)
	#define T4_INT_PRIOR_3                  (3)
	#define T4_INT_PRIOR_2                  (2)
	#define T4_INT_PRIOR_1                  (1)
	#define T4_INT_PRIOR_0                  (0)

	#define T4_INT_SUB_PRIOR_3              (3 << 4)
	#define T4_INT_SUB_PRIOR_2              (2 << 4)
	#define T4_INT_SUB_PRIOR_1              (1 << 4)
	#define T4_INT_SUB_PRIOR_0              (0 << 4)

	#define T4_TICK 						31250
	
/* TIMER 5 */

	#define T5_ON                           (1 << _T5CON_ON_POSITION)		/* Timer5 ON */
	#define T5_OFF							(0)

	#define T5_IDLE_STOP                    (1 << _T5CON_SIDL_POSITION)		/* stop during idle */
	#define T5_IDLE_CON 					(0)								/* operate during idle */

	#define T5_GATE_ON                      (1 << _T5CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
	#define T5_GATE_OFF						(0)

	#define T5_PS_1_256                     (7 << _T5CON_TCKPS_POSITION)    /* Prescaler 1:256 */
	#define T5_PS_1_64                      (6 << _T5CON_TCKPS_POSITION)    /*           1:64 */
	#define T5_PS_1_32                      (5 << _T5CON_TCKPS_POSITION)    /*           1:32 */
	#define T5_PS_1_16                      (4 << _T5CON_TCKPS_POSITION)    /*           1:16 */
	#define T5_PS_1_8                       (3 << _T5CON_TCKPS_POSITION)    /*           1:8 */
	#define T5_PS_1_4                       (2 << _T5CON_TCKPS_POSITION)    /*           1:4 */
	#define T5_PS_1_2                       (1 << _T5CON_TCKPS_POSITION)    /*           1:2 */
	#define T5_PS_1_1                       (0)								/*           1:1 */

	#define T5_SOURCE_EXT                   (1 << _T5CON_TCS_POSITION)      /* External clock source */
	#define T5_SOURCE_INT					(0)								/* Internal clock source */

	#define T5_INT_ON			            (1<<15)		/* Interrupt Enable */
	#define T5_INT_OFF						(0)

	#define T5_INT_PRIOR_7                  (7)
	#define T5_INT_PRIOR_6                  (6)
	#define T5_INT_PRIOR_5                  (5)
	#define T5_INT_PRIOR_4                  (4)
	#define T5_INT_PRIOR_3                  (3)
	#define T5_INT_PRIOR_2                  (2)
	#define T5_INT_PRIOR_1                  (1)
	#define T5_INT_PRIOR_0                  (0)

	#define T5_INT_SUB_PRIOR_3              (3 << 4)
	#define T5_INT_SUB_PRIOR_2              (2 << 4)
	#define T5_INT_SUB_PRIOR_1              (1 << 4)
	#define T5_INT_SUB_PRIOR_0              (0 << 4)

	#define T5_TICK 						31250

#endif
