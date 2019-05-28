/********************************************************************
 * FileName:		LCD_Control.h									*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibreria per LCD_Control.c									*
 *																	*
 * Change History:			Version 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverte		29/10/18		Versio inicial.					*
 *																	*
 ********************************************************************/

#ifndef LCD_H
#define LCD_H
/***************** Definicio de subrutines usades *******************/

void status_check(void);
unsigned char read_Status(void);
void lcd_send_command(unsigned char lcd_command);
void lcd_send_data(unsigned char lcd_data);
void lcd_init (void);
void write_text(unsigned char text_to_write[]);
void write_variable(unsigned long variable_to_write);
void set_address_pointer(unsigned long position_pointer[2]);
void clean_screen(unsigned char cleaning_option);
void draw_lcd_graphic(unsigned char *draw_direction);
unsigned char convert_to_letter (const char *character);
void weclome_screen(void);
void screen_show_wide(void);
void screen_show_position(void);
void screen_show_step(void);
void screen_show_pressure(void);
void positioning_screen(void);
void main_menu_screen(void);
void modifying_values_screen(void);






/***************** definicions de variables **************************/

#define LCD_DELAY_US 20

// Comandes LCD

#define LANGUAGE 4
#define WRITE	 			0xc0			// Comanda per escriure
#define READ 				0xc1			// Comanda per llegir
#define TEXTHOMEADRESS  	0x40			// Comanda per establir adressa de text 
#define TEXTAREA			0x41			// Comanda per establir area de text
#define GRAPHICHOMEADRESS	0x42			// Comanda per establir adressa de grafiques
#define GRAPHICAREA			0x43 			// Comanda per establir area de grafiques
#define ORMODE				0x80			// Comanda per usar el mode "OR"
#define TEXTMODE 			0x94			// Comanda per usar el mode de text
#define GRAPHICMODE 		0x98			// Comanda per usar el mode de grafiques
#define TIGMODE				0x9C			// Comanda per usar el mdoe "text&graphics"
#define SETADRESSPOINTER	0x24 			// Comanda per determinar el adress pointer 

// Mode de funcionament 

#define TEXT 				0 				// Mode de funcionament de pantalla per text
#define GRAPHIC 			1 				// Mode de funcionament de pantalla per grafics
#define ALL 				2				// Mode de funcionament de pantalla per les dues 

// Address Pointer

#define XWIDE				0x51			// Coordenada X per escriure Wide
#define YWIDE				0x00			// Coordenada Y per escrirue Wide



// Variables 

#define lenght_max_line	40				// Valor maxim de llargada de fila de la pantalla. Com els pixels els podem tractar de 6 en 6 -> 6 x 40 = 240 (tamany maxim del hardware)

// Dibuixos 

extern unsigned char *pwelcome; 
	
#endif
/**************************** EOF ***********************************/
