#include <SoftwareSerial.h>     //loads program for software serial
#include <Servo.h>              //loads object to control servo motor
#include "Adafruit_Soundboard.h"//loads program for soundboard
#define SFX_TX 52               //defines pin 52 as transmit to soundboard
#define SFX_RX 53               //defines pin 53 as receive from soundboard
#define SFX_RST 30              //defines pin 30 as the reset pin
#include "Adafruit_TLC5947.h"   //loads program for 24 channel PWM module
#define NUM_TLC5974 1           //defines the number of PWM modules used
#define data   22               //arduino port that sends data to PWM module
#define clock   24              //arduino port that synchronizes time w PWM
#define latch   26              //arduino port that help PWM module
int fadeSpeed = 30;             //value changes fade speed 1<x<1000 (lower is slower)
int fadeSpeedA = 2;             //value changes fade speed 1<x<50 (lower is slower)
int fadeSpeedA2 = 20;           //value changes fade speed 1<x<50 (lower is slower)
int fadeSpeedA3 = 1;            //value changes fade speed 1<x<50 (lower is slower)

//defines names for PWM channels
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);
Servo larva, wormanL, wormanC, worme, back, intermission, robroom, robball;

int welcome = 0,  lobby = 1,  checkIn = 2,  juice = 3,  announce = 4, ball = 5, GStoCB = 6, MBtoMS = 7,
    ROtoMM = 8,   r2H = 9,    r2A = 10,     r2B = 11,   r2C = 12,     r2D = 13, r3H = 14,   r3A = 15,
    r3B = 16,     r3C = 17,   r3D = 47,     r4H = 31,   r4A = 19,     r4B = 21, r4C = 22,   r4D = 23,
    s1CI = 2,     s1JW = 3,   s1L = 4,      sI3 = 5,    BF2 = 35,     AF2 = 33,  TL = 8,     G3 = 9,
    s4B = 10,     s4A = 11,   EL = 12,      s3A = 7,   AF3 = 38,     CF2 = 42, AF4 = 43,   EL1 = 36,
    DF2 = 37,     s1R = 6;   

Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5974, clock, data, latch); //renames PWM module to "tlc"

void setup() {   
  tlc.begin();                    //initializes PWM device
  boolean begin(void);            //initializes PWM device
  pinMode(G3,OUTPUT),   pinMode(TL, OUTPUT),  pinMode(EL, OUTPUT),  pinMode(12, OUTPUT),
  pinMode(AF3, OUTPUT), pinMode(AF4, OUTPUT), pinMode(AF2, OUTPUT), pinMode(BF2, OUTPUT),
  pinMode(CF2, OUTPUT), pinMode(DF2, OUTPUT), pinMode(r3D, OUTPUT), pinMode(r4H, OUTPUT);
  ss.begin(9600);                 // softwareserial at 9600 baud
}

