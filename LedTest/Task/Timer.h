#ifndef TIMER
#define TIMER

#include "Arduino.h"

volatile bool timerFlag;

ISR(TIMER1_COMPA_vect) {
    timerFlag = true;
}

class Timer {

    public:
        Timer() {
            timerFlag = false;
        }

        void setupFreq(int freq) {
            cli();

            TCCR1A = 0;
            TCCR1B = 0;
            TCNT1 = 0;

            OCR1A = 16*1024/freq;
            TCCR1B |= (1 << WGM12);
            TCCR1B |= (1 << CS12) | (1 << CS10);
            TIMSK1 |= (1 << OCIE1A);

            sei();
        }

        void setupPeriod(int period) {
            cli();

            TCCR1A = 0; // set entire TCCR1A register to 0
            TCCR1B = 0; // same for TCCR1B
            TCNT1  = 0; //initialize counter value to 0
  
            OCR1A = 16.384*period; 
            // turn on CTC mode
            TCCR1B |= (1 << WGM12);
            // Set CS11 for 8 prescaler
            TCCR1B |= (1 << CS12) | (1 << CS10);  
            // enable timer compare interrupt
            TIMSK1 |= (1 << OCIE1A);

            // enabling interrupt
            sei();
        }

        void waitForNextTick() {
            while(!timerFlag) {}
            timerFlag = false;
        }
};

#endif