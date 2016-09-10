/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <IRremote.h>

int RECV_PIN = 11;
int switchPin = 8;
int btn_1 = 4;
int btn_2 = 5;


IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;

struct button{
  int nbits;
  decode_type_t type;
  unsigned long code[5];
}btn[2];

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
int i=0,j=0,k=0,x;
void loop() {
  //--------------- Reciever Code -----------------//
  if (digitalRead(switchPin) == HIGH){
    //---------- SET Button 1 ----------//
    if (irrecv.decode(&results) && digitalRead(btn_1) == HIGH) {
        btn[0].code[i] = results.value;
        btn[0].nbits = results.bits;
        btn[0].type = results.decode_type;
        i++;
        irrecv.resume(); // Receive the next value

          for(x=0; x<i; x++){
            Serial.println(btn[0].code[x]);
          }
          Serial.println(results.decode_type);
          Serial.println(btn[0].nbits);
          Serial.println("___________");
        
    }
    //---------- SET Button 2 ----------//
    else if (irrecv.decode(&results) && digitalRead(btn_2) == HIGH) {
        btn[1].code[j] = results.value;
        btn[1].nbits = results.bits;
        btn[1].type = results.decode_type;
        j++;
        irrecv.resume(); // Receive the next value

        
          for(x=0; x<j; x++){
            Serial.println(btn[1].code[x]);
          }
          Serial.println(results.decode_type);
          Serial.println(btn[1].nbits);
          Serial.println("___________");
        
    }
  }

  
  //------------ Transmitter Code ----------------//
  else{
    //---------- SEND Button 1 ----------//
    if (digitalRead(btn_1) == HIGH) {
      
      
      for(x=0;x<i;x++){
        if(btn[0].type == NEC)
          irsend.sendNEC(btn[0].code[x], btn[0].nbits);

        else if(btn[0].type == SONY)
          irsend.sendSony(btn[0].code[x], btn[0].nbits);

        else if(btn[0].type == RC5)
          irsend.sendRC5(btn[0].code[x], btn[0].nbits);

        else if(btn[0].type == RC6)
          irsend.sendRC6(btn[0].code[x], btn[0].nbits);

        delay(40);
       
          Serial.println(btn[0].code[x]);
         
      
        if(Serial.available())
          Serial.println("Transmitter on 1");
    }
    //---------- SEND Button 2 ----------//
    else if (digitalRead(btn_2) == HIGH) {
      
   
      for(x=0;x<j;x++){
        if(btn[1].type == NEC)
          irsend.sendNEC(btn[1].code[x], btn[1].nbits);

        else if(btn[0].type == SONY)
          irsend.sendSony(btn[1].code[x], btn[1].nbits);

        else if(btn[0].type == RC5)
          irsend.sendRC5(btn[1].code[x], btn[1].nbits);

        else if(btn[0].type == RC6)
          irsend.sendRC6(btn[1].code[x], btn[1].nbits);
        
        delay(40);
        
        
          Serial.println(btn[1].code[x]);
         
      }
      
          Serial.println("Transmitter on 2");
    }
    delay(500);
  }
  delay(100);
}
}
