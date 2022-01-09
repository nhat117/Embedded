#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/interrupt.h>
#include <util/delay.h>
#include "TimeControl.h"
#include "TimeLogic.h"
#include "Debounce.h"
volatile bool mode = 0;

/*

    A
   ---
  F |   | B
  | G |
   ---
  E |   | C
  |   |
   ---
    D

    PIND3-PIND9 : a->g SEVEN SEG (D in this case is D pin D port)

    # These ports are for D1 -> D4 (Controlling digit position in multiplex)
    B3: d1
    B4: d2
    B5: d3
    B6: d4

    (D in this case is D pin D port)
   D3 a
    4 b
    5 c
    6 d
    7 e
   B0 f
    1 g

    (D in this case is D pin D port)
    a D3
    b D4
    c D5
    d D6
    e D7
    f B0
    g B1

    For display number:

    0 a b c d e f
    1 b c
    2 a b g e d
    3 a b g c d
    4 f g b c d
    5 a f g c d
    6 a f e d c g
    7 a b c
    8 a b c d e f g
    9 a b c d f g
*/


volatile bool one = false; // Flag for 1 second has elapsed
volatile bool timeSet = false; // Time mode
volatile int countAlarm = 0; // For Alarm function
volatile int countBuzzer = 0; // For counting 5 buzzes

int main(void) {

  DDRD |= (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7) | (1 << DDD0) | (1 << DDD1); // 7 Seg and sec LED
  DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); // 4 D


  DDRC &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 <<3)); // Hr and Mi and Time mode button
  DDRC |=(1 <<4); // Set mode indicator

  PORTB = 0b11111111;
  PORTD = 0b11111111;

  PORTD &= ~(1 << 1);
  PORTD &= ~(1 << 0);

  PORTC &= ~((1 << 0) | (1 << 1) | (1 << 2));

  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // 1024 prescaler

  OCR1A = 15624; // Set compare value // for testing 1/4 sec: 3124 // normal 15624

  TIMSK1 = 1 << OCIE1A;

  sei();

  int preSetCount = 60; // Alarm at 1 min

  int currentTime[4] = {0, 0, 0, 0};
  YasuoTime yt; // Init custom time object
  Button button0;
  button0.begin(0);


  // Main loop
  while (1) {
    if(button0.debounce()) {
      timeSet = false;
      countBuzzer = 0;
      countAlarm = 0;
    }
    if (timeSet) { // Clock mode
      PORTC &=~(1 << 4);
      if (one) { // one sec
        countAlarm++;
        if (countAlarm >= preSetCount) { // Alarm control
          if (countBuzzer < 5) {
            PORTD ^= (1 << 1);
            countBuzzer++;
          } else {
            PORTD &= ~(1 << 1);
          }
        }

        // Time control
        yt.calculateTime(currentTime); // Calculate current time
        showTime(currentTime); // Display time
        one = false; // Reset time

      }
      showTime(currentTime);

    } else { // To set time
      PORTC |= (1 << 4);
      yt.setTime(currentTime); // Pressing button to choose time
      yt.setTime(currentTime[0] * 10 + currentTime[1], currentTime[2] * 10 + currentTime[3], 0); // Save selected time for further calculations
      timeSet = true; // Switch mode
    }

  }
}

ISR(TIMER1_COMPA_vect) {
  one = true; // Turn on flag for one second
}
