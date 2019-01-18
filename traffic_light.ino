#define F1 22
#define G1 23
#define A1 24
#include <avr/interrupt.h>
#include "LedControl.h"
#include "binary.h"
#define B1 25
#define COM1 26
#define COM2 27
#define F2 28
#define A2 29
#define B2 30
#define E1 31
#define D1 32
#define C1 33
#define E2 34
#define D2 35
#define G2 36
#define C2 37

LedControl lc=LedControl(12,11,10,1);
// happy face
byte hf[8]= {B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};
// sad face
byte sf[8]= {B00111100,B01000010,B10100101,B10000001,B10011001,B10100101,B01000010,B00111100};

volatile int currentColor = 1; //0 -red, 1 -green
volatile int currentState = 1; //0 - red for pedestrians, 1 button Pressed
volatile int n;

void setup(){
  for(int i=22;i <= 37; i++){
    pinMode(i, OUTPUT); 
  }
  for(int i=4;i<=6;i++){
    pinMode(i, OUTPUT); 
  }

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), buttonPressed, RISING);

  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,8);
  // Clear the display
  lc.clearDisplay(0);

  sadFace();
}

void buttonPressed(){
  currentState = 0; 
  cli(); // disable the global interrupts system in order to setup the timers
  TCCR1A = 0; // SET TCCR1A and B to 0
  TCCR1B = 0;
  // Set the OCR1A with the desired value:
  OCR1A = 15624;
  // Active CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set the prescaler to 1024:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // Enable the Output Compare interrupt (by setting the mask bit)
  TIMSK1 |= (1 << OCIE1A);
  sei(); // enable global interrupts 
}

void loop(){
   green();
   currentColor = 1;
   displayNothing();
   if(currentState == 0){
      n=32;
      countBack();

      currentColor = 0;
      red();
      happyFace();
      n=16;
      countBack();
      currentColor = 1;
      displayNothing();
      currentState = 1;
      sadFace();
    }
}

