/********************************************************************
 * FileName:		Timers.c										*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Codi per inicialitzar els timers del sistema.					*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		17/10/18		Versió inicial.					*
 *																	*
 ********************************************************************/

#include "main.h" 

/***************** Definició de subrutines usades *******************/

/********************************************************************
 * Function:	Config_Timer1()										*
 * Definition:	Configura el timer 1 (tick general).				*
 ********************************************************************/
void Config_Timer1(void)
{
	// Timer 1 configurado para que produzca una interrupción cada 1 ms.
	ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_1);				// Enable Timer1 interrupt, interrupt priority 1.
	OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, T1_TICK);	// Enable Timer1, internal clk, prescaler 1:64; PR1.
	// Ahora mismo voy a 80MHz
	// un tick del Timer1 = (1/80M)*64 = 1250KHz (0.8us). Su interrupción es cada 1250 => 1250/1250KHz = 1ms
}
 /********************************************************************
 * Function:	Config_Timer2()										*
 * Definition:	Configura el timer 2. 1 us. Para PWM.				*
 ********************************************************************/
void Config_Timer2(void)
{
	// Timer 2 configurado para que produzca una interrupción cada 1 us.
	ConfigIntTimer2(T2_INT_OFF | T2_INT_PRIOR_3);			// Enable Timer2 interrupt, interrupt priority 3.
	OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, T2_TICK);		// Enable Timer2, internal clk, prescaler 1:1; PR2 = 10.
	// Ahora mismo voy a 80MHz
	// un tick del Timer2 = (1/80M)*1 = 80MHz (0.0125us). Su interrupción es cada 10 => 80/80MHz = 1us
}


/********************************************************************
 * Function:	Config_Timer3()										*
 * Definition:	Configura el timer 3. PWM shine i Contrast.			*
 ********************************************************************/
void Config_Timer3(void)
{
	// Open Timer3 with Period register value
	OpenTimer3(T3_ON | T3_PS_1_16, T3_TICK);	// Aquí pones la frecuencia.
	// No configurem interrupcions ja que sols el volem per al PWM de shine i contrast. 
	// A 80MHz
	// un tick del Timer3 = (1/80M)*16 = 5MHz(0.2us).
}

/********************************************************************
 * Function:	Config_Timer4()										*
 * Definition:	Configura el timer 4. 100 ms. Cilindro.				*
 ********************************************************************/
void Config_Timer4(void)
{
	// Timer 4 configurado para que produzca una interrupción cada 100 ms.
	ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_3);				// Enable Timer4 interrupt, interrupt priority 3.
	OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_256, T4_TICK);	// Enable Timer4, internal clk, prescaler 1:256; PR4 = 31250.
	// Ahora mismo voy a 80MHz
	// un tick del Timer4 = (1/80M)*256 = 312,5KHz (3.2us). Su interrupción es cada 31250 => 31250/312,5KHz = 100ms
}

/********************************************************************
 * Function:	Config_Timer5()										*
 * Definition:	Configura el timer 5. 100 ms. 						*
 ********************************************************************/
void Config_Timer5(void)
{
	// Timer 5 configurado para que produzca una interrupción cada 1 us.
	ConfigIntTimer5(T5_INT_ON | T5_INT_PRIOR_3);				// Enable Timer5 interrupt, interrupt priority 3.
	OpenTimer5(T5_ON | T5_SOURCE_INT | T5_PS_1_256, T5_TICK);	// Enable Timer5, internal clk, prescaler 1:1; PR4 = 10.
	// Ahora mismo voy a 80MHz
	// un tick del Timer4 = (1/80M)*1 = 80MHz (0.0125us). Su interrupción es cada 10 => 80/80MHz = 1us
}