void loop() {                     //main project code goes here
  turnOff(r2A);                   //turn off Player 1s room to remind Arduino I'm in charge
  digitalWrite(r3D, HIGH);        //turn off WormyWorld (reversed)
  digitalWrite(r4H, HIGH);        //turn off 4H lights (reversed)
  sfx.reset();                    //resert SFX board
  hideCheck();                    //hide Check In
  hideLobby();                    //hide lobby
  hideBack();                     //hide Backscratcher
  hideLarva();                    //hide Larva
  moveRobBall(0);                 //move Rob Ball to 0
  moveRobRoom(0);                 //move Rob Room to 0
  fadeIn2A(EL, TL);               //fade in Top Light and Extendo Light  
  delay(60000);
  sfx.playTrack((uint8_t)00);      //play audio track 00
  delay(5000);
  showLobby();                    //show Worman Bates at front lobbyd
  fadeIn(welcome);                //fade in welcome lights
  delay(3000);
  fadeIn(lobby);                  //fade in lobby
  delay(10000);
  lightShow();                    
  lightShow();
  delay(4000);
  hideLobby();                    //Worman leaves lobby
  crossFade21(lobby, welcome, checkIn);
  turnOff(welcome);       
  delay(3000);
  showCheck();                    //show Worman at checkin
  delay(3000);
  moveCheck(180);                  //Worman motion
  delay(3000);
  moveCheck(170);                  //Worman motion
  delay(3000);
  moveCheck(175);                  //Worman motion
  delay(5000);
  moveCheck(180);                  //Worman motion
  delay(2000);
  moveCheck(170);                  //Worman motion
  delay(4000);
  moveCheck(180);                  //Worman motion
  delay(2000);
  moveCheck(170);                  //Worman motion
  delay(5000);
  moveCheck(180);                  //Worman motion
  hideCheck();                    //hide Checkin
  crossFade(checkIn, juice);      //fade from checkin to Juicy Worm Cafe
  delay(6500);                    //6800
  //sfx.playTrack((uint8_t)1);    //play audio track 01
  delay(6000);
  showLarva();                    //show Larva
  delay(2000);
  moveLarva(165);                 //Larva motion
  delay(1000);
  moveLarva(160);                 //Larva motion
  delay(4000);
  moveLarva(165);                 //Larva motion
  delay(1000);
  moveLarva(170);                 //Larva motion
  delay(3000);
  moveLarva(165);                 //Larva motion
  delay(4000);
  moveLarva(175);                 //Larva motion
  delay(19400);                   //19700
  //sfx.playTrack((uint8_t)02);   //play audio track 02
  delay(1000);
  crossFade15(juice, announce, GStoCB, ROtoMM, MBtoMS, ball);   //crossfade Juicy Worm to Ballroom lights
  hideLarva();                    //hide Larva
  delay(2000);
  dim4(GStoCB, ROtoMM, MBtoMS, ball);           //spot on announce
  delay(7000);
  undim4(GStoCB, ROtoMM, MBtoMS, ball);         //spot off announce
  delay(4000);
  dim4(ROtoMM, MBtoMS, ball, announce);         //spot on General and Captain
  delay(26000);
  undim4(ROtoMM, MBtoMS, ball, announce);       //spot off General and Captain
  delay(1200);                                  //1500
  moveRobBall(180);
  dim4(GStoCB, MBtoMS, ball, announce);         //spot on Rob and Madame
  delay(3800);                                  //3500
  moveRobBall(90);
  delay(500);                                   //800
  //sfx.playTrack((uint8_t)03);                 //play audio track 03  
  moveRobBall(50);
  delay(3000);
  moveRobBall(100);
  delay(2000);
  moveRobBall(20);
  delay(4000);
  moveRobBall(180);
  delay(6000);
  moveRobBall(100);
  delay(2000);
  moveRobBall(20);
  crossFadeDim(ROtoMM, MBtoMS);                 //switch Rob to Monsieur
  delay(24000);
  crossFadeDim(MBtoMS, announce);               //switch Monsieur to announce
  delay(4000);
  undim4(GStoCB, ROtoMM, MBtoMS, ball);         //spot off announce
  delay(4200);                                  //4500
  //sfx.playTrack((uint8_t)04);                 //play audio track 04
  turnOn(ROtoMM), turnOn(announce), turnOn(ball), turnOn(MBtoMS), turnOn(GStoCB);  //DELETE LATER
  delay(10500);                    //11000
  digitalWrite(EL1, HIGH);         //turn on elevator light
  turnOff(ROtoMM), turnOff(announce), turnOff(ball), turnOff(MBtoMS), turnOff(GStoCB);
  delay(6500);                     //6000
  digitalWrite(EL1, LOW);          //turn off elevator light
  delay(2000);
  fadeIn(r2H);                     //fade in Hallway 2
  delay(875);
  turnOn(r2A);                     //turn on Player 1 lights
  digitalWrite(AF2, HIGH);         //turn on Player 1 fan
  delay(22000);
  digitalWrite(AF2, LOW);          //turn off Player 1 fan
  crossFade21(r2H, r2A, r2B);      //crossfade from Player 1 room and Hallway 1 to Monsieur's room
  digitalWrite(BF2, HIGH);         //turn on Monsieur's fan
  delay(8000);                     //8300
  //sfx.playTrack((uint8_t)05);    //play audio track 05
  delay(34000);
  crossFade(r2B, r2H);             //crossfade Monsieur to Hallway 2
  delay(22000);                    //22200
  //sfx.playTrack((uint8_t)06);    //play audio track 06
  crossFade(r2H, r2C);             //crossfade Hallway 2 to Captain
  digitalWrite(CF2, HIGH);         //turn on Captain's fan
  delay(52000);
  crossFade(r2C, r2D);             //crossfade Captain to General
  digitalWrite(CF2, LOW);          //turn off Captain's fan
  digitalWrite(DF2, HIGH);         //turn on General's fan
  delay(6500);                     //6800
  //sfx.playTrack((uint8_t)07);    //play audio track 07
  delay(31000);
  fadeDip(r2D);                    //dip lights for ghost
  delay(11800);                    //12000
  //sfx.playTrack((uint8_t)8);     //play audio track 08
  delay(8000);
  fadeOut(r2D);                    //fade out General's lights
  delay(1500);
  digitalWrite(r3D, LOW);         //turn on Wormy World Intermission (reversed)
  wormyWorld();                   //rotate concession stand
  delay(500);
  wormyWorld();                   //rotate concession stand     
  delay(500);
  wormyWorld();                   //rotate concession stand
  delay(500);
  wormyWorld();                   //rotate concession stand
  delay(500);
  wormyWorld();                   //rotate concession stand
  delay(2500);
  digitalWrite(r3D, HIGH);        //turn off Wormy World Intermission (reversed)
  delay(5700);
  fadeInDim(r3C);                 //fade in Madame's lights to dim setting
  //sfx.playTrack((uint8_t)9);    //play audio track 09
  delay(46000);
  fadeInFull(r3C);                //fade in Madam's lights from dim to full
  delay(14300);                   //14500
  //sfx.playTrack((uint8_t)10);   //play audio track 10
  delay(7500);
  crossFade(r3C, r3H);            //crossfade Madame to Hallway 3
  delay(2500);
  crossFade(r3H, r3B);            //crossfade Hallway 3 to Mis Speling
  delay(6000);
  fadeDip(r3B);                   //dip for ghost
  delay(6000);
  fadeDip(r3B);                   //dip for ghost
  delay(1000);
  fadeDipOut(r3B);                //dip to off to reveal ghost
  fadeInA(G3);                    //fade in Ghost
  fadeGhostA(G3);                 //light slow oscillate for ghost
  fadeGhostA(G3);                 //light slow oscillate for ghost
  fadeGhostA(G3);                 //light slow oscillate for ghost
  delay(1000);
  fadeDipA(G3);                   //dip ghost for effect
  fadeGhostA(G3);                 //light slow oscillate for ghost
  fadeDipA(G3);                   //dip ghost for effect
  delay(17700);                   //17900
  //sfx.playTrack((uint8_t)11);   //play audio track 11
  delay(1000);
  fadeDipA(G3);                   //dip ghost for exit
  fadeDipA(G3);                   //dip ghost for exit
  fadeDipA(G3);                   //dip ghost for exit
  fadeOutA(G3);                   //dip ghost for exit
  delay(5000);
  digitalWrite(AF3, HIGH);        //turn on Rob's fan
  fadeSpeed = 15;                 //slow fade speed
  fadeIn(r3A);                    //fade in Rob's lights
  fadeSpeed = 30;                 //return fade speed to 3-
  digitalWrite(AF3, LOW);         //turn off Rob's fan
  moveRobRoom(90);                //move Rob's arm
  delay(1000);
  blink(r3A);                     //blink Rob's lights
  delay(5000);
  moveRobRoom(30);                //move Rob's arm
  digitalWrite(AF3, HIGH);        //turn off Rob's fan
  delay(1000);
  blink(r3A);                     //blink Rob's lights
  moveRobRoom(0);                 //move Rob's arm
  digitalWrite(AF3, LOW);         //turn off Rob's fan
  delay(2000);
  blink(r3A);                     //blink Rob's lights
  delay(2000);
  moveRobRoom(180);               //move Rob's arm
  delay(1000);
  digitalWrite(AF3, HIGH);        //turn on Rob's fan
  delay(1000);
  digitalWrite(AF3, LOW);         //turn off Rob's fan
  delay(2000);
  blink(r3A);                     //blink Rob's lights
  delay(2000);
  moveRobRoom(80);                //move Rob's arm
  delay(1000);
  digitalWrite(AF3, HIGH);        //turn on Rob's fan
  delay(1000);
  digitalWrite(AF3, LOW);         //turn off Rob's fan
  blink(r3A);                     //blink Rob's lights
  delay(2000);
  moveRobRoom(90);                //move Rob's arm
  delay(1000);
  blink(r3A);                     //blink Rob's lights
  delay(5000);
  moveRobRoom(30);                //move Rob's arm
  digitalWrite(AF3, HIGH);        //turn off Rob's fan
  delay(1000);
  blink(r3A);                     //blink Rob's lights
  moveRobRoom(0);                 //move Rob's arm
  digitalWrite(AF3, LOW);         //turn off Rob's fan
  delay(2000);
  blink(r3A);                     //blink Rob's lights
  delay(3000);
  digitalWrite(AF4, HIGH);        //turn on Worman's fan
  crossFade(r3A, r4A);            //cross fade Rob to Worman
  delay(1000);
  delay(1800);                    //2000
  //sfx.playTrack((uint8_t)12);   //play audio track 12
  delay(9000);
  showWorme();                    //show Mr. Worme
  delay(17000); 
  fadeOut(r4A);                   //fade out Worman lights
  digitalWrite(AF4, LOW);         //turn off Worman's fan
  delay(1000);
  hideWorme();                    //hide Mr. Worme
  delay(7000);
  fadeIn(r4B);                    //fade in Worme lights
  delay(9300);                    //9500
  //sfx.playTrack((uint8_t)13);   //play audio track 13
  delay(30550); 
  fadeDip(r4B);                   //fade dip for ghost
  delay(1200);
  fadeDip(r4B);                   //fade dip for ghost
  delay(19500);
  fadeDip(r4B);                   //fade dip for ghost
  fadeDip(r4B);                   //fade dip for ghost
  delay(19000);
  showBack();                     //show backscratcher
  delay(12800);                   //13000
  //sfx.playTrack((uint8_t)14);   //play audio track 14
  delay(2000);
  fadeOutSlow(r4B);               //fade out Worme's room
  fadeIn(r4C);                    //fade in Credits
  delay(10000);
  fadeIn(r4D);                    //fade in Utility room
  delay(10000);
  turnOn(r4A);                    //turn on Worman's lights
  digitalWrite(AF4, HIGH);        //turn on Worman's fan
  turnOn(r4B);
  digitalWrite(r4H, LOW);         //turn on Hallway 4 (reversed)
  digitalWrite(r3D, LOW);         //turn on Wormy World Intermission (reversed)
  turnOn(r3C);                    //turn on Madame's lights
  turnOn(r3H);                    //turn on Hallway 3
  turnOn(r3B);                    //turn on Mis Speling's lights
  turnOn(r3A);                    //turn on Rob Ottic's lights
  digitalWrite(AF3, HIGH);        //turn on Rob Ottic's fan
  turnOn(r2A);
  digitalWrite(AF2, HIGH);        //turn on Player 1s fan
  turnOn(r2B);
  digitalWrite(BF2, HIGH);        //turn on Monsieur's fan
  turnOn(r2H);
  digitalWrite(CF2, HIGH);        //turn on Captain's fan
  turnOn(r2C);
  digitalWrite(DF2, HIGH);        //turn on General's fan
  turnOn(r2D);
  turnOn(ROtoMM);                 //turn on all ballroom lights
  turnOn(announce),
  turnOn(ball);
  turnOn(MBtoMS);
  turnOn(GStoCB);
  turnOn(welcome);                //turn on Welcome
  turnOn(lobby);                  //turn on Lobby
  turnOn(checkIn);                //turn on Checkin
  turnOn(juice);                  //turn on Juicy Worm
  wormyWorld();                   //rotate Wormy World concession stand
  wormyWorld();                   //rotate Wormy World concession stand
  wormyWorld();                   //rotate Wormy World concession stand
  digitalWrite(AF2, LOW);         //turn off Player 1s fan
  digitalWrite(BF2, LOW);         //turn off Monsieur's fan
  digitalWrite(CF2, LOW);         //turn off Captain's fan
  digitalWrite(DF2, LOW);         //turn off General's fan
  digitalWrite(AF3, LOW);         //turn off Rob's fan
  digitalWrite(AF4, LOW);         //turn off Worman's fan
  fadeOutAll();                   //fadeOutAll
  digitalWrite(r3D, HIGH);        //turn off Intermission (reversed)
  digitalWrite(r4H, HIGH);        //turn off Hallway 4 (reversed)
  fadeOutA2(TL, EL);
  hideBack();                     //hide backscratcher
  moveRobBall(0);                 //return rob ball to starting position
  delay(600000);
}

