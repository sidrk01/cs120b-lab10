#ifndef __DOORLOCK_H__
#define __DOORLOCK_H__
 
#define button1 ~PINA & 0x01

enum Keypad_Lock { SMStart2, Wait, Pound_Press, Pound_Wait, One_Press, One_Wait, Two_Press, Two_Wait, 
                  Three_Press, Three_Wait, Four_Press, Four_Wait, Five_Press, Five_Wait};

int Tick_Fct2(int state){
  unsigned char x = GetKeypadKey();
  
  switch (state){
    case SMStart2:
    state = Wait;
    break;
      
    case Wait:
    if (x == '#'){
      state = Pound_Press;
    } else {
      state = Wait;
    }
      break;
     
    case Pound_Press:
      if (x == '#'){
        state = Pound_Press;
      } else if (x == '\0') {
        state = Pound_Wait;
      } else {
        state = Wait;
      }
      break;
      
    case Pound_Wait:
      if (x == '\0'){
        state = Pound_Wait;
      } else if (x == '1'){
        state = One_Press;
      } else {
        state = Wait;
      }
      break;
      
    case One_Press:
      if (x == '1'){
        state = One_Press;
      } else if (x == '\0'){
        state = One_Wait;
      } else {
        state = Wait;
      }
     break;
      
    case One_Wait:
      if (x == '\0'){
        state = One_Wait;
      } else if (x == '2'){
        state = Two_Press;
      } else {
        state = Wait;
      }
      break;
      
      case Two_Press:
      if (x == '2'){
        state = Two_Press;
      } else if (x == '\0'){
        state = Two_Wait;
      } else {
        state = Wait;
      }
     break;
      
    case Two_Wait:
      if (x == '\0'){
        state = Two_Wait;
      } else if (x == '3'){
        state = Three_Press;
      } else {
        state = Wait;
      }
      break;
      
      case Three_Press:
      if (x == '3'){
        state = Three_Press;
      } else if (x == '\0'){
        state = Three_Wait;
      } else {
        state = Wait;
      }
     break;
      
    case Three_Wait:
      if (x == '\0'){
        state = Three_Wait;
      } else if (x == '4'){
        state = Four_Press;
      } else {
        state = Wait;
      }
      break;
      
   case Four_Press:
      if (x == '4'){
        state = Four_Press;
      } else if (x == '\0'){
        state = Four_Wait;
      } else {
        state = Wait;
      }
     break;
      
    case Four_Wait:
      if (x == '\0'){
        state = Four_Wait;
      } else if (x == '5'){
        state = Five_Press;
      } else {
        state = Wait;
      }
      break;
     
     case Five_Press:
      if (x == '5'){
        state = Five_Press;
      } else if (x == '\0'){
        state = Five_Wait;
      } else {
        state = Wait;
      }
     break;
      
    case Five_Wait:
      if (button1){
        state = Wait;
      } else {
        state = Five_Wait;
      }
      break;         
  } 
  
  switch (state){
    case SMStart2: 
      break;
    
    case Five_Wait:
       PORTB = 0x01;
    break;
      
    case One_Wait:
      PORTB = 0x02;
    break;
    
   case Two_Wait:
    PORTB = 0x04;
    break;
   
   case Three_Wait:
    PORTB = 0x08;
    break;
    
   case Four_Wait:
    PORTB = 0x10;
    break;
  }
 
 return state;
}


#endif //__DOORLOCK_H__
