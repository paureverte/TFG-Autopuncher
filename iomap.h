/********************************************************************
 * FileName:		iomap.h											*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Mapa d'entrades / sortides.									*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		15/10/18		Versió inicial.					*
 *																	*
 ********************************************************************/
#ifndef IOMAP_H
#define IOMAP_H

#include <p32xxxx.h>

// Salidas
#define MOTOR_EN_TRIS		TRISCbits.TRISC1
#define MOTOR_EN			LATCbits.LATC1
#define MOTOR_DIR_TRIS		TRISCbits.TRISC2
#define MOTOR_DIR			LATCbits.LATC2
#define OUT_EVCIL_TRIS		TRISAbits.TRISA2
#define OUT_EVCIL			LATAbits.LATA2
#define OUT_CP_TRIS			TRISDbits.TRISD3
#define OUT_CP				LATDbits.LATD3
#define BEACON_START_TRIS	TRISBbits.TRISB13
#define BEACON_START 		LATBbits.LATB13
#define BEACON_STOP_TRIS	TRISBbits.TRISB14
#define BEACON_STOP 		LATBbits.LATB14
#define OUT_5_TRIS			TRISAbits.TRISA3
#define OUT_5				LATAbits.LATA3
#define OUT_6_TRIS			TRISAbits.TRISA4
#define OUT_6				LATAbits.LATA4
#define OUT_7_TRIS			TRISAbits.TRISA5
#define OUT_7				LATAbits.LATA5


// Control lcd
#define FS_TRIS				TRISCbits.TRISC3
#define FS					LATCbits.LATC3
#define CE_TRIS				TRISDbits.TRISD11
#define CE					LATDbits.LATD11
#define W_R_TRIS			TRISDbits.TRISD4
#define W_R					LATDbits.LATD4
#define RD_TRIS				TRISDbits.TRISD5
#define RD					LATDbits.LATD5
#define RST_LCD_TRIS		TRISGbits.TRISG12
#define RST_LCD				LATGbits.LATG12
#define CD_TRIS				TRISGbits.TRISG13
#define CD					LATGbits.LATG13

// Datos lcd
#define D0_TRIS				TRISEbits.TRISE0
#define D0					LATEbits.LATE0
#define D1_TRIS				TRISEbits.TRISE1
#define D1					LATEbits.LATE1
#define D2_TRIS				TRISEbits.TRISE2
#define D2					LATEbits.LATE2
#define D3_TRIS				TRISEbits.TRISE3
#define D3					LATEbits.LATE3
#define D4_TRIS				TRISEbits.TRISE4
#define D4					LATEbits.LATE4
#define D5_TRIS				TRISEbits.TRISE5
#define D5					LATEbits.LATE5
#define D6_TRIS				TRISEbits.TRISE6
#define D6					LATEbits.LATE6
#define D7_TRIS				TRISEbits.TRISE7
#define D7					LATEbits.LATE7

// Switches de entrada
#define PISW_TRIS			TRISGbits.TRISG8
#define PISW				PORTGbits.RG8
#define CIDESSW_TRIS		TRISDbits.TRISD14
#define CIDESSW				PORTDbits.RD14
#define ZESW_TRIS			TRISBbits.TRISB2
#define ZESW				PORTBbits.RB2
#define SEDOSW_TRIS			TRISCbits.TRISC13
#define SEDOSW				PORTCbits.RC13
#define FISW_TRIS			TRISCbits.TRISC14
#define FISW				PORTCbits.RC14
//#define FISW_TRIS			TRISBbits.TRISB15
//#define FISW				PORTBbits.RB15
#define EMSTSW_TRIS			TRISEbits.TRISE8
#define EMSTSW				PORTEbits.RE8
#define INPUT7_TRIS			TRISBbits.TRISB5
#define INPUT7				PORTBbits.RB5
#define INPUT8_TRIS			TRISBbits.TRISB4
#define INPUT8				PORTBbits.RB4
#define INPUT9_TRIS			TRISBbits.TRISB3
#define INPUT9				PORTBbits.RB3