//fade in 1 circuit from Arduino
void fadeInA(int r) {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += fadeSpeedA) {
    analogWrite (r, fadeValue);
    delay(20);
  }
}

//fade in 2 circuits from Arduino
void fadeIn2A(int r, int r1) {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += fadeSpeedA) {
    analogWrite (r, fadeValue);
    analogWrite (r1, fadeValue);
    delay(20);
  }
}

//fade out 1 circuit from Arduino
void fadeOutA(int r) {
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= fadeSpeedA) {
    analogWrite (r, fadeValue);
    delay(20);
  }
    analogWrite (r, 0);
}

//fade out 2 circuits from Arduino
void fadeOutA2(int r1, int r2) {
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= fadeSpeedA) {
    analogWrite (r1, fadeValue);
    analogWrite (r2, fadeValue);
    delay(20);
  }
    analogWrite (r1, 0);
    analogWrite (r2, 0);
}
//blink 1 circuit
void blink(int r1) {            
    tlc.setPWM (r1, 0);
    tlc.write();
    delay(50);
    tlc.setPWM (r1, 4095);
    tlc.write();
    delay(50);
    tlc.setPWM (r1, 0);
    tlc.write();
    delay(50);
    tlc.setPWM (r1, 4095);
    tlc.write();
    delay(50);
}

