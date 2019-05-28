/********************************************************************
 * FileName:		CAP1208.h 										*
 * Dependencies:													*
 * Processor:		PIC32MX460F512L									*
 * Company:			Medyp S.L.										*
 *																	*
 ********************************************************************
 * File Description:												*
 *																	*
 * 	- Llibrería per CAP1208.c										*
 *																	*
 * Change History:			Versió 0.0								*
 *																	*
 * Name				Date            Changes							*
 * -----			-----			--------						*
 * P.Reverté		11/02/19		Versio inicial.					*
 *																	*
 ********************************************************************/

#ifndef CAP1208_H
#define CAP1208_H
		
#define CAP1208_Address 		0x50
#define MANID 					0xFE

#define MAIN_CONTROL_REGISTER	0x00
#define INPUT_ENABLE			0x21
#define MULT_TOUCH				0x2A
#define SENSIV_CONF				0x1F /* default 0x2F */
#define DELTA_SENSE_MASK		0x70
#define DELTA_SENSE_LSHIFT		4
#define BASE_SHIFT_MASK			0x0F
#define BASE_SHIFT_LSHIFT		0
#define CONFIGURATION 			0x20
#define INPUT_CONFIGURATION		0x22
#define INTERRUPT_ENABLE 		0x27
#define REPEAT_RATE_ENABLE 		0x28
#define CONFIGURATION_2 		0x44

typedef enum
{
	CAP1208_INITIALIZE,
	CAP1208_WAITING_INITIALIZE,
	CAP1208_ENABLE,
	CAP1208_WAITING_ENABLE,
	CAP1208_MULTITOUCH,
	CAP1208_WAITING_MULTITOUCH,
	CAP1208_SENSIBILITY,
	CAP1208_WAITING_SENSIBILITY,
	CAP1208_READ,
	CAP1208_WAITING_I2C,
	CAP1208_RESTORE_INT,
	CAP1208_WAITING_RESTORE_INT,
	CAP1208_READY

}CAP1208_state_t;

typedef struct
{
	unsigned char txbuffer[8];
	unsigned char rxbuffer[8];
	CAP1208_state_t state;
	unsigned char manufacturer_id;
	unsigned char input_status;
	unsigned char i2c_ready;
	unsigned char expected_i2c_ready;
} CAP1208_t;

typedef enum
{
	NEG_DELTA_CNT_8,
	NEG_DELTA_CNT_16, /* default */
	NEG_DELTA_CNT_32,
	NEG_DELTA_CNT_None /* disabled */
} NEG_DELTA_CNT_t;

typedef enum
{
	CAL_CFG_update_time_16,
	CAL_CFG_update_time_32,
	CAL_CFG_update_time_64, /* default */
	CAL_CFG_update_time_128,
	CAL_CFG_update_time_256,
	CAL_CFG_update_time_1024,
	CAL_CFG_update_time_2048,
	CAL_CFG_update_time_4096,
} CAL_CFG_t;

typedef enum
{
	DELTA_SENSE_128x = 0, /* most sensitive */
	DELTA_SENSE_64x,
	DELTA_SENSE_32x, /* default */
	DELTA_SENSE_16x,
	DELTA_SENSE_8x,
	DELTA_SENSE_4x,
	DELTA_SENSE_2x,
	DELTA_SENSE_1x, /* least sensitive */
} DELTA_SENSE_t;

typedef enum
{
	BASE_SHIFT_1x = 0,
	BASE_SHIFT_2x,
	BASE_SHIFT_4x,
	BASE_SHIFT_8x,
	BASE_SHIFT_16x,
	BASE_SHIFT_32x,
	BASE_SHIFT_64x,
	BASE_SHIFT_128x,
	BASE_SHIFT_256x, /* default */
} BASE_SHIFT_t;

typedef enum
{
	MAX_DUR_560ms = 0,
	MAX_DUR_840ms,
	MAX_DUR_1120ms,
	MAX_DUR_1400ms,
	MAX_DUR_1680ms,
	MAX_DUR_2240ms,
	MAX_DUR_2800ms,
	MAX_DUR_3360ms,
	MAX_DUR_3920ms,
	MAX_DUR_4480ms,
	MAX_DUR_5600ms, /* default */
	MAX_DUR_6720ms,
	MAX_DUR_7840ms,
	MAX_DUR_8906ms,
	MAX_DUR_10080ms,
	MAX_DUR_11200ms,
} MAX_DUR_t;

typedef enum
{
	RPT_RATE_35ms = 0,
	RPT_RATE_70ms,
	RPT_RATE_105ms,
	RPT_RATE_140ms,
	RPT_RATE_175ms, /* default */
	RPT_RATE_210ms,
	RPT_RATE_245ms,
	RPT_RATE_280ms,
	RPT_RATE_315ms,
	RPT_RATE_350ms,
	RPT_RATE_385ms,
	RPT_RATE_420ms,
	RPT_RATE_455ms,
	RPT_RATE_490ms,
	RPT_RATE_525ms,
	RPT_RATE_560ms,
} RPT_RATE_t;


void CAP1208_SetCurrentCAP(CAP1208_t * pointer);
void CAP1208_ProgramRead(CAP1208_t * pointer);
CAP1208_state_t CAP1208_Tasks(CAP1208_t * cap);

#endif
