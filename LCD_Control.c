/********************************************************************
 * FileName:		LCD_Control.c									*
 * Dependencies:	LCD_Control.h									*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*	
 * 	- Funcions de control de pantalla LCD Winstar 24064C i 			*
 *		driver T6963.												*	
 *																	*
 * Change History:													*
 *																	*
 * Name				Date            Changes							*	
 * -----			-----			--------						*
 * P.Reverté		29/10/18		Versió inicial	 				*
 * 																	*
 ********************************************************************/
#include "main.h"


void screen_clean_modifying_bars(void);
void clean_modifying_lines_screen(void);


// Dibuixos //

unsigned const char welcome[] =
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3,0xF8,0x1,0xF0,0x7,0xC7,0xFF,0xFF,0x0,0x3F,0x80,0x0,0x0,0x3,0xFF,0xF8,0xF,0x80,0x3E,0x1F,0x80,0x3C,0x0,0x7F,0x0,0x3E,0x0,0xF8,0x7F,0xFF,0xE1,0xFF,0xFE,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3,0xF8,0x1,0xF0,0x7,0xC7,0xFF,0xFF,0x1,0xFF,0xF0,0x0,0x0,0x3,0xFF,0xFC,0xF,0x80,0x3E,0x1F,0x80,0x3C,0x3,0xFF,0xC0,0x3E,0x0,0xF8,0x7F,0xFF,0xE1,0xFF,0xFF,0x80,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0xFC,0x1,0xF0,0x7,0xC7,0xFF,0xFF,0x3,0xFF,0xF8,0x0,0x0,0x3,0xFF,0xFE,0xF,0x80,0x3E,0x1F,0xC0,0x3C,0x7,0xFF,0xE0,0x3E,0x0,0xF8,0x7F,0xFF,0xE1,0xFF,0xFF,0xC0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0xFC,0x1,0xF0,0x7,0xC7,0xFF,0xFF,0x7,0xFF,0xFC,0x0,0x0,0x3,0xFF,0xFF,0xF,0x80,0x3E,0x1F,0xC0,0x3C,0xF,0xFF,0xF0,0x3E,0x0,0xF8,0x7F,0xFF,0xE1,0xFF,0xFF,0xC0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0xBC,0x1,0xF0,0x7,0xC0,0xF,0x80,0xF,0xE0,0xFE,0x0,0x0,0x3,0xF0,0x3F,0x8F,0x80,0x3E,0x1F,0xE0,0x3C,0x1F,0x83,0xF8,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0x7,0xE0,0x0,0x0,
0x0,0x0,0x0,0x0,0xF,0xBE,0x1,0xF0,0x7,0xC0,0xF,0x80,0x1F,0x80,0x3F,0x0,0x0,0x3,0xF0,0x1F,0x8F,0x80,0x3E,0x1F,0xE0,0x3C,0x3F,0x0,0xF8,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0x3,0xE0,0x0,0x0,
0x0,0x0,0x0,0x0,0xF,0xBE,0x1,0xF0,0x7,0xC0,0xF,0x80,0x1F,0x0,0x1F,0x0,0x0,0x3,0xF0,0xF,0x8F,0x80,0x3E,0x1F,0xF0,0x3C,0x3E,0x0,0xFC,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0x3,0xE0,0x0,0x0,
0x0,0x0,0x0,0x0,0xF,0x1E,0x1,0xF0,0x7,0xC0,0xF,0x80,0x1F,0x0,0x1F,0x0,0x0,0x3,0xF0,0xF,0x8F,0x80,0x3E,0x1E,0xF0,0x3C,0x3E,0x0,0x70,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0x3,0xE0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1F,0x1F,0x1,0xF0,0x7,0xC0,0xF,0x80,0x3E,0x0,0xF,0x80,0x0,0x3,0xF0,0xF,0x8F,0x80,0x3E,0x1E,0xF8,0x3C,0x7C,0x0,0x0,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0x3,0xE0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1F,0x1F,0x1,0xF0,0x7,0xC0,0xF,0x80,0x3E,0x0,0xF,0x80,0x0,0x3,0xF0,0x1F,0x8F,0x80,0x3E,0x1E,0x78,0x3C,0x7C,0x0,0x0,0x3F,0xFF,0xF8,0x7F,0xFF,0xC1,0xF0,0x7,0xC0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1E,0xF,0x1,0xF0,0x7,0xC0,0xF,0x80,0x3E,0x0,0xF,0x80,0x0,0x3,0xF0,0x3F,0x8F,0x80,0x3E,0x1E,0x7C,0x3C,0x7C,0x0,0x0,0x3F,0xFF,0xF8,0x7F,0xFF,0xC1,0xFF,0xFF,0xC0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3E,0xF,0x81,0xF0,0x7,0xC0,0xF,0x80,0x3E,0x0,0xF,0x80,0x0,0x3,0xFF,0xFF,0xF,0x80,0x3E,0x1E,0x3C,0x3C,0x7C,0x0,0x0,0x3F,0xFF,0xF8,0x7F,0xFF,0xC1,0xFF,0xFF,0x80,0x0,0x0,
0x0,0x0,0x0,0x0,0x3E,0xF,0x81,0xF0,0x7,0xC0,0xF,0x80,0x3E,0x0,0xF,0x80,0x0,0x3,0xFF,0xFE,0xF,0x80,0x3E,0x1E,0x3E,0x3C,0x7C,0x0,0x0,0x3F,0xFF,0xF8,0x7F,0xFF,0xC1,0xFF,0xFF,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3E,0xF,0x81,0xF0,0x7,0xC0,0xF,0x80,0x3E,0x0,0xF,0x80,0x0,0x3,0xFF,0xFC,0xF,0x80,0x3E,0x1E,0x1E,0x3C,0x7C,0x0,0x0,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xFF,0xF8,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7C,0x7,0xC1,0xF0,0x7,0xC0,0xF,0x80,0x3E,0x0,0xF,0x8F,0xFF,0x83,0xFF,0xF0,0xF,0x80,0x3E,0x1E,0x1F,0x3C,0x7C,0x0,0x0,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0xFC,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7F,0xFF,0xC1,0xF0,0x7,0xC0,0xF,0x80,0x3E,0x0,0xF,0x8F,0xFF,0x83,0xF0,0x0,0xF,0x80,0x3E,0x1E,0xF,0x3C,0x7C,0x0,0x70,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0x7E,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7F,0xFF,0xC1,0xF0,0x7,0xC0,0xF,0x80,0x1F,0x0,0x1F,0xF,0xFF,0x83,0xF0,0x0,0xF,0x80,0x3E,0x1E,0xF,0xBC,0x3E,0x0,0x7C,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0x3F,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xFF,0xFF,0xE1,0xF0,0x7,0xC0,0xF,0x80,0x1F,0x0,0x1F,0xF,0xFF,0x83,0xF0,0x0,0xF,0x80,0x3E,0x1E,0x7,0xBC,0x3E,0x0,0xFC,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0x1F,0x80,0x0,0x0,
0x0,0x0,0x0,0x0,0xFF,0xFF,0xE1,0xF8,0xF,0xC0,0xF,0x80,0x1F,0x80,0x3F,0x0,0x0,0x3,0xF0,0x0,0xF,0xC0,0x7E,0x1E,0x7,0xFC,0x3F,0x1,0xF8,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0xF,0xC0,0x0,0x0,
0x0,0x0,0x0,0x0,0xF8,0x3,0xE0,0xFC,0x1F,0x80,0xF,0x80,0xF,0xE0,0xFE,0x0,0x0,0x3,0xF0,0x0,0x7,0xE0,0xFC,0x1E,0x3,0xFC,0x1F,0x83,0xF8,0x3E,0x0,0xF8,0x7C,0x0,0x1,0xF0,0xF,0xC0,0x0,0x0,
0x0,0x0,0x0,0x1,0xF0,0x1,0xF0,0xFF,0xFF,0x80,0xF,0x80,0x7,0xFF,0xFC,0x0,0x0,0x3,0xF0,0x0,0x7,0xFF,0xFC,0x1E,0x3,0xFC,0xF,0xFF,0xF0,0x3E,0x0,0xF8,0x7F,0xFF,0xE1,0xF0,0x7,0xE0,0x0,0x0,
0x0,0x0,0x0,0x1,0xF0,0x1,0xF0,0x7F,0xFF,0x0,0xF,0x80,0x3,0xFF,0xF8,0x0,0x0,0x3,0xF0,0x0,0x3,0xFF,0xF8,0x1E,0x1,0xFC,0x7,0xFF,0xE0,0x3E,0x0,0xF8,0x7F,0xFF,0xE1,0xF0,0x3,0xE0,0x0,0x0,
0x0,0x0,0x0,0x1,0xF0,0x1,0xF0,0x3F,0xFE,0x0,0xF,0x80,0x1,0xFF,0xF0,0x0,0x0,0x3,0xF0,0x0,0x1,0xFF,0xF0,0x1E,0x1,0xFC,0x3,0xFF,0xC0,0x3E,0x0,0xF8,0x7F,0xFF,0xE1,0xF0,0x3,0xF0,0x0,0x0,
0x0,0x0,0x0,0x3,0xE0,0x0,0xF8,0xF,0xF8,0x0,0xF,0x80,0x0,0x3F,0x80,0x0,0x0,0x3,0xF0,0x0,0x0,0x7F,0xC0,0x1E,0x0,0xFC,0x0,0xFF,0x0,0x3E,0x0,0xF8,0x7F,0xFF,0xE1,0xF0,0x1,0xF8,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};

unsigned char *pwelcome = &welcome[0];

/***************** Variables locals *************************/
unsigned int draw_pointer;											// Auxiliar per usar en el moment de dibuixar, per navegar per dintre del array del dibuix. 
unsigned char array_for_converting_to_string[] = {'\0'};						// Array base per convert_to_letter variables a strings i poder representarles.
unsigned int bytestoclean = 0;										// Auxiliar per saber els bits a eliminar de la pantalla.
extern volatile type_values_to_modify value_to_modify; 
extern volatile type_password_numbering_to_modify password_numbering_to_modify;
extern volatile type_submenu_parameter_to_modify submenu_parameter_to_modify; 
extern volatile type_error error_state; 
extern volatile type_submenu2_parameter_to_modify submenu2_parameter_to_modify;
extern volatile type_stop_values_to_modify stop_values_to_modify;

volatile unsigned char flag_blink_value = 0; 
volatile unsigned char flag_already_passed_through_all_password_numbering = 0; 
volatile unsigned char flag_show_particular_error_message = 0;

/***************** Variables externes ***********************/

extern unsigned long step; 
extern unsigned long wide;
extern unsigned long wide_MAX; 
extern unsigned long TON;
extern unsigned long TOFF;
extern unsigned long TOFF_MAX;
extern unsigned long TOFF_MIN;
extern unsigned long position;
extern unsigned long pressure;
extern unsigned long speed;
extern unsigned long accelerate_constant;
extern unsigned long decelerate_constant; 
extern unsigned long distance_limit_to_start;
extern unsigned long reset_speed;
extern unsigned long MAX_WIDE; 
extern unsigned char bridge;
extern unsigned long submenu2_turns_number;
extern volatile unsigned long necessary_steps_for_change;
extern volatile unsigned char mainlanguage; 

extern volatile unsigned long zero_value;
extern volatile unsigned long end_limit;

extern unsigned char password_try_thousands;
extern unsigned char password_try_hundreds;
extern unsigned char password_try_tens;
extern unsigned char password_try_units; 


