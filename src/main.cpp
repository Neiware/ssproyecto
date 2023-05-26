#include <Arduino.h>
#include <string.h>
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
LiquidCrystal_I2C lcd(0x27,20,4);
TMRpcm Audio; //object for TMRpcm library

//----------------OWN CLASS -----------------------//
class Componentes
{
private:
  /* data */
  bool A,B,C,D;
  String audioFile;
  String lcdText;

  
public:
//constructor parametros A,B,C,D definen en binario el numero de combinacion. 
  Componentes(bool A_,bool B_,bool C_,bool D_, String audioFile_, String lcdText_)
  {
    A = A_;
    B = B_;
    C = C_;
    D = D_;
    audioFile = audioFile_;
    lcdText = lcdText_;
  }
  void WriteMux()
  {
    digitalWrite(MUX_A,A);
    digitalWrite(MUX_B,B);
    digitalWrite(MUX_C,C);
    digitalWrite(MUX_D,D);
  }
  void PlayAudio(int m)
  {
    bool reading;
    while (Audio.isPlaying() == true || reading == true)
    {
      Serial.println(audioFile);
      reading = digitalRead(MUX_Y);
    }
  }
  
  void Printlcd()
  {
    Serial.println("holaJ?");
    lcd.clear();
    lcd.home();
    lcd.print(lcdText);
  }
};
//----------CREATE OBJEXTS------//
//OBJECT CALL lcd using external library


Componentes capacitor(LOW,LOW,LOW,LOW,"capacitor.wav","capacitor");
Componentes diodo(HIGH,LOW,LOW,LOW,"diodo.wav","diodo");
Componentes led(LOW,HIGH,LOW,LOW,"led.wav","led");
Componentes resistencia(HIGH,HIGH,LOW,LOW,"resistencia.wav","resistencia");
Componentes transistor(LOW,LOW,HIGH,LOW,"transistor.wav","transistor");
Componentes potenciometro(HIGH,LOW,HIGH,LOW,"potenciometro.wav","Potenciometro");
Componentes fusible(LOW,HIGH,HIGH,LOW,"fusible.wav","fusible");
Componentes ic(HIGH,HIGH,HIGH,LOW,"IC.wav","IC");
Componentes inductores(LOW,LOW,LOW,HIGH,"inductores.wav","inductores");
Componentes interruptor(HIGH,LOW,LOW,HIGH,"interruptor.wav","interruptor");
Componentes motorDC(LOW,HIGH,LOW,HIGH,"motorDC.wav","motorDC");
Componentes oscilador(HIGH,HIGH,LOW,HIGH,"oscilador.wav","oscilador");
Componentes regulador(LOW,LOW,HIGH,HIGH,"reguladorDeVolaje.wav","regulador");
Componentes rele(HIGH,LOW,HIGH,HIGH,"rele.wav","rele");
Componentes zener(LOW,HIGH,HIGH,HIGH,"zener.wav","zener");
//add the 16 component

//-----------FUNCTIONS--------------//
// display all keycodes
bool Movimiento_Bits(int n);
void LCD_Select();
void Bocina_Select(int n);


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
  if(n <= 3){
      Serial.print("Value of n is ");
    Serial.println(n);
    n++;
  }else{
       n = 0;
       Serial.println("End loop");
  }
  if(Movimiento_Bits(n) == true){
    LCD_Select();
    Bocina_Select(n);
    delay(200);
  }
}
bool Movimiento_Bits(int n)
{
  switch (n)
  {
  case 0:
    capacitor.WriteMux();
    break;
  case 1:
    diodo.WriteMux();
    break;
  case 2:
    led.WriteMux();
    break;
  case 3:
    resistencia.WriteMux();
    break;
  case 4:
    transistor.WriteMux();
    break;

  default:
    break;
  }
  if(digitalRead(MUX_Y) == HIGH){
    return true;
  }else{
    return false;
  }
}
void LCD_Select()
{
  switch (n)
  {
  case 0:
    capacitor.Printlcd();
    break;
  case 1:
    diodo.Printlcd();
    break;
  case 2:
    led.Printlcd();
    break;
  case 3:
    resistencia.Printlcd();
    break;
  case 4:
    transistor.Printlcd();
    break;
  case 5:
    potenciometro.Printlcd();
    break;
  case 6:
    fusible.Printlcd();
    break;
  case 7:
    ic.Printlcd();
    break;
  case 8:
    inductores.Printlcd();
    break;
  case 9:
    interruptor.Printlcd();
    break;
  case 10:
    motorDC.Printlcd();
    break;
  case 11:
    oscilador.Printlcd();
    break;
  case 12:
    regulador.Printlcd();
    break;
  case 13:
    rele.Printlcd();
    break;
  case 14:
    zener.Printlcd();
    break;
  case 15:
    //add last 
    break;

  default:
    break;
  }

}
void Bocina_Select(int n){
  switch (n)
  {
  case 0:
    Audio.play("capacitor.wav");
    capacitor.PlayAudio(n);
    break;
  case 1:
    Audio.play("diodo.wav");
    diodo.PlayAudio(n);
    break;
  case 2:
    Audio.play("led.wav");
    led.PlayAudio(n);
    break;
  case 3:
    Audio.play("resistencia.wav");
    resistencia.PlayAudio(n);
    break;
  case 4:
    Audio.play("transistor.wav");  
    transistor.PlayAudio(n);
    break;
  case 5:
    Audio.play("potenciometro.wav");  
    potenciometro.PlayAudio(n);
    break;
  case 6:
    Audio.play("fusible.wav");  
    fusible.PlayAudio(n);
    break;
  case 7:
    Audio.play("IC.wav");
    ic.PlayAudio(n);
    break;
  case 8:
    Audio.play("inductores.wav");
    inductores.PlayAudio(n);
    break;
  case 9:
    Audio.play("interruptor.wav");
    interruptor.PlayAudio(n);
    break;
  case 10:
    Audio.play("motorDC.wav");  
    motorDC.PlayAudio(n);
    break;
  case 11:
    Audio.play("oscilador.wav");  
    oscilador.PlayAudio(n);
    break;
  case 12:
    Audio.play("reguladorDeVoltaje.wav");  
    regulador.PlayAudio(n);
    break;
  case 13:
    Audio.play("rele.wav");
    rele.PlayAudio(n);
    break;
  case 14:
    Audio.play("zener.wav");  
    zener.PlayAudio(n);
    break;
  case 15:
  //add last case
   // Audio.play("meme4.wav");  
   // .PlayAudio(n);
    break;

  default:
    break;
  }
}