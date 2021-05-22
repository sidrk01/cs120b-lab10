// Permission to copy is granted provided that this header remains intact. 
// // This software is provided with no warranties.
//
// ////////////////////////////////////////////////////////////////////////////////
//
 #ifndef TIMER_H
 #define TIMER_H
//
 #include <avr/interrupt.h>
//
 volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
 unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
 unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerISR();

// Set TimerISR() to tick every M ms
 void TimerSet(unsigned long M) {
 	_avr_timer_M = M;
 		_avr_timer_cntcurr = _avr_timer_M;
 		}


void TimerOn() {
	// AVR timer/counter controller register TCCR1
	 	TCCR1B 	= 0x0B;	// bit3 = 1: CTC mode (clear timer on compare)
	 		// bit2bit1bit0=011: prescaler /64
	// 											// 00001011: 0x0B
	// 									        // SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// 									       // Thus, TCNT1 register will count at 125,000 ticks/s
	

       OCR1A = 125;
       TIMSK1 	= 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;	// 0x80: 1000000

void TimerOff() {
	TCCR1B 	= 0x00; // bit3bit2bit1bit0=0000: timer off
}


ISR(TIMER1_COMPA_vect)
{

_avr_timer_cntcurr--; 			// Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { 	// results in a more efficient compare
		TimerISR(); 				// Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

#endif //TIMER_H