//fade in 1 circuit
void fadeIn(int r1) {            
  for (int fadeValue = 0 ; fadeValue <= 4095; fadeValue += fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
}

//fade in 2 circuits
void fadeIn2(int r1, int r2) {     
  for (int fadeValue = 0 ; fadeValue <= 4095; fadeValue += fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.write();
    delay(10);
  }
}

//fade in 3 circuits
void fadeIn3(int r1, int r2, int r3) {     
  for (int fadeValue = 0 ; fadeValue <= 4095; fadeValue += fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, fadeValue);
    tlc.write();
    delay(10);
  }
}

//fade in 4 circuits
void fadeIn4(int r1, int r2, int r3, int r4) {     
  for (int fadeValue = 0 ; fadeValue <= 4095; fadeValue += fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, fadeValue);
    tlc.setPWM (r4, fadeValue);
    tlc.write();
    delay(10);
  }
}

//fade in 5 circuits
void fadeIn5(int r1, int r2, int r3, int r4, int r5) {     
  for (int fadeValue = 0 ; fadeValue <= 4095; fadeValue += fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, fadeValue);
    tlc.setPWM (r4, fadeValue);
    tlc.setPWM (r5, fadeValue);
    tlc.write();
    delay(10);
  }
}

//fade in 1 circuit dim
void fadeInDim(int r1) {            
  for (int fadeValue = 0 ; fadeValue <= 500; fadeValue += fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
}

//fade in 1 circuit from dim to full
void fadeInFull(int r1) {            
  for (int fadeValue = 500 ; fadeValue <= 4095; fadeValue += fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
}

//fade out 1 circuit
void fadeOut(int r1) {           
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
tlc.setPWM (r1, 0);
tlc.write();
}

//fade out 1 circuit
void fadeOutSlow(int r1) {           
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= 10) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(5);
  }
tlc.setPWM (r1, 0);
tlc.write();
}

