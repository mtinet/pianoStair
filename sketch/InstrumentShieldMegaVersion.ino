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


int br1_B;  // 버튼1 상태 확인용 입력값 임시저장용
int br2_B;  // 이하, 위와 유사
int br3_B;
int br4_B;
int br5_B;
int br6_B;
int br7_B;
int br8_B;
int br9_B;
int br10_B;
int br11_B;
int br12_B;

int bn1 = 60; //버튼1의  note(음계)  가령 "도"  0~127까지 지정가능 (정확한 음계 설정은 MIDI관련정보참고)
int bn2 = 62; //버튼2의  note(음계)  가령 "레"
int bn3 = 64; //버튼3의  note(음계)  가령 "미"
int bn4 = 65; //버튼4의  note(음계)  가령 "파"
int bn5 = 67; //버튼5의  note(음계)  가령 "솔"
int bn6 = 69; //버튼6의  note(음계)  가령 "라"
int bn7 = 71; //버튼7의  note(음계)  가령 "시"
int bn8 = 72; //버튼8의  note(음계)  가령 "도~"
int bn9 = 74;
int bn10 = 76;
int bn11 = 77;
int bn12 = 79;

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
  br4 = analogRead(CdsPin4);
  br5 = analogRead(CdsPin5);
  br6 = analogRead(CdsPin6);
  br7 = analogRead(CdsPin7);
  br8 = analogRead(CdsPin8);
  br9 = analogRead(CdsPin9);
  br10 = analogRead(CdsPin10);
  br11 = analogRead(CdsPin11);
  br12 = analogRead(CdsPin12);
  
  br1_B = br1;  
  br2_B = br2;  
  br3_B = br3;
  br4_B = br4;
  br5_B = br5;
  br6_B = br6;
  br7_B = br7;
  br8_B = br8;
  br9_B = br9;
  br10_B = br10;
  br11_B = br11;
  br12_B = br12;
  delay(500);

  
  Serial.print(br1_B);
  Serial.print(" ");
  Serial.print(br2_B);
  Serial.print(" ");  
  Serial.print(br3_B);
  Serial.print(" ");
  Serial.print(br4_B);
  Serial.print(" ");
  Serial.print(br5_B);
  Serial.print(" ");
  Serial.print(br6_B);
  Serial.print(" ");
  Serial.print(br7_B);
  Serial.print(" ");
  Serial.print(br8_B);
  Serial.print(" ");
  Serial.print(br9_B);
  Serial.print(" ");
  Serial.print(br10_B);
  Serial.print(" ");
  Serial.print(br11_B);
  Serial.print(" ");
  Serial.print(br12_B);

  
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
   if( br4 < br4_B - 50 ){
     noteOn(0, bn4, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn4, 0); 
     Serial.print("L");  
   }
   if( br5 < br5_B - 50 ){
     noteOn(0, bn5, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn5, 0); 
     Serial.print("L");  
   }
   if( br6 < br6_B - 50 ){
     noteOn(0, bn6, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn6, 0);   
     Serial.print("L");
   }
   if( br7 < br7_B - 50 ){
     noteOn(0, bn7, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn7, 0); 
     Serial.print("L");  
   }
   if( br8 < br8_B - 50 ){
     noteOn(0, bn8, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn8, 0); 
     Serial.print("L");  
   }
   if( br9 < br9_B - 50 ){
     noteOn(0, bn9, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn9, 0); 
     Serial.print("L");  
   }
   if( br10 < br10_B - 50 ){
     noteOn(0, bn10, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn10, 0);
     Serial.print("L");   
   }
   if( br11 < br11_B - 50 ){
     noteOn(0, bn11, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn11, 0);
     Serial.print("L");   
   }
   if( br12 < br12_B - 50 ){
     noteOn(0, bn12, 50);
     Serial.print("H");
   }else{
     noteOff(0, bn12, 0);
     Serial.println("L");   
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
