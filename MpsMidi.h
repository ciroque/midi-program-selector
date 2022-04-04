#ifndef __MPSMIDI_H__
#define __MPSMIDI_H__

struct CurrentChannelProgram {
  byte channel;
  byte program;
};

class MpsMidi {
private:
  const int MIDI_BAUD_RATE = 31250;
  const int PROGRAM_CHANGE_COMMAND = 0xC0;
  const int CHANNELIZATION_MASK = 0x0F;
  const int PROGRAM_WRAP_MASK = 0x7F;

  byte currentChannel = 0;
  byte programs[16];

  byte ProgramChangeCommand(byte channel) {
    return PROGRAM_CHANGE_COMMAND | (channel & CHANNELIZATION_MASK);
  }

  void SendProgramChange(byte channel, byte program) {
    Serial1.write(ProgramChangeCommand(channel));
    Serial1.write(program);
  }

  CurrentChannelProgram CurrentState() {
    return CurrentChannelProgram{currentChannel, programs[currentChannel]};
  }

public:
  MpsMidi(void) {}

  void Initialize(void) {
    Serial1.begin(MIDI_BAUD_RATE);
  }

  CurrentChannelProgram IncrementProgram() {
    programs[currentChannel]++;
    programs[currentChannel] &= PROGRAM_WRAP_MASK;
    SendProgramChange(currentChannel, programs[currentChannel]);

    return CurrentState();
  }

  CurrentChannelProgram DecrementProgram() {
    programs[currentChannel]--;
    programs[currentChannel] &= PROGRAM_WRAP_MASK;
    SendProgramChange(currentChannel, programs[currentChannel]);

    return CurrentState();
}

  CurrentChannelProgram IncrementProgramTen() {
    programs[currentChannel] += 10;
    programs[currentChannel] &= PROGRAM_WRAP_MASK;
    SendProgramChange(currentChannel, programs[currentChannel]);

    return CurrentState();
  }

  CurrentChannelProgram DecrementProgramTen() {
    programs[currentChannel] -= 10;
    programs[currentChannel] &= PROGRAM_WRAP_MASK;
    SendProgramChange(currentChannel, programs[currentChannel]);

    return CurrentState();
  }

  CurrentChannelProgram IncrementChannel() {
     currentChannel++;
     currentChannel &= CHANNELIZATION_MASK;

    return CurrentState();
  }

  CurrentChannelProgram DecrementChannel() {
     currentChannel--;
     currentChannel &= CHANNELIZATION_MASK;  

    return CurrentState();
  }
};

#endif
