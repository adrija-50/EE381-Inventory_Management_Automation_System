




// change setup.h to switch between buffered and pixel-by-pixel processing
#include "setup.h"
#include <SoftwareSerial.h>
int timer1;
int timer2;

float Time;

int flag1 = 0;
int flag2 = 0;
int detect=0;
int INFLAG = 0;
int OUTFLAG = 0; 

int totalin = 0;
int totalout = 0;

int RX = 13;
int LED_Processing = 11;
int TX = 8;
 
int ir_s1 = 9;
int ir_s2 = 10;

SoftwareSerial BT(RX, TX); // SRX | STX


void setup() {

  BT.begin(9600);
  BT.println("hola!");
  // This is not necessary and has no effect for ATMEGA based Arduinos.
  // WAVGAT Nano has slower clock rate by default. We want to reset it to maximum speed
  CLKPR = 0x80; // enter clock rate change mode
  CLKPR = 0; // set prescaler to 0. WAVGAT MCU has it 3 by default.

  initializeScreenAndCamera();
  delay(5000);
  processFrame();
  delay(2000);
  
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
}


void loop() {
  
//digitalWrite(LED_Idle, HIGH);
//if(flag1 == 1 && flag2==0 && millis()-timer1> 1000){timer1 = millis(); flag1=0;}
//if(flag2 == 1 && flag1==0 && millis()-timer1> 1000){timer2 = millis(); flag1=0;}
if(digitalRead (ir_s1) == LOW && flag1==0){timer1 = millis(); flag1=1;}

if(digitalRead (ir_s2) == LOW && flag2==0){timer2 = millis(); flag2=1;}

if (flag1==1 && flag2==1){

     detect=1;
     //digitalWrite(LED_Idle, LOW);
     digitalWrite(LED_Processing, HIGH);
     BT.println("PROCESSING");
     
     if(timer1 > timer2){

      OUTFLAG = 0;
      BT.println("IN");
      totalin = totalin + 1;
      
      }
else if(timer2 > timer1)
 {
   OUTFLAG = 1;
   BT.println("OUT");
   totalout = totalout + 1;
  
  }
                      
}

if(detect==0)
 {  
  //Serial.println("Idle");
}
else{
    processFrame();
    if(OUTFLAG == 0)
      {
        BT.print("IN, totalin :");
        BT.println(totalin);
      }
      if(OUTFLAG == 1)
      {
        BT.print("OUT, totalout :");
        BT.println(totalout);
      }
    delay(2000);
    BT.println("DONE!!!!!!");
      
    
    digitalWrite(LED_Processing, LOW);
    delay(2000);
     
   // digitalWrite(buzzer, LOW);
    detect = 0;
    flag1 = 0;
    flag2 = 0;    
 }
}
