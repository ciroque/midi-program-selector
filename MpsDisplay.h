/*
 * 
 */

#ifndef __MPSDISPLAY_H__
#define __MPSDISPLAY_H__

#include <Wire.h>
#include <Adafruit_SSD1306.h>


class MpsDisplay {
private:
  const int SCREEN_WIDTH = 128;
  const int SCREEN_HEIGHT = 32;

  const int OLED_RESET = 4;
  const int SCREEN_ADDRESS = 0x3C;

  
  const int CHANNEL_LABEL_X = 0;
  const int CHANNEL_LABEL_Y = 0;
  
  const int PROGRAM_LABEL_X = 58;
  const int PROGRAM_LABEL_Y = 0;

  const int VALUE_Y = 6;
  const int VALUE_X_OFFSET = 15;

  Adafruit_SSD1306 display;

  void Clear(void) {
    display.clearDisplay();
  }

  void Update(void) {
    display.display();
  }

  void DrawChannel(byte channel) {
    display.setCursor(VALUE_X_OFFSET, VALUE_Y);
    DrawPaddedTens(channel);
  }

  void DrawLabels(void) {
    display.setTextSize(2);
    
    display.setCursor(CHANNEL_LABEL_X,CHANNEL_LABEL_Y);
    display.println(F("C"));
    display.println(F("H"));

    display.setCursor(PROGRAM_LABEL_X, PROGRAM_LABEL_Y);
    display.println(F("P"));
    display.setCursor(PROGRAM_LABEL_X, display.getCursorY());
    display.println(F("G"));

    Update();
  }

  void DrawProgram(byte program) {
    display.setCursor(PROGRAM_LABEL_X + VALUE_X_OFFSET, VALUE_Y);
    DrawPaddedHundreds(program);
  }

  void DrawPaddedTens(byte number) {
    if(number < 10) { display.print("0"); }
    display.print(number);
  }

  void DrawPaddedHundreds(byte number) {
    if(number < 100) { display.print("0"); }
    DrawPaddedTens(number);
  }
  
public:
  MpsDisplay() {
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  }

  bool Initialize() {
    return display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  }

  void ShowSplash(void) {
    Clear();
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display.setTextSize(2);
  
    display.println("midiProg W");
    display.println("v0.0.1");
    
    Update();
    
    delay(2000); // Pause for 2 seconds
  }

  void UpdateValues(int channel, int program) {
    display.clearDisplay();
    DrawLabels();
    display.setTextSize(3);
    DrawChannel(channel + 1);
    DrawProgram(program + 1);

    Update();
  }
};

#endif
