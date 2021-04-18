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
enum Lock_States {Lock_SMStart, Lock_wait, Lock_code, LOCK, UNLOCK} Lock_State;
unsigned char lockArray[4] = {0x04, 0x01, 0x02, 0x01};
unsigned char count = 1;
void SMTick(){
	switch(Lock_State){
		case Lock_SMStart:
			Lock_State = Lock_wait;
			break;
		case Lock_wait:
			if(PINA & 0x80){
				Lock_State = LOCK;
			}
			else if(PINA & 0x04){
			Lock_State =  Lock_hash;
			}
			else{
				Lock_State = Lock_wait;	
			}
			break;
		case Lock_code:
			if(count == 4){
				count = 1;
				Lock_State = UNLOCK;
			}
			else if(PINA == lockArray[count]){
				count++;
				Lock_State = Lock_code;
			}
			else{
				Lock_State = Lock_wait;
				count = 1;	
			}
			break;
		case UNLOCK:
			Lock_State = Lock_wait;
			break;
		case LOCK:
			Lock_State = Lock_wait;
			break;
		default:
			Lock_State = Lock_SMStart;
			break;
	}
	switch(Lock_State) {   // State actions
 		case Lock_SMStart:
			break;
		case Lock_wait:
			break;
		case Lock_code:
			break;
		case UNLOCK:
			PORTB = !PORTB; //flips if locked or unlocked 
			break;
		case LOCK:
			PORTB = 0x00;
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

	DDRC = 0xFF;
	PORTC = 0x00;
    /* Insert your solution below */
//	LED_State = LED_SMStart;
	//Counter_State = Counter_start;
    while (1) {
	SMTick();
	PORTC = Lock_State;
    }
    return 1;
}
