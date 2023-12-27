//v.0.2

#define SW_RST  12
#define SW_DAT  11
#define SW_CLK  10
#define SW_STRB  9

#define MIDI_OFFSET 48

#include <MIDI.h>

const unsigned char keyaddr[] = {
0x00, 
0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 
0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 
0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 
0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 
0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 
0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 
0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 
};

MIDI_CREATE_DEFAULT_INSTANCE();

void SWload( unsigned char addr, unsigned char value ){
  uint8_t i, p;
  addr = addr << 1;
  for( i = 0; i < 7; i++ ){
    digitalWrite(SW_CLK, LOW);
    if( addr & 0x80 ) digitalWrite(SW_DAT, HIGH);
    else digitalWrite(SW_DAT, LOW);
    delayMicroseconds(1);
    digitalWrite(SW_CLK, HIGH);
    addr = addr << 1;
  }
  digitalWrite(SW_CLK, LOW);
  if( value ) digitalWrite(SW_DAT, HIGH);
  else digitalWrite(SW_DAT, LOW);
  delayMicroseconds(1);
  digitalWrite(SW_STRB, HIGH);
  delayMicroseconds(1);
  digitalWrite(SW_STRB, LOW);
}

void setup() {
pinMode(SW_RST, OUTPUT);
pinMode(SW_DAT, OUTPUT);
pinMode(SW_CLK, OUTPUT);
pinMode(SW_STRB, OUTPUT);

digitalWrite(SW_RST, HIGH);
delay(2);
digitalWrite(SW_RST, LOW);

MIDI.begin();

}

void loop() {
 uint8_t vel = 0;
 uint8_t mnote = 0;
 
 if (MIDI.read())                
    {
        switch(MIDI.getType())
        {
            case midi::NoteOn:
                mnote = MIDI.getData1();
                vel = MIDI.getData2();
                if (vel > 0) SWload(keyaddr[mnote - MIDI_OFFSET],1);
                else SWload(keyaddr[mnote - MIDI_OFFSET],0);
                break;
            case midi::NoteOff:
                mnote = MIDI.getData1();            
                SWload(keyaddr[mnote - MIDI_OFFSET],0);
                break; 
 
            default:
                break;
        }
    }
}
