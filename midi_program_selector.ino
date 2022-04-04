
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "MpsDisplay.h"
#include "MpsMidi.h"
#include "MpsButtonScanner.h"
 
MpsDisplay display = MpsDisplay();
MpsMidi midi = MpsMidi();
MpsButtonScanner buttonScanner = MpsButtonScanner();

void setup() {
  midi.Initialize();
  buttonScanner.Initialize();
  display.Initialize();
  display.ShowSplash();

  display.Update(CurrentChannelProgram {0, 0});

}

void loop() {
  CurrentChannelProgram currentState;
  
  switch(buttonScanner.Poll()) {
    case ButtonAction::NO_ACTION: {
      break;
    }

    case ButtonAction::PROGRAM_UP_ONE: {
      Serial.println("PROGRAM_UP_ONE");
      currentState = midi.IncrementProgram();
      display.Update(currentState);
      break;
    }

    case ButtonAction::PROGRAM_DOWN_ONE: {
      Serial.println("PROGRAM_DOWN_ONE");
      currentState = midi.DecrementProgram();
      display.Update(currentState);
      break;
    }
    
    case ButtonAction::PROGRAM_UP_TEN: {
      Serial.println("PROGRAM_UP_TEN");
      currentState = midi.IncrementProgramTen();
      display.Update(currentState);
      break;
    }
    
    case ButtonAction::PROGRAM_DOWN_TEN: {
      Serial.println("PROGRAM_DOWN_TEN");
      currentState = midi.DecrementProgramTen();
      display.Update(currentState);
      break;
    }
    
    case ButtonAction::CHANNEL_UP: {
      Serial.println("CHANNEL_UP");
      currentState = midi.IncrementChannel();
      display.Update(currentState);
      break;
    }
    
    case ButtonAction::CHANNEL_DOWN: {
      Serial.println("CHANNEL_DOWN");
      currentState = midi.DecrementChannel();
      display.Update(currentState);
      break;
    }
    
    default: {
      Serial.println("default");
      break;
    }
  }


  delay(250);
}
