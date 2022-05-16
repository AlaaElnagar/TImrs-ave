#ifndef TIMR_PRIVATE_H_
#define TIMR_PRIVATE_H_


#define TCCR0         *((volatile u8 *) 0x53)   /*Timer counter controlregister */

#define TCCR0_WGM00_PIN			6               /*Wave generation mode bit 0*/
#define TCCR0_WGM01_PIN			3				/*Wave generation mode bit 1*/

#define TCCR0_COM00_PIN			4				/*Compare Match output bit 0*/
#define TCCR0_COM01_PIN			5				/*Compare Match output bit 1*/
 
#define TCCR0_CS00_PIN 			0               /*Timer Clock Select bit 0*/
#define TCCR0_CS01_PIN 			1               /*Timer Clock Select bit 1*/
#define TCCR0_CS02_PIN 			2               /*Timer Clock Select bit 2*/


#define OCR0 		  *((volatile u8 *) 0x5C)   /*Output compare register */


#define TIMSK         *((volatile u8 *) 0x59)   /*Timer Counter Interrupt Mask*/
#define TIMSK_OCIE0_PIN         1         		/*Timer Output Comapre Match Interrupt Enable */       


#define  TIFR		  *((volatile u8 *) 0x58)   /*Timer Interrupt Flag Register*/
#define  TIFR_OCF0              1                /*Output Compare Flag */

/*Timr 1 */


#define TCCR1A	  *((volatile u8*)0x4F)

#define TCCR1B    *((volatile u8*)0x4E)


#define TCCR1B_CS12_PIN		 	2
#define TCCR1B_CS11_PIN		 	1
#define TCCR1B_CS10_PIN		 	0

#define TCCR1B_ICES1_PIN		6			/*Input captur Edge select */

#define TIMSK         *((volatile u8 *) 0x59)   /*Timer Counter Interrupt Mask*/

#define TIMSK_ICIE1_PIN			5		/*Timr1 Input captur Interrupt enable */
#define TIMSK_ICIE0_PIN         1        /*Timer1 Output Comapre Match Interrupt Enable */



#define TCNT1L    *((volatile u16*)0x4C)   /*Timer Counter register */

#define ICR1      *((volatile u16*)0x46)

#define OCR1A      *((volatile u16*)0x4A)



#define TCCR1A_WGM10_PIN		0
#define TCCR1A_WGM11_PIN		1

#define TCCR1A_COM1A1_PIN		7
#define TCCR1A_COM1A0_PIN		6

#define TCCR1B_WGM12_PIN     		    3
#define TCCR1B_WGM13_PIN				4


#define PRESCALLER_MASK       0b11111000
#define DIVIDE_BY_8             2



#endif


