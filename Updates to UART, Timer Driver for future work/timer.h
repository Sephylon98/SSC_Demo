 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR Timer driver. Supports Timer 0, Timer1 only.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/
#define TIMER0 0
#define TIMER1 1

#define BOTH_TIMERS TRUE       /* You can turn on Timer 1 or Timer 0, or turn on both timers. */
#define TIMER TIMER0          /* Supports Timer0 , Timer1 Only. */

/*******************************************************************************
 *                                Enums                                        *
 *******************************************************************************/

typedef enum{
	clock_off, prescaler_1, prescaler_8, prescaler_64, prescaler_256, prescaler_1024,
	clock_falling_edge, clock_rising_edge
}Timer_Prescaler;

typedef enum{
	Pin_Disconnected, Toggle_Pin, Clear_Pin, Set_Pin
}Compare_OutputMode;

#if(BOTH_TIMERS == FALSE)
	#if(TIMER == TIMER0)
		typedef enum{
			Normal_mode, PWM_PC, CTC_OCR0_mode, F_PWM
		}Timer0_Waveform_GenerationMode;

	#elif(TIMER == TIMER1)
		typedef enum{
			Normal_mode, PWM_PC_8, PWM_PC_9, PWM_PC_10, CTC_OCR1A_mode, F_PWM_8, F_PWM_9, F_PWM_10, PWM_PFC_ICR1,
			PWM_PFC_OCR1A, PWM_PC_ICR1, PWM_PC_OCR1A, CTC_ICR1_mode, F_PWM_ICR1 = 14, F_PWM_OCR1A
		}Timer1_Waveform_GenerationMode;
	#endif

#elif(BOTH_TIMERS == TRUE)
		typedef enum{
			Timer0_Normal_mode, PWM_PC, CTC_OCR0_mode, F_PWM
		}Timer0_Waveform_GenerationMode;

		typedef enum{
			Timer1_Normal_mode, PWM_PC_8, PWM_PC_9, PWM_PC_10, CTC_OCR1A_mode, F_PWM_8, F_PWM_9, F_PWM_10, PWM_PFC_ICR1,
			PWM_PFC_OCR1A, PWM_PC_ICR1, PWM_PC_OCR1A, CTC_ICR1_mode, F_PWM_ICR1 = 14, F_PWM_OCR1A
		}Timer1_Waveform_GenerationMode;
#endif

/*******************************************************************************
 *                               Structures                                    *
 *******************************************************************************/
#if(BOTH_TIMERS == FALSE)
typedef struct{
#if(TIMER == TIMER0)
	Timer_Prescaler prescale;
	Timer0_Waveform_GenerationMode mode; //WGM01 , WGM00
	Compare_OutputMode Force_Output_Compare; // COM01, COM00
	uint8 Initial_Value; //TNCT0 Value
	uint8 Compare_Value; //OCR0
#else
	Timer_Prescaler prescale;
	Timer1_Waveform_GenerationMode mode;
	Compare_OutputMode Force_Output_CompareA;
	Compare_OutputMode Force_Output_CompareB;
	uint16 Initial_Value; //TCNT1 Value
	uint16 Compare_ValueA; //OCR1A
	uint16 Compare_ValueB; //OCR1B
#endif
}Timer_ConfigType;

#else
typedef struct Timer0_ConfigType{
	Timer_Prescaler prescale;
	Timer0_Waveform_GenerationMode mode;
	Compare_OutputMode Force_Output_Compare;
	uint8 Initial_Value; //TNCT0 Value
	uint8 Compare_Value; //OCR0
}Timer0_ConfigType;

typedef struct Timer1_ConfigType{
	Timer_Prescaler prescale;
	Timer1_Waveform_GenerationMode mode;
	Compare_OutputMode Force_Output_CompareA;
	Compare_OutputMode Force_Output_CompareB;
	uint16 Initial_Value; //TCNT1 Value
	uint16 Compare_ValueA; //OCR1A
	uint16 Compare_ValueB; //OCR1B
}Timer1_ConfigType;
#endif

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

#if(BOTH_TIMERS == FALSE)
/* -----------------------------------------------------------------------------
 * [Function Name]: Timer_init
 * [Description]: Initialize the Timer driver as required.
 * 				  Setup Timer mode of operation.
 * [Args]: this function takes a pointer to structure as input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer_init(Timer_ConfigType *Config_Timer);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer_setCallBack
 * [Description]: Initialize the Timer Call back function.
 * [Args]: this function takes a pointer to function as input
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer_setCallBack(void(*a_ptr)(void));

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer_deinit
 * [Description]: disables Timer.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer_deinit(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_Enable_OVF_Interrupt
 * [Description]: enables Timer0 overflow interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_Enable_OVF_Interrupt(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_Enable_COMP_Interrupt
 * [Description]:enables Timer0 compare match interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_Enable_COMP_Interrupt(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_Enable_OVF_Interrupt
 * [Description]:enables Timer1 overflow interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_Enable_OVF_Interrupt(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_Enable_COMP_Interrupt
 * [Description]:enables Timer1 compare match A and B interrupts.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_Enable_COMP_Interrupt(void);
#else
/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_init
 * [Description]: Initialize the Timer driver as required.
 * 				  Setup Timer mode of operation.
 * [Args]: this function takes a pointer to structure as input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_init(Timer0_ConfigType *Config_Timer);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_init
 * [Description]: Initialize the Timer driver as required.
 * 				  Setup Timer mode of operation.
 * [Args]: this function takes a pointer to structure as input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_init(Timer1_ConfigType *Config_Timer);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_setCallBack
 * [Description]: Initialize the Timer Call back function.
 * [Args]: this function takes a pointer to function as input
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_setCallBack(void(*a_ptr)(void));

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_setCallBack
 * [Description]: Initialize the Timer Call back function.
 * [Args]: this function takes a pointer to function as input
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_setCallBack(void(*a_ptr)(void));

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_deinit
 * [Description]: disables Timer.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_deinit(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_deinit
 * [Description]: disables Timer.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_deinit(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_Enable_OVF_Interrupt
 * [Description]: enables Timer0 overflow interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_Enable_OVF_Interrupt(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_Enable_COMP_Interrupt
 * [Description]:enables Timer0 compare match interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_Enable_COMP_Interrupt(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_Enable_OVF_Interrupt
 * [Description]:enables Timer1 overflow interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_Enable_OVF_Interrupt(void);

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_Enable_COMP_Interrupt
 * [Description]:enables Timer1 compare match A and B interrupts.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_Enable_COMP_Interrupt(void);
#endif
#endif /* TIMER_H_ */
