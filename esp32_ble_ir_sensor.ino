#include <EEPROM.h>
#define EEPROM_SIZE 11
int l0=13,l1=12,l2=27,l3=26,l4=25,l5=33,l6=32,l7=16,l8=2,l1_0=22,l1_1=23;
int iled = 17;

#include "BluetoothSerial.h" //Bluetooth_code
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//ir remote
#include <IRremote.h>
#include <Arduino.h>
#define RECEIVER_PIN 5
IRrecv receiver(RECEIVER_PIN);
decode_results results;

int tem;
int fs;

void setup(){
  EEPROM.begin(EEPROM_SIZE);
  //Serial.begin(9600);
  SerialBT.begin("Home_bluetooth"); //bluetooth name
  receiver.enableIRIn(); //ir remote

  pinMode(l0,OUTPUT);
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(l3,OUTPUT);     //all pin is output pin
  pinMode(l4,OUTPUT);
  pinMode(l5,OUTPUT);
  pinMode(l6,OUTPUT);
  pinMode(l7,OUTPUT);
  pinMode(l8,OUTPUT);
  pinMode(l1_0,OUTPUT);
  pinMode(l1_1,OUTPUT);
  pinMode(iled,OUTPUT);
  digitalWrite(iled,HIGH);
  delay(1000);
  digitalWrite(iled,LOW);
  }

void loop(){

  digitalWrite(l0,EEPROM.read(0));
  digitalWrite(l2,EEPROM.read(2));
  digitalWrite(l3,EEPROM.read(3));
  digitalWrite(l4,EEPROM.read(4));
  digitalWrite(l5,EEPROM.read(5));
  digitalWrite(l6,EEPROM.read(6));
  digitalWrite(l7,EEPROM.read(7));
  digitalWrite(l8,EEPROM.read(8));

  //Serial.println(EEPROM.read(1));

  if(EEPROM.read(1) == 1){
    digitalWrite(l1_0,HIGH);
    digitalWrite(l1_1,LOW);
    digitalWrite(l1,LOW);
    }
  else if(EEPROM.read(1) == 2){
    digitalWrite(l1_1,HIGH);
    digitalWrite(l1_0,LOW);
    digitalWrite(l1,LOW);
    }
  else if(EEPROM.read(1) == 3){
    digitalWrite(l1_0,HIGH);
    digitalWrite(l1_1,HIGH);
    digitalWrite(l1,LOW);
    }
  else if(EEPROM.read(1) == 4){
    digitalWrite(l1_0,LOW);
    digitalWrite(l1_1,LOW);
    digitalWrite(l1,HIGH);
    }
  else if(EEPROM.read(1) == 0){
    digitalWrite(l1_0,LOW);
    digitalWrite(l1_1,LOW);
    digitalWrite(l1,LOW);
    }
  /*for(int i=0;i<9;i++){
    EEPROM.write(i,0);
    }*/
  if (SerialBT.available()) {     //bluetooth loop
    char bchar = SerialBT.read();
    //Serial.write(SerialBT.read());
    if(bchar == 'A'){
      tem = EEPROM.read(0);
      tem = ~tem;
      EEPROM.write(0,tem);
      }
    else if(bchar == 'C'){
      tem = EEPROM.read(2);
      tem = ~tem;
      EEPROM.write(2,tem);
      }
    else if(bchar == 'D'){
      tem = EEPROM.read(3);
      tem = ~tem;
      EEPROM.write(3,tem);
      }
    else if(bchar == 'E'){
      tem = EEPROM.read(4);
      tem = ~tem;
      EEPROM.write(4,tem);
      }
    else if(bchar == 'F'){
      tem = EEPROM.read(5);
      tem = ~tem;
      EEPROM.write(5,tem);
      }
    else if(bchar == 'G'){
      tem = EEPROM.read(6);
      tem = ~tem;
      EEPROM.write(6,tem);
      }
    else if(bchar == 'H'){
      tem = EEPROM.read(7);
      tem = ~tem;
      EEPROM.write(7,tem);
      }
    else if(bchar == 'I'){
      tem = EEPROM.read(8);
      tem = ~tem;
      EEPROM.write(8,tem);
      }

    else if(bchar == 'K'){
      tem = 0;
      EEPROM.write(1,tem);
      }
    else if(bchar == 'L'){
      tem = 1;
      EEPROM.write(1,tem);
      }
    else if(bchar == 'M'){
      tem = 2;
      EEPROM.write(1,tem);
      }
    else if(bchar == 'N'){
      tem = 3;
      EEPROM.write(1,tem);
      }
    else if(bchar == 'O'){
      tem = 4;
      EEPROM.write(1,tem);
      }
      EEPROM.commit();
    }

if(receiver.decode(&results)){          //ir remote loop
    //Serial.println(results.value,DEC);
    if(results.value == 33441975){
      for(int i=0;i<9;i++){
        EEPROM.write(i,0);
        }
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        //EEPROM.commit();
      }
    else if(results.value == 33444015){
      tem = EEPROM.read(0);
      tem = ~tem;
      EEPROM.write(0,tem);
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      }
    else if(results.value == 33478695){
      tem = EEPROM.read(1);
      if(tem <= 0){
        fs = 4;
        EEPROM.write(1,fs);   //working here
        //EEPROM.commit();
        }
      else if(tem > 0){
        fs = 0;
        EEPROM.write(1,fs);
        //EEPROM.commit();
      }
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
    }
    else if(results.value == 33486855){
      tem = EEPROM.read(2);
      tem = ~tem;
      EEPROM.write(2,tem);
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      }
    else if(results.value == 33435855){
      tem = EEPROM.read(3);
      tem = ~tem;
      EEPROM.write(3,tem);
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      }
    else if(results.value == 33468495){
      tem = EEPROM.read(4);
      tem = ~tem;
      EEPROM.write(4,tem);
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      }
    else if(results.value == 33452175){
      tem = EEPROM.read(5);
      tem = ~tem;
      EEPROM.write(5,tem);
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      }
    else if(results.value == 33423615){
      tem = EEPROM.read(6);
      tem = ~tem;
      EEPROM.write(6,tem);
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      }
    else if(results.value == 33484815){
      tem = EEPROM.read(7);
      tem = ~tem;
      EEPROM.write(7,tem);
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      }
    else if(results.value == 33462375){
      tem = EEPROM.read(8);
      tem = ~tem;
      EEPROM.write(8,tem);
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      }
    else if(results.value == 33448095){
      tem = EEPROM.read(1);
      if(tem < 4 && tem >= 0){
      tem = tem+1;
      EEPROM.write(1,tem);
      }
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      /*else {
        tem = 4;
        EEPROM.write(1,tem);
        }*/
       }
    else if(results.value == 33464415){
      tem = EEPROM.read(1);
      if(tem <= 4 && tem > 1){
      tem = tem-1;
      EEPROM.write(1,tem);
      }
      digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
        delay(5);
        digitalWrite(iled,HIGH);
        delay(5);
        digitalWrite(iled,LOW);
      /*else {
        tem = 0;
        EEPROM.write(1,tem);
        }*/
      }
    tem = EEPROM.read(1);
    if(tem <= 255 && tem > 4){
      fs=4;
      EEPROM.write(1,fs);
      }
    EEPROM.commit();
    receiver.resume();
    }
}
