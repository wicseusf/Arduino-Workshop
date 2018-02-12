/*
 * This program operates a simplistic arduino that makes a customizable smiley face on an arduino board.  
 * The IR remote controls the eyes and the potentiometer controls the smile amount.  
 * By Rachel Klesius
 */

//Globally defined variables go here, anything created or initialized here can be changed in any other function.

//define the classes that you are going to use in your program
#include <IRremote.h>  //IRremote.h is a library that I have added that allows me to use an infrared remote

//define the pins that you are using here so that you can change them quickly
//using the #define allows you to create permanent variables that cannot be changed
#define irSensor 11  //ir sensor reciever
#define leftEye 9   //left eye LED
#define rightEye 8  //right eye LED
#define PM A0      //potentiometer reciever

//value of the potentiometer
int PMvalue = 0;

//potentiometer returns a number between 0 and 1023, separated into 5 sections
int section = 1023/5;

//Array defined for the smile LED's
int smile[4] = {7, 6, 5, 4};

//create an object from the IRremote class for your use
IRrecv irrecv(irSensor);

void setup() {
  pinMode(irSensor, INPUT);
  pinMode(leftEye, OUTPUT);
  pinMode(rightEye, OUTPUT);

  irrecv.enableIRIn(); //start the IR reciever
  
  for (int i = 0; i <= 3; i++)
  {
     pinMode(smile[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //a function inside the IRremote library to decode the results from the IR remote
  decode_results results;

  //for the IR sensor and the eyes of the smile
  if (irrecv.decode(&results))  //if results are recieved 
  {
    if (results.value == 0xFFA25D)  //if the results value is the code associated with 1 on the remote
    {
      digitalWrite(leftEye, HIGH);
      digitalWrite(rightEye, LOW);
    }
    if (results.value == 0xFF629D) //if the results value is the code associated with 2 on the remote
    {
      digitalWrite(rightEye, HIGH);
      digitalWrite(leftEye, LOW);
    }
    if (results.value == 0xFFE21D)  //3 turns both of the eyes on
    {
      digitalWrite(leftEye, HIGH);
      digitalWrite(rightEye, HIGH);
    }
    if (results.value == 0xFF22DD)  //4 turns both of the eyes off
    {
      digitalWrite(leftEye, LOW);
      digitalWrite(rightEye, LOW);
    }
    irrecv.resume();  //prepare for next value
  }

  //for the potentiometer and the mouth
  PMvalue = analogRead(PM);  //analog read will read in a value between 0 and 1023, based on the potentiometer
  
  if(PMvalue <= section)  //first 5th of the potentiometer, all lights off
  {
    for(int i = 0; i <= 3; i++)
    {
      digitalWrite(smile[i], LOW);
    }
  }
  
  if((PMvalue > section) && (PMvalue <= section * 2)) //second 5th of the potentiometer, first light on
  {
    digitalWrite(smile[0], HIGH);
    digitalWrite(smile[1], LOW);
    digitalWrite(smile[2], LOW);
    digitalWrite(smile[3], LOW);
  }
  
  if((PMvalue > section * 2) && (PMvalue <= section * 3)) //third 5th of the potentiometer, first light on
  {
    digitalWrite(smile[0], HIGH);
    digitalWrite(smile[1], HIGH);
    digitalWrite(smile[2], LOW);
    digitalWrite(smile[3], LOW);
  }

  if((PMvalue > section * 3) && (PMvalue <= section * 4)) //fourth 5th of the potentiometer, first light on
  {
    digitalWrite(smile[0], HIGH);
    digitalWrite(smile[1], HIGH);
    digitalWrite(smile[2], HIGH);
    digitalWrite(smile[3], LOW);
  }

  if((PMvalue > section * 4) && (PMvalue <= section * 5))  //fifth 5th of the potentiometer, all lights off
  {
    for(int i = 0; i <= 3; i++)
    {
      digitalWrite(smile[i], HIGH);
    }
  }  
}
