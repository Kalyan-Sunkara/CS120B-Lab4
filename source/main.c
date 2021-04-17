/*	Author: ksunk001
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
#endif
enum LED_States {LED_SMStart, LED_B0on, LED_B1on, LED_B0wait, LED_B1wait} LED_State;
void SMTick(){
	switch(LED_State){
		case LED_SMStart:
			LED_State = LED_B0on;
			break;
		case LED_B0on:
			if(PINA & 0x01){
				LED_State = LED_B0on;
			}
			else{
				LED_State = LED_B0wait;
			}
			break;
		case LED_B0wait:
			if(PINA & 0x01){
				LED_State = LED_B1on;
			}
			else{
				LED_State = LED_B0wait;
			}
			break;
	 	case LED_B1on:
			if(PINA & 0x01){
                                LED_State = LED_B1on;
                        }
                        else{
                                LED_State = LED_B1wait;
                        }
                        break; 
		case LED_B1wait:
			if(PINA & 0x01){
				LED_State = LED_B0on;
			}
			else{
				LED_State = LED_B1wait;
			}
			break;
		default:
			LED_State = LED_SMStart;
			break;
	}
	switch(LED_State) {   // State actions
     		case LED_SMStart:
        		break;
		case LED_B0on:
			PORTB = 0x01;
			break;
		case LED_B0wait:
			PORTB = 0x01;
			break;
		case LED_B1wait:
			PORTB = 0x02;
			break;
		case LED_B1on:
			PORTB = 0x02;
                        break;
		default:
			break;
		}


}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;

	DDRB = 0xFF;
	PORTB = 0x00;
    /* Insert your solution below */
	LED_State = LED_SMStart;
    while (1) {
	SMTick();
    }
    return 1;
}
