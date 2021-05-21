//--Shared Variables
unsigned char led0_output = 0x00;
unsigned char led1_output = 0x00;
unsigned char pause = 0;
//--End Shared Variables

enum pauseButtonSM_States { pauseButton_wait, pauseButton_press, pauseButton_release };

//Monitors button connected to PA0 
//When button is pressed, shared variable "pause is toggled

int pauseButtonSMTick(int state){
  //Local Variables
  unsigned char press = ~PINA  & 0x01;
  
  switch (state){
    case pauseButton_wait:
      state = press == 0x01 ? pauseButton_press: pauseButton_wait; break;
    case pauseButton_press:
      state = pauseButton_release; break;
    case pauseButton_release:
      state = press == 0x00 ? pauseButton_wait : pauseButton_press; break;
    default: state = pauseButton_wait; break;   
  }
  
  switch (state) {
    case pauseButton_wait: break;
    case pauseButton_press:
      pause = (pause == 0) ? 1 : 0; //toggle pause 
      break;
    case pauseButton_release: break;
  }
  return state;
}

enum toggleLED0_States { toggleLED0_wait, toggleLED0_blink };

int toggleLED0SMTick (int state){
  switch (state){
    case toggleLED0_wait: state = !pause? toggleLED0_blink: toggleLED0_wait; break;
    case toggleLED0_blink: state = pause? toggleLED0_wait: toggleLED0_blink; break;
    default: state = toggleLED0_wait; break;
  }
  
  switch (state) {
    case toggleLED0_wait: break;
    case toggleLED0_blink:
      led0_output = (led0_output == 0x00) ? 0x01 : 0x00; //toggle LED
      break;
  }
  return state;
  }

enum toggleLED1_States {toggleLED1_wait, toggleLED1_blink };

int toggleLED1SMTick(int state){
  switch (state){
    case toggleLED1_wait : state = !pause? toggleLED1_blink : toggleLED1_wait; break;
    case toggleLED1_blink: state = pause? toggleLED1_wait: toggleLED1_blink; break;
    default: state = toggleLED1_wait; break;
  }
  
  switch (state){
    case toggleLED1_wait: break;
    case toggleLED1_blink:
        led1_output = (led1_output == 0x00) ? 0x01 : 0x00; //toggle LED
    break;
  }
  return state;
}

enum display_States {display_display };
int displaySMTick(int state) {
  unsigned char output;
  
  switch (state) {
    case display_display: state = display_display; break;
    default: state = display_display; break;
  }
  
  switch(state){
    case display_display:
      output = led0_output | led1_output << 1;
      
      break;
  }
  PORTB = output;
  return state;
}
