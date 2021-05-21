/*	Author: sramk002
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #10  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#include "../header/keypad.h"
// #include "../header/task.h"
// #include "../header/pause.h"
// #include "../header/gcd.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRB = 0xFF; PORTB = 0x00;
        DDRC = 0xF0; PORTC = 0x0F;
    /* Insert your solution below */
    unsigned char x;
    while (1) {
        x = GetKeypadKey();
        switch(x){
            case '\0': PORTB = 0x1F; break; //All 5 LEDS On
            case '1': PORTB = 0x01; break; //Hex equivalent
            case '2': PORTB = 0x02; break;
                
            // .. ***** FINISH ***** 
            
            case 'D': PORTB = 0x0D; break;
            case '*': PORTB = 0x0E; break;
            case '0': PORTB = 0x00; break;
            case '#': PORTB = 0x0F; break;
            default: PORTB = 0x1B; break; //Should never occur. Middle LED off.
        }

    }
    return 1;
}
