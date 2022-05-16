#include "Lib/STD_TYPES.h"
#include "Lib/BIT_MATH.h"
#include "TIMR_private.h"
#include "TIMR_config.h"
#include "TIMR_interface.h"






void TIMR0_VidInit(void) {

/*Select Mode CTC */

	CLEAR_BIT(TCCR0 , TCCR0_WGM00_PIN );
	SET_BIT(TCCR0   , TCCR0_WGM01_PIN );


/*Timr Interrupt En*/

	SET_BIT(TIMSK ,TIMSK_OCIE0_PIN  ) ;

/*OCR*/

	OCR0 = 250   ;  /*4000 COUNT to achive 1 SEC */

/*set Timr prescaller Prescaller BY 8*/   //Enable Prepherial

	CLEAR_BIT(TCCR0 ,TCCR0_CS00_PIN  ) ;
	SET_BIT(TCCR0,TCCR0_CS01_PIN)      ;
	CLEAR_BIT(TCCR0 , TCCR0_CS02_PIN)  ;

}

static void (*TIMR0_SetCallBackFunc)(void)  = NULL;


void TIMR0_SetCallBack(void (*Copy_pCallBackFunction)(void)){

if (Copy_pCallBackFunction !=NULL){

	TIMR0_SetCallBackFunc = Copy_pCallBackFunction ;
}

}




void __vector_10(void) __attribute__ ((signal)) ;

void __vector_10(void){

	if (TIMR0_SetCallBackFunc != NULL){

		TIMR0_SetCallBackFunc() ;
	}



}





void TIMR0_SetCompareMatchReg(u8 Copy_u8Value){


	OCR0= Copy_u8Value ;

}





void TIMR0_VidInitFPWM(void) {

/*Select Mode FPWM Mode  */

	SET_BIT(TCCR0 ,   TCCR0_WGM00_PIN );
	SET_BIT(TCCR0   , TCCR0_WGM01_PIN );


/*Not Interested in the TIMR Now Disable Timr Interrupt En*/

	//SET_BIT(TIMSK ,TIMSK_OCIE0_PIN  ) ;


	/*	Set on compare CLR On top*/


	SET_BIT(TCCR0,TCCR0_COM01_PIN)      ;
	CLEAR_BIT(TCCR0,TCCR0_COM00_PIN)      ;


//
	/*set Timr prescaller Prescaller BY 64*/   //Enable Prepherial

	SET_BIT(TCCR0 ,TCCR0_CS00_PIN  ) ;
	SET_BIT(TCCR0,TCCR0_CS01_PIN)      ;
	CLEAR_BIT(TCCR0 , TCCR0_CS02_PIN)  ;



}










/*servo*/

void TIMR1_VidInit(void){

	/*Setting Fast PWM non-Inverting mode*/

	SET_BIT(TCCR1A , TCCR1A_COM1A1_PIN) ;
	CLEAR_BIT(TCCR1A , TCCR1A_COM1A0_PIN) ;


	/*Setting waveform for AS fAST  pwm */
	CLEAR_BIT(TCCR1A , TCCR1A_WGM10_PIN) ;
	SET_BIT  (TCCR1A , TCCR1A_WGM11_PIN) ;
	SET_BIT  (TCCR1B , TCCR1B_WGM12_PIN) ;
	SET_BIT  (TCCR1B , TCCR1B_WGM13_PIN) ;

	/*set prescaller*/

	TCCR1B&=PRESCALLER_MASK ;
	TCCR1B|=DIVIDE_BY_8 ;

}

void TIMR1_VidSetICR(u16 Copy_u16Top){

	ICR1 = Copy_u16Top ;

}

void TIMR1_VidSetChannelACompMatch(u16 Copy_u16CompMatch){

	OCR1A = Copy_u16CompMatch ;

}









/*ICU*/

/*Generate specific Pwm Using TIMR0 With  256 us*/
void TIMR0_VidInitFPWMICU(void) {

/*Select Mode FPWM Mode  */

	SET_BIT(TCCR0 ,   TCCR0_WGM00_PIN );
	SET_BIT(TCCR0   , TCCR0_WGM01_PIN );
/*Set Compare Match for Duty Cycle */
	OCR0 = 64    ;

	/*Non Inverting Mode*/


	SET_BIT(TCCR0,TCCR0_COM01_PIN)      ;
	CLEAR_BIT(TCCR0,TCCR0_COM00_PIN)      ;


	/*set Timr prescaller Prescaller BY 8*/   //Enable Prepherial

	CLEAR_BIT(TCCR0 ,TCCR0_CS00_PIN  ) ;
	SET_BIT(TCCR0,TCCR0_CS01_PIN)      ;
	CLEAR_BIT(TCCR0 , TCCR0_CS02_PIN)  ;



}


/*TIMR1 Setting For ICU As Timer */

void TIMR1_VidInitICU(void){


	/*Intialaize at Normal Mode prescaller divide by 8 */

	CLEAR_BIT(TCCR1B , TCCR1B_CS10_PIN) ;
	SET_BIT  (TCCR1B , TCCR1B_CS11_PIN) ;
	CLEAR_BIT(TCCR1B , TCCR1B_CS12_PIN) ;

}


void TIMR1_SetTimerValue (u8 Copy_u8Val){

	TCNT1L = Copy_u8Val  ;

}


u16 TIMR1_VidGetReading(){

	return TCNT1L ;

}


/****************************ICU  Hardware ***************************************/
/****************************ICU  Hardware ***************************************/
/****************************ICU  Hardware ***************************************/
/****************************ICU  Hardware ***************************************/
/****************************ICU  Hardware ***************************************/
/****************************ICU  Hardware ***************************************/
/****************************ICU  Hardware ***************************************/

void ICU_VidInit(void )

{
/*set trigger source to rising edge initialy*/

	SET_BIT(TCCR1B , TCCR1B_ICES1_PIN)  ;

/*Enable Interrupt */

    SET_BIT(TIMSK , TIMSK_ICIE1_PIN) ;


}


/*Function to set the edge */

void ICU_VidSetTriggerEdge(u8 Copy_Edge) {

if (Copy_Edge==ICU_RISING_EDGE){

	SET_BIT(TCCR1B , TCCR1B_ICES1_PIN) ;

}

else if (Copy_Edge ==ICU_FALLINF_EDGE ){
	CLEAR_BIT(TCCR1B , TCCR1B_ICES1_PIN) ;

}


}

/*Function to Enable ICU Interrupt */

void ICU_VidEnableInterrupt(){

    SET_BIT(TIMSK , TIMSK_ICIE1_PIN) ;
}



void ICU_VidDisableInterrupt(){

    CLEAR_BIT(TIMSK , TIMSK_ICIE1_PIN) ;
}


u16 ICU_U16ReadInputCaptur (void )
{
return ICR1 ;
}



static void (*ICU_VidCallBack)(void) = NULL ;
void ICU_u8SetCallBack (void (*Copy_pvCallBackFunc)(void))

{

if (Copy_pvCallBackFunc !=NULL ){

	ICU_VidCallBack =  Copy_pvCallBackFunc ;
}

}

/*ICU Vector */
void __vector_6(void) __attribute__ ((signal)) ;

void __vector_6(void){

	if (ICU_VidCallBack != NULL){

		ICU_VidCallBack() ;
	}

}

