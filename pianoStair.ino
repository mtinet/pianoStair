
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
const int CdsPin4 = A3;
const int CdsPin5 = A4;
const int CdsPin6 = A5;
const int CdsPin7 = A8;
const int CdsPin8 = A9;
const int CdsPin9 = A10;
const int CdsPin10 = A11;
const int CdsPin11 = A12;
const int CdsPin12 = A13;

int br1;  // 버튼1 상태 확인용 입력값 임시저장용
int br2;  // 이하, 위와 유사
int br3;
int br4;
int br5;
int br6;
int br7;
int br8;
int br9;
int br10;
int br11;
int br12;


int bn1 = 60; //버튼1의  note(음계)  가령 "도"  0~127까지 지정가능 (정확한 음계 설정은 MIDI관련정보참고)
int bn2 = 62; //버튼2의  note(음계)  가령 "레"
int bn3 = 64; //버튼3의  note(음계)  가령 "미"
int bn4 = 65; //버튼4의  note(음계)  가령 "파"
int bn5 = 67; //버튼5의  note(음계)  가령 "솔"
int bn6 = 69; //버튼6의  note(음계)  가령 "라"
int bn7 = 71; //버튼7의  note(음계)  가령 "시"
int bn8 = 72; //버튼8의  note(음계)  가령 "도~"

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
}


void loop() {
  
  talkMIDI(0xC0, instrument, 0);
  
  br1 = analogRead(CdsPin1);
  br2 = analogRead(CdsPin2);
  br3 = analogRead(CdsPin3);
  br4 = analogRead(CdsPin4);
  br5 = analogRead(CdsPin5);
  br6 = analogRead(CdsPin6);
  br7 = analogRead(CdsPin7);
  br8 = analogRead(CdsPin8);
  br9 = analogRead(CdsPin9);
  br10 = analogRead(CdsPin10);
  br11 = analogRead(CdsPin11);
  br12 = analogRead(CdsPin12);

  buttonState = digitalRead(button);

  Serial.print(br1);
  Serial.print(" ");
  Serial.print(br2);
  Serial.print(" ");  
  Serial.print(br3);
  Serial.print(" ");
  Serial.print(br4);
  Serial.print(" ");
    Serial.print(br5);
  Serial.print(" ");
    Serial.print(br6);
  Serial.print(" ");
    Serial.print(br7);
  Serial.print(" ");
    Serial.print(br8);
  Serial.print(" ");
    Serial.print(br9);
  Serial.print(" ");
    Serial.print(br10);
  Serial.print(" ");
    Serial.print(br11);
  Serial.print(" ");
    Serial.print(br12);
      Serial.print(" ");
    Serial.println(buttonState);

    
//   if( !bs1 && !br1 ){
//     noteOn(0, bn1,100);
//     bs1 = true;
//   }else if(bs1 && br1){
//     noteOff(0, bn1,0);   
//     bs1 = false;
//   }
//   if( !bs2 && !br2 ){
//     noteOn(0, bn2,100);
//     bs2 = true;
//   }else if(bs2 && br2){
//     noteOff(0, bn2,0);   
//
//     bs2 = false;
//   }   
//   if( !bs3 && !br3 ){
//     noteOn(0, bn3,100);
//     bs3 = true;
//   }else if(bs3 && br3){
//     noteOff(0, bn3,0);   
//     bs3 = false;
//   }
//   if( !bs4 && !br4 ){
//     noteOn(0, bn4,100);
//     bs4 = true;
//   }else if(bs4 && br4){
//     noteOff(0, bn4,0);   
//     bs4 = false;
//   }
//   
//   if( !bs5 && !br5 ){
//     noteOn(0, bn5,100);
//     bs5 = true;
//   }else if(bs5 && br5){
//     noteOff(0, bn5,0);   
//     bs5 = false;
//   }
//   
//   if( !bs6 && !br6 ){
//     noteOn(0, bn6,100);
//     bs6 = true;
//   }else if(bs6 && br6){
//     noteOff(0, bn6,0);   
//     bs6 = false;
//   }   
//   
//   if( !bs7 && !br7 ){
//     noteOn(0, bn7,100);
//     bs7 = true;
//   }else if(bs7 && br7){
//     noteOff(0, bn7,0);   
//     bs7 = false;
//   }   
//   if( !bs8 && !br8 ){
//     noteOn(0, bn8,100);
//     bs8 = true;
//   }else if(bs8 && br8){
//     noteOff(0, bn8,0);   
//     bs8 = false;
//   }
//   
//
//  //delay(1000);
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
