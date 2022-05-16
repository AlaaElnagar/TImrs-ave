#ifndef TIMR_INTERFACE_H_
#define TIMR_INTERFACE_H_


#define ICU_RISING_EDGE   10
#define ICU_FALLINF_EDGE   20

void TIMR0_VidInit(void) ;

void TIMR0_VidInitFPWMICU(void) ;
/*TIMR1 Setting For ICU As Timer */

void TIMR1_VidInitICU(void);

void TIMR0_SetCallBack(void (*Copy_pCallBackFunction)(void));



void TIMR1_VidInit(void) ;


void TIMR1_VidSetICR(u16 Copy_u16Top) ;

void TIMR1_VidSetChannelACompMatch(u16 Copy_u16CompMatch);











/*********************************888**********************/


void ICU_VidInit(void );

/*Function to set the edge */

void ICU_VidSetTriggerEdge(u8 Copy_Edge) ;
/*Function to Enable ICU Interrupt */

void ICU_VidEnableInterrupt();

void ICU_VidDisableInterrupt();

u16 ICU_U16ReadInputCaptur (void );























#endif


