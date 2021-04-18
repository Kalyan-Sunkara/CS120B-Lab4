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
enum Lock_States {Lock_SMStart, Lock_wait, Lock_hash, Lock_hashWait, Lock_Y, Lock_YWait, LOCK, UNLOCK} Lock_State;
void SMTick(){
	switch(Lock_State){
		case Lock_SMStart:
			Lock_State = Lock_wait;
			break;
		case Lock_wait:
			Lock_State =  Lock_wait;
			break;
		default:
			Lock_State = Lock_SMStart;
			break;
	}
	switch(Counter_State) {   // State actions
 		case Counter_SMStart:
			break;
		case Counter_start:
			PORTC = 0x07;
		case Counter_wait:
			break;
	 	case Counter_add:
			if(PORTC < 9){
				PORTC = PORTC + 1;	
			}
                        break;
		case  Counter_addWait:
			break;
		case Counter_sub:
			if(PORTC > 0){
				PORTC = PORTC - 1;	
			}
			break;
		case  Counter_subWait:
			break;
		case Counter_reset:
			PORTC = 0x00;
			break;
		default:
			break;
		}


}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;

	DDRC = 0xFF;
	PORTC = 0x00;
    /* Insert your solution below */
//	LED_State = LED_SMStart;
	//Counter_State = Counter_start;
    while (1) {
	SMTick();
    }
    return 1;
}