void writeNumberOnSSD(int n){
  switch(n/10){
    case 0:{
      digitalWrite(G1,0);
      digitalWrite(A1,1);
      digitalWrite(B1,1);
      digitalWrite(C1,1);
      digitalWrite(D1,1);
      digitalWrite(E1,1);
      digitalWrite(F1,1);
      break;
    }
    case 1:{
      digitalWrite(G1,0);
      digitalWrite(A1,0);
      digitalWrite(B1,1);
      digitalWrite(C1,1);
      digitalWrite(D1,0);
      digitalWrite(E1,0);
      digitalWrite(F1,0);
      break;
    }
    case 2:{
      digitalWrite(G1,1);
      digitalWrite(A1,1);
      digitalWrite(B1,1);
      digitalWrite(C1,0);
      digitalWrite(D1,1);
      digitalWrite(E1,1);
      digitalWrite(F1,0);
      break;
    }
    case 3:{
      digitalWrite(G1,1);
      digitalWrite(A1,1);
      digitalWrite(B1,1);
      digitalWrite(C1,1);
      digitalWrite(D1,1);
      digitalWrite(E1,0);
      digitalWrite(F1,0);
      break;
    }
    case 4:{
      digitalWrite(G1,1);
      digitalWrite(A1,0);
      digitalWrite(B1,1);
      digitalWrite(C1,1);
      digitalWrite(D1,0);
      digitalWrite(E1,0);
      digitalWrite(F1,1);
      break;
    }
    case 5:{
      digitalWrite(G1,1);
      digitalWrite(A1,1);
      digitalWrite(B1,0);
      digitalWrite(C1,1);
      digitalWrite(D1,1);
      digitalWrite(E1,0);
      digitalWrite(F1,1);
      break;
    }
    case 6:{
      digitalWrite(G1,1);
      digitalWrite(A1,1);
      digitalWrite(B1,0);
      digitalWrite(C1,1);
      digitalWrite(D1,1);
      digitalWrite(E1,1);
      digitalWrite(F1,1);
      break;
    }
    case 7:{
      digitalWrite(G1,0);
      digitalWrite(A1,1);
      digitalWrite(B1,1);
      digitalWrite(C1,1);
      digitalWrite(D1,0);
      digitalWrite(E1,0);
      digitalWrite(F1,0);
      break;
    }
    case 8:{
      digitalWrite(G1,1);
      digitalWrite(A1,1);
      digitalWrite(B1,1);
      digitalWrite(C1,1);
      digitalWrite(D1,1);
      digitalWrite(E1,1);
      digitalWrite(F1,1);
      break;
    }
    case 9:{
      digitalWrite(G1,1);
      digitalWrite(A1,1);
      digitalWrite(B1,1);
      digitalWrite(C1,1);
      digitalWrite(D1,1);
      digitalWrite(E1,0);
      digitalWrite(F1,1);
      break;
    }
  }

  switch(n%10){
    case 0:{
      digitalWrite(G2,0);
      digitalWrite(A2,1);
      digitalWrite(B2,1);
      digitalWrite(C2,1);
      digitalWrite(D2,1);
      digitalWrite(E2,1);
      digitalWrite(F2,1);
      break;
    }
    case 1:{
      digitalWrite(G2,0);
      digitalWrite(A2,0);
      digitalWrite(B2,1);
      digitalWrite(C2,1);
      digitalWrite(D2,0);
      digitalWrite(E2,0);
      digitalWrite(F2,0);
      break;
    }
    case 2:{
      digitalWrite(G2,1);
      digitalWrite(A2,1);
      digitalWrite(B2,1);
      digitalWrite(C2,0);
      digitalWrite(D2,1);
      digitalWrite(E2,1);
      digitalWrite(F2,0);
      break;
    }
    case 3:{
      digitalWrite(G2,1);
      digitalWrite(A2,1);
      digitalWrite(B2,1);
      digitalWrite(C2,1);
      digitalWrite(D2,1);
      digitalWrite(E2,0);
      digitalWrite(F2,0);
      break;
    }
    case 4:{
      digitalWrite(G2,1);
      digitalWrite(A2,0);
      digitalWrite(B2,1);
      digitalWrite(C2,1);
      digitalWrite(D2,0);
      digitalWrite(E2,0);
      digitalWrite(F2,1);
      break;
    }
    case 5:{
      digitalWrite(G2,1);
      digitalWrite(A2,1);
      digitalWrite(B2,0);
      digitalWrite(C2,1);
      digitalWrite(D2,1);
      digitalWrite(E2,0);
      digitalWrite(F2,1);
      break;
    }
    case 6:{
      digitalWrite(G2,1);
      digitalWrite(A2,1);
      digitalWrite(B2,0);
      digitalWrite(C2,1);
      digitalWrite(D2,1);
      digitalWrite(E2,1);
      digitalWrite(F2,1);
      break;
    }
    case 7:{
      digitalWrite(G2,0);
      digitalWrite(A2,1);
      digitalWrite(B2,1);
      digitalWrite(C2,1);
      digitalWrite(D2,0);
      digitalWrite(E2,0);
      digitalWrite(F2,0);
      break;
    }
    case 8:{
      digitalWrite(G2,1);
      digitalWrite(A2,1);
      digitalWrite(B2,1);
      digitalWrite(C2,1);
      digitalWrite(D2,1);
      digitalWrite(E2,1);
      digitalWrite(F2,1);
      break;
    }
    case 9:{
      digitalWrite(G2,1);
      digitalWrite(A2,1);
      digitalWrite(B2,1);
      digitalWrite(C2,1);
      digitalWrite(D2,1);
      digitalWrite(E2,0);
      digitalWrite(F2,1);
      break;
    }
  }
}
void countBack(){
  while(n >= 0){
      writeNumberOnSSD(n);
      if(currentColor == 1 && n==4) yellow();
  }
}

void displayNothing(){
  digitalWrite(G1, 1);
  digitalWrite(G2, 1);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(B1, 0);
  digitalWrite(B2, 0);
  digitalWrite(C1, 0);
  digitalWrite(C2, 0);
  digitalWrite(D1, 0);
  digitalWrite(D2, 0);
  digitalWrite(E1, 0);
  digitalWrite(E2, 0);
  digitalWrite(F1, 0);
  digitalWrite(F2, 0);
}

void happyFace(){
  lc.setRow(0,0,hf[0]);
  lc.setRow(0,1,hf[1]);
  lc.setRow(0,2,hf[2]);
  lc.setRow(0,3,hf[3]);
  lc.setRow(0,4,hf[4]);
  lc.setRow(0,5,hf[5]);
  lc.setRow(0,6,hf[6]);
  lc.setRow(0,7,hf[7]);
}

void sadFace(){
  lc.setRow(0,0,sf[0]);
  lc.setRow(0,1,sf[1]);
  lc.setRow(0,2,sf[2]);
  lc.setRow(0,3,sf[3]);
  lc.setRow(0,4,sf[4]);
  lc.setRow(0,5,sf[5]);
  lc.setRow(0,6,sf[6]);
  lc.setRow(0,7,sf[7]);
}

void red(){
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void yellow(){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void green(){
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

ISR(TIMER1_COMPA_vect)
{
 if(n>=0) n--;
} 
