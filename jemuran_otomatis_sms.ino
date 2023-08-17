#include<Wire.h>
#include <LiquidCrystal_I2C.h> // libray lcd

#include <Sim800l.h>
#include <SoftwareSerial.h> 
Sim800l Sim800l;  
char* text1;
char* text2;
char* number;
bool error; 

#include <AccelStepper.h>
#define motorPin1 6
#define motorPin2 7
#define motorPin3 8
#define motorPin4 9
#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType,
motorPin1, motorPin3, motorPin2, motorPin4);
int cahaya = 4;
int air = A3;
int status_jemuran=0;
const int bawah=0;
const int atas=1024;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  Sim800l.begin();
  number="081248280702"; //no tujuan
  text1="Jemuran telah mengeluarkan pakaian";
  text2="Jemuran telah memasukan pakaian";  //isi pesan 

  Serial.begin(9600);
  pinMode(cahaya,INPUT);
    pinMode(air,INPUT); 
stepper.setMaxSpeed(1000);
stepper.setAcceleration(900);
lcd.begin();
lcd.setCursor(0,0);
lcd.print("AvilianyRetuadan");
lcd.setCursor(1,1);
lcd.print("NIM : 190101017");


}

void loop(){
int data_cahaya=digitalRead(cahaya);
  Serial.print("LDR ");
  Serial.print(data_cahaya);
  Serial.print(" - ");
  int data_air=analogRead(air);
  int range=map(data_air,bawah,atas,0,3);
  Serial.print("AIR ");
  Serial.println(range);
	if((data_cahaya==0)&&(range==2))
	{
  stepper.runToNewPosition(6500);//MEMBUKA PINTU
	if(status_jemuran==0)
  {
    Sim800l.sendSms(number,text1);
    status_jemuran=1;
  }
	}
 else
{
  stepper.runToNewPosition(0);//menutup PINTU   
  if(status_jemuran==1)
  {
    Sim800l.sendSms(number,text2);
    status_jemuran=0;
  }
  }
    delay(1000);
}
