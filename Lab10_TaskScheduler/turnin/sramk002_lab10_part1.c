/*      Author: Sidharth Ramkumar 
 *  Partner(s) Name: none 
 *      Lab Section: 022
 *      Assignment: Lab #10  Exercise #1
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "keypad.h"
#include "task.h"
//#include "doorlock.h"
// #include "pause.h"
#include "gcd.h"
#endif

//#define button1 = ~PINB & 0x80
unsigned char keypadKey;

enum Keypad_State { SMStart, Wait, Read };

int Tick_Fct(int state){
    switch (state){
        case SMStart:
            state = Wait;
        break;

        case Wait:
            state = Read;
        break;

        case Read:
            state = Read;
               break;
    }

    switch (state){
        case SMStart:
        break;

        case Wait:
            keypadKey = '\0';
        break;

        case Read:
             keypadKey = GetKeypadKey();
        break;
    }

    return state;
}

int main(void) {


    /*Insert DDR and PORT initializations*/
    /*
    DDRB = 0x7F; PORTB = 0x80;
    DDRC = 0x00; PORTC = 0xFF;
    */
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    //Declare an array of tasks
    static task task1;
    task *tasks[] = {&task1 };
    const unsigned short numTasks = sizeof(tasks) / sizeof(task*);

      const char start = -1;
    //Task1 (pauseButtonToggleSM)
    task1.state = start; //Task initial state.
    task1.period = 50; //Task period 
    task1.elapsedTime = task1.period; //Task current elapsed time.
    task1.TickFct = &Tick_Fct; //Function pointer for the tick.


    unsigned long GCD = tasks[0]->period;
    for (unsigned int i = 1; i < numTasks; i++) {
    GCD = findGCD(GCD, tasks[i]->period);
    }

    TimerSet(GCD);
    TimerOn();

    unsigned short i;
    unsigned char x;

    while (1) {

        x = GetKeypadKey();

        switch(x){
            case '\0': PORTB = 0x1F; break; //All 5 LEDS On
            case '1': PORTB = 0x01 | 0x80; break; //Hex equivalent
            case '2': PORTB = 0x02 | 0x80; break;
            case '3': PORTB = 0x03 | 0x80; break;
            case '4': PORTB = 0x04 | 0x80; break;
            case '5': PORTB = 0x05 | 0x80; break;
            case '6': PORTB = 0x06 | 0x80; break;
            case '7': PORTB = 0x07 | 0x80; break;
            case '8': PORTB = 0x08 | 0x80; break;
            case '9': PORTB = 0x09 | 0x80; break;
            case 'A': PORTB = 0x0A | 0x80; break;
            case 'B': PORTB = 0x0B | 0x80; break;
            case 'C': PORTB = 0x0C | 0x80; break;
            case 'D': PORTB = 0x0D | 0x80; break;
            case '*': PORTB = 0x0E | 0x80; break;
            case '0': PORTB = 0x00 | 0x80; break;
            case '#': PORTB = 0x0F | 0x80; break;

            default: PORTB = 0x1B; break; //Should never occur. Middle LED off.
                   }

        for (i = 0; i < numTasks; i++){
            if (tasks[i]->elapsedTime == tasks[i]->period) { //Task is ready to tick
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state); //Set next state
                tasks[i]->elapsedTime = 0; //Reset the elapsed time for next tick.
            }
            tasks[i]->elapsedTime += GCD;
    }
        while (!TimerFlag);
        TimerFlag = 0;
}
return 0; //Error: Program should not exit;

}


                                                                                           

