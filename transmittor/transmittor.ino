//For Red Tank

#include <IRLib.h>
#include <EEPROM.h>

#define hltAddr 0
#define buzz A2
#define RECV_PIN  2
#define  btn A1
#define btn1 A2
int LED_pin=3;
#define y A4
#define x A5

int hlt=0; //Setting initial health to zero.
long debounce=200;
int read1;
int read2;
int time=0;
int acclx=0;
int accly=0;


IRrecv My_Receiver(RECV_PIN);
IRsend My_Sender;

IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];
char input="";

void setup()

{
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
  for(int i=4;i<9;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  EEPROM.write(hltAddr,0);
  hlt=EEPROM.read(hltAddr);
  Serial.begin(9600);
  pinMode(btn,INPUT_PULLUP);
  pinMode(btn1,INPUT_PULLUP);
  My_Receiver.enableIRIn(); // Start the receiver
  My_Decoder.UseExtnBuf(Buffer);
}

void checkForInput(){
    if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();
    TIMSK2 = 0;  
     if (My_Decoder.value == 3021 && hlt <= 15)
    {
      hlt++;
      if(hlt%3==0){
        LED_pin++;
      EEPROM.write(hltAddr,hlt);
      digitalWrite(LED_pin,LOW); 
      digitalWrite(buzz, HIGH);
      delay(200);//500 se change kiya
      digitalWrite(buzz, LOW);
      //Serial.println("inside receiver loop right");
      //Serial.println(My_Decoder.value, HEX);
      }
      delay(100);
    }
    //My_Decoder.DumpResults();

    Serial.println("inside receiver loop");
    Serial.println(My_Decoder.value,HEX);
    delay(100); 
    My_Receiver.resume();
    My_Receiver.enableIRIn();
  //  My_Receiver.resume();
  }
  
  }
void loop() {
analogReference(EXTERNAL);
  
  //if (Serial.read() != -1) {
  
    accly=analogRead(y);
    acclx=analogRead(x);
    //Serial.println(accl);
    if(accly>=550)
    {
    Serial.println("forward");
    My_Sender.send(RC5,0xf, 20);
    My_Receiver.enableIRIn();
    //checkForInput();
   // My_Receiver.enableIRIn();
    time=millis();
  }
  else if(accly<=460)
    {
    Serial.println("backward");
    My_Sender.send(RC5,0xb, 20);
    My_Receiver.enableIRIn();
   // checkForInput();
    //My_Receiver.enableIRIn();
    time=millis();
  }
  else if(acclx<=450){
  
  Serial.println("Left");
   My_Sender.send(RC5,0xa, 20);
    }
  else if(acclx>=570){
    Serial.println("Right");
     My_Sender.send(RC5,0xc, 20);
    
  }
  else{
    Serial.println("nothing");
    My_Sender.send(RC5,0xbcc,20);
  }
  //Serial.print("Health:");
  //Serial.println(hlt);
  //delay(1000);
}

