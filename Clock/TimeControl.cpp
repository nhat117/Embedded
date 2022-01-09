#include "TimeControl.h"
#include <avr/io.h>
#include <util/delay.h>

void resetDX(int pos) {
  // Choosing from D1 to D4 (2 -> 5)
  for (int i = 2; i <= 5; i++) {
    if (pos == i) {
      PORTB |= (1 << pos);  // Turn on Dpos
    } else {
      PORTB &= ~(1 << i);   // Turn off other pos
    }
  }

}

void showZero(int pos) {
  resetDX(pos);
  PORTD &= ~((1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7)); 
  PORTB &= ~(1 << 0); 
  PORTB |= (1 << 1); 
}

void showOne(int pos) {
  resetDX(pos);
  PORTD &= ~((1 << 4) | (1 << 5));
  PORTB |= (1 << 0) | (1 << 1);
  PORTD |= (1 << 3) | (1 << 6) | (1 << 7);
}

void showTwo(int pos) {
  resetDX(pos);
  PORTD |= (1 << 5);
  PORTB |= (1 << 0);
  PORTD &= ~((1 << 3) | (1 << 4) | (1 << 7) | (1 << 6));
  PORTB &=  ~(1 << 1);
}

void showThree(int pos) {
  resetDX(pos);
  PORTD |= (1 << 7);
  PORTB |= (1 << 0);
  PORTD &= ~((1 << 3) | (1 << 4) | (1 << 5) | (1 << 6));
  PORTB &=  ~(1 << 1);
}

void showFour(int pos) {
  resetDX(pos);
  PORTD |= (1 << 3) | (1 << 6) | (1 << 7);
  PORTD &= ~((1 << 4) | (1 << 5));
  PORTB &=  ~((1 << 1) | (1 << 0));
}

void showFive(int pos) {
  resetDX(pos);
  PORTD |= (1 << 4) | (1 << 7);
  PORTD &= ~( (1 << 3) | (1 << 5) | (1 << 6) );
  PORTB &=  ~((1 << 1) | (1 << 0));
}

void showSix(int pos) {
  resetDX(pos);
  PORTD |= (1 << 4);
  PORTD &= ~((1 << 3) | (1 << 5) | (1 << 6) | (1 << 7));
  PORTB &=  ~((1 << 1) | (1 << 0));
}

void showSeven(int pos) {
  resetDX(pos);
  PORTD &= ~((1 << 3) | (1 << 4) | (1 << 5));
  PORTD |= (1 << 6) | (1 << 7);
  PORTB |= (1 << 0) | (1 << 1);
}

void showEight(int pos) {
  resetDX(pos);
  PORTD &= ~( (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) );
  PORTB &=  ~((1 << 1) | (1 << 0));
}

void showNine(int pos) {
  resetDX(pos);
  PORTD &= ~((1 << 3) | (1 << 4) | (1 << 5) | (1 << 6));
  PORTD |= (1 << 7);
  PORTB &= ~((1 << 1) | (1 << 0));
}

void showBlank(int pos) {
  resetDX(pos);
  PORTD |= (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
  PORTB |= (1 << 0) | (1 << 1);
 }

void showTime(int currentTime[]) {
  for (int i = 0; i < 4; i++) {
    switch (currentTime[i]) {
      case 0:
        showZero(i + 2);
            _delay_ms(5);
        break;
      case 1:
        showOne(i + 2);
         _delay_ms(5);
        break;
      case 2:
        showTwo(i + 2);
         _delay_ms(5);
        break;
      case 3:
        showThree(i + 2);
         _delay_ms(5);
        break;
      case 4:
        showFour(i + 2);
         _delay_ms(5);
        break;
      case 5:
        showFive(i + 2);
         _delay_ms(5);
        break;
      case 6:
        showSix(i + 2);
         _delay_ms(5);
        break;
      case 7:
        showSeven(i + 2);
         _delay_ms(5);
        break;
      case 8:
        showEight(i + 2);
        _delay_ms(5);
        break;
      case 9:
        showNine(i + 2);
         _delay_ms(5);
        break;
      case -1:
        showBlank(i + 2);
         _delay_ms(5);
        break;
    }
  }
}
