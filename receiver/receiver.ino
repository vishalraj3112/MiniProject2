//For Red Tank

#include <IRLib.h>
#include <EEPROM.h>

#define hltAddr 0
#define buzz A2
#define RECV_PIN  2
#define  btn A0
int LED_pin=3;
#define m1 4//forward
#define m2 5//baackward
#define m3 6//Left
#define m4 7//Right


int hlt=0; //Setting initial health to zero.
long debounce=200;
int read;
int time=0;


IRrecv My_Receiver(RECV_PIN);
IRsend My_Sender;

IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];

void setup()

{pinMode(m1,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m4,OUTPUT);
digitalWrite(m1,LOW);
digitalWrite(m2,LOW);
digitalWrite(m3,LOW);
digitalWrite(m4,LOW);

  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
 
  EEPROM.write(hltAddr,0);
  hlt=EEPROM.read(hltAddr);
  Serial.begin(9600);
  pinMode(btn,INPUT);
  My_Receiver.enableIRIn(); // Start the receiver
  My_Decoder.UseExtnBuf(Buffer);
}

void checkForInput(){
    if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();
    TIMSK2 = 0;  
    if (My_Decoder.value == 15 && hlt <= 15)
    {
    
      EEPROM.write(hltAddr,hlt);
      digitalWrite(m1,HIGH);
      digitalWrite(LED_pin,LOW); 
      digitalWrite(buzz, HIGH);
      delay(200);//500 se change kiya
      digitalWrite(buzz, LOW);
      //Serial.println("inside receiver loop right");
      //Serial.println(My_Decoder.value, HEX);
      
      delay(100);
    }
    
    else if (My_Decoder.value == 11 && hlt <= 15)
    {
     
      EEPROM.write(hltAddr,hlt);
      digitalWrite(m2,HIGH);
      digitalWrite(LED_pin,LOW); 
      digitalWrite(buzz, HIGH);
      delay(200);//500 se change kiya
      digitalWrite(buzz, LOW);
      //Serial.println("inside receiver loop right");
      //Serial.println(My_Decoder.value, HEX);
      
      delay(100);
    }else if (My_Decoder.value == 10 && hlt <= 15)
    {
     
      EEPROM.write(hltAddr,hlt);
      digitalWrite(m3,HIGH);
      digitalWrite(LED_pin,LOW); 
      digitalWrite(buzz, HIGH);
      delay(200);//500 se change kiya
      digitalWrite(buzz, LOW);
      //Serial.println("inside receiver loop right");
      //Serial.println(My_Decoder.value, HEX);
      
      delay(100);
    }
    else if (My_Decoder.value == 12 && hlt <= 15)
    {
     
      EEPROM.write(hltAddr,hlt);
      digitalWrite(m4,HIGH);
      digitalWrite(LED_pin,LOW); 
      digitalWrite(buzz, HIGH);
      delay(200);//500 se change kiya
      digitalWrite(buzz, LOW);
      //Serial.println("inside receiver loop right");
      //Serial.println(My_Decoder.value, HEX);
      
      delay(100);
    }
    
     else if (My_Decoder.value == 3020 && hlt <= 15)
    {
     
      EEPROM.write(hltAddr,hlt);
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
      digitalWrite(LED_pin,LOW); 
      digitalWrite(buzz, HIGH);
      delay(200);//500 se change kiya
      digitalWrite(buzz, LOW);
      //Serial.println("inside receiver loop right");
      //Serial.println(My_Decoder.value, HEX);
      
      delay(100);
    }

   
    //My_Decoder.DumpResults();

   // Serial.println("inside receiver loop");
    Serial.println(My_Decoder.value,HEX);
    delay(100); 
    My_Receiver.resume();
    My_Receiver.enableIRIn();
  //  My_Receiver.resume();
  }
  
  }
void loop() {

  
  //if (Serial.read() != -1) {
    read=digitalRead(btn);
    if(read==HIGH && millis()-time > debounce)
    {
    Serial.println("send loop");
    My_Sender.send(RC5,0xbcb, 20);
    My_Receiver.enableIRIn();
    checkForInput();
    My_Receiver.enableIRIn();
    time=millis();
  }
  checkForInput();

  //Serial.print("Health:");
  //Serial.println(hlt);
  //delay(1000);
}