//fade dip for ghost
void fadeDip(int r1) {           
  for (int fadeValue = 4095 ; fadeValue >= 1000; fadeValue -= 300) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
  for (int fadeValue = 1000 ; fadeValue <= 4095; fadeValue += 300) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
   for (int fadeValue = 4095 ; fadeValue >= 1000; fadeValue -= 300) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
  for (int fadeValue = 1000 ; fadeValue <= 4095; fadeValue += 300) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
tlc.setPWM (r1, 4095);
tlc.write();
}


//fade dip stay dim for ghost
void fadeDipOut(int r1) {           
  for (int fadeValue = 4095 ; fadeValue >= 1000; fadeValue -= 300) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
  for (int fadeValue = 1000 ; fadeValue <= 4095; fadeValue += 300) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
   for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= 300) {
    tlc.setPWM (r1, fadeValue);
    tlc.write();
    delay(10);
  }
  
tlc.setPWM (r1, 0);
tlc.write();
}

//fade dip for ghost
void fadeDipA(int r) {   
  for (int fadeValue = 255 ; fadeValue >= 100; fadeValue -= fadeSpeedA2) {
    analogWrite (r, fadeValue);
    delay(20);
  }
    analogWrite (r, 0);

  for (int fadeValue = 100 ; fadeValue <= 255; fadeValue += fadeSpeedA2) {
    analogWrite (r, fadeValue);
    delay(20);
  }
  for (int fadeValue = 255 ; fadeValue >= 100; fadeValue -= fadeSpeedA2) {
    analogWrite (r, fadeValue);
    delay(20);
  }
    analogWrite (r, 0);

  for (int fadeValue = 100 ; fadeValue <= 255; fadeValue += fadeSpeedA2) {
    analogWrite (r, fadeValue);
    delay(20);
  }
}

