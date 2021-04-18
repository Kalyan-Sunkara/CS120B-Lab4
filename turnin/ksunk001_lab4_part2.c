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
enum Counter_States {Counter_SMStart, Counter_start, Counter_add, Counter_sub, Counter_reset, Counter_wait, Counter_addWait, Counter_subWait} Counter_State;
void SMTick(){
	switch(Counter_State){
		case Counter_SMStart:
			Counter_State = Counter_start;
			break;
		case Counter_start:
			Counter_State =  Counter_wait;
			break;
		case Counter_wait:
			if((PINA & 0x01) && !(PINA & 0x02)){
				Counter_State = Counter_add;
			}
			else if(!(PINA & 0x01) && (PINA & 0x02)){
				Counter_State = Counter_sub;
			}
			else if((PINA & 0x01) && (PINA & 0x02)){
				Counter_State  = Counter_reset;
			}
			else{
				Counter_State = Counter_wait;	
			}
			break;
	 	case Counter_add:
			if(!(PINA & 0x01)){
                                Counter_State = Counter_wait;
                        }
// 			else if((PINA & 0x01) && !(PINA & 0x02)){
// 				Counter_State = Counter_addWait
// 			}
                        else{
                                Counter_State = Counter_addWait;
                        }
                        break;
		case  Counter_addWait:
			if(!(PINA & 0x01)){
                                Counter_State = Counter_wait;
                        }
			else if((PINA & 0x01) && (PINA & 0x02)){
				Counter_State = Counter_reset;
			}
			else{
				Counter_State = Counter_addWait;
			}
			break;
		case Counter_sub:
			if(!(PINA & 0x02)){
                                Counter_State = Counter_wait;
                        }
                        else{
                                Counter_State = Counter_subWait;
                        }
                        break;
		case  Counter_subWait:
			if(!(PINA & 0x02)){
                                Counter_State = Counter_wait;
                        }
			else if((PINA & 0x02) && (PINA & 0x01)){
				Counter_State = Counter_reset;
			}
			else{
				Counter_State = Counter_subWait;
			}
				break;
		case Counter_reset:
			if((PINA & 0x01) & (PINA & 0x02)){
				Counter_State = Counter_reset;	
			}
			else{
				Counter_State = Counter_wait;	
			}
			break;
		default:
			Counter_State = Counter_SMStart;
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
