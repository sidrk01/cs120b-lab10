/*      Author: Sidharth Ramkumar 
 *  Partner(s) Name: none 
 *      Lab Section: 022
 *      Assignment: Lab #10  Exercise #2
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
#include "getkey.h"
#include "doorlock.h"
// #include "pause.h"
//#include "pwm.h"
//#include "notes.h"
#include "gcd.h"
#endif

#define button1 ~PINB & 0x80

double freq[8] = {261.63, 293.66, 261.63, 349.23, 261.63};
unsigned int index
enum Note_States { Cont, Play, Stop } notes;

int Tick_Fct3(int state){
  switch(state){
    case Cont:
      index = 0;
       if (button2){
        state = Play;
         PWM_on()
       } else {
        state = Cont;
       }
      break;
      
    case Play:
      if (index < 7){
        index += 1;
        state = Play;
      } else if (index > 7){
        state = Stop;
      }
      break;
      
    case Stop:
     state = Cont;
      break;
  }
  
  switch (state){
    case Cont:
      break;
      
    case Wait:
      set_PWM(freq[index]);
     break;
      
    case Stop:
      PWM_off();
     break;
  }
}

unsigned char x;

enum Keypad_State { SMStart, Wait_One, Read };

int Tick_Fct(int state){
    switch (state){
        case SMStart:
            state = Wait_One;
        break;

        case Wait_One:
            state = Read;
        break;

        case Read:
            state = Read;
        break;
    }

    switch (state){
        case SMStart:
        break;

        case Wait_One:
            x = '\0';
        break;

        case Read:
             x = GetKeypadKey();
        break;
    }

    return state;
}

char userCombo[6] = {'#', '1', '2', '3', '4', '5'};

enum Keypad_Lock {Reset, Wait, Release, Unlock} ;

int Tick_Fct2(int state){
  unsigned int i; 
 
  switch (state){
  
    case Reset:
     if (x != userCombo[i]){
      state = Reset;
      i = 0;
     } else if (x == userCombo[i]) {
      state = Wait;
     } 
     break;           
                
   case Wait:
    if (x == '/0'){
     state = Release;
     i += 1;
    } else if (x == userCombo[i]){
     state = Wait;
    } else {
     state = Reset;
     i = 0;
    } 
    break;
  
   case Release:
    if ((x == userCombo[i]) && (i < 5)){
     state = Wait;
    } else if (i >= 5){
     state = Unlock;
    } else if (x != userCombo[i]) {
     state = Reset;
     i = 0;
    }
    break;
    
   case Unlock:
    if (button1){
     state = Reset;
    } else {
     state = Unlock;
    }
    break;
     
  switch (state){
   case Reset: 
      PORTB = 0x00;
    break;
    
   case Wait: 
     PORTB = 0x08;
    break;
    
   case Release: 
     PORTB = 0x10;
    break;
    
   case Unlock:
     PORTB = 0x01;
    break;
  
    
   default:
    PORTB = 0x00;
  }
 return state;
}

int main(void) {


    /*Insert DDR and PORT initializations*/
    DDRB = 0x7F; PORTB = 0x80;  // config PB[6:0] as outputs, PB[7] inputs
    DDRC = 0xF0; PORTC = 0x0F;

    //Declare an array of tasks
    static task task1, task2;
    task *tasks[] = {&task1, &task2 };
    const unsigned short numTasks = sizeof(tasks) / sizeof(task*);

      const char start = -1;
    //Task1 (pauseButtonToggleSM)
    task1.state = start; //Task initial state.
    task1.period = 50; //Task period 
    task1.elapsedTime = task1.period; //Task current elapsed time.
    task1.TickFct = &Tick_Fct; //Function pointer for the tick.

    task2.state = start;
    task2.period = 500;
    task2.elapsedTime = task2.period;
    task2.TickFct = &Tick_Fct2;

    unsigned long GCD = tasks[0]->period;
    for (unsigned int i = 1; i < numTasks; i++) {
    GCD = findGCD(GCD, tasks[i]->period);
    }
    
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

}

