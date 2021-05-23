#include "pwm.h"

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
