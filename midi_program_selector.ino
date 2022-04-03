
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "MpsDisplay.h"
#include "MpsMidi.h"
 
MpsDisplay display = MpsDisplay();
MpsMidi midi = MpsMidi();

void setup() {
  midi.Initialize();
  display.Initialize();
  display.ShowSplash();
}

void loop() {
  delay(3000);

  
  byte channel = random(0, 9); // zero-based channel
  byte program = random(0, 127); // zero-based program
  
  display.UpdateValues(channel, program);
  midi.SendProgramChange(channel, program);
}
