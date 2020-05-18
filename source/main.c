/*	Author: victoromosor
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "pwm.h"
#include "timer.h"
#endif




enum BL_States {OFF, Play} state;
double tsolfa[] = {329.63, 293.66, 261.63, 293.63, 329.63, 0, 293.63, 293.63, 0,  329.63, 392.00};
unsigned char i = 0;
void TickFct_Blink() {

   switch ( state ) { //Transitions

      case Play:
	if ((PINA & 0x01) == 0x00){ 
		 state = Play;		
	}
	else {
              state = OFF;
	}
	break;	
       case OFF:
	      if ((PINA & 0x01) == 0x00){
		   state = Play;
	      }
	      else {
		   state = OFF;
	      }
	break; 
       default: 
	state = Play;
	break;

   }

   switch (state) { //State actions
      case Play:
	if (i >= 0){
		set_PWM(tsolfa[i]);
	}
	break;
      case OFF:
	 i = 0;
	// set_PWM(0);
	 break;
     
      default:
         break;
   }
}

int main(void) {
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0xFF; PORTB = 0x00;
   
   TimerSet(300);
   TimerOn();
   PWM_on(); 
   PORTB = 0x01; 
   state = Play; // Indicates initial call to tick-fct
   while (1) {         
      while (!TimerFlag){}  // Wait for BL's period
      TimerFlag = 0;        // Lower flag
      TickFct_Blink();
    }

    return 1;
}
