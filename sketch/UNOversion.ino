#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); //SW시리얼핀 정의 D3이 MIDI신호 전송용,  D2는 미사용 

byte note = 10; //The MIDI연주될 note(음계)
byte resetMIDI = 4; // VS1053 Reset용 핀
byte ledPin = 13; //MIDI 트래픽 표시용 LED

const int button = 14;
boolean buttonState = false;
int  instrument = 1;


const int CdsPin1 = A0;
const int CdsPin2 = A1;
const int CdsPin3 = A2;

int br1;  // 버튼1 상태 확인용 입력값 임시저장용
int br2;  // 이하, 위와 유사
int br3;


int br1_B;  // 버튼1 상태 확인용 입력값 임시저장용
int br2_B;  // 이하, 위와 유사
int br3_B;


int bn1 = 60; //버튼1의  note(음계)  가령 "도"  0~127까지 지정가능 (정확한 음계 설정은 MIDI관련정보참고)
int bn2 = 62; //버튼2의  note(음계)  가령 "레"
int bn3 = 64; //버튼3의  note(음계)  가령 "미"


void setup() {
  Serial.begin(57600);

  //Setup soft serial for MIDI control
  mySerial.begin(31250);

  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 120);

  pinMode(button, INPUT_PULLUP);

  br1 = analogRead(CdsPin1);
  br2 = analogRead(CdsPin2);
  br3 = analogRead(CdsPin3);
  
  br1_B = br1;  
  br2_B = br2;  
  br3_B = br3;
  delay(500);

  
  Serial.print(br1_B);
  Serial.print(" ");
  Serial.print(br2_B);
  Serial.print(" ");  
  Serial.print(br3_B);
  Serial.print(" ");
}


void loop() {
  if (buttonState == false) {
    instrument ++;
  }
  if (instrument > 127) {
    instrument = 0;
  }
    
  talkMIDI(0xC0, instrument, 0);
  
  br1 = analogRead(CdsPin1);
  br2 = analogRead(CdsPin2);
  br3 = analogRead(CdsPin3);

  buttonState = digitalRead(button);

  Serial.print(br1);
  Serial.print(" ");
  Serial.print(br2);
  Serial.print(" ");  
  Serial.print(br3);
  Serial.print(" ");
  Serial.print(buttonState);
  Serial.print(" ");
  Serial.println(instrument);
    
   if( br1 < br1_B - 50 ){
     noteOn(0, bn1, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn1, 0);   
     Serial.print("L");
   }
   if( br2 < br2_B - 50 ){
     noteOn(0, bn2, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn2, 0);  
     Serial.print("L"); 
   }
   if( br3 < br3_B - 50 ){
     noteOn(0, bn3, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn3, 0);  
     Serial.print("L"); 
   }
  delay(1000);
}

//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd);
  mySerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

  digitalWrite(ledPin, LOW);
}
