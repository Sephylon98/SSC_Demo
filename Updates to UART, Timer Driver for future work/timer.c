 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR Timer driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use Timer Registers */
#include <avr/interrupt.h> /* For Timer ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

#if(BOTH_TIMERS == FALSE)
#if (TIMER == 0)
ISR(TIMER0_COMP_vect){
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function */
		g_callBackPtr0();
	}
}

ISR(TIMER0_OVF_vect){
	if(g_callBackPtr0 != NULL_PTR)
		{
			/* Call the Call Back function */
		g_callBackPtr0();
		}
}

#else
ISR(TIMER1_COMPA_vect)

{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function */
		g_callBackPtr1();
	}
}

ISR(TIMER1_OVF_vect){
	if(g_callBackPtr1 != NULL_PTR)
		{
			/* Call the Call Back function */
		g_callBackPtr1();
		}
}

ISR(TIMER1_COMPB_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function */
		g_callBackPtr1();
	}
}

#endif
#else
ISR(TIMER0_COMP_vect){
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function */
		g_callBackPtr0();
	}
}

ISR(TIMER0_OVF_vect){
	if(g_callBackPtr0 != NULL_PTR)
		{
			/* Call the Call Back function */
		g_callBackPtr0();
		}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function */
		g_callBackPtr1();
	}
}

ISR(TIMER1_OVF_vect){
	if(g_callBackPtr1 != NULL_PTR)
		{
		/* Call the Call Back function */
		g_callBackPtr1();
		}
}

ISR(TIMER1_COMPB_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function */
		g_callBackPtr1();
	}
}
#endif
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/* -----------------------------------------------------------------------------
 * [Function Name]: Timer_init
 * [Description]: Initialize the Timer driver as required.
 * 				  Setup Timer mode of operation.
 * [Args]: this function takes a pointer to structure as input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
#if(BOTH_TIMERS == FALSE)
void Timer_init(Timer_ConfigType *Config_Timer){
#if (TIMER == TIMER0)
	TCNT0 = Config_Timer->Initial_Value;
	OCR0 = Config_Timer->Compare_Value;

	/* Setting CS12, CS11, CS10 */
	TCCR0 = (TCCR0 & 0xF8)|(Config_Timer->prescale);

	/* Setting COM01, COM00 */
	TCCR0 = (TCCR0 & 0xCF)|((Config_Timer->Force_Output_Compare)<<4);

	/* Setting WGM01 , WGM00 */
	TCCR0 = (TCCR0 & 0xB7)|((Config_Timer->mode&0x01)<<3)|((Config_Timer->mode&0x02)<<5);

	/* Clearing FOC0 */
	TCCR0 &= ~(1<<FOC0);

	/* Turn on Interrupts */
	TIMSK |= (1<<OCF0);
	TIMSK |= (1<<TOV0);

#elif(TIMER == TIMER1)
	TCNT1 = Config_Timer->Initial_Value;
	OCR1A = Config_Timer->Compare_ValueA;
	OCR1B = Config_Timer->Compare_ValueB;

	/* Setting WGM11, WGM10 */
	TCCR1A = (TCCR1A & 0xFC)|((Config_Timer->mode) & 0x03);

	/* Setting COM1B1, COM1B0 */
	TCCR1A = (TCCR1A & 0xCF)|((Config_Timer->Force_Output_CompareB)<<4);

	/* Setting COM1A1, COM1A0 */
	TCCR1A = (TCCR1A & 0x3F)|((Config_Timer->Force_Output_CompareA)<<6);

	/* Setting CS12, CS11, CS10 */
	TCCR1B = (TCCR1B & 0xF8)|(Config_Timer->prescale);

	/* Setting WGM13, WGM12 */
	TCCR1B = (TCCR1B & 0xE7)|(((Config_Timer->mode) & 0x0C)<<1);

	/* Clearing FOC1A , FOC1B */
	TCCR1A &= ~(1<<FOC1A);
	TCCR1A &= ~(1<<FOC1B);
#endif
}