// Leds
#define LED_RUN_TRIS		TRISGbtis.TRISG15
#define LED_RUN 			LATGbits.LATG15
#define LED_AB_TRIS			TRISAbits.TRISA7
#define LED_AB				LATAbits.LATA7
#define LED_AA_TRIS			TRISGbits.TRISG14
#define LED_AA				LATGbits.LATG14
#define LED_START_TRIS		TRISFbits.TRISF13
#define LED_START			LATFbits.LATF13
#define LED_STOP_TRIS		TRISBbits.TRISB12
#define LED_STOP			LATBbits.LATB12
#define LED_ENTER_TRIS		TRISDbits.TRISD6
#define LED_ENTER			LATDbits.LATD6
#define LED_ESC_TRIS		TRISDbits.TRISD7
#define LED_ESC 			LATDbits.LATD7
#define LED_PUNCH_TRIS		TRISFbits.TRISF0
#define LED_PUNCH			LATFbits.LATF0
#define LED_STEP_TRIS		TRISFbits.TRISF1
#define LED_STEP			LATFbits.LATF1
#define LED_BELT_TRIS		TRISGbtis.TRISG1
#define LED_BELT			LATGbits.LATG1
#define LED_RESET_TRIS		TRISGbtis.TRISG0
#define LED_RESET			LATGbits.LATG0
#define LED_MENU_TRIS		TRISAbits.TRISA6
#define LED_MENU			LATAbits.LATA6
#define LED_N0_TRIS 		TRISDbits.TRISD13
#define LED_N0 				LATDbits.LATD13
#define LED_N1_TRIS 		TRISDbits.TRISD12
#define LED_N1 				LATDbits.LATD12
#define LED_N2_TRIS 		TRISDbits.TRISD8
#define LED_N2 				LATDbits.LATD8
#define LED_N3_TRIS			TRISGbits.TRISG6
#define LED_N3 				LATGbits.LATG6
#define LED_N4_TRIS			TRISGbits.TRISG7
#define LED_N4 				LATGbits.LATG7
#define LED_N5_TRIS			TRISCbits.TRISC4
#define LED_N5 				LATCbits.LATC4
#define LED_N6_TRIS			TRISGbits.TRISG9
#define LED_N6				LATGbits.LATG9
#define LED_N7_TRIS			TRISBbits.TRISB1
#define LED_N7				LATBbits.LATB1
#define LED_N8_TRIS			TRISBbits.TRISB0
#define LED_N8				LATBbits.LATB0
#define LED_N9_TRIS			TRISAbits.TRISA1
#define LED_N9				LATAbits.LATA1

// Definiciones para USB
#define D_MAS_TRIS			TRISGbits.TRISG2
#define D_MAS				LATGbits.LATG2
#define D_MENOS_TRIS		TRISGbits.TRISG3
#define D_MENOS				LATGbits.LATG3

// PWM
#define PWM_CONTRAST_TRIS	TRISDbits.TRISD1
#define PWM_CONTRAST		LATDbits.LATD1
#define PWM_LED_TRIS		TRISDbits.TRISD2
#define PWM_LED				LATDbits.LATD2

#define BEEP_TRIS			TRISBbits.TRISB15
#define BEEP				LATBbits.LATB15

//I2C
#define SCL_1_TRIS			TRISAbits.TRISA14
#define SCL_1 				LATAbits.LATA14
#define SCL_1_PORT			PORTAbits.RA14
#define SDA_1_TRIS			TRISAbits.TRISA15
#define SDA_1_PORT			PORTAbits.RA15
#define SDA_1 				LATAbits.LATA15
#define RST_D_TRIS 			TRISDbits.TRISD15
#define RST_D 				LATDbits.LATD15
#define RXU_D_TRIS			TRISFbits.TRISF4
#define RXU_D 				PORTFbits.LATF4
#define TXU_D_TRIS			TRISFbits.TRISF5
#define TXU_D 				LATFbits.LATF5
#define RST_BT_TRIS			TRISFbits.TRISF3
#define RST_BT 				LATFbits.LATF3
#define RXU_BT_TRIS			TRISFbits.TRISF2
#define RXU_BT 				PORTFbits.LATF2
#define TXU_BT_TRIS			TRISFbits.TRISF8
#define TXU_BT 				LATFbits.LATF8
#define ALERT_INT_TRIS		TRISDbits.TRISD0
#define ALTERT_INT			PORTDbits.RD0
#define RST_KBD_TRIS		TRISDbits.TRISD9
#define RST_KBD 			LATDbits.LATD9

#endif
/****************************** EOF *********************************/
