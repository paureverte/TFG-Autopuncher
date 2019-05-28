/********************************************************************
 * FileName:		GUI.h											*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per GUI.c											*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		30/10/18		Versió inicial.					*
 *																	*
 ********************************************************************/
#ifndef GUI_H
#define GUI_H

#include "main.h"

/***************** Definicio de subrutines usades *******************/
void GUI_Initialize(void);
void GUI_Callback(type_key key);
void GUI_ProcessKey(void);
unsigned char GUI_Get_MainMenuModifying(void);

void GUI_AutoTest_Set_Door(void);
void GUI_AutoTest_Reset_Door(void);
void GUI_AutoTest_Set_Emergency(void);
void GUI_AutoTest_Reset_Emergency(void);
void GUI_AutoTest_Set_Cylinder(void);
void GUI_AutoTest_Reset_Cylinder(void);
void GUI_AutoTest_Set_Holder(void);
void GUI_AutoTest_Reset_Holder(void);
void GUI_AutoTest_Set_Start(void);
void GUI_AutoTest_Reset_Start(void);
void GUI_AutoTest_Set_End(void);
void GUI_AutoTest_Reset_End(void);
void GUI_AutoTest_Set_Curtain(void);
void GUI_AutoTest_Reset_Curtain(void);
void GUI_AutoTest_Set_8(void);
void GUI_AutoTest_Reset_8(void);
void GUI_AutoTest_Set_9(void);
void GUI_AutoTest_Reset_9(void);
void GUI_AutoTest_FirstTime_Set(void);
void GUI_AutoTest_FirstTime_Set_Holder(void);
void GUI_AutoTest_FirstTime_Set_Emergency(void);
void GUI_AutoTest_FirstTime_Set_Cylinder(void);
void GUI_AutoTest_FirstTime_Set_Door(void);
void GUI_AutoTest_FirstTime_Set_Start(void);
void GUI_AutoTest_FirstTime_Set_End(void);
void GUI_AutoTest_FirstTime_Set_8(void);
void GUI_AutoTest_FirstTime_Set_9(void);
void GUI_AutoTest_FirstTime_Set_Curtain(void);
void GUI_Set_From_Autotest(void);
void GUI_Reset_From_Autotest(void);

typedef enum type_mainmenu_screen
{
	screen_mainmenu_normal = 0,
	screen_mainmenu_door_error = 1,
	screen_mainmenu_holder_error = 2,
	screen_mainmenu_emergency_error = 3,
	screen_mainmenu_curtain_error = 4,

} type_mainmenu_screen;

typedef enum type_wait_screen
{
	screen_wait_normal = 0,
	screen_wait_holder_error = 1,
	screen_wait_door_error = 2

} type_wait_screen;
#endif
