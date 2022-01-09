#include "TimeLogic.h"
#include <avr/io.h>
#include "TimeControl.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Debounce.h"
YasuoTime::YasuoTime() {
  this->setSecond(0);
  this->setMinute(0);
  this->setHour(0);
}

YasuoTime::YasuoTime(int second, int minute, int hour) {
  this->setSecond(second);
  this->setMinute(minute);
  this->setHour(hour);
}

void YasuoTime::calculateTime(int currentTime[]) {
  this->setSecond(this->getSecond() + 1);

  if (this->getSecond() == 60) { // 60 seconds
    this->setSecond(0);

    if (this->getMinute() == 59) { // 60 min
      this->setMinute(0);

      if (this->getHour() == 23) { // 23:59:59
        this->setHour(0);
        currentTime[0] = 0;
        currentTime[1] = 0;
        currentTime[2] = 0;
        currentTime[3] = 0;

        return;
      } else {

        this->setHour(this->getHour() + 1); // Increase hour
      }

    } else {
      this->setMinute(this->getMinute() + 1);
    }

  } else {
    PORTD ^= (1 << 0);
    return;
  }

  currentTime[0] = (this->getHour() / 10);
  currentTime[1] = (this->getHour() % 10);
  currentTime[2] = (this->getMinute() / 10);
  currentTime[3] = (this->getMinute() % 10);
  PORTD ^= (1 << 0);

}

void YasuoTime::setTime(int currentTime[]) {
  // Reset time
  currentTime[0] = 0;
  currentTime[1] = 0;
  currentTime[2] = 0;
  currentTime[3] = 0;

  // For debouncing
  Button button0;
  Button button1;
  Button button2;
  Button button3;
  button0.begin(0);
  button1.begin(1);
  button2.begin(2);
  button3.begin(3);

  // For selecting digit
  int tmpPos = 0;
  
  while (1) {
    // Accept time, return to clock mode
    if (button0.debounce()) {
      break;
    }

    /*
    Increase and decrease constraints for D0 and D1:
    #Increase:
    If D1 >= 4 so D0 can't be 2 (there are no such 27 hour)
    If D0 == 2 so D1 can't be greater than 3 
    #Decrease:
    We only care about when we reach the 0, otherwise, handle it normally
    If D1 >= 4 we have to resset D0 to 1 if 0 is reached
    If D0 == 2 we have to reset D1 to 3 if 0 is reached
    */ 
      
    // Increase button
    if (button1.debounce()) {
      if (tmpPos == 0) {
        if (currentTime[1] >= 4) {
          currentTime[tmpPos] = ++currentTime[tmpPos] % 2;
        } else {
          currentTime[tmpPos] = ++currentTime[tmpPos] % 3;
        }
      } else if (tmpPos == 1) {
        if (currentTime[0] == 2) {
          currentTime[tmpPos] = ++currentTime[tmpPos] % 4;
        } else {
          currentTime[tmpPos] = ++currentTime[tmpPos] % 10;
        }

      } else if (tmpPos == 2) {
        currentTime[tmpPos] = ++currentTime[tmpPos] % 6;
      } else {
        currentTime[tmpPos] = ++currentTime[tmpPos] % 10;
      }

    }

    // Decrease button
    if (button2.debounce()) { 
      if (tmpPos == 0) {
        if (currentTime[tmpPos] == 0) {
          if (currentTime[1] >= 4) {
            currentTime[tmpPos] = 1;
          } else {
            currentTime[tmpPos] = 2;
          }
        } else {
          currentTime[tmpPos] -= 1;
        }
      } else if (tmpPos == 1) {
        if (currentTime[tmpPos] == 0) {
          if (currentTime[0] == 2) {
            currentTime[tmpPos] = 3;
          } else {
            currentTime[tmpPos] = 9;
          }
        } else {
          currentTime[tmpPos] -= 1;
        }
      } else if (tmpPos == 2) {
        if (currentTime[tmpPos] == 0) {
          currentTime[tmpPos] = 5;
        } else {
          currentTime[tmpPos] -= 1;
        }
      } else {
        if (currentTime[tmpPos] == 0) {
          currentTime[tmpPos] = 9;
        } else {
          currentTime[tmpPos] -= 1;
        }
      }
    }

    // Switch between digits
    if (button3.debounce()) { 
      tmpPos = (++tmpPos) % 4;
    }
    
    showTime(currentTime);
  }
}

void YasuoTime::setTime(int hour, int minute, int second) {
  this->setHour(hour);
  this->setMinute(minute);
  this->setSecond(second);
}
