#ifndef __MPSMIDI_H__
#define __MPSMIDI_H__

class MpsMidi {
private:
  const int MIDI_BAUD_RATE = 31250;
  const int PROGRAM_CHANGE_COMMAND = 0xC0;
  const int CHANNELIZATION_MASK = 0x0F;

  byte ProgramChangeCommand(byte channel) {
    return PROGRAM_CHANGE_COMMAND | (channel & CHANNELIZATION_MASK);
  }
  
public:
  MpsMidi(void) {}

  void Initialize(void) {
    Serial1.begin(MIDI_BAUD_RATE);
//    while(!Serial) { ; }
  }
  
  void SendProgramChange(byte channel, byte program) {
    Serial1.write(ProgramChangeCommand(channel));
    Serial1.write(program);
  }
};

#endif
