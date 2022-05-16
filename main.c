/*
 * main.c
 *
 *  Created on: Aug 24, 2021
 *      Author: AlaaElnagar
 */
#include "Lib/STD_TYPES.h"
#include "Lib/BIT_MATH.h"
#include "DIO_Interface.h"
#include "GIE_interface.h"
#include "TIMR_interface.h"
#include "util/delay.h"
#include "CLCD_interface.h"

#define OCR               20
#define OCR_PWM           50  //SWI
#define FPWM              10
/*26/8*/
#define TIMR1_FPWM        30
#define ICU_SW             40
#define ICU_HW             100




#define Mode   ICU_HW



#if Mode ==  OCR_PWM



void ISR_Blink(void){

static u16 Loc_u16Counter = 0 ;
Loc_u16Counter++ ;

if (Loc_u16Counter >0 && Loc_u16Counter<=2000 ){

	DIO_VidSetPinValue(Port_A ,high , Pin_0) ;

}

else if (Loc_u16Counter >2000 && Loc_u16Counter<=4000 ){

	DIO_VidSetPinValue(Port_A ,low , Pin_0) ;

}

else {

	Loc_u16Counter =  0 ;

}




}

/**************************************************/
void ISR_SWI(void){

static u16 Loc_u16Counter = 0 ;
Loc_u16Counter ++ ;    //4000count    ---->  sec       // 0 -----300


if (Loc_u16Counter >0 &&Loc_u16Counter<75){

	DIO_VidSetPinValue(Port_A ,high , Pin_0) ;


}

else if (Loc_u16Counter >=75 &&Loc_u16Counter <300 ){
	DIO_VidSetPinValue(Port_A ,low , Pin_0) ;
}
else {
	Loc_u16Counter = 0 ;
}
}






void main (){

	TIMR0_SetCallBack(ISR_SWI ) ;
	DIO_VidSetPinDirection(Port_A , Pin_0 , output) ;
	GIE_VidEnable() ;
	TIMR0_VidInit() ;

	while (1){


	}


}










#elif Mode ==  OCR

void ISR_Blink(void){

static u16 Loc_u16Counter = 0 ;
static u8 state         = 0 ;

if (Loc_u16Counter == 1000){

	state = !state ;
	DIO_VidSetPinValue(Port_A ,state , Pin_0) ;
	Loc_u16Counter = 0 ;

}

else {

	Loc_u16Counter ++ ;

}




}

/**************************************************/
void ISR_SWI(void){

static u16 Loc_u16Counter = 0 ;
Loc_u16Counter ++ ;    //4000


if (Loc_u16Counter >0 &&Loc_u16Counter<150){

	DIO_VidSetPinValue(Port_A ,high , Pin_0) ;


}

else if (Loc_u16Counter >=150 &&Loc_u16Counter <300 ){
	DIO_VidSetPinValue(Port_A ,low , Pin_0) ;
}
else {
	Loc_u16Counter = 0 ;
}
}






void main (){

	TIMR0_SetCallBack(ISR_SWI ) ;
	DIO_VidSetPinDirection(Port_A , Pin_0 , output) ;
	GIE_VidEnable() ;
	TIMR0_VidInit() ;

	while (1){


	}


}

#elif Mode ==FPWM





void main (){


	DIO_VidSetPinDirection(Port_B , 3 , output) ;
	TIMR0_VidInitFPWM() ;
	TIMR0_SetCompareMatchReg(100) ;   // prepheral

	while (1){

		//ana hena

/*
		for (u8 i = 0  ; i < 255 ; i ++){

				TIMR0_SetCompareMatchReg(i) ;

				_delay_ms (500) ;

		}
*/



	}

}



#elif Mode ==  TIMR1_FPWM

void main (){

/*set oc1A as outpuT */
	DIO_VidSetPinDirection(Port_D , 5 , output) ;
	TIMR1_VidInit() ;
	TIMR1_VidSetICR(20000) ;

	u16 i = 1000 ;
	while (1){

		for (i = 750  ; i < 2500; i ++){

				TIMR1_VidSetChannelACompMatch(i) ;

				_delay_ms (3) ;

		}

	}


}

#elif Mode == ICU_SW

u16 Perios_Tics = 0 ;
u16 on_ticks  = 0 ;
void ICU_SW (void){

	static u8 Local_u8Counter = 0 ;
	Local_u8Counter++ ;

	/*First Rising edge*/
	if (Local_u8Counter ==1 ){

	//reset the timmer

	}

	else if (Local_u8Counter ==2 )
	{
			//read Timr Value
		Perios_Tics =
			/*Change EXIT sense control to falling */


	}

	else if (Local_u8Counter == 3) {

		//read Timr Value
	Perios_Tics =

	on_ticks =  on_ticks - Perios_Tics ;

	/*Disable ExiInt0*/

	}


}

int main (){




}



#elif Mode  == ICU_HW


///*
// * 1-Intialize Timr 1 ----> Normal Mode
// * Initialize  ICU Starting Edge at Timer 1 initi
// *
// *
//
//
// * 2 - ICU_SETEDGE (Edge)
// * *
// *3- ICU Enable Disable
// *4 - ICU SET CALL BACK
// *4
// *4 ISR
// * /

u16 Period_Ticks = 0 ;

u16 onTicks = 0 ;


