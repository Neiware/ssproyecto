#include <Arduino.h>
#include <LiquidCrystal_I2C.h> //library for communication I2C with LCD
//----------------MACROS----------------------//

//---Outputs for Mux---//
#define MUX_A 2 
#define MUX_B 3
#define MUX_C 4
#define MUX_D 5
//---Input for Mux---//
#define MUX_Y 6
//---Modulo SD-------//
#define SD_SCK 13
#define SD_MISO 12
#define SD_MOSI 11
#define SD_CS 10
//---Modulo Bocina---//
#define BOCINA_PWM 9
//---Modulo I2C------//
#define I2C_SDA A4
#define I2C_SCL A5

//----------CREATE OBJEXTS------//
//OBJECT CALL lcd using external library
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  // SETUP I/O FOR MUX
  pinMode(MUX_A,OUTPUT);
  pinMode(MUX_B,OUTPUT);
  pinMode(MUX_C,OUTPUT);
  pinMode(MUX_D,OUTPUT);
  pinMode(MUX_Y,INPUT);
  //inicitialize low
  digitalWrite(MUX_A,LOW);
  digitalWrite(MUX_B,LOW);
  digitalWrite(MUX_C,LOW);
  digitalWrite(MUX_D,LOW);
  // SETUP I2C FOR LCD WITH LIBRARY INCLUDED


//new commento to test branch master

}

void loop() { 
  // put your main code here, to run repeatedly:
}