//fade slop dip for ghost
void fadeGhostA(int r) {   
  for (int fadeValue = 255 ; fadeValue >= 100; fadeValue -= fadeSpeedA3) {
    analogWrite (r, fadeValue);
    delay(15);
  }
    analogWrite (r, 0);

  for (int fadeValue = 100 ; fadeValue <= 255; fadeValue += fadeSpeedA3) {
    analogWrite (r, fadeValue);
    delay(15);
  }
}

//fade out 2 circuits
void fadeOut2(int r1, int r2) {           
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.write();
    delay(10);
  }
tlc.setPWM (r1, 0);
tlc.setPWM (r2, 0);
tlc.write();
}

//fade out 3 circuits
void fadeOut3(int r1, int r2, int r3) {           
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, fadeValue);
    tlc.write();
    delay(10);
  }
tlc.setPWM (r1, 0);
tlc.setPWM (r2, 0);
tlc.setPWM (r3, 0);
tlc.write();
}

//fade out 4 circuits
void fadeOut4(int r1, int r2, int r3, int r4) {           
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, fadeValue);
    tlc.setPWM (r4, fadeValue);
    tlc.write();
    delay(10);
  }
tlc.setPWM (r1, 0);
tlc.setPWM (r2, 0);
tlc.setPWM (r3, 0);
tlc.setPWM (r4, 0);
tlc.write();
}

//fade out 5 circuits
void fadeOut5(int r1, int r2, int r3, int r4, int r5) {           
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, fadeValue);
    tlc.setPWM (r4, fadeValue);
    tlc.setPWM (r5, fadeValue);
    tlc.write();
    delay(10);
  }
tlc.setPWM (r1, 0);
tlc.setPWM (r2, 0);
tlc.setPWM (r3, 0);
tlc.setPWM (r4, 0);
tlc.setPWM (r5, 0);
tlc.write();
}

//fade out all circuits
void fadeOutAll() {           
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= 10) {
    tlc.setPWM (welcome, fadeValue);
    tlc.setPWM (lobby, fadeValue);
    tlc.setPWM (juice, fadeValue);
    tlc.setPWM (checkIn, fadeValue);
    tlc.setPWM (announce, fadeValue);
    tlc.setPWM (ball, fadeValue);
    tlc.setPWM (ROtoMM, fadeValue);
    tlc.setPWM (MBtoMS, fadeValue);
    tlc.setPWM (GStoCB, fadeValue);
    tlc.setPWM (r2A, fadeValue);
    tlc.setPWM (r2B, fadeValue);
    tlc.setPWM (r2C, fadeValue);
    tlc.setPWM (r2H, fadeValue);
    tlc.setPWM (r2D, fadeValue);
    tlc.setPWM (r3A, fadeValue);
    tlc.setPWM (r3B, fadeValue);
    tlc.setPWM (r3C, fadeValue);
    tlc.setPWM (r3H, fadeValue);
    tlc.setPWM (r4A, fadeValue);
    tlc.setPWM (r4B, fadeValue);
    tlc.setPWM (r4C, fadeValue);
    tlc.setPWM (r4D, fadeValue);
    tlc.write();
    delay(10);

  }