#else

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_init
 * [Description]: Initialize the Timer driver as required.
 * 				  Setup Timer mode of operation.
 * [Args]: this function takes a pointer to structure as input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_init(Timer0_ConfigType *Config_Timer){
	TCNT0 = Config_Timer->Initial_Value;
	OCR0 = Config_Timer->Compare_Value;

	/* Setting CS12, CS11, CS10 */
	TCCR0 = (TCCR0 & 0xF8)|(Config_Timer->prescale);

	/* Setting COM01, COM00 */
	TCCR0 = (TCCR0 & 0xCF)|((Config_Timer->Force_Output_Compare)<<4);

	/* Setting WGM01 , WGM00 */
	TCCR0 = (TCCR0 & 0xB7)|((Config_Timer->mode&0x01)<<3)|((Config_Timer->mode&0x02)<<5);

	TCCR0 &= ~(1<<FOC0);
}

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_init
 * [Description]: Initialize the Timer driver as required.
 * 				  Setup Timer mode of operation.
 * [Args]: this function takes a pointer to structure as input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_init(Timer1_ConfigType *Config_Timer){
	TCNT1 = Config_Timer->Initial_Value;
	OCR1A = Config_Timer->Compare_ValueA;
	OCR1B = Config_Timer->Compare_ValueB;

	/* Setting WGM11, WGM10 */
	TCCR1A = (TCCR1A & 0xFC)|((Config_Timer->mode) & 0x03);

	/* Setting COM1B1, COM1B0 */
	TCCR1A = (TCCR1A & 0xCF)|((Config_Timer->Force_Output_CompareB)<<4);

	/* Setting COM1A1, COM1A0 */
	TCCR1A = (TCCR1A & 0x3F)|((Config_Timer->Force_Output_CompareA)<<6);

	/* Setting CS12, CS11, CS10 */
	TCCR1B = (TCCR1B & 0xF8)|(Config_Timer->prescale);

	/* Setting WGM13, WGM12 */
	TCCR1B = (TCCR1B & 0xE7)|(((Config_Timer->mode) & 0x0C)<<1);

	TCCR1A &= ~(1<<FOC1A);
	TCCR1A &= ~(1<<FOC1B);
}

#endif
/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_setCallBack
 * [Description]: Initialize the Timer Call back function.
 * [Args]: this function takes a pointer to function as input
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr0 = a_ptr;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_setCallBack
 * [Description]: Initialize the Timer Call back function.
 * [Args]: this function takes a pointer to function as input
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr1 = a_ptr;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer_deinit
 * [Description]: disables Timer.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
#if(BOTH_TIMERS == FALSE)
void Timer_deinit(void){
#if(TIMER == 0)
	TCCR0 = 0;
	OCR0 = 0;
	TCNT0 = 0;
#else
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCNT1 = 0;
#endif
}

#else
/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_deinit
 * [Description]: disables Timer.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_deinit(void){
	TCCR0 = 0;
	OCR0 = 0;
	TCNT0 = 0;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_deinit
 * [Description]: disables Timer.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_deinit(void){
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCNT1 = 0;
}
#endif
/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_Enable_OVF_Interrupt
 * [Description]: enables Timer0 overflow interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_Enable_OVF_Interrupt(void){
	TIMSK |= (1<<TOIE0);
}

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer0_Enable_COMP_Interrupt
 * [Description]:enables Timer0 compare match interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer0_Enable_COMP_Interrupt(void){
	TIMSK |= (1<<OCIE0);
}

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_Enable_OVF_Interrupt
 * [Description]:enables Timer1 overflow interrupt.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_Enable_OVF_Interrupt(void){
	TIMSK |= (1<<TOV1);
}

/* -----------------------------------------------------------------------------
 * [Function Name]: Timer1_Enable_COMP_Interrupt
 * [Description]:enables Timer1 compare match A and B interrupts.
 * [Args]: this function takes void input.
 * [Returns]: this function returns void.
 * ----------------------------------------------------------------------------*/
void Timer1_Enable_COMP_Interrupt(void){
	TIMSK |= (1<<OCF1A)|(1<<OCF1B);
}