/***************** Textos i draw_pointers *************************/


 	/*static const*/ unsigned long position_version_presentation[LANGUAGE][2] = {{0x10,0x01},{0x10,0x01},{0x10,0x01},{0x10,0x01}};
	/*static const*/ unsigned long position_version_submenu[LANGUAGE][2] = {{0x3A,0x01},{0x3A,0x01},{0x3A,0x01},{0x3A,0x01}};
	// /*static const*/ unsigned char text_version[LANGUAGE][STRING_MAX_LENGTH] = {"v0.0.1","v0.0.1","v0.0.1","v0.0.1"};
	//*static const*/ unsigned char text_version[LANGUAGE][STRING_MAX_LENGTH] = {"v0.0.2","v0.0.2","v0.0.2","v0.0.2"}; /* se soluciona problema pel qual a l'arrencar acciona el cilindre i no s'ha de fer */
	//*static const*/ unsigned char text_version[LANGUAGE][STRING_MAX_LENGTH] = {"v0.0.3","v0.0.3","v0.0.3","v0.0.3"}; 
	/*static const*/ unsigned char text_version[LANGUAGE][STRING_MAX_LENGTH] = {"v0.0.4","v0.0.4","v0.0.4","v0.0.4"}; /*190430 Modificat comportament pantalla error de porta oberta a menú principal. Afegit xiulet quan s'activa el sensor de cortina durant el funcionament.

	/*static const*/ unsigned long text_memory_position[LANGUAGE][2]	= {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00}};
	/*static const*/ unsigned long graphic_memory_position[LANGUAGE][2]	= {{0x00,0x40},{0x00,0x40},{0x00,0x40},{0x00,0x40}};
	/*static const*/ unsigned long all_memory_position[LANGUAGE][2]	= {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00}};

	/*static const*/ unsigned long position_welcome[LANGUAGE][2]	= {{0x00,0x40},{0x00,0x40},{0x00,0x40},{0x00,0x40}};

	/*static const*/ unsigned char text_wide[LANGUAGE][STRING_MAX_LENGTH]	= {"ANCHO EN CM -> ", "WIDE IN CM -> ", "LARGHEZZA -> ","LARGEUR CM -> "};
	/*static const*/ unsigned long position_text_wide[LANGUAGE][2]	= {{0x51,0x00},{0x51,0x00},{0x51,0x00},{0x51,0x00}};

	/*static const*/ unsigned long position_text_position[LANGUAGE][2] = {{0x64,0x00},{0x64,0x00},{0x64,0x00},{0x64,0x00}};
	/*static const*/ unsigned long position_value_position[LANGUAGE][2] = {{0x70,0x00},{0x70,0x00},{0x70,0x00},{0x70,0x00}};
	/*static const*/ unsigned char text_position[LANGUAGE][STRING_MAX_LENGTH] = {"POSICION -> ","POSITION -> ","POSIZIONE-> ","POSITION.-> "};
	/*static const*/ unsigned char text_empty_position[LANGUAGE][STRING_MAX_LENGTH] = {"            ","            ","            ","             "};

	/*static const*/ unsigned long position_text_step[LANGUAGE][2] = {{0xc9,0x00},{0xc9,0x00},{0xc9,0x00},{0xc9,0x00}};
	/*static const*/ unsigned char text_step[LANGUAGE][STRING_MAX_LENGTH] = {"PASO -> ","STEP -> ","PASSO-> ","PAS  -> "};

	/*static const*/ unsigned long position_text_pressure[LANGUAGE][2] = {{0xdc,0x00},{0xdc,0x00},{0xdc,0x00},{0xdc,0x00}};
	/*static const*/ unsigned char text_pressure[LANGUAGE][STRING_MAX_LENGTH] = {"TIEMPO CORTE -> ","CUT TIME -> ","TEMPO FUSTE. -> ","TEMPS COUPE  -> "};

	/*static const*/ unsigned long position_text_positioning[LANGUAGE][2] = {{0x59,0x00},{0x59,0x00},{0x5D,0x00},{0x59,0x00}};
	/*static const*/ unsigned char text_positioning[LANGUAGE][STRING_MAX_LENGTH] = {"BUSCANDO POSICION INICIO","SEARCHING START POSITION","CERCANDO ORIGINE","RECHERCHE POSITION DEPART"};
	/*static const*/ unsigned char text_positioning_limit[LANGUAGE][STRING_MAX_LENGTH] = {"BUSCANDO POSICION FINAL","SEARCHING FINAL POSITION","CERCANDO FINALE","RECHERCHE POSITION FINAL"};
	
	/*static const*/ unsigned long position_text_remember_door[LANGUAGE][2] = {{0x55,0x00},{0x55,0x00},{0x55,0x00},{0x55,0x00}};
	/*static const*/ unsigned char text_remember_door[LANGUAGE][STRING_MAX_LENGTH] = {"RECUERDE CAMBIAR PASO Y PRESION","REMEMBER TO CHANGE STEP AND PR.","RICORDA DI CAMBIARE PASSO E PR.","NOUBLIEZ DE CHANGER PAS ET PRES."};

	/*static const*/ unsigned long position_clean_wide_bar[LANGUAGE][2] = {{0xF8,0x47},{0xF7,0x47},{0xF6,0x47},{0xF7,0x47}};
	/*static const*/ unsigned long position_clean_step_bar[LANGUAGE][2] = {{0xB1,0x47},{0xB1,0x47},{0xB1,0x47},{0xB1,0x47}};
	/*static const*/ unsigned long position_clean_pressure_bar[LANGUAGE][2] = {{0xFC,0x43},{0xF8,0x43},{0xFC,0x43},{0xFC,0x43}};

	/*static const*/ unsigned long position_value_wide[LANGUAGE][2] = {{0x60,0x00},{0x5F,0x00},{0x5E,0x00},{0x5F,0x00}};
	/*static const*/ unsigned long position_value_step[LANGUAGE][2] = {{0xD1,0x00},{0xD1,0x00},{0xD1,0x00},{0xD1,0x00}};
	/*static const*/ unsigned long position_value_pressure[LANGUAGE][2] = {{0xEC,0x00},{0xE8,0x00},{0xEC,0x00},{0xEC,0x00}};	

	/*static const*/ unsigned char text_empty_wide[LANGUAGE][STRING_MAX_LENGTH] = {"   ","   ","   ","   "};
	/*static const*/ unsigned char text_empty_step[LANGUAGE][STRING_MAX_LENGTH] = {"    ","    ","    ","    "};
	/*static const*/ unsigned char text_empty_pressure[LANGUAGE][STRING_MAX_LENGTH] = {"    ","    ","    ","    "};


	/*static const*/ unsigned long position_bar_wide[LANGUAGE][2] = {{0xF8,0x43},{0xF7,0x43},{0xF6,0x43},{0xF7,0x43}};
	/*static const*/ unsigned long position_bar_step[LANGUAGE][2] = {{0xB1,0x47},{0xB1,0x47},{0xB1,0x47},{0xB1,0x47}};
	/*static const*/ unsigned long position_bar_pressure[LANGUAGE][2] = {{0xCC,0x47},{0xC8,0x47},{0xCC,0x47},{0xCC,0x47}};

	/*static const*/ unsigned long position_text_password[LANGUAGE][2] = {{0x82,0x00},{0x82,0x00},{0x82,0x00},{0x82,0x00}};
	/*static const*/ unsigned long position_asterisks_password[LANGUAGE][2] = {{0x8E,0x00},{0x8E,0x00},{0x8E,0x00},{0x8E,0x00}};

	/*static const*/ unsigned char text_password[LANGUAGE][STRING_MAX_LENGTH] = {"PASSWORD: ","PASSWORD: ","PASSWORD: ","PASSWORD: "};
	/*static const*/ unsigned char text_asterisks[LANGUAGE][STRING_MAX_LENGTH] = {"* * *","* * *","* * *","* * *"};

	/*static const*/ unsigned long position_password_line_thousands[LANGUAGE][2] = {{0x3C,0x45},{0x3C,0x45},{0x3C,0x45},{0x3C,0x45}};
	/*static const*/ unsigned long position_password_line_hundreds[LANGUAGE][2] = {{0x3C + 2,0x45},{0x3C + 2,0x45},{0x3C + 2,0x45},{0x3C + 2,0x45}};
	/*static const*/ unsigned long position_password_line_tens[LANGUAGE][2] = {{0x3C + 4,0x45},{0x3C + 4,0x45},{0x3C + 4,0x45},{0x3C + 4,0x45}};
	/*static const*/ unsigned long position_password_line_units[LANGUAGE][2] = {{0x3C + 6,0x45},{0x3C + 6,0x45},{0x3C + 6,0x45},{0x3C + 6,0x45}};

	/*static const*/ unsigned long position_thousands_password[LANGUAGE][2] = {{0x8C,0x00},{0x8C,0x00},{0x8C,0x00},{0x8C,0x00}};
	/*static const*/ unsigned long position_hundreds_password[LANGUAGE][2] = {{0x8E,0x00},{0x8E,0x00},{0x8E,0x00},{0x8E,0x00}};
	/*static const*/ unsigned long position_tens_password[LANGUAGE][2] = {{0x90,0x00},{0x90,0x00},{0x90,0x00},{0x90,0x00}};
	/*static const*/ unsigned long position_units_password[LANGUAGE][2] = {{0x92,0x00},{0x92,0x00},{0x92,0x00},{0x92,0x00}};

	/*static const*/ unsigned char text_empty_password[LANGUAGE][STRING_MAX_LENGTH] = {"  ","  ","  ","  "};

	/*static const*/ unsigned long position_submenu_bridge[LANGUAGE][2] = {{0x51,0x00},{0x51,0x00},{0x51,0x00},{0x51,0x00}};
	/*static const*/ unsigned char text_bridge[LANGUAGE][STRING_MAX_LENGTH] = {"PUENTE A/C -> ","BRIDGE O/C -> ","PONTE A/C  -> ","PONT A/C   -> "};
	/*static const*/ unsigned long position_submenu_maxwide[LANGUAGE][2] = {{0xC9,0x00},{0xC9,0x00},{0xC9,0x00},{0xC9,0x00}};
	/*static const*/ unsigned char text_maxwide[LANGUAGE][STRING_MAX_LENGTH] = {"ANCHO MAX. -> ","MAX. WIDE  -> ","LARGH. MAS.-> ","LARGEUR MAX.->"};
	/*static const*/ unsigned long position_submenu_idioma[LANGUAGE][2] = {{0x65,0x00},{0x65,0x00},{0x65,0x00},{0x65,0x00}};
	/*static const*/ unsigned char text_idioma[LANGUAGE][STRING_MAX_LENGTH] = {"LENGUAJE -> ","LANGUAGE -> ","LINGUA ->    ","LANGUE ->   "};	
	/*static const*/ unsigned long position_submenu_bar[LANGUAGE][2] = {{0xEC,0x00},{0xEC,0x00},{0xEC,0x00},{0xEC,0x00}};
	/*static const*/ unsigned char text_bar[LANGUAGE][STRING_MAX_LENGTH] = {"/","/","/","/"};
	/*static const*/ unsigned long position_submenu_zero[LANGUAGE][2] = {{0xDD,0x00},{0xDD,0x00},{0xDD,0x00},{0xDD,0x00}};
	/*static const*/ unsigned char text_zero[LANGUAGE][STRING_MAX_LENGTH] = {"VAL. INI. -> ","STA. VAL. -> ","VAL. INI. -> ","VAL.DEPART->"};

	/*static const*/ unsigned long position_submenu_cleanbar_bridge[LANGUAGE][2] = {{0xcF,0x43},{0xcF,0x43},{0xcF,0x43},{0xcF,0x43}};
	/*static const*/ unsigned long position_submenu_cleanbar_maxwide[LANGUAGE][2] = {{0xB7,0x47},{0xB7,0x47},{0xB7,0x47},{0xB7,0x47}};
	/*static const*/ unsigned long position_submenu_cleanbar_idioma[LANGUAGE][2] = {{0xE1,0x43},{0xE1,0x43},{0xE1,0x43},{0xE1,0x43}};
	/*static const*/ unsigned long position_submenu_cleanbar_zero[LANGUAGE][2] = {{0xC9,0x47},{0xC9,0x47},{0xC9,0x47},{0xC9,0x47}};
	/*static const*/ unsigned long position_submenu_cleanbar_limit[LANGUAGE][2] = {{0xCD,0x47},{0xCD,0x47},{0xCD,0x47},{0xCD,0x47}};

	/*static const*/ unsigned long position_value_bridge[LANGUAGE][2] = {{0x5F,0x00},{0x5F,0x00},{0x5F,0x00},{0x5F,0x00}};
	/*static const*/ unsigned char text_bridge_open[LANGUAGE][STRING_MAX_LENGTH] = {"ABIE.","OPEN","APER.","OUVE."};
	/*static const*/ unsigned char text_bridge_closed[LANGUAGE][STRING_MAX_LENGTH] = {"CERR.","CLOS.","CHIU.","FERM."};

	/*static const*/ unsigned char text_empty_bridge[LANGUAGE][STRING_MAX_LENGTH] = {"     ","     ","     ","     "};
	/*static const*/ unsigned long position_value_maxwidth[LANGUAGE][2] = {{0xD7,0x00},{0xD7,0x00},{0xD7,0x00},{0xD7,0x00}};
	/*static const*/ unsigned char text_empty_maxwidth[LANGUAGE][STRING_MAX_LENGTH] = {"   ","   ","   "};
	/*static const*/ unsigned long position_value_language[LANGUAGE][2] = {{0x71,0x00},{0x71,0x00},{0x71,0x00},{0x71,0x00}};
	/*static const*/ unsigned char text_language_spanish[LANGUAGE][STRING_MAX_LENGTH] = {"ESP","SPA","SPA","ESP"};
	/*static const*/ unsigned char text_language_english[LANGUAGE][STRING_MAX_LENGTH] = {"ING","ENG","ING","ANG"};
	/*static const*/ unsigned char text_language_italian[LANGUAGE][STRING_MAX_LENGTH] = {"ITA.","ITA","ITA","ITA"};
	/*static const*/ unsigned char text_language_french[LANGUAGE][STRING_MAX_LENGTH] = {"FRA","FRE","FRA","FRA"};
	/*static const*/ unsigned char text_empty_language[LANGUAGE][STRING_MAX_LENGTH] = {"       ","       ","       ","       "};
	/*static const*/ unsigned long position_value_3_zero[LANGUAGE][2] = {{0xE9,0x00},{0xE9,0x00},{0xE9,0x00},{0xE9,0x00}};
	/*static const*/ unsigned long position_value_2_zero[LANGUAGE][2] = {{0xEA,0x00},{0xEA,0x00},{0xEA,0x00},{0xEA,0x00}};
	/*static const*/ unsigned char text_empty_zero[LANGUAGE][STRING_MAX_LENGTH] = {"   ","   ","   ","   "};
	/*static const*/ unsigned long position_value_limit[LANGUAGE][2] = {{0xED,0x00},{0xED,0x00},{0xED,0x00},{0xED,0x00}};
	/*static const*/ unsigned char text_empty_limit[LANGUAGE][STRING_MAX_LENGTH] = {"   ","   ","   ","   "};	

	/*static const*/ unsigned long position_submenu_value_bridge[LANGUAGE][2] = {{0xcF,0x43},{0xcF,0x43},{0xcF,0x43},{0xcF,0x43}};
	/*static const*/ unsigned long position_submenu_value_maxwide[LANGUAGE][2] = {{0xB7,0x47},{0xB7,0x47},{0xB7,0x47},{0xB7,0x47}};
	/*static const*/ unsigned long position_submenu_value_idioma[LANGUAGE][2] = {{0xE1,0x43},{0xE1,0x43},{0xE1,0x43},{0xE1,0x43}};
	/*static const*/ unsigned long position_submenu_value_3_zero[LANGUAGE][2] = {{0xC9,0x47},{0xC9,0x47},{0xC9,0x47},{0xC9,0x47}};
	/*static const*/ unsigned long position_submenu_value_2_zero[LANGUAGE][2] = {{0xCA,0x47},{0xCA,0x47},{0xCA,0x47},{0xCA,0x47}};
	/*static const*/ unsigned long position_submenu_value_limit[LANGUAGE][2] = {{0xCD,0x47},{0xCD,0x47},{0xCD,0x47},{0xCD,0x47}};

	/*static const*/ unsigned long position_text_reset_error[LANGUAGE][2] = {{0x5E,0x00},{0x5E,0x00},{0x5E,0x00},{0x5B,0x00}};
	/*static const*/ unsigned char text_reset_error[LANGUAGE][STRING_MAX_LENGTH]  ={"PULSE RESET", "PRESS RESET","PULSA RESET","REINITIALISATION"};
	/*static const*/ unsigned long position_text_error_door[LANGUAGE][2] = {{0x5D,0x00},{0x5D,0x00},{0x5D,0x00},{0x5D,0x00}};
	/*static const*/ unsigned char text_sec_door[LANGUAGE][STRING_MAX_LENGTH] = {"PUERTA ABIERTA", "OPEN SEC. DOOR","SPORTELO APERTA"," PORTE OUVERTE "};
	/*static const*/ unsigned long position_text_error_holder[LANGUAGE][2] = {{0x5D,0x00},{0x5D,0x00},{0x5D,0x00},{0x5D,0x00}};
	/*static const*/ unsigned char text_sec_holder[LANGUAGE][STRING_MAX_LENGTH] = {"BARRA PISADOR", "HOLDER ERROR","BARRA PREMILASTRA","BARRE PISADOR"};
	/*static const*/ unsigned long position_text_error_emergency[LANGUAGE][2] = {{0x56,0x00},{0x59,0x00},{0x59,0x00},{0x59,0x00}};
	/*static const*/ unsigned char text_sec_emergency[LANGUAGE][STRING_MAX_LENGTH] = {"PULSADOR EMERGENCIA ENCLAVADO", "EMERGENCY BUTTON NESTLED","ARRESTO DI EMERGENZA","ARRET D'URGENCE"};
	/*static const*/ unsigned long position_text_error_cylinder[LANGUAGE][2] = {{0x5B,0x00},{0x5B,0x00},{0x5C,0x00},{0x5B,0x00}};
	/*static const*/ unsigned char text_sec_cylinder[LANGUAGE][STRING_MAX_LENGTH] = {"DETECTOR CILINDRO", "CYLINDER DETECTED","SENSORE CILINDRO","DETECTEUR CYLINDRE"};
	/*static const*/ unsigned long position_text_error_start[LANGUAGE][2] = {{0x5E,0x00},{0x5E,0x00},{0x5E,0x00},{0x5E,0x00}};
	/*static const*/ unsigned char text_sec_start[LANGUAGE][STRING_MAX_LENGTH] = {"ERROR INICIO", "START ERROR","ERRORE INIZIO","ERREUR ACCUEIL"};
	/*static const*/ unsigned long position_text_error_end[LANGUAGE][2] = {{0x5D,0x00},{0x5D,0x00},{0x5D,0x00},{0x5D,0x00}};
	/*static const*/ unsigned char text_sec_end[LANGUAGE][STRING_MAX_LENGTH] = {"LIMITE CARRERA", "LIMIT DETECTED","LIMITE DI CORSA","LIMITE DE COURSE"};
	/*static const*/ unsigned long position_text_error_curtain[LANGUAGE][2] = {{0x5C,0x00},{0x5D,0x00},{0x5C,0x00},{0x5C,0x00}};
	/*static const*/ unsigned char text_sec_curtain[LANGUAGE][STRING_MAX_LENGTH] = {"CORTINA SEGURIDAD", "SAFETY CURTAIN","TENDA SICUREZZA","RIDEAU SECURITE"};
	/*static const*/ unsigned long position_text_error_sensors[LANGUAGE][2] = {{0x56,0x00},{0x56,0x00},{0x56,0x00},{0x56,0x00}};
	/*static const*/ unsigned char text_sec_sensors[LANGUAGE][STRING_MAX_LENGTH] = {"ERROR INICIO Y LIMITE CARRERA", "START AND END ERROR","INIZIO E LIMITE ERRORE","ACCUEIL ET LIMITE ERREUR"};
	/*static const*/ unsigned long position_text_start_to_continue[LANGUAGE][2] = {{0x5D,0x00},{0x5D,0x00},{0x5D,0x00},{0x5D,0x00}};
	/*static const*/ unsigned char text_start_to_continue[LANGUAGE][STRING_MAX_LENGTH] = {"PULSE START", "PULSE START","PREMERE START","APPUYEZ START"};


	/*static const*/ unsigned long position_submenu2_text_ton[LANGUAGE][2] = {{0x29,0x00},{0x29,0x00},{0x29,0x00},{0x29,0x00}};
	/*static const*/ unsigned long position_submenu2_text_toffmin[LANGUAGE][2] = {{0x79,0x00},{0x79,0x00},{0x79,0x00},{0x79,0x00}};
	/*static const*/ unsigned long position_submenu2_text_toffmax[LANGUAGE][2] = {{0xC9,0x00},{0xC9,0x00},{0xC9,0x00},{0xC9,0x00}};
	/*static const*/ unsigned long position_submenu2_text_stepspdchange[LANGUAGE][2] = {{0x3C,0x00},{0x3C,0x00},{0x3C,0x00},{0x3C,0x00}};
	/*static const*/ unsigned long position_submenu2_text_aceldecel[LANGUAGE][2] = {{0x8C,0x00},{0x8C,0x00},{0x8C,0x00},{0x8C,0x00}};
	/*static const*/ unsigned long position_submenu2_text_turns[LANGUAGE][2] = {{0xDC,0x00},{0xDC,0x00},{0xDC,0x00},{0xDC,0x00}};
	/*static const*/ unsigned long position_submenu2_text_bar[LANGUAGE][2] = {{0x9B,0x00},{0x9B,0x00},{0x9B,0x00},{0x9B,0x00}};
	/*static const*/ unsigned long position_submenu2_text_bar2[LANGUAGE][2] = {{0x9D,0x00},{0x9D,0x00},{0x9D,0x00},{0x9D,0x00}};
	

	/*static const*/ unsigned char text_submenu2_ton[LANGUAGE][STRING_MAX_LENGTH] = {"Ton -> ","Ton -> ","Ton -> ","Ton -> "};
	/*static const*/ unsigned char text_submenu2_toffmin[LANGUAGE][STRING_MAX_LENGTH] = {"Toff MIN. -> ","Toff MIN. -> ","Toff MIN. -> ","Toff MIN. -> "};
	/*static const*/ unsigned char text_submenu2_toffmax[LANGUAGE][STRING_MAX_LENGTH] = {"Toff MAX. -> ","Toff MAX. -> ","Toff MAX. -> ","Toff MAX. -> "};
	/*static const*/ unsigned char text_submenu2_stepspdchange[LANGUAGE][STRING_MAX_LENGTH] = {"PasoCambioVel-> ","StepSpdChange-> ","StepSpdChange-> ","StepSpdChange-> "};
	/*static const*/ unsigned char text_submenu2_aceldecel[LANGUAGE][STRING_MAX_LENGTH] = {"ACEL/DEC/L0-> ","ACEL/DEC/L0-> ","ACEL/DEC/L0-> ","ACEL/DEC/L0-> "};
	/*static const*/ unsigned char text_submenu2_turns[LANGUAGE][STRING_MAX_LENGTH] = {"VUELTAS -> ","TURNS -> ","TURNS -> ","TURNS -> "};
	/*static const*/ unsigned char text_submenu2_bar[LANGUAGE][STRING_MAX_LENGTH] = {"/","/","/","/"};


	/*static const*/ unsigned long position_submenu2_value_ton[LANGUAGE][2] = {{0x38,0x00},{0x38,0x00},{0x38,0x00},{0x38,0x00}};
	/*static const*/ unsigned long position_submenu2_value_toffmin[LANGUAGE][2] = {{0x88,0x00},{0x88,0x00},{0x88,0x00},{0x88,0x00}};
	/*static const*/ unsigned long position_submenu2_value_toffmax[LANGUAGE][2] = {{0xD7,0x00},{0xD7,0x00},{0xD7,0x00},{0xD7,0x00}};
	/*static const*/ unsigned long position_submenu2_value_stepspdchange[LANGUAGE][2] = {{0x4C,0x00},{0x4C,0x00},{0x4C,0x00},{0x4C,0x00}};
	/*static const*/ unsigned long position_submenu2_value_acel[LANGUAGE][2] = {{0x9A,0x00},{0x9A,0x00},{0x9A,0x00},{0x9A,0x00}};
	/*static const*/ unsigned long position_submenu2_value_decel[LANGUAGE][2] = {{0x9C,0x00},{0x9C,0x00},{0x9C,0x00},{0x9C,0x00}};
	/*static const*/ unsigned long position_submenu2_value_longini[LANGUAGE][2] = {{0x9E,0x00},{0x9E,0x00},{0x9E,0x00},{0x9E,0x00}};
	/*static const*/ unsigned long position_submenu2_value_turns[LANGUAGE][2] = {{0xEC,0x00},{0xEC,0x00},{0xEC,0x00},{0xEC,0x00}};
		
	/*static const*/ unsigned char text_empty_ton[LANGUAGE][STRING_MAX_LENGTH] = {"   ","   ","   ","   "};
	/*static const*/ unsigned char text_empty_toffmin[LANGUAGE][STRING_MAX_LENGTH] = {"   ","   ","   ","   "};
	/*static const*/ unsigned char text_empty_toffmax[LANGUAGE][STRING_MAX_LENGTH] = {"    ","    ","    ","    "};
	/*static const*/ unsigned char text_empty_stepspdchange[LANGUAGE][STRING_MAX_LENGTH] = {"   ","   ","   ","   "};
	/*static const*/ unsigned char text_empty_acel[LANGUAGE][STRING_MAX_LENGTH] = {" "," "," "," "};
	/*static const*/ unsigned char text_empty_decel[LANGUAGE][STRING_MAX_LENGTH] = {" "," "," "," "};
	/*static const*/ unsigned char text_empty_longini[LANGUAGE][STRING_MAX_LENGTH] = {"  ","  ","  ","  "};
	/*static const*/ unsigned char text_empty_turns[LANGUAGE][STRING_MAX_LENGTH] = {"  ","  ","  ","  "};
	
	/*static const*/ unsigned long position_submenu2_line_ton[LANGUAGE][2] = {{0xB8,0x42},{0xB8,0x42},{0xB8,0x42},{0xB8,0x42}};
	/*static const*/ unsigned long position_submenu2_line_toffmin[LANGUAGE][2] = {{0x38,0x45},{0x38,0x45},{0x38,0x45},{0x38,0x45}};
	/*static const*/ unsigned long position_submenu2_line_toffmax[LANGUAGE][2] = {{0xB7,0x47},{0xB7,0x47},{0xB7,0x47},{0xB7,0x47}};
	/*static const*/ unsigned long position_submenu2_line_stepspdchange[LANGUAGE][2] = {{0xCC,0x42},{0xCC,0x42},{0xCC,0x42},{0xCC,0x42}};
	/*static const*/ unsigned long position_submenu2_line_acel[LANGUAGE][2] = {{0x4A,0x45},{0x4A,0x45},{0x4A,0x45},{0x4A,0x45}};
	/*static const*/ unsigned long position_submenu2_line_decel[LANGUAGE][2] = {{0x4A+2,0x45},{0x4A+2,0x45},{0x4A+2,0x45},{0x4A+2,0x45}};
	/*static const*/ unsigned long position_submenu2_line_longini[LANGUAGE][2] = {{0x4A+4,0x45},{0x4A+4,0x45},{0x4A+4,0x45},{0x4A+4,0x45}};
	/*static const*/ unsigned long position_submenu2_line_turns[LANGUAGE][2] = {{0xCC,0x47},{0xCC,0x47},{0xCC,0x47},{0xCC,0x47}};

 	/*static const*/ unsigned long position_test_reset[LANGUAGE][2] = {{0xCF,0x00},{0xCF,0x00},{0xCF,0x00},{0xCF,0x00}};
	/*static const*/ unsigned char text_test_reset[LANGUAGE][STRING_MAX_LENGTH] = {"R  ","R  ","R  ","R  "};
 	/*static const*/ unsigned long position_test_aa[LANGUAGE][2] = {{0x2C,0x00},{0x2C,0x00},{0x2C,0x00},{0x2C,0x00}};
	/*static const*/ unsigned char text_test_aa[LANGUAGE][STRING_MAX_LENGTH] = {"AA ","AA ","AA ","AA "};
 	/*static const*/ unsigned long position_test_ab[LANGUAGE][2] = {{0xCC,0x00},{0xCC,0x00},{0xCC,0x00},{0xCC,0x00}};
	/*static const*/ unsigned char text_test_ab[LANGUAGE][STRING_MAX_LENGTH] = {"AB ","AB ","AB ","AB "};
 	/*static const*/ unsigned long position_test_stop[LANGUAGE][2] = {{0xC9,0x00},{0xC9,0x00},{0xC9,0x00},{0xC9,0x00}};
	/*static const*/ unsigned char text_test_stop[LANGUAGE][STRING_MAX_LENGTH] = {"RO ","RO ","RO ","RO "};
 	/*static const*/ unsigned long position_test_start[LANGUAGE][2] = {{0x29,0x00},{0x29,0x00},{0x29,0x00},{0x29,0x00}};
	/*static const*/ unsigned char text_test_start[LANGUAGE][STRING_MAX_LENGTH] = {"VE ","VE ","VE ","VE "};
 	/*static const*/ unsigned long position_test_menu[LANGUAGE][2] = {{0x2F,0x00},{0x2F,0x00},{0x2F,0x00},{0x2F,0x00}};
	/*static const*/ unsigned char text_test_menu[LANGUAGE][STRING_MAX_LENGTH] = {"ME ","ME ","ME ","ME "};
 	/*static const*/ unsigned long position_test_esc[LANGUAGE][2] = {{0x35,0x00},{0x35,0x00},{0x35,0x00},{0x35,0x00}};
	/*static const*/ unsigned char text_test_esc[LANGUAGE][STRING_MAX_LENGTH] = {"ES","ES","ES","ES"};
 	/*static const*/ unsigned long position_test_number[LANGUAGE][2] = {{0xCC,0x00},{0xCC,0x00},{0xCC,0x00},{0xCC,0x00}};
 	/*static const*/ unsigned long position_test_0[LANGUAGE][2] = {{0x85,0x00},{0x85,0x00},{0x85,0x00},{0x85,0x00}};
	/*static const*/ unsigned char text_test_0[LANGUAGE][STRING_MAX_LENGTH] = {" 0 "," 0 "," 0 "," 0 "};
 	/*static const*/ unsigned long position_test_1[LANGUAGE][2] = {{0x38,0x00},{0x38,0x00},{0x38,0x00},{0x38,0x00}};
	/*static const*/ unsigned char text_test_1[LANGUAGE][STRING_MAX_LENGTH] = {" 1 "," 1 "," 1 "," 1 "};
 	/*static const*/ unsigned long position_test_2[LANGUAGE][2] = {{0x3B,0x00},{0x3B,0x00},{0x3B,0x00},{0x3B,0x00}};
	/*static const*/ unsigned char text_test_2[LANGUAGE][STRING_MAX_LENGTH] = {" 2 "," 2 "," 2 "," 2 "};
 	/*static const*/ unsigned long position_test_3[LANGUAGE][2] = {{0x3E,0x00},{0x3E,0x00},{0x3E,0x00},{0x3E,0x00}};
	/*static const*/ unsigned char text_test_3[LANGUAGE][STRING_MAX_LENGTH] = {" 3 "," 3 "," 3 "," 3 "};
 	/*static const*/ unsigned long position_test_4[LANGUAGE][2] = {{0x88,0x00},{0x88,0x00},{0x88,0x00},{0x88,0x00}};
	/*static const*/ unsigned char text_test_4[LANGUAGE][STRING_MAX_LENGTH] = {" 4 "," 4 "," 4 "," 4 "};
 	/*static const*/ unsigned long position_test_5[LANGUAGE][2] = {{0x8B,0x00},{0x8B,0x00},{0x8B,0x00},{0x8B,0x00}};
	/*static const*/ unsigned char text_test_5[LANGUAGE][STRING_MAX_LENGTH] = {" 5 "," 5 "," 5 "," 5 "};
 	/*static const*/ unsigned long position_test_6[LANGUAGE][2] = {{0x8E,0x00},{0x8E,0x00},{0x8E,0x00},{0x8E,0x00}};
	/*static const*/ unsigned char text_test_6[LANGUAGE][STRING_MAX_LENGTH] = {" 6 "," 6 "," 6 "," 6 "};
 	/*static const*/ unsigned long position_test_7[LANGUAGE][2] = {{0xD8,0x00},{0xD8,0x00},{0xD8,0x00},{0xD8,0x00}};
	/*static const*/ unsigned char text_test_7[LANGUAGE][STRING_MAX_LENGTH] = {" 7 "," 7 "," 7 "," 7 "};
 	/*static const*/ unsigned long position_test_8[LANGUAGE][2] = {{0xDB,0x00},{0xDB,0x00},{0xDB,0x00},{0xDB,0x00}};
	/*static const*/ unsigned char text_test_8[LANGUAGE][STRING_MAX_LENGTH] = {" 8 "," 8 "," 8 "," 8 "};
 	/*static const*/ unsigned long position_test_9[LANGUAGE][2] = {{0xDE,0x00},{0xDE,0x00},{0xDE,0x00},{0xDE,0x00}};
	/*static const*/ unsigned char text_test_9[LANGUAGE][STRING_MAX_LENGTH] = {" 9 "," 9 "," 9 "," 9 "};
 	/*static const*/ unsigned long position_test_ok[LANGUAGE][2] = {{0xD5,0x00},{0xD5,0x00},{0xD5,0x00},{0xD5,0x00}};
	/*static const*/ unsigned char text_test_ok[LANGUAGE][STRING_MAX_LENGTH] = {"OK ","OK ","OK ","OK "};
 	/*static const*/ unsigned long position_test_emergency[LANGUAGE][2] = {{0x49,0x00},{0x49,0x00},{0x49,0x00},{0x49,0x00}};
	/*static const*/ unsigned char text_test_emergency[LANGUAGE][STRING_MAX_LENGTH] = {"EM ","EM ","EM ","EM "};
 	/*static const*/ unsigned long position_test_cylinder[LANGUAGE][2] = {{0x4C,0x00},{0x4C,0x00},{0x4C,0x00},{0x4C,0x00}};
	/*static const*/ unsigned char text_test_cylinder[LANGUAGE][STRING_MAX_LENGTH] = {"CI ","CI ","CI ","CI "};
 	/*static const*/ unsigned long position_test_inicio[LANGUAGE][2] = {{0x99,0x00},{0x99,0x00},{0x99,0x00},{0x99,0x00}};
	/*static const*/ unsigned char text_test_inicio[LANGUAGE][STRING_MAX_LENGTH] = {"IN ","IN ","IN ","IN "};
 	/*static const*/ unsigned long position_test_end[LANGUAGE][2] = {{0x9C,0x00},{0x9C,0x00},{0x9C,0x00},{0x9C,0x00}};
	/*static const*/ unsigned char text_test_end[LANGUAGE][STRING_MAX_LENGTH] = {"FI ","FI ","FI ","FI "};
 	/*static const*/ unsigned long position_test_curtain[LANGUAGE][2] = {{0x46,0x00},{0x46,0x00},{0x46,0x00},{0x46,0x00}};
	/*static const*/ unsigned char text_test_curtain[LANGUAGE][STRING_MAX_LENGTH] = {"CO ","CO ","CO ","CO "};
 	/*static const*/ unsigned long position_test_i8[LANGUAGE][2] = {{0x96,0x00},{0x96,0x00},{0x96,0x00},{0x96,0x00}};
	/*static const*/ unsigned char text_test_i8[LANGUAGE][STRING_MAX_LENGTH] = {"I8 ","I8 ","I8 ","I8 "};
 	/*static const*/ unsigned long position_test_i9[LANGUAGE][2] = {{0xE6,0x00},{0xE6,0x00},{0xE6,0x00},{0xE6,0x00}};
	/*static const*/ unsigned char text_test_i9[LANGUAGE][STRING_MAX_LENGTH] = {"I9 ","I9 ","I9 ","I9 "};
 	/*static const*/ unsigned long position_test_door[LANGUAGE][2] = {{0xE9,0x00},{0xE9,0x00},{0xE9,0x00},{0xE9,0x00}};
	/*static const*/ unsigned char text_test_door[LANGUAGE][STRING_MAX_LENGTH] = {"PU ","PU ","PU ","PU "};
 	/*static const*/ unsigned long position_test_holder[LANGUAGE][2] = {{0xEC,0x00},{0xEC,0x00},{0xEC,0x00},{0xEC,0x00}};
	/*static const*/ unsigned char text_test_holder[LANGUAGE][STRING_MAX_LENGTH] = {"BA ","BA ","BA ","BA "};
	/*static const*/ unsigned char text_test_empty[LANGUAGE][STRING_MAX_LENGTH] = {"   ","   ","   ","   "}; 
	/*static const*/ unsigned char text_test_empty_number[LANGUAGE][STRING_MAX_LENGTH] = {" "," "," "," "};
	/*static const*/ unsigned long position_autotest[LANGUAGE][2] = {{0x61,0x00},{0x61,0x00},{0x61,0x00},{0x61,0x00}};
	/*static const*/ unsigned char text_autotest[LANGUAGE][STRING_MAX_LENGTH] = {"AUTOTEST","AUTOTEST","AUTOTEST","AUTOTEST"};
	/*static const*/ unsigned long position_test_belt[LANGUAGE][2] = {{0x32,0x00},{0x32,0x00},{0x32,0x00},{0x32,0x00}};
	/*static const*/ unsigned char text_test_belt[LANGUAGE][STRING_MAX_LENGTH] = {"WI ","WI ","WI ","WI "};
	/*static const*/ unsigned long position_test_step[LANGUAGE][2] = {{0x82,0x00},{0x82,0x00},{0x82,0x00},{0x82,0x00}};
	/*static const*/ unsigned char text_test_step[LANGUAGE][STRING_MAX_LENGTH] = {"ST ","ST ","ST ","ST "};
	/*static const*/ unsigned long position_test_punch[LANGUAGE][2] = {{0xD2,0x00},{0xD2,0x00},{0xD2,0x00},{0xD2,0x00}};
	/*static const*/ unsigned char text_test_punch[LANGUAGE][STRING_MAX_LENGTH] = {"TI ","TI ","TI ","TI "};
	

