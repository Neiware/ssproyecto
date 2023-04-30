#include <Arduino.h>
#include <LiquidCrystal_I2C.h> //library for communication I2C with LCD
#include <TMRpcm.h> // library for SD and Speaker communicatios.
#include <SPI.h>
#include <SD.h>
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif


//----------------MACROS----------------------//

//---Outputs for Mux---//
#define MUX_A 2 
#define MUX_B 3
#define MUX_C 4
#define MUX_D 5
//---Input for Mux---//
#define MUX_Y 6
//---Modulo SD-------//
#define SD_ChipSelecPin 10 // Pin 10 is gonna be CS for the SD Module 
#define SD_SCK 13
#define SD_MISO 12
#define SD_MOSI 11
//---Modulo Bocina---//
#define BOCINA_PWM 9

//---Modulo I2C------//
#define I2C_SDA A4
#define I2C_SCL A5
//------------TESTING LCD--------------//
uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {	0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
//----------CREATE OBJEXTS------//
//OBJECT CALL lcd using external library
LiquidCrystal_I2C lcd(0x27,20,4);
TMRpcm Audio; //object for TMRpcm library


//-----------FUNCTIONS--------------//
// display all keycodes
bool Movimiento_Bits(int n);
void LCD_Select();
void Bocina_Select(int n);
void displayKeyCodes(void) {
  uint8_t i = 0;
  while (1) {
    lcd.clear();
    lcd.print("Codes 0x"); lcd.print(i, HEX);
    lcd.print("-0x"); lcd.print(i+15, HEX);
    lcd.setCursor(0, 1);
    for (int j=0; j<16; j++) {
      lcd.printByte(i+j);
    }
    i+=16;
    
    delay(4000);
  }
}


//------------GLOBAL VARIABLES-------------//

void setup() {
  Serial.begin(9600);
   //SETUP SD 
  if (SD.begin(SD_ChipSelecPin)) //check if SD.begin is working. .being return boolean
  {
    Serial.println("Working");
    //YES IS WORKING 
    //Maybe add sound or show response in the LCD
  }else{
    Serial.println("not Working");
    //NOT WORKING 
    //Display Eror to the user and reset the whole program
  }
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
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  lcd.home();

  lcd.print("Hello world...");
  lcd.setCursor(0, 1);
  lcd.print(" i ");
  lcd.printByte(3);
  lcd.print(" arduinos!");
  delay(5000);
  //displayKeyCodes();
  //SETUP SPEAKER
  Audio.speakerPin = BOCINA_PWM; //select pin connected from arduino to speaker 

  Audio.quality(1); // Improve quality of the sound, but i think will consume more power and time for instruction
  Audio.setVolume(5); // Select volume from 0 to 7
  
 
  

  //------------------TEST SD ADN SPEAKER ONLY------------------//
 // Audio.play("Toni.wav"); //Function is to play the file selecting a file
                                      // I still need to get the SD and add files so
                                      //not ready yet

  //Audio.pause();// Method to pause the audio, the delay is to check how this methods works during runtime
//new commento to test branch master

}
int n = 0;

void loop() { 
  // put your main code here, to run repeatedly:
  if(Movimiento_Bits(n)== true){
    LCD_Select();
    Bocina_Select(n);
    delay(500);
  }

    if(n == 15){
    n = 0;
  }else{
    Serial.print("Value of n is ");
    Serial.println(n);

    n++;  
  }
}

bool Movimiento_Bits(int n){
  switch (n)
  {
  case 0:
    digitalWrite(MUX_A,LOW);
    digitalWrite(MUX_B,LOW);
    digitalWrite(MUX_C,LOW);
    digitalWrite(MUX_D,LOW);
    break;
  case 1:
    digitalWrite(MUX_A,HIGH);
    digitalWrite(MUX_B,LOW);
    digitalWrite(MUX_C,LOW);
    digitalWrite(MUX_D,LOW);
    break;
  case 2:
    digitalWrite(MUX_A,LOW);
    digitalWrite(MUX_B,HIGH);
    digitalWrite(MUX_C,LOW);
    digitalWrite(MUX_D,LOW);
    break;
  case 3:
    digitalWrite(MUX_A,HIGH);
    digitalWrite(MUX_B,HIGH);
    digitalWrite(MUX_C,LOW);
    digitalWrite(MUX_D,LOW);
    break;
  case 4:
    digitalWrite(MUX_A,LOW);
    digitalWrite(MUX_B,LOW);
    digitalWrite(MUX_C,HIGH);
    digitalWrite(MUX_D,LOW);
    break;

  default:
    break;
  }
  if(digitalRead(MUX_Y) == false){
    return true;
  }else{
    return false;
  }
}
void LCD_Select(){
return;
}
void Bocina_Select(int n){
  switch (n)
  {
  case 0:
    Serial.println("Auidio 0");
    break;
  case 1:
    Serial.println("Auidio 1");
    break;
  case 2:
    Serial.println("Auidio 2");
    break;
  case 3:
    Serial.println("Auidio 3");
    break;
  case 4:
    Serial.println("Auidio 4");
    break;

  default:
    break;
  }
}