tlc.setPWM (welcome, 0);
tlc.setPWM (lobby, 0);
tlc.setPWM (checkIn, 0);
tlc.setPWM (announce, 0);
tlc.setPWM (ball, 0);
tlc.setPWM (ROtoMM, 0);
tlc.setPWM (MBtoMS, 0);
tlc.setPWM (GStoCB, 0);
tlc.setPWM (r2A, 0);
tlc.setPWM (r2B, 0);
tlc.setPWM (r2C, 0);
tlc.setPWM (r2H, 0);
tlc.setPWM (r2D, 0);
tlc.setPWM (r3A, 0);
tlc.setPWM (r3B, 0);
tlc.setPWM (r3C, 0);
tlc.setPWM (r3H, 0);
tlc.setPWM (r4A, 0);
tlc.setPWM (r4B, 0);
tlc.setPWM (r4C, 0);
tlc.setPWM (r4D, 0);
tlc.write();
}

//cross fade between two circuits
void crossFade(int r1, int r2) {    
   for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, 4095-fadeValue);
    tlc.write();
    delay(10);
  }
  tlc.setPWM (r1, 0);
  tlc.setPWM (r2, 4095);
  tlc.write(); 
}

//cross fade leaving dim behind
void crossFadeDim(int r1, int r2) {
  for (int fadeValue = 4095 ; fadeValue >= 250; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, 4095-fadeValue);
    tlc.write();
    delay(10);
  }
  tlc.setPWM (r1, 250);
  tlc.setPWM (r2, 4095);
  tlc.write(); 
}

//cross fade from 2 to 1
void crossFade21(int r1, int r2, int r3) {
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, 4095-fadeValue);
    tlc.write();
    delay(10);
  }
  tlc.setPWM (r1, 0);
  tlc.setPWM (r2, 0);
  tlc.setPWM (r3, 4095);
  tlc.write(); 
}

//cross fade from 1 to 5
void crossFade15(int r1, int r2, int r3, int r4, int r5, int r6) {
  for (int fadeValue = 4095 ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, 4095-fadeValue);
    tlc.setPWM (r3, 4095-fadeValue);
    tlc.setPWM (r4, 4095-fadeValue);
    tlc.setPWM (r5, 4095-fadeValue);
    tlc.setPWM (r6, 4095-fadeValue);
    tlc.write();
    delay(10);
  }
  tlc.setPWM (r1, 0);
  tlc.setPWM (r2, 4095);
  tlc.write(); 
}

//dim 4 lights
void dim4 (int r1, int r2, int r3, int r4) {
  for (int fadeValue = 4095 ; fadeValue >= 250; fadeValue -= fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, fadeValue);
    tlc.setPWM (r4, fadeValue);
    tlc.write();
    delay(10);
  }
}

//undim 4 lights
void undim4 (int r1, int r2, int r3, int r4) {
  for (int fadeValue = 250 ; fadeValue <= 4095; fadeValue += fadeSpeed) {
    tlc.setPWM (r1, fadeValue);
    tlc.setPWM (r2, fadeValue);
    tlc.setPWM (r3, fadeValue);
    tlc.setPWM (r4, fadeValue);
    tlc.write();
    delay(10);
  }
}

//turn on PWM light
void turnOn(int r1) {
    tlc.setPWM (r1, 4095);
    tlc.write();
}

void turnOff(int r1) {
    tlc.setPWM (r1, 0);
    tlc.write();
}

void showBack () {          //show backscratcher
    back.attach(s4B);
    back.write(60);
    delay(500);
    back.detach();
}

void hideBack () {          //hide backscratcher
    back.attach(s4B);
    back.write(95);
    delay(500);
    back.detach();
}

void showWorme () {          //show Worme
    back.attach(s4A);
    back.write(10);
    delay(500);
    back.detach();
}

void hideWorme () {          //hide Worme
    worme.attach(s4A);
    worme.write(90);
    delay(500);
    worme.detach();
}

void showLarva () {          //show Larva
    larva.attach(s1JW);
    larva.write(160);
    delay(500);
    larva.detach();
}

void hideLarva () {          //hide Larva
    larva.attach(s1JW);
    larva.write(90);
    delay(500);
    larva.detach();
}
void moveLarva (int r1) {    //move Larva to specific position
    wormanC.attach(s1JW);
    wormanC.write(r1);
    delay(500);
    wormanC.detach();
}
void showLobby () {          //show Lobby
    wormanL.attach(s1L);
    wormanL.write(10);
    delay(500);
    wormanL.detach();
}

void hideLobby () {          //hide Lobby
    wormanL.attach(s1L);
    wormanL.write(90);
    delay(500);
    wormanL.detach();
}

