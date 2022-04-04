#ifndef __MPSBUTTONSCANNER_H__
#define __MPSBUTTONSCANNER_H__

enum ButtonAction {
  NO_ACTION = 1,
  PROGRAM_UP_ONE,
  PROGRAM_DOWN_ONE,
  PROGRAM_UP_TEN,
  PROGRAM_DOWN_TEN,
  CHANNEL_UP,
  CHANNEL_DOWN
};

class MpsButtonScanner {
private:
  const int pins[6] = {PROGRAM_UP_ONE, PROGRAM_DOWN_ONE, PROGRAM_UP_TEN, PROGRAM_DOWN_TEN, CHANNEL_UP, CHANNEL_DOWN};

  bool PinHigh(int pin) {
    return digitalRead(pin) == LOW;
  }
  
public:
  MpsButtonScanner() {
    
  }

  void Initialize(void) {
    for(int pin : pins) {
      pinMode(pin, INPUT_PULLUP);
    }
  }

  ButtonAction Poll() {
    for(int pin : pins) {
      if(PinHigh(pin)) {
        return (ButtonAction)pin;
      }
    }
    return NO_ACTION;
  }
};

#endif
