#ifndef __DOORLOCK_H__
#define __DOORLOCK_H__
 
#define button1 ~PINB & 0x80

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


#endif //__DOORLOCK_H__
