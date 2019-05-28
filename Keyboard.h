/********************************************************************
 * FileName:		keyboard.h										*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibreria per keyboard.c										*
 *																	*
 * Change History:			Versio 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverte		30/10/18		Versio inicial.					*
 *																	*
 ********************************************************************/

#ifndef keyboard_H
#define keyboard_H

#define READ_KEYBOARD_EVERY_MS 30
#define KEYBOARD_LONG_PRESS_KEYBOARD_TICKS 100 /* every tick is READ_KEYBOARD_EVERY_MS */
#define KEYBOARD_SHORT_PRESS_TICKS 1

/***************** Types *****************/ 

typedef enum
{
	KEY_AA,
	KEY_AB,
	KEY_START,
	KEY_STOP,
	KEY_RESET,
	KEY_MENU,
	KEY_MENU_3S,
	KEY_SECRET,
	KEY_AAAB,
	KEY_ENTER,
	KEY_ENTER_3S,
	KEY_N1,
	KEY_N2,
	KEY_N3,
	KEY_N4,
	KEY_N5,
	KEY_N6,
	KEY_N7,
	KEY_N7,
	KEY_N8,
	KEY_N9,
	KEY_N0,
	KEY_ESC,
	KEY_BELT,
	KEY_STEP,
	KEY_PUNCH
}type_key;											// Type para les tecles.

typedef void (*myCallbackType)(type_key, ...);			// Type del callback per a entrar-li com a variable la tecla polsada.

typedef enum type_StateKeyboardRead
{
	KEYBOARD_INIT = 0,
	KEYBOARD_WAIT,
	KEYBOARD_DONE
	
} type_StateKeyboardRead;


/***************** Definicio de subrutines usades *******************/
void Keyboard_SetMyCallback(myCallbackType callback);
void Keyboard_Initialize(void);
void Keyboard_Read(void);



#endif