void ICU_VidHW(){

static u16 Reading1 , Reading2 , Reading3 ;
static u8 Local_U8Counter = 0 ;
Local_U8Counter++ ;


if (Local_U8Counter == 1){
/*get intial timer value at first rising edge */
	Reading1 = ICU_U16ReadInputCaptur() ;

}

else if (Local_U8Counter == 2){
	/*End of period at second rising edge */

	Reading2 = ICU_U16ReadInputCaptur() ;
	/*get period ticks */
	Period_Ticks = Reading2 - Reading1 ;
	/*set  as rising  to get on time */
    ICU_VidSetTriggerEdge(ICU_FALLINF_EDGE) ;
}

else if (Local_U8Counter == 3){

	Reading3 = ICU_U16ReadInputCaptur() ;
	onTicks = Reading3 - Reading2 ;
	ICU_VidDisableInterrupt() ;
}




}



void main (){

/*set ICu Pin as Input */
	DIO_VidSetPinDirection(Port_D , 6, input) ;

/*set TIMR0 PWM PIN  Pin as Output */
	DIO_VidSetPinDirection(Port_B, 3, output) ;
/*Generate fast pwm from timer0 for icu to read*/
	TIMR0_VidInitFPWMICU() ;
/*Generate 1 timer as normal mode */
	TIMR1_VidInitICU() ;
	ICU_VidInit() ;
	GIE_VidEnable() ;

	/*Lcd */
	DIO_VidSetPortDirection(Port_A , 0xff );
	DIO_VidSetPortDirection(Port_C , 0xff) ;

	CLCD_VidInit() ;

	ICU_u8SetCallBack(ICU_VidHW) ;

	CLCD_VidGotoXY(0,0) ;
	CLCD_VidSendString("PERIODICITY: ") ;
	CLCD_VidSendInt(Period_Ticks) ;
	CLCD_VidGotoXY(1,0) ;
	CLCD_VidSendString("On Ticks: ") ;
	CLCD_VidSendInt(onTicks) ;

	while (1){

		while (( Period_Ticks == 0 ) || ( onTicks == 0)) ;

		CLCD_VidGotoXY(0,0) ;
		CLCD_VidSendString("PERIODICITY: ") ;
		CLCD_VidSendInt(Period_Ticks) ;
		CLCD_VidGotoXY(1,0) ;
		CLCD_VidSendString("On Ticks: ") ;
		CLCD_VidSendInt(onTicks) ;
	}


}








#endif







































//void ISR_SWI(void){
//
//static u16 Loc_u16Counter = 0 ;
//Loc_u16Counter ++ ;    //4000
//
//
//if (Loc_u16Counter >0 &&Loc_u16Counter<150){
//
//	DIO_VidSetPinValue(Port_A ,high , Pin_0) ;
//
//
//}
//
//else if (Loc_u16Counter >=100 &&Loc_u16Counter <=1 ){
//	DIO_VidSetPinValue(Port_A ,low , Pin_0) ;
//}
//else {
//	Loc_u16Counter = 0 ;
//}
//}


//---------------------------------------------------
//ICU

//void ICU_VidHW(){
//
//static u16 Reading1 , Reading2 , Reading3 ;
//static u8 Local_U8Counter = 0 ;
//Local_U8Counter++ ;
//
//
//if (Local_U8Counter == 1){
//
//	Reading1 = ICU_U16ReadInputCaptur() ;
//
//}
//
//else if (Local_U8Counter == 2){
//
//	Reading2 = ICU_U16ReadInputCaptur() ;
//	Period_Ticks = Reading2 - Reading1 ;
//
//}
//
//else if (Local_U8Counter == 3){
//
//	Reading3 = ICU_U16ReadInputCaptur() ;
//	onTicks = Reading3 - Reading2 ;
//	ICU_VidDisableInterrupt() ;
//}
//
//
//
//
//}
//
//
//
//
//void main (){
//
///*set ICu Pin as Input */
//	DIO_VidSetPinDirection(Port_D , 6, input) ;
//	DIO_VidSetPinDirection(Port_B, 3, output) ;
//
//	GIE_VidEnable() ;
//	TIMR0_VidInitFPWMICU() ;
//	TIMR1_VidInit() ;
//	ICU_VidInit() ;
//
//
//	/*Lcd */
//	DIO_VidSetPortDirection(Port_A , 0xff );
//	DIO_VidSetPortDirection(Port_C , 0xff) ;
//
//	CLCD_VidInit() ;
//	TIMR1_VidSetICR(20000) ;
//
//
//	ICU_u8SetCallBack(ICU_VidHW) ;
//
//	CLCD_VidGotoXY(0,0) ;
//	CLCD_VidSendString("PERIODICITY: ") ;
//	CLCD_VidSendInt(Period_Ticks) ;
//	CLCD_VidGotoXY(1,0) ;
//	CLCD_VidSendString("On Ticks: ") ;
//	CLCD_VidSendInt(onTicks) ;
//
//	while (1){
//
//		while (( Period_Ticks == 0 ) && ( onTicks == 0)) ;
//
//		CLCD_VidGotoXY(0,0) ;
//		CLCD_VidSendString("PERIODICITY: ") ;
//		CLCD_VidSendInt(Period_Ticks) ;
//		CLCD_VidGotoXY(1,0) ;
//		CLCD_VidSendString("On Ticks: ") ;
//		CLCD_VidSendInt(onTicks) ;
//	}
//
//
//}