unsigned const char underlined_wide[]={0xFF,0xFF,0xFF};
unsigned const char clean_underlined_wide[]={0x00,0x00,0x00};
unsigned const char underlined_step[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
unsigned const char clean_underlined_step[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned const char underlined_pressure[]={0xFF,0xFF,0xFF,0xFF};
unsigned const char clean_underlined_pressure[]={0x00,0x00,0x00,0x00};

unsigned char *punderlined_wide = &underlined_wide[0];
unsigned char *punderlined_step = &underlined_step[0];
unsigned char *punderlined_pressure = &underlined_pressure[0];
unsigned char *pclean_underlined_wide = &clean_underlined_wide[0];
unsigned char *pclean_underlined_step = &clean_underlined_step[0];
unsigned char *pclean_underlined_pressure = &clean_underlined_pressure[0];


/********************************************************************
 * Function:	status_check() y read_Status()						*
 * Definition:	Funcions per chequejar l'estat de la pantalla 		*
 *				i poder enviar la seguent instruccio.				*			
 ********************************************************************/
void status_check(void)
{
	#warning comentat per poder depurar sense pantalla
	#if 1
		unsigned char status = 0;
		status = read_Status();
		status &= 0x3;
		while (status != 0x3)
		{
			Nop();
			status = read_Status();
			Nop();
			status &= 0x3;
			Nop();
		}
	#endif
}

unsigned char read_Status(void)
{
	unsigned char Datta = 0;
	
	D0_TRIS = 1;		// Dades com entrada.
	D1_TRIS = 1;		// Dades com entrada.
	D2_TRIS = 1;		// Dades com entrada.
	D3_TRIS = 1;		// Dades com entrada.
	D4_TRIS = 1;		// Dades com entrada.
	D5_TRIS = 1;		// Dades com entrada.
	D6_TRIS = 1;		// Dades com entrada.
	D7_TRIS = 1;		// Dades com entrada.

	CD = 1;
	CE = 0;
	RD = 0;
	DelayUs(10);
	Datta = PORTE;		// Llegeix bus de dades.
	DelayUs(10);
	CE = 1;
	W_R = 1;
	RD = 1;	
	
	D0_TRIS = 0;		// Dades com sortida.
	D1_TRIS = 0;		// Dades com sortida.
	D2_TRIS = 0;		// Dades com sortida.
	D3_TRIS = 0;		// Dades com sortida.
	D4_TRIS = 0;		// Dades com sortida.
	D5_TRIS = 0;		// Dades com sortida.
	D6_TRIS = 0;		// Dades com sortida.
	D7_TRIS = 0;		// Dades com sortida.
	
	return (Datta);
}
/********************************************************************
 * Function:	lcd_send_command(lcd_command)						*
 * Definition:	Subrutina per escriure una comanda per la pantalla. *
 ********************************************************************/
void lcd_send_command(unsigned char lcd_command)
{	
	status_check();

	D0_TRIS = 0;		// Dades com sortida.
	D1_TRIS = 0;		// Dades com sortida.
	D2_TRIS = 0;		// Dades com sortida.
	D3_TRIS = 0;		// Dades com sortida.
	D4_TRIS = 0;		// Dades com sortida.
	D5_TRIS = 0;		// Dades com sortida.
	D6_TRIS = 0;		// Dades com sortida.
	D7_TRIS = 0;		// Dades com sortida.
	DelayUs(LCD_DELAY_US);
	CD = 1;
	CE = 0;
	W_R = 0;
	DelayUs(LCD_DELAY_US);
	LATE = lcd_command;		// Escriure la comanda al bus.
	DelayUs(LCD_DELAY_US);
	CE = 1;
	W_R = 1;
	CD = 0;
}
/********************************************************************
 * Function:	lcd_send_data(lcd_data)								*
 * Definition:	Subrutina per escriure dades a la pantalla.			*
 ********************************************************************/
void lcd_send_data(unsigned char lcd_data)
{
	status_check();	

	D0_TRIS = 0;		// Dades com sortida.
	D1_TRIS = 0;		// Dades com sortida.
	D2_TRIS = 0;		// Dades com sortida.
	D3_TRIS = 0;		// Dades com sortida.
	D4_TRIS = 0;		// Dades com sortida.
	D5_TRIS = 0;		// Dades com sortida.
	D6_TRIS = 0;		// Dades com sortida.
	D7_TRIS = 0;		// Dades com sortida.
	DelayUs(LCD_DELAY_US);
	CD = 0;
	CE = 0;
	W_R = 0;
	DelayUs(LCD_DELAY_US);
	LATE = lcd_data;	// Escriure dades al bus.
	DelayUs(LCD_DELAY_US);
	CE = 1;
	W_R = 1;
} 
/********************************************************************
 * Function:	lcd_init()											*
 * Definition:	Subrutina per inicialitzar la pantalla.				*
 ********************************************************************/
void lcd_init (void)
{
	RST_LCD = 0;
	DelayUs(LCD_DELAY_US);		// Assegurem un temps de reset. M?im hauria de ser de 800ns.
	W_R = 1;
	RD = 1;
	CE = 1;
	CD = 1;
	FS = 1;						// lletra petita.
	RST_LCD = 1;
	DelayMs(15);

	lcd_send_data(0x00);		// 0x0f00 = 3840 bytes en total cada pantalla.<--240*128
	lcd_send_data(0x00);		// 0x0780 = 1920 bytes en total cada pantalla.<--240*64	
	lcd_send_command(TEXTHOMEADRESS);	// <--text home address
	
	lcd_send_data(0x00);		// Donde empieza el grafico
	lcd_send_data(0x40);		// Data = 0x3c;<--240*128 240*64<--0x1e
	lcd_send_command(GRAPHICHOMEADRESS); 	// <--graphic home address
	    
	lcd_send_data(0x28);		//  0x001e 30 bytes
	lcd_send_data(0x00);
	lcd_send_command(TEXTAREA);	// <--text area set
              
	lcd_send_data(0x28);		// 0x001e = 30 bytes cada fila
	lcd_send_data(0x00);
	lcd_send_command(GRAPHICAREA);	// <--graphic area set					  
			
	lcd_send_command(ORMODE);	// Modo "or" 80
		
	lcd_send_command(TIGMODE);	// mode text&graphics. 0x94 -> mode text. 0x98 -> mode graphics.
}
/********************************************************************
 * Function:	draw_lcd_graphic(*draw_direction)					*
 * Definition:	Subrutina per dibuixar grafic en pantalla	    	*
 ********************************************************************/
void draw_lcd_graphic(unsigned char *draw_direction)
{		
	set_address_pointer(graphic_memory_position[mainlanguage]);
	unsigned char draw_value = 0;
	
	draw_pointer = 0x0000;  
	while (draw_pointer < 0xA00)				// Tamany de les grafiques determinat pel tamany de la pantalla
	{
		draw_value = *(draw_direction + draw_pointer);
	   	lcd_send_data(draw_value);
		lcd_send_command(WRITE);
		draw_pointer++;
	}
  
}  
/********************************************************************
 * Function:	draw_lcd_line(*colorpintar,lenght_to_draw)		*
 * Definition:	Subrutina per dibuixar una linea a la pantalla.	*
 ********************************************************************/
void draw_lcd_line(unsigned char colour_to_draw,unsigned int lenght_to_draw)
{		
	
	// A LA HORA DE PINTAR HEM DE TENIR EN COMPTE QUE LA MEITAT DE LA PANTALLA SERIA INTRODUIR 20.
	// LES LINIES SOLS PODRÀN SER MÚLTIPLES DE 6, EL TAMANY INDIVIDUAL DE LES LLETRES.  
	// De posar 0x00 a 0x01 -> la distancia es separa 6 pixels, que serà  la unitat mÃínima que podrem controlar al pintar. 
	
	unsigned char coutner_line_draw = 0;
	unsigned char value_line_draw = 0;
	lenght_to_draw = lenght_to_draw / 6; 
	
	draw_pointer = 0x0000;  

	while (draw_pointer < lenght_max_line)		
	{
		if (colour_to_draw == 1)
		{
			value_line_draw = 0xFF; 
		}
		else 
		{
			value_line_draw = 0x00;
		}

    	lcd_send_data(value_line_draw);
		lcd_send_command(WRITE);
		draw_pointer++;
		coutner_line_draw++;
		
		if (coutner_line_draw == lenght_to_draw)
		{
			draw_pointer = lenght_max_line;
		}
	}	
} 
/********************************************************************
 * Function:	write_text(text_to_write)							*
 * Definition:	Subrutina per escriure text en pantalla. 			*
 ********************************************************************/
void write_text(unsigned char text_to_write[])
{
	unsigned long lenght_pointer_write = 0; 
	unsigned char lenght_string_to_write = strlen(&text_to_write[0]);
	unsigned char *pointeraux = &text_to_write[0];
	unsigned long converted_data_text = 0; 

	while (lenght_pointer_write < lenght_string_to_write) {

		converted_data_text = convert_to_letter(pointeraux + lenght_pointer_write);
		lcd_send_data(converted_data_text);
		lcd_send_command(WRITE);							
		lenght_pointer_write++;
	} 
}  
/********************************************************************
 * Function:	write_variable(variable_to_write)					*
 * Definition:	Subrutina per escriure variables en pantalla. 		*
 ********************************************************************/
void write_variable(unsigned long variable_to_write)
{
	sprintf(array_for_converting_to_string, "%d", variable_to_write);
	write_text(array_for_converting_to_string); 
}   
/************************************************************************************************
 * Function:	set_address_pointer(pointer_write_line,pointer_write_column)					*
 * Definition:	Establir coordenades d'escriptura a pantalla.									*
 ***********************************************************************************************/
void set_address_pointer(unsigned long position_pointer[2])
{
	lcd_send_data(position_pointer[0]);
	lcd_send_data(position_pointer[1]);
	lcd_send_command(SETADRESSPOINTER);  								
}
/********************************************************************
 * Function:	clean_screen(cleaning_option)						*
 * Definition:	Borrat de pantalla.			 						*
 ********************************************************************/
void clean_screen(unsigned char cleaning_option)
{
	switch (cleaning_option)
	{
		case TEXT:
			set_address_pointer(text_memory_position[mainlanguage]);
			bytestoclean = 0x0140;
		break;
		case GRAPHIC:
			set_address_pointer(graphic_memory_position[mainlanguage]);
			bytestoclean = 0x0A00;
		break;
		case ALL:
			set_address_pointer(all_memory_position[mainlanguage]);
			bytestoclean = 0x4A00;
		break;
		default:	;
		break;
	}
	
	do{
		lcd_send_data(0x00);
	    lcd_send_command(WRITE);
	}while (--bytestoclean);
}
/********************************************************************
 * Function:	(letter)convert_to_letter(character)				*
 * Definition:	Funcio per convert_to_letter a lletres.				*
 ********************************************************************/
unsigned char convert_to_letter (const char *character)
{
	char letter;

	letter = *character;
	letter = letter - 0x20;

	return letter;
}


/**********************************************************************************************/
/*********************** Funcions de representacio de l'Autopuncher ***************************/
/**********************************************************************************************/

/********************************************************************
 * Function:	weclome_screen()									*
 * Definition:	Mostrar pantalla de benvinguda.						*
 ********************************************************************/
void weclome_screen(void)
{
	set_address_pointer(position_welcome[mainlanguage]);						// Posem la direccio per escriure la imatge de benvinguda
	draw_lcd_graphic(pwelcome); 												// Dibuixem la presentacio
}
/********************************************************************
 * Function:	screen_show_wide()									*
 * Definition:	Mostrar wide i el valor.	 						*
 ********************************************************************/
void screen_show_wide(void)
{
	set_address_pointer(position_text_wide[mainlanguage]);
	write_text(text_wide[mainlanguage]);
	write_variable(wide);
}
/********************************************************************
 * Function:	screen_show_position()								*
 * Definition:	Mostrar posicion i el valor.						*
 ********************************************************************/
void screen_show_position(void)
{
	set_address_pointer(position_text_position[mainlanguage]);
	write_text(text_position[mainlanguage]);
	set_address_pointer(position_value_position[mainlanguage]);
	write_text(text_empty_position[mainlanguage]);
	set_address_pointer(position_value_position[mainlanguage]);
	write_variable(position);
}
/********************************************************************
 * Function:	screen_show_step()									*
 * Definition:	Mostrar paso i el valor.							*
 ********************************************************************/
void screen_show_step(void)
{
	set_address_pointer(position_text_step[mainlanguage]);
	write_text(&text_step[mainlanguage][0]);
	write_variable(step);
}
/********************************************************************
 * Function:	screen_show_pressure()								*
 * Definition:	Mostrar pressio i el valor.							*
 ********************************************************************/
void screen_show_pressure(void)
{
	set_address_pointer(position_text_pressure[mainlanguage]);
	write_text(text_pressure[mainlanguage]);
	write_variable(pressure);
}
/********************************************************************
 * Function:	positioning_screen()								*
 * Definition:	Mostrar pantalla del positioning.					*
 ********************************************************************/
void positioning_screen(void)
{
	set_address_pointer(position_text_positioning[mainlanguage]);
	write_text(text_positioning[mainlanguage]); 				// El text de posicionando no es un numero, sino que posa zero. 
}
/********************************************************************
 * Function:	searching_limit_screen()							*
 * Definition:	Mostrar pantalla del buscando limite.				*
 ********************************************************************/
void searching_limit_screen(void)
{
	set_address_pointer(position_text_positioning[mainlanguage]);
	write_text(text_positioning_limit[mainlanguage]); 				// El text de posicionando no es un numero, sino que posa zero. 
}

/********************************************************************
 * Function:	clean_pressure_value()								*
 * Definition:	Neteja el valor de pressure.						*
 ********************************************************************/
void clean_pressure_value(void)
{
	set_address_pointer(position_value_pressure[mainlanguage]);
	write_text(text_empty_pressure[mainlanguage]);
}

/********************************************************************
 * Function:	main_menu_screen()									*
 * Definition:	Mostrar pantalla del menu principal.				*
 ********************************************************************/
void main_menu_screen(void)
{
	screen_show_wide();
	screen_show_position();
	screen_show_step();
	screen_show_pressure();
}

/********************************************************************
 * Function:	door_remember_screen()								*
 * Definition:	Recordatori porta del menu principal.				*
 ********************************************************************/
void door_remember_screen(void)
{
	set_address_pointer(position_text_remember_door[mainlanguage]);
	write_text(text_remember_door[mainlanguage]);
}


/********************************************************************
 * Function:	curtain_stop_screen()								*
 * Definition:	Mostrar pantalla del paro per cortina.				*
 ********************************************************************/
void curtain_stop_screen(void)
{
	set_address_pointer(position_text_error_curtain[mainlanguage]);
	write_text(text_sec_curtain[mainlanguage]);
} 

/********************************************************************
 * Function:	pulse_start_to_continue_screen()					*
 * Definition:	Mostrar pantalla pulsar start per continuar.		*
 ********************************************************************/
void pulse_start_to_continue_screen(void)
{
	set_address_pointer(position_text_start_to_continue[mainlanguage]);
	write_text(text_start_to_continue[mainlanguage]);
}

/********************************************************************
 * Function:	screen_clean_modifying_bars()						*
 * Definition:	Eliminar barres d'edicio al menu principal.			*
 ********************************************************************/
void screen_clean_modifying_bars(void)
{
	set_address_pointer(position_bar_wide[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_bar_step[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_bar_pressure[mainlanguage]);				
	draw_lcd_line(0,18);
}

/********************************************************************
 * Function:	modifying_values_screen()							*
 * Definition:	Funcio per mostrar per pantalla la edició dels 		*
 *				parametres de l'autopuncher.						*
 ********************************************************************/
void modifying_values_screen(void)
{
	switch (value_to_modify)
	{
		case modify_wide: 
		{
			screen_show_step();
			screen_show_pressure();

			set_address_pointer(position_value_wide[mainlanguage]);
			write_text(text_empty_wide[mainlanguage]);

			set_address_pointer(position_value_wide[mainlanguage]);
			write_variable(wide);

			break;
		}
		case modify_step: 
		{
			screen_show_wide();
			screen_show_pressure();

			set_address_pointer(position_value_step[mainlanguage]);
			write_text(text_empty_step[mainlanguage]);

			set_address_pointer(position_value_step[mainlanguage]);
			write_variable(step);
		
			break;
		}
		case modify_pressure:
		{
			screen_show_wide();
			screen_show_step();			

			set_address_pointer(position_value_pressure[mainlanguage]);
			write_text(text_empty_pressure[mainlanguage]);

			set_address_pointer(position_value_pressure[mainlanguage]);
			write_variable(pressure);
			
			break;
		}
		case modify_none:
		{
			clean_modifying_lines_screen();
			break;
		}
	}
}	

/********************************************************************
 * Function:	change_flag_blink_value()							*
 * Definition:	Eliminar barres d'edicio al menu principal.			*
 ********************************************************************/
void change_flag_blink_value(void)
{
	if (flag_blink_value == 1)
	{
		flag_blink_value = 0;
	}
	else 
	{
		flag_blink_value = 1;
	}
}

/********************************************************************
 * Function:	clean_modifying_lines_screen()						*
 * Definition:	Funcio per netejar les linies d'edició.				*
 ********************************************************************/
void clean_modifying_lines_screen(void)
{ 
	set_address_pointer(position_bar_pressure[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_bar_step[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_bar_wide[mainlanguage]);
	draw_lcd_line(0,18);
}
/********************************************************************
 * Function:	modifying_lines_screen()							*
 * Definition:	Funcio per mostrar per pantalla les linies d'edicio *
 *				del parametre que es modifica.						*
 ********************************************************************/
void modifying_lines_screen(void)
{ 
	switch (value_to_modify)
	{
		case modify_wide: 
		{
			set_address_pointer(position_bar_wide[mainlanguage]);
			if (GUI_Get_MainMenuModifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					if (wide >= 100)
					{
						draw_lcd_line(1,18);;
					}
					else if (wide >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
				}
				else 
				{
					draw_lcd_line(0,18);
				}										
			}

			else
			{
					if (wide >= 100)
					{
						draw_lcd_line(1,18);;
					}
					else if (wide >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
			}	

			break;
		}
		case modify_step: 
		{
			set_address_pointer(position_bar_step[mainlanguage]);
			if (GUI_Get_MainMenuModifying() == 1)
			{
				if (flag_blink_value == 1)
				{
					if (step >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
					
				}
				else 
				{
					draw_lcd_line(0,18);
				}
			}
			else
			{
				if (step >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
			}	
			break;
		}
		case modify_pressure:
		{
			set_address_pointer(position_bar_pressure[mainlanguage]);
			if (GUI_Get_MainMenuModifying() == 1)
			{
				if (flag_blink_value == 1)
				{
					if (pressure >= 10)
					{
						draw_lcd_line(1,12);	
					}
					else 
					{
						draw_lcd_line(1,6);
					}
				}
				else 
				{
					draw_lcd_line(0,12);
				}
			}
			else
			{
				if (pressure >= 10)
					{
						draw_lcd_line(1,12);	
					}
					else 
					{
						draw_lcd_line(1,6);
					}
			}	
			break;
		}
	}
}	

/********************************************************************
 * Function:	modifying_lines_screen()							*
 * Definition:	Funcio per mostrar per pantalla les linies d'edicio *
 *				del parametre que es modifica.						*
 ********************************************************************/
void stopped_lines_screen(void)
{ 
	switch (stop_values_to_modify)
	{
		case modify_stop_pressure:
		{
			set_address_pointer(position_bar_pressure[mainlanguage]);
			if (pressure >= 10)
				{
					draw_lcd_line(1,12);	
				}
			else 
				{
					draw_lcd_line(1,6);
				}
			break;
		}
		case modify_stop_none:
		{
			set_address_pointer(position_bar_pressure[mainlanguage]);
			draw_lcd_line(0,12);
			break;
		}
	}
}	

/********************************************************************
 * Function:	password_initial_screen()							*
 * Definition:	Funcio de mostra la pantalla inicial del menu 		*
 *				password.											*
 ********************************************************************/
void password_initial_screen(void)
{
	set_address_pointer(position_text_password[mainlanguage]);
	write_text(text_password[mainlanguage]);											// Escribim text de password. 
	set_address_pointer(position_asterisks_password[mainlanguage]);	
	write_text(text_asterisks[mainlanguage]);									// Escribim els tres asteriscos inicials.
	flag_already_passed_through_all_password_numbering = 0;
}

/********************************************************************
 * Function:	screen_clean_password_bars()						*
 * Definition:	Eliminar barres d'edicio del password.				*
 ********************************************************************/
void screen_clean_password_bars(void)
{

	set_address_pointer(position_password_line_thousands[mainlanguage]);
	draw_lcd_line(0,6);
	set_address_pointer(position_password_line_hundreds[mainlanguage]);
	draw_lcd_line(0,6);
	set_address_pointer(position_password_line_tens[mainlanguage]);
	draw_lcd_line(0,6);
	set_address_pointer(position_password_line_units[mainlanguage]);
	draw_lcd_line(0,6);
	
}

/********************************************************************
 * Function:	password_lines_screen()								*
 * Definition:	Funcio per mostrar per pantalla les linies d'edicio *
 *				del parametre que es modifica a password.			*
 ********************************************************************/
void password_lines_screen(void)
{ 
	switch (password_numbering_to_modify)
	{
		case password_modify_thousands: 
		{
			if (flag_blink_value == 1)
			{
				set_address_pointer(position_password_line_thousands[mainlanguage]);
				draw_lcd_line(1,6);
			}
			else 
			{
				set_address_pointer(position_password_line_thousands[mainlanguage]);
				draw_lcd_line(0,6);
			}
			
			break;
		}
		case password_modify_hundreds: 
		{
			if (flag_blink_value == 1)
			{
				set_address_pointer(position_password_line_hundreds[mainlanguage]);
				draw_lcd_line(1,6);
			}
			else 
			{
				set_address_pointer(position_password_line_hundreds[mainlanguage]);
				draw_lcd_line(0,6);
			}

			break;
		}
		case password_modify_tens: 
		{
			if (flag_blink_value == 1)
			{
				set_address_pointer(position_password_line_tens[mainlanguage]);
				draw_lcd_line(1,6);
			}
			else 
			{
				set_address_pointer(position_password_line_tens[mainlanguage]);
				draw_lcd_line(0,6);
			}
			
			break;
		}
		case password_modify_units: 
		{
			if (flag_blink_value == 1)
			{
				set_address_pointer(position_password_line_units[mainlanguage]);
				draw_lcd_line(1,6);
			}
			else 
			{
				set_address_pointer(position_password_line_units[mainlanguage]);
				draw_lcd_line(0,6);
			}
			

			break;
		}	
	}
}
/********************************************************************
 * Function:	modifying_password()								*
 * Definition:	Funcio de mostra per pantalla la modificació dels   *
 *				valors de la password quan s'intenta accedir.		*
 ********************************************************************/
void modifying_password(void)
{
	switch (password_numbering_to_modify)
	{
		case password_modify_thousands:
		{
			set_address_pointer(position_thousands_password[mainlanguage]);
			write_text(text_empty_password[mainlanguage]);

			set_address_pointer(position_thousands_password[mainlanguage]);
			write_variable(password_try_thousands);
			
			
			if(flag_already_passed_through_all_password_numbering == 1)				// Sols volem pintar-ho si ja hem passat per les unitats. Sino volem que segueixi sent un asterisc. 
			{
				set_address_pointer(position_hundreds_password[mainlanguage]);
				write_variable(password_try_hundreds);
				set_address_pointer(position_tens_password[mainlanguage]);
				write_variable(password_try_tens);
				set_address_pointer(position_units_password[mainlanguage]);
				write_variable(password_try_units);
			}
			break;
		}

		case password_modify_hundreds:
		{
			set_address_pointer(position_hundreds_password[mainlanguage]);
			write_text(text_empty_password[mainlanguage]);

			set_address_pointer(position_hundreds_password[mainlanguage]);
			write_variable(password_try_hundreds);
			
			set_address_pointer(position_thousands_password[mainlanguage]);
			write_variable(password_try_thousands);
			
			if (flag_already_passed_through_all_password_numbering == 1)				// Sols volem pintar-ho si ja hem passat per les unitats. Sino volem que segueixi sent un asterisc. 
			{
				set_address_pointer(position_tens_password[mainlanguage]);
				write_variable(password_try_tens);
				set_address_pointer(position_units_password[mainlanguage]);
				write_variable(password_try_units);
			}

			break;

		}

		case password_modify_tens:
		{
			set_address_pointer(position_tens_password[mainlanguage]);
			write_text(text_empty_password[mainlanguage]);

			set_address_pointer(position_tens_password[mainlanguage]);
			write_variable(password_try_tens);

			set_address_pointer(position_thousands_password[mainlanguage]);
			write_variable(password_try_thousands);
			set_address_pointer(position_hundreds_password[mainlanguage]);
			write_variable(password_try_hundreds);
			
			if (flag_already_passed_through_all_password_numbering == 1)				// Sols volem pintar-ho si ja hem passat per les unitats. Sino volem que segueixi sent un asterisc. 
			{
				set_address_pointer(position_units_password[mainlanguage]);
				write_variable(password_try_units);
			}

			break;

		}

		case password_modify_units:
		{
			set_address_pointer(position_units_password[mainlanguage]);
			write_text(text_empty_password[mainlanguage]);

			set_address_pointer(position_units_password[mainlanguage]);
			write_variable(password_try_units);
			
			flag_already_passed_through_all_password_numbering = 1;

			set_address_pointer(position_thousands_password[mainlanguage]);
			write_variable(password_try_thousands);
			set_address_pointer(position_hundreds_password[mainlanguage]);
			write_variable(password_try_hundreds);
			set_address_pointer(position_tens_password[mainlanguage]);
			write_variable(password_try_tens);

			break;

		}
	}

}

/********************************************************************
 * Function:	modifying_submenu_text()							*
 * Definition:	Funcio de mostra per pantalla els textos del 		*
 *				submenú.											*
 ********************************************************************/
void modifying_submenu_text(void)
{

	set_address_pointer(position_submenu_bridge[mainlanguage]); 
	write_text(text_bridge[mainlanguage]);
	set_address_pointer(position_submenu_maxwide[mainlanguage]); 
	write_text(text_maxwide[mainlanguage]);	
	set_address_pointer(position_submenu_idioma[mainlanguage]); 
	write_text(text_idioma[mainlanguage]);
	set_address_pointer(position_submenu_bar[mainlanguage]);
	write_text(text_bar[mainlanguage]);
	set_address_pointer(position_submenu_zero[mainlanguage]); 
	write_text(text_zero[mainlanguage]);

}
/********************************************************************
 * Function:	screen_clean_submenu_bars()							*
 * Definition:	Eliminar barres d'edicio del submenú.				*
 ********************************************************************/
void screen_clean_submenu_bars(void)
{

	set_address_pointer(position_submenu_cleanbar_bridge[mainlanguage]);
	draw_lcd_line(0,30);
	set_address_pointer(position_submenu_cleanbar_maxwide[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_submenu_cleanbar_idioma[mainlanguage]);
	draw_lcd_line(0,42);
	set_address_pointer(position_submenu_cleanbar_zero[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_submenu_cleanbar_limit[mainlanguage]);
	draw_lcd_line(0,18);
}
/********************************************************************
 * Function:	modifying_submenu_values()							*
 * Definition:	Funcio de mostra per pantalla la modificació dels   *
 *				valors de la password quan s'intenta accedir.		*
 ********************************************************************/
void modifying_submenu_values(void)
{
	switch (submenu_parameter_to_modify)
	{
		case submenu_bridge:
		{
			set_address_pointer(position_value_bridge[mainlanguage]);
			write_text(text_empty_bridge[mainlanguage]);
			set_address_pointer(position_value_bridge[mainlanguage]);
			if(bridge == 0)
			{
				write_text(text_bridge_open[mainlanguage]);
			}
			else 
			{
				write_text(text_bridge_closed[mainlanguage]);
			}	

			set_address_pointer(position_value_maxwidth[mainlanguage]);
			write_variable(MAX_WIDE);
			set_address_pointer(position_value_language[mainlanguage]);
			if (mainlanguage == 0)
			{
				write_text(text_language_spanish[mainlanguage]);	
			}
			else if (mainlanguage == 1)
			{
				write_text(text_language_english[mainlanguage]);
			}
			else if (mainlanguage == 2)
			{
				write_text(text_language_italian[mainlanguage]);
			}
			else if (mainlanguage == 3)
			{
				write_text(text_language_french[mainlanguage]);
			}
			if (zero_value >= 100)
			{	
				set_address_pointer(position_value_3_zero[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_value_2_zero[mainlanguage]);
			}
			write_variable(zero_value);
			set_address_pointer(position_value_limit[mainlanguage]);
			write_variable(end_limit);
			
			break;

		}

		case submenu_max_width:
		{
			set_address_pointer(position_value_maxwidth[mainlanguage]);
			write_text(text_empty_maxwidth[mainlanguage]);

			set_address_pointer(position_value_maxwidth[mainlanguage]);
			write_variable(MAX_WIDE);
						
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.


			set_address_pointer(position_value_bridge[mainlanguage]);
			if(bridge == 0)
			{
				write_text(text_bridge_open[mainlanguage]);
			}
			else 
			{
				write_text(text_bridge_closed[mainlanguage]);
			}
			set_address_pointer(position_value_language[mainlanguage]);
			if (mainlanguage == 0)
			{
				write_text(text_language_spanish[mainlanguage]);	
			}
			else if (mainlanguage == 1)
			{
				write_text(text_language_english[mainlanguage]);
			}
			else if (mainlanguage == 2)
			{
				write_text(text_language_italian[mainlanguage]);
			}
			else if (mainlanguage == 3)
			{
				write_text(text_language_french[mainlanguage]);
			}
			if (zero_value >= 100)
			{	
				set_address_pointer(position_value_3_zero[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_value_2_zero[mainlanguage]);
			}
			write_variable(zero_value);
			set_address_pointer(position_value_limit[mainlanguage]);
			write_variable(end_limit);
			break;

		}

		case submenu_language:
		{
			set_address_pointer(position_value_language[mainlanguage]);
			write_text(text_empty_language[mainlanguage]);

			set_address_pointer(position_value_language[mainlanguage]);
			if (mainlanguage == 0)
			{
				write_text(text_language_spanish[mainlanguage]);	
			}
			else if (mainlanguage == 1)
			{
				write_text(text_language_english[mainlanguage]);
			}
			else if (mainlanguage == 2)
			{
				write_text(text_language_italian[mainlanguage]);
			}
			else if (mainlanguage == 3)
			{
				write_text(text_language_french[mainlanguage]);
			}
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.

			set_address_pointer(position_value_bridge[mainlanguage]);
			if(bridge == 0)
			{
				write_text(text_bridge_open[mainlanguage]);
			}
			else 
			{
				write_text(text_bridge_closed[mainlanguage]);
			}
			set_address_pointer(position_value_maxwidth[mainlanguage]);
			write_variable(MAX_WIDE);
			if (zero_value >= 100)
			{	
				set_address_pointer(position_value_3_zero[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_value_2_zero[mainlanguage]);
			}
			write_variable(zero_value);
			set_address_pointer(position_value_limit[mainlanguage]);
			write_variable(end_limit);

			break;

		}

		case submenu_zero_value: 
		{		

			set_address_pointer(position_value_3_zero[mainlanguage]);
			write_text(text_empty_zero[mainlanguage]);

			if (zero_value >= 100)
			{	
				set_address_pointer(position_value_3_zero[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_value_2_zero[mainlanguage]);
			}
			write_variable(zero_value);
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.

			set_address_pointer(position_value_bridge[mainlanguage]);
			if(bridge == 0)
			{
				write_text(text_bridge_open[mainlanguage]);
			}
			else 
			{
				write_text(text_bridge_closed[mainlanguage]);
			}
			set_address_pointer(position_value_maxwidth[mainlanguage]);
			write_variable(MAX_WIDE);
			set_address_pointer(position_value_language[mainlanguage]);
			if (mainlanguage == 0)
			{
				write_text(text_language_spanish[mainlanguage]);	
			}
			else if (mainlanguage == 1)
			{
				write_text(text_language_english[mainlanguage]);
			}
			else if (mainlanguage == 2)
			{
				write_text(text_language_italian[mainlanguage]);
			}
			else if (mainlanguage == 3)
			{
				write_text(text_language_french[mainlanguage]);
			}
			set_address_pointer(position_value_limit[mainlanguage]);
			write_variable(end_limit);		

			break;
		}

		case submenu_limit_value:
		{

			set_address_pointer(position_value_limit[mainlanguage]);
			write_text(text_empty_limit[mainlanguage]);

			set_address_pointer(position_value_limit[mainlanguage]);
			write_variable(end_limit);

			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.

			set_address_pointer(position_value_bridge[mainlanguage]);
			if(bridge == 0)
			{
				write_text(text_bridge_open[mainlanguage]);
			}
			else 
			{
				write_text(text_bridge_closed[mainlanguage]);
			}
			set_address_pointer(position_value_maxwidth[mainlanguage]);
			write_variable(MAX_WIDE);
			set_address_pointer(position_value_language[mainlanguage]);
			if (mainlanguage == 0)
			{
				write_text(text_language_spanish[mainlanguage]);	
			}
			else if (mainlanguage == 1)
			{
				write_text(text_language_english[mainlanguage]);
			}
			else if (mainlanguage == 2)
			{
				write_text(text_language_italian[mainlanguage]);
			}
			else if (mainlanguage == 3)
			{
				write_text(text_language_french[mainlanguage]);
			}
			if (zero_value >= 100)
			{	
				set_address_pointer(position_value_3_zero[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_value_2_zero[mainlanguage]);
			}
			write_variable(zero_value);

			break;
		}


	}

}

/********************************************************************
 * Function:	submenu_lines_screen()								*
 * Definition:	Funcio per mostrar per pantalla les linies d'edicio *
 *				del parametre que es modifica a submenu.			*
 ********************************************************************/
void submenu_lines_screen(void)
{ 

	switch (submenu_parameter_to_modify)
	{
		case submenu_bridge: 
		{
			if (GUI_Get_SubmenuModifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu_value_bridge[mainlanguage]);
					draw_lcd_line(1,30);
				}
				else 
				{
					set_address_pointer(position_submenu_value_bridge[mainlanguage]);
					draw_lcd_line(0,30);
				}
			}
			else
			{
				set_address_pointer(position_submenu_value_bridge[mainlanguage]);
				draw_lcd_line(1,30);
			}
			
			break;
		}
		case submenu_max_width: 
		{
			if (GUI_Get_SubmenuModifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu_value_maxwide[mainlanguage]);
					if (MAX_WIDE >= 100)
					{
						draw_lcd_line(1,18);
					}
					else 
					{
						draw_lcd_line(1,12);
					}
				}
				else 
				{
					set_address_pointer(position_submenu_value_maxwide[mainlanguage]);
					draw_lcd_line(0,18);
				}
			}
			else
			{
				set_address_pointer(position_submenu_value_maxwide[mainlanguage]);
				if (MAX_WIDE >= 100)
				{
					draw_lcd_line(1,18);
				}
				else 
				{
					draw_lcd_line(1,12);
				}
			}
			break;
		}
		case submenu_language: 
		{
			if (GUI_Get_SubmenuModifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu_value_idioma[mainlanguage]);
					draw_lcd_line(1,18);
				}
				else 
				{
					set_address_pointer(position_submenu_value_idioma[mainlanguage]);
					draw_lcd_line(0,18);
				}
			}
			else
			{
				set_address_pointer(position_submenu_value_idioma[mainlanguage]);
				draw_lcd_line(1,18);
			}
			break;
		}
		case submenu_zero_value: 
		{
			if (GUI_Get_SubmenuModifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					if (zero_value >= 100)
					{
						set_address_pointer(position_submenu_value_3_zero[mainlanguage]);
						draw_lcd_line(1,18);
					}
					else 
					{
						set_address_pointer(position_submenu_value_2_zero[mainlanguage]);
						draw_lcd_line(1,12);
					}
				}
				else 
				{
						set_address_pointer(position_submenu_value_3_zero[mainlanguage]);
						draw_lcd_line(0,18);
				}
			}
			else
			{
				if (zero_value >= 100)
				{
					set_address_pointer(position_submenu_value_3_zero[mainlanguage]);
					draw_lcd_line(1,18);
				}
				else 
				{
					set_address_pointer(position_submenu_value_2_zero[mainlanguage]);
					draw_lcd_line(1,12);
				}
			}

			break;
		}
		case submenu_limit_value: 
		{
			if (GUI_Get_SubmenuModifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu_value_limit[mainlanguage]);
					if (end_limit >= 100)
					{
						draw_lcd_line(1,18);
					}
					else 
					{
						draw_lcd_line(1,12);
					}
				}
				else 
				{
					set_address_pointer(position_submenu_value_limit[mainlanguage]);
					draw_lcd_line(0,18);
				}
			}
			else
			{
				set_address_pointer(position_submenu_value_limit[mainlanguage]);
				if (end_limit >= 100)
				{
					draw_lcd_line(1,18);
				}
				else 
				{
					draw_lcd_line(1,12);
				}
			}

			break;
		}		
	}
}

/********************************************************************
 * Function:	error_show_particular_message()						*
 * Definition:	Funcio per mostrar per pantalla l'error particular	*
 *				que es doni en aquell moment.						*
 ********************************************************************/
void error_show_particular_message(void)
{
	flag_show_particular_error_message = 1; 
}
/********************************************************************
 * Function:	error_show_general_reset_message()					*
 * Definition:	Funcio per mostrar per pantalla que l'error ha		*
 *				desaparegut i mostrar polsar reset.					*
 ********************************************************************/
void error_show_general_reset_message(void)
{
	flag_show_particular_error_message = 0; 
}
/********************************************************************
 * Function:	error_show_door_message()							*
 * Definition:	Funcio per mostrar per pantalla l'error de porta.	*
 ********************************************************************/
void error_show_door_message(void)
{
	set_address_pointer(position_text_error_door[mainlanguage]);
	write_text(text_sec_door[mainlanguage]);	
}
/********************************************************************
 * Function:	error_show_holder_message()							*
 * Definition:	Funcio per mostrar per pantalla l'error de holder.	*
 ********************************************************************/
void error_show_holder_message(void)
{
	set_address_pointer(position_text_error_holder[mainlanguage]);
	write_text(text_sec_holder[mainlanguage]);	
}

/*********************************************************************
 * Function:	error_show_emergency_message()						 *
 * Definition:	Funcio per mostrar per pantalla l'error d'emergencia.*
 *********************************************************************/
void error_show_emergency_message(void)
{
	set_address_pointer(position_text_error_emergency[mainlanguage]);
	write_text(text_sec_emergency[mainlanguage]);	
}

/*********************************************************************
 * Function:	error_show_cylinder_message()						 *
 * Definition:	Funcio per mostrar per pantalla l'error d'emergencia.*
 *********************************************************************/
void error_show_cylinder_message(void)
{
	set_address_pointer(position_text_error_cylinder[mainlanguage]);
	write_text(text_sec_cylinder[mainlanguage]);	
}
/*********************************************************************
 * Function:	error_show_start_message()							 *
 * Definition:	Funcio per mostrar per pantalla l'error d'emergencia.*
 *********************************************************************/
void error_show_start_message(void)
{
	set_address_pointer(position_text_error_start[mainlanguage]);
	write_text(text_sec_start[mainlanguage]);	
}

/*********************************************************************
 * Function:	error_show_end_message()							 *
 * Definition:	Funcio per mostrar per pantalla l'error d'emergencia.*
 *********************************************************************/
void error_show_end_message(void)
{
	set_address_pointer(position_text_error_end[mainlanguage]);
	write_text(text_sec_end[mainlanguage]);	
}

/********************************************************************
 * Function:	error_screen()										*
 * Definition:	Funcio per mostrar per pantalla l'error en funcio   *
 *				del que sigui.										*
 ********************************************************************/
void error_screen(void)
{
	switch (error_state)
	{
		case error_holder: 
		{
			if (flag_show_particular_error_message == 1)
			{
				set_address_pointer(position_text_error_holder[mainlanguage]);
				write_text(text_sec_holder[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_text_reset_error[mainlanguage]);
				write_text(text_reset_error[mainlanguage]);
			}
			break;
		}
		case error_cylinder: 
		{
			if (flag_show_particular_error_message == 1)
			{
				set_address_pointer(position_text_error_cylinder[mainlanguage]);
				write_text(text_sec_cylinder[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_text_reset_error[mainlanguage]);
				write_text(text_reset_error[mainlanguage]);
			}
			break;
		}
		case error_emergency: 
		{
			if (flag_show_particular_error_message == 1)
			{
				set_address_pointer(position_text_error_emergency[mainlanguage]);
				write_text(text_sec_emergency[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_text_reset_error[mainlanguage]);
				write_text(text_reset_error[mainlanguage]);
			}
			break;
		}
		case error_start: 
		{
			if (flag_show_particular_error_message == 1)
			{
				set_address_pointer(position_text_error_start[mainlanguage]);
				write_text(text_sec_start[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_text_reset_error[mainlanguage]);
				write_text(text_reset_error[mainlanguage]);
			}
			break;
		}
		case error_end: 
		{
			if (flag_show_particular_error_message == 1)
			{
				set_address_pointer(position_text_error_end[mainlanguage]);
				write_text(text_sec_end[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_text_reset_error[mainlanguage]);
				write_text(text_reset_error[mainlanguage]);
			}
			break;
		}
		case error_door: 
		{
			if (flag_show_particular_error_message == 1)
			{
				set_address_pointer(position_text_error_door[mainlanguage]);
				write_text(text_sec_door[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_text_reset_error[mainlanguage]);
				write_text(text_reset_error[mainlanguage]);
			}
			break;
		}
		case error_sensors: 
		{
			if (flag_show_particular_error_message == 1)
			{
				set_address_pointer(position_text_error_sensors[mainlanguage]);
				write_text(text_sec_sensors[mainlanguage]);
			}
			else 
			{
				set_address_pointer(position_text_reset_error[mainlanguage]);
				write_text(text_reset_error[mainlanguage]);
			}
			break;
		}

	}


}

/********************************************************************
 * Function:	modifying_submenu2_text()							*
 * Definition:	Funcio de mostra per pantalla els textos del 		*
 *				submenú2.											*
 ********************************************************************/
void modifying_submenu2_text(void)
{

	set_address_pointer(position_submenu2_text_ton[mainlanguage]); 
	write_text(text_submenu2_ton[mainlanguage]);
	set_address_pointer(position_submenu2_text_toffmin[mainlanguage]); 
	write_text(text_submenu2_toffmin[mainlanguage]);	
	set_address_pointer(position_submenu2_text_toffmax[mainlanguage]); 
	write_text(text_submenu2_toffmax[mainlanguage]);
	set_address_pointer(position_submenu2_text_stepspdchange[mainlanguage]);
	write_text(text_submenu2_stepspdchange[mainlanguage]);
	set_address_pointer(position_submenu2_text_aceldecel[mainlanguage]); 
	write_text(text_submenu2_aceldecel[mainlanguage]);
	set_address_pointer(position_submenu2_text_turns[mainlanguage]);
	write_text(text_submenu2_turns[mainlanguage]);

}

/********************************************************************
 * Function:	modifying_submenu2_values()							*
 * Definition:	Funcio de mostra per pantalla la modificació dels   *
 *				valors del submenu 2.								*
 ********************************************************************/
void modifying_submenu2_values(void)
{
	switch (submenu2_parameter_to_modify)
	{
		case submenu2_ton:
		{

			set_address_pointer(position_submenu2_value_ton[mainlanguage]);					// Netejo el valor que es modifica
			write_text(text_empty_ton[mainlanguage]);

			set_address_pointer(position_submenu2_value_ton[mainlanguage]);					// Pinto el valor nou que es modifica
			write_variable(TON);
			
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.
			

			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_variable(TOFF_MIN);
			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_variable(TOFF_MAX);
			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_variable(necessary_steps_for_change);			
			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_variable(accelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(decelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(distance_limit_to_start);
			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_variable(submenu2_turns_number);
			break;

		}
		
		case submenu2_toffmin:
		{

			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_text(text_empty_toffmin[mainlanguage]);

			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_variable(TOFF_MIN);
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.
			
			set_address_pointer(position_submenu2_value_ton[mainlanguage]);
			write_variable(TON);
			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_variable(TOFF_MAX);
			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_variable(necessary_steps_for_change);			
			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_variable(accelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(decelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(distance_limit_to_start);
			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_variable(submenu2_turns_number);
			break;

		}
		
		case submenu2_toffmax:
		{

			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_text(text_empty_toffmax[mainlanguage]);

			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_variable(TOFF_MAX);
			
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.
			

			set_address_pointer(position_submenu2_value_ton[mainlanguage]);
			write_variable(TON);
			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_variable(TOFF_MIN);
			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_variable(necessary_steps_for_change);			
			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_variable(accelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(decelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(distance_limit_to_start);
			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_variable(submenu2_turns_number);
			break;

		}
		
		case submenu2_stepspdchange:
		{

			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_text(text_empty_stepspdchange[mainlanguage]);

			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_variable(necessary_steps_for_change);
		
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.
			

			set_address_pointer(position_submenu2_value_ton[mainlanguage]);
			write_variable(TON);
			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_variable(TOFF_MIN);
			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_variable(TOFF_MAX);
			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_variable(accelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(decelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(distance_limit_to_start);
			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_variable(submenu2_turns_number);
			break;

		}
		
		case submenu2_acel:
		{

			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_text(text_empty_acel[mainlanguage]);

			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_variable(accelerate_constant);
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.
			

			set_address_pointer(position_submenu2_value_ton[mainlanguage]);
			write_variable(TON);
			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_variable(TOFF_MIN);
			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_variable(TOFF_MAX);
			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_variable(necessary_steps_for_change);			
			set_address_pointer(position_submenu2_text_bar[mainlanguage]);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(decelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(distance_limit_to_start);
			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_variable(submenu2_turns_number);
			break;

		}
		
		case submenu2_decel:
		{

			set_address_pointer(position_submenu2_value_decel[mainlanguage]);
			write_text(text_empty_decel[mainlanguage]);

			set_address_pointer(position_submenu2_value_decel[mainlanguage]);
			write_variable(decelerate_constant);
			
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.
			

			set_address_pointer(position_submenu2_value_ton[mainlanguage]);
			write_variable(TON);
			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_variable(TOFF_MIN);
			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_variable(TOFF_MAX);
			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_variable(necessary_steps_for_change);			
			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_variable(accelerate_constant);
			set_address_pointer(position_submenu2_text_bar2[mainlanguage]);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(distance_limit_to_start);
			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_variable(submenu2_turns_number);
			break;

		}
		
		case submenu2_longini:
		{
			set_address_pointer(position_submenu2_value_longini[mainlanguage]);
			write_text(text_empty_longini[mainlanguage]);

			set_address_pointer(position_submenu2_value_longini[mainlanguage]);
			write_variable(distance_limit_to_start);
			

			set_address_pointer(position_submenu2_value_ton[mainlanguage]);
			write_variable(TON);
			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_variable(TOFF_MIN);
			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_variable(TOFF_MAX);
			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_variable(necessary_steps_for_change);			
			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_variable(accelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(decelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_variable(submenu2_turns_number);

			break;
		} 

		case submenu2_turns:
		{

			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_text(text_empty_turns[mainlanguage]);

			set_address_pointer(position_submenu2_value_turns[mainlanguage]);
			write_variable(submenu2_turns_number);
			
			// Pintem la resta de valors, per assegurar-nos que no s'han quedat en blanc al editar-los.
			

			set_address_pointer(position_submenu2_value_ton[mainlanguage]);
			write_variable(TON);
			set_address_pointer(position_submenu2_value_toffmin[mainlanguage]);
			write_variable(TOFF_MIN);
			set_address_pointer(position_submenu2_value_toffmax[mainlanguage]);
			write_variable(TOFF_MAX);
			set_address_pointer(position_submenu2_value_stepspdchange[mainlanguage]);
			write_variable(necessary_steps_for_change);			
			set_address_pointer(position_submenu2_value_acel[mainlanguage]);
			write_variable(accelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(decelerate_constant);
			write_text(text_submenu2_bar[mainlanguage]);
			write_variable(distance_limit_to_start);

			break;

		}
	}

}

/********************************************************************
 * Function:	screen_clean_submenu2_bars()						*
 * Definition:	Eliminar barres d'edicio del submenú2.				*
 ********************************************************************/
void screen_clean_submenu2_bars(void)
{
	set_address_pointer(position_submenu2_line_ton[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_submenu2_line_toffmin[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_submenu2_line_toffmax[mainlanguage]);
	draw_lcd_line(0,24);
	set_address_pointer(position_submenu2_line_stepspdchange[mainlanguage]);
	draw_lcd_line(0,18);
	set_address_pointer(position_submenu2_line_acel[mainlanguage]);
	draw_lcd_line(0,6);
	set_address_pointer(position_submenu2_line_decel[mainlanguage]);
	draw_lcd_line(0,6);
	set_address_pointer(position_submenu2_line_longini[mainlanguage]);
	draw_lcd_line(0,12);
	set_address_pointer(position_submenu2_line_turns[mainlanguage]);
	draw_lcd_line(0,18);	
}
/********************************************************************
 * Function:	submenu2_lines_screen()								*
 * Definition:	Funcio per mostrar per pantalla les linies d'edicio *
 *				del parametre que es modifica a submenu2.			*
 ********************************************************************/
void submenu2_lines_screen(void)
{ 
	switch (submenu2_parameter_to_modify)
	{
		case submenu2_ton: 
		{
			if (GUI_Get_Submenu2Modifying() == 1)	
			{	
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu2_line_ton[mainlanguage]);
					if (TON >= 100)
					{	
						draw_lcd_line(1,18);
					}
					else 
					{
						draw_lcd_line(1,12);
					}
				}
				else 
				{
					set_address_pointer(position_submenu2_line_ton[mainlanguage]);
					draw_lcd_line(0,18);
				}
			}
			else
			{
				set_address_pointer(position_submenu2_line_ton[mainlanguage]);
				if (TON >= 100)
				{	
					draw_lcd_line(1,18);
				}
				else 
				{
					draw_lcd_line(1,12);
				}
			}
			break;
		}
		case submenu2_toffmin: 
		{
			if (GUI_Get_Submenu2Modifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu2_line_toffmin[mainlanguage]);
					if (TOFF_MIN >= 100)
					{
						draw_lcd_line(1,18);
					}
					else if (TOFF_MIN >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
				}
				else 
				{
					set_address_pointer(position_submenu2_line_toffmin[mainlanguage]);
					draw_lcd_line(0,18);
				}
			}
			else
			{
				set_address_pointer(position_submenu2_line_toffmin[mainlanguage]);
				if (TOFF_MIN >= 100)
				{
					draw_lcd_line(1,18);
				}
				else if (TOFF_MIN >= 10)
				{
					draw_lcd_line(1,12);
				}
				else 
				{
					draw_lcd_line(1,6);
				}	
			}	

			break;
		}
		case submenu2_toffmax: 
		{
			if (GUI_Get_Submenu2Modifying() == 1)	
			{	
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu2_line_toffmax[mainlanguage]);
	
					if (TOFF_MAX >= 1000)
					{
						draw_lcd_line(1,24);
					}
					else if (TOFF_MAX >= 100)
					{
						draw_lcd_line(1,18);
					}
					else if (TOFF_MAX >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
				}
				else 
				{
					set_address_pointer(position_submenu2_line_toffmax[mainlanguage]);
					draw_lcd_line(0,24);
				}	
			}
			else
			{
				set_address_pointer(position_submenu2_line_toffmax[mainlanguage]);
				if (TOFF_MAX >= 1000)
				{
					draw_lcd_line(1,24);
				}
				else if (TOFF_MAX >= 100)
				{
					draw_lcd_line(1,18);
				}
				else if (TOFF_MAX >= 10)
				{
					draw_lcd_line(1,12);
				}
				else 
				{
					draw_lcd_line(1,6);
				}
			}		
			break;
		}
		case submenu2_stepspdchange: 
		{
			if (GUI_Get_Submenu2Modifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu2_line_stepspdchange[mainlanguage]);
	
					if (necessary_steps_for_change >= 100)
					{
						draw_lcd_line(1,18);
					}
					else if (necessary_steps_for_change >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
				}
				else 
				{
					set_address_pointer(position_submenu2_line_stepspdchange[mainlanguage]);
					draw_lcd_line(0,18);
				}	
			}
			else
			{
				set_address_pointer(position_submenu2_line_stepspdchange[mainlanguage]);
				if (necessary_steps_for_change >= 100)
				{
					draw_lcd_line(1,18);
				}
				else if (necessary_steps_for_change >= 10)
				{
					draw_lcd_line(1,12);
				}
				else 
				{
					draw_lcd_line(1,6);
				}	
			}	
			break;
		}
		case submenu2_acel: 
		{
			if (GUI_Get_Submenu2Modifying() == 1)	
			{	
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu2_line_acel[mainlanguage]);
					draw_lcd_line(1,6);
				}
				else 
				{
					set_address_pointer(position_submenu2_line_acel[mainlanguage]);
					draw_lcd_line(0,6);
				}
			}
			else
			{
				set_address_pointer(position_submenu2_line_acel[mainlanguage]);
				draw_lcd_line(1,6);
			}
			break;
		}
		case submenu2_decel: 
		{
			if (GUI_Get_Submenu2Modifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu2_line_decel[mainlanguage]);
					draw_lcd_line(1,6);
				}
				else 
				{
					set_address_pointer(position_submenu2_line_decel[mainlanguage]);
					draw_lcd_line(0,6);
				}
			}
			else
			{
				set_address_pointer(position_submenu2_line_decel[mainlanguage]);
				draw_lcd_line(1,6);
			}
			break;
		}

		case submenu2_longini:
		{
			if (GUI_Get_Submenu2Modifying() == 1)	
			{
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu2_line_longini[mainlanguage]);
					if (distance_limit_to_start >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
				}
				else 
				{
					set_address_pointer(position_submenu2_line_longini[mainlanguage]);
					draw_lcd_line(0,12);
				}	
			}
			else
			{
				set_address_pointer(position_submenu2_line_longini[mainlanguage]);
				if (distance_limit_to_start >= 10)
				{
					draw_lcd_line(1,12);
				}
				else 
				{
					draw_lcd_line(1,6);
				}
			}		
			break;
		}

		case submenu2_turns: 
		{
			if (GUI_Get_Submenu2Modifying() == 1)	
			{	
				if (flag_blink_value == 1)
				{
					set_address_pointer(position_submenu2_line_turns[mainlanguage]);
					if (submenu2_turns_number >= 10)
					{
						draw_lcd_line(1,12);
					}
					else 
					{
						draw_lcd_line(1,6);
					}
				}
				else 
				{
					set_address_pointer(position_submenu2_line_turns[mainlanguage]);
					draw_lcd_line(0,12);
				}
			}
			else
			{
				set_address_pointer(position_submenu2_line_turns[mainlanguage]);
				if (submenu2_turns_number >= 10)
				{
					draw_lcd_line(1,12);
				}
				else 
				{
					draw_lcd_line(1,6);
				}
			}
			break;
		}
	}
}
/********************************************************************
 * Function:	print_autotest_reset()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_reset(void)
{
	set_address_pointer(position_test_reset[mainlanguage]);
	write_text(text_test_reset[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_reset_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_reset_empty(void)
{
	set_address_pointer(position_test_reset[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_aa()									*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_aa(void)
{
	set_address_pointer(position_test_aa[mainlanguage]);
	write_text(text_test_aa[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_aa_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_aa_empty(void)
{
	set_address_pointer(position_test_aa[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_ab()									*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_ab(void)
{
	set_address_pointer(position_test_ab[mainlanguage]);
	write_text(text_test_ab[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_ab_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_ab_empty(void)
{
	set_address_pointer(position_test_ab[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_stop()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_stop(void)
{
	set_address_pointer(position_test_stop[mainlanguage]);
	write_text(text_test_stop[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_stop_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_stop_empty(void)
{
	set_address_pointer(position_test_stop[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_start()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_start(void)
{
	set_address_pointer(position_test_start[mainlanguage]);
	write_text(text_test_start[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_start_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_start_empty(void)
{
	set_address_pointer(position_test_start[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_menu()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_menu(void)
{
	set_address_pointer(position_test_menu[mainlanguage]);
	write_text(text_test_menu[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_menu_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_menu_empty(void)
{
	set_address_pointer(position_test_menu[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_esc()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_esc(void)
{
	set_address_pointer(position_test_esc[mainlanguage]);
	write_text(text_test_esc[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_menu_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_esc_empty(void)
{
	set_address_pointer(position_test_esc[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_ok()									*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_ok(void)
{
	set_address_pointer(position_test_ok[mainlanguage]);
	write_text(text_test_ok[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_ok_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_ok_empty(void)
{
	set_address_pointer(position_test_ok[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_emergency()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_emergency(void)
{
	set_address_pointer(position_test_emergency[mainlanguage]);
	write_text(text_test_emergency[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_emergency_empty()					*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_emergency_empty(void)
{
	set_address_pointer(position_test_emergency[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_cylinder()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_cylinder(void)
{
	set_address_pointer(position_test_cylinder[mainlanguage]);
	write_text(text_test_cylinder[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_cylinder_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_cylinder_empty(void)
{
	set_address_pointer(position_test_cylinder[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_inicio()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_inicio(void)
{
	set_address_pointer(position_test_inicio[mainlanguage]);
	write_text(text_test_inicio[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_inicio_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_inicio_empty(void)
{
	set_address_pointer(position_test_inicio[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_end()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_end(void)
{
	set_address_pointer(position_test_end[mainlanguage]);
	write_text(text_test_end[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_end_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_end_empty(void)
{
	set_address_pointer(position_test_end[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_door()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_door(void)
{
	set_address_pointer(position_test_door[mainlanguage]);
	write_text(text_test_door[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_door_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_door_empty(void)
{
	set_address_pointer(position_test_door[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_curtain()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_curtain(void)
{
	set_address_pointer(position_test_curtain[mainlanguage]);
	write_text(text_test_curtain[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_curtain_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_curtain_empty(void)
{
	set_address_pointer(position_test_curtain[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_8()									*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_i8(void)
{
	set_address_pointer(position_test_i8[mainlanguage]);
	write_text(text_test_8[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_8_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_i8_empty(void)
{
	set_address_pointer(position_test_i8[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_9()									*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_i9(void)
{
	set_address_pointer(position_test_i9[mainlanguage]);
	write_text(text_test_9[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_9_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_i9_empty(void)
{
	set_address_pointer(position_test_i9[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_holder()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_holder(void)
{
	set_address_pointer(position_test_holder[mainlanguage]);
	write_text(text_test_holder[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_holder_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_holder_empty(void)
{
	set_address_pointer(position_test_holder[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_belt()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_belt(void)
{
	set_address_pointer(position_test_belt[mainlanguage]);
	write_text(text_test_belt[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_belt_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_belt_empty(void)
{
	set_address_pointer(position_test_belt[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_step()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_step(void)
{
	set_address_pointer(position_test_step[mainlanguage]);
	write_text(text_test_step[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_step_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_step_empty(void)
{
	set_address_pointer(position_test_step[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_punch()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_punch(void)
{
	set_address_pointer(position_test_punch[mainlanguage]);
	write_text(text_test_punch[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_punch_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_punch_empty(void)
{
	set_address_pointer(position_test_punch[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_0()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_0(void)
{
	set_address_pointer(position_test_0[mainlanguage]);
	write_text(text_test_0[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_0_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_0_empty(void)
{
	set_address_pointer(position_test_0[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_1()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_1(void)
{
	set_address_pointer(position_test_1[mainlanguage]);
	write_text(text_test_1[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_1_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_1_empty(void)
{
	set_address_pointer(position_test_1[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_2()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_2(void)
{
	set_address_pointer(position_test_2[mainlanguage]);
	write_text(text_test_2[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_2_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_2_empty(void)
{
	set_address_pointer(position_test_2[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_3()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_3(void)
{
	set_address_pointer(position_test_3[mainlanguage]);
	write_text(text_test_3[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_3_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_3_empty(void)
{
	set_address_pointer(position_test_3[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_4()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_4(void)
{
	set_address_pointer(position_test_4[mainlanguage]);
	write_text(text_test_4[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_4_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_4_empty(void)
{
	set_address_pointer(position_test_4[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_5()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_5(void)
{
	set_address_pointer(position_test_5[mainlanguage]);
	write_text(text_test_5[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_5_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_5_empty(void)
{
	set_address_pointer(position_test_5[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_6()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_6(void)
{
	set_address_pointer(position_test_6[mainlanguage]);
	write_text(text_test_6[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_6_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_6_empty(void)
{
	set_address_pointer(position_test_6[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_7()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_7(void)
{
	set_address_pointer(position_test_7[mainlanguage]);
	write_text(text_test_7[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_7_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_7_empty(void)
{
	set_address_pointer(position_test_7[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_8()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_8(void)
{
	set_address_pointer(position_test_8[mainlanguage]);
	write_text(text_test_8[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_8_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_8_empty(void)
{
	set_address_pointer(position_test_8[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_9()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_9(void)
{
	set_address_pointer(position_test_9[mainlanguage]);
	write_text(text_test_9[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_9_empty()							*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_9_empty(void)
{
	set_address_pointer(position_test_9[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}
/********************************************************************
 * Function:	print_autotest_number_empty()						*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_number_empty(void)
{
	set_address_pointer(position_test_number[mainlanguage]);
	write_text(text_test_empty[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_autotest_title()								*
 * Definition:	Mostrar pantalla del autotest.						*
 ********************************************************************/
void print_autotest_title(void)
{
	set_address_pointer(position_autotest[mainlanguage]);
	write_text(text_autotest[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_software_version_presentation()				*
 * Definition:	Mostrar versio de sowftware							*
 ********************************************************************/
void print_software_version_presentation(void)
{
	set_address_pointer(position_version_presentation[mainlanguage]);
	write_text(text_version[mainlanguage]); 				
}

/********************************************************************
 * Function:	print_software_version_submenu()					*
 * Definition:	Mostrar versio de sowftware							*
 ********************************************************************/
void print_software_version_submenu(void)
{
	set_address_pointer(position_version_submenu[mainlanguage]);
	write_text(text_version[mainlanguage]); 				
}

/**************************** EOF ***********************************/
