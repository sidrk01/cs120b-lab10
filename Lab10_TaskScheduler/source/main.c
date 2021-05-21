/*	Author: Sidharth Ramkumar 
 *  Partner(s) Name: none 
 *	Lab Section: 022
 *	Assignment: Lab #10  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include ".simAVRHeader.h"
#include "timer.h"
#include "keypad.h"
#include "task.h"
// #include "pause.h"
// #include "gcd.h"
#endif

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
            keypadKey = GetKeyPadKey();
        break;
    }
    
    return state;
}

int main(void) {
    
  
    /*Insert DDR and PORT initializations*/
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    //Declare an array of tasks
    static task task1, task2, task3, task4;
    _task *tasks[] = {&task1, &task2, &task3, &task4 };
    const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
    
    const char start = -1;
    //Task1 (pauseButtonToggleSM)
    task1.state = start; //Task initial state.
    task1.period = 50; //Task period 
    task1.elapsedTime = task1.period; //Task current elapsed time.
    task1.TickFct = &pauseButtonToggleSMTick; //Funciton pointer for the tick.
    //Task2 (toggleLED0SM)
    task2.state = start; 
    task2.period = 500;
    task2.elapsedTime = task2.period;
    task2.TickFct = &toggleLED0SMTick;
    //Task3 (toggleLED1SM)
    task3.state = start;
    task3.period = 1000; 
    task3.elapsedTime = task3.period;
    task3.TickFct = &toggleLED1SMTick;
    //Task4 (displaySM)
    task4.state = start;
    task4.period = 10;
    task4.elapsedTime = task4.period;
    task4.TickFct = &displaySMTick;
    
    
    unsigned long GCD = tasks[0]->period;
    for (i = 1; i < numTasks, i++) {
    GCD = findGCD(GCD, tasks[i]->period);
    
    TimerSet(GCD);
    TimerOn();
        
    unsigned short i; 
    while (1) {
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
    
    
    /* Insert DDR and PORT initializations 
        DDRB = 0xFF; PORTB = 0x00;
        DDRC = 0xF0; PORTC = 0x0F;
    /* Insert your solution below 
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
    */
}