void showCheck () {          //show Check In
    wormanC.attach(s1CI);
    wormanC.write(180);
    delay(500);
    wormanC.detach();
}

void hideCheck () {          //hide Checkin
    wormanC.attach(s1CI);
    wormanC.write(90);
    delay(500);
    wormanC.detach();
}

void moveCheck (int r1) {           //move Checkin to specific position
    wormanC.attach(s1CI);
    wormanC.write(r1);
    delay(500);
    wormanC.detach();
}

void moveRobRoom(int r1) {           //move RobRoom to specific position
    robroom.attach(s3A);
    robroom.write(r1);
    delay(500);
    robroom.detach();
}

void moveRobBall(int r1) {           //move RobBall to specific position
    robball.attach(s1R);
    robball.write(r1);
    delay(500);
    robball.detach();
}

void wormyWorld ()      {
  int pos = 0;                        // variable to store the servo position
  intermission.attach(sI3);
  for (pos = 0; pos <= 200; pos += 1) { // goes from 0 degrees to 180 degrees
    intermission.write(pos);            // tell servo to go to position in variable 'pos'
    delay(15);                          // waits 15ms for the servo to reach the position
  }
  for (pos = 200; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    intermission.write(pos);            // tell servo to go to position in variable 'pos'
    delay(15);                          // waits 15ms for the servo to reach the position
  }
}


void lightShow () {
    int wait = 200;
    turnOff(welcome);
    turnOff(lobby);
    turnOn(checkIn);
    delay(wait);
    turnOff(checkIn);
    turnOn(juice);
    delay(wait);
    turnOff(juice);
    turnOn(ball);
    delay(wait);
    turnOff(ball);
    turnOn(r2A);
    delay(wait);
    turnOff(r2A);
    turnOn(r2B);
    delay(wait);
    turnOff(r2B);
    turnOn(r2H);
    delay(wait);
    turnOff(r2H);
    turnOn(r2C);
    delay(wait);
    turnOff(r2C);
    turnOn(r2D);
    delay(wait);
    turnOff(r2D);
    turnOn(r3D);
    delay(wait);
    turnOff(r3D);
    turnOn(r3C);
    delay(wait);
    turnOff(r3C);
    turnOn(r3H);
    delay(wait);
    turnOff(r3H);
    turnOn(r3B);
    delay(wait);
    turnOff(r3B);
    turnOn(r3A);
    delay(wait);
    turnOff(r3A);
    turnOn(r4A);
    delay(wait);
    turnOff(r4A);
    turnOn(r4B);
    delay(wait);
    turnOff(r4B);
    turnOn(r4H);
    delay(wait);
    turnOff(r4H);
    turnOn(r4C);
    delay(wait);
    turnOff(r4C);
    turnOn(r4D);
    delay(wait);
    turnOff(r4D);
    turnOn(r4A);
    delay(wait);
    turnOff(r4A);
    turnOn(r4B);
    delay(wait);
    turnOff(r4B);
    turnOn(r4H);
    delay(wait);
    turnOff(r4H);
    turnOn(r4C);
    delay(wait);
    turnOff(r4C);
    turnOn(r4D);
    delay(wait);
    turnOff(r4D);
    turnOn(r3A);
    delay(wait);
    turnOff(r3A);
    turnOn(r3B);
    delay(wait);
    turnOff(r3B);
    turnOn(r3H);
    delay(wait);
    turnOff(r3H);
    turnOn(r3C);
    delay(wait);
    turnOff(r3C);
    turnOn(r3D);
    delay(wait);
    turnOff(r3D);
    turnOn(r2A);
    delay(wait);
    turnOff(r2A);
    turnOn(r2B);
    delay(wait);
    turnOff(r2B);
    turnOn(r2C);
    delay(wait);
    turnOff(r2C);
    turnOn(r2H);
    delay(wait);
    turnOff(r2H);
    turnOn(r2C);
    delay(wait);
    turnOff(r2C);
    turnOn(r2D);
    delay(wait);
    turnOff(r2D);
    turnOn(ball);
    delay(wait);
    turnOff(ball);
    turnOn(juice);
    delay(wait);
    turnOff(juice);
    turnOn(checkIn);
    delay(wait);
    turnOff(checkIn);
    turnOn(lobby);
    turnOn(welcome);
    delay(wait);
}
