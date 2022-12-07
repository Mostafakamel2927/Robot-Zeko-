
#include<Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 9
#define RST_PIN 8

#define input1  2
#define input2  3
#define input3  4
#define input4  5
#define speed1 6                                                                                                                                                        
#define speed2 7
#define center_sen A1
#define Right_sen A0
#define Left_sen A2 

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
char Key[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  
  };
  byte rowpin[4]={30,31,32,33};
  byte colpin[4]={34,35,36,37};
  Keypad mykeypad=Keypad(makeKeymap(Key),rowpin,colpin,4,4);
void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);
  pinMode(speed1,OUTPUT);

}

void loop() {
int key=mykeypad.getKey();
while(key=='A')
{
  car();
 
}
}
void car()
{
     int Right_val=digitalRead(Right_sen);
     int Left_val=digitalRead(Left_sen);
     int center_val=digitalRead(center_sen);

Serial.println(Right_val);
     if(Right_val==1&&Left_val==1)
    {
     Up(); 
    }
        
        else if(Right_val==1&&Left_val==0)
        {
         right(); 
        }
        
        else if(Right_val==0&&Left_val==1)
        {
         left(); 
        }
                
         else if(Right_val==0&&Left_val==0)
        {
         Stop(); 
        }

    

rfid();
}
void rfid()
{
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "6C 39 3D 22") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    Stop();
    delay(3000);
  }
  
}

void Up()
{
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  analogWrite(speed1,120);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  analogWrite(speed2,120); 
} 
void Back()
{
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  analogWrite(speed1,120);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  analogWrite(speed2,120) ;
} 
void left()
{
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  analogWrite(speed1,120);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  analogWrite(speed2,120) ;
} 
void right()
{
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  analogWrite(speed1,120);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  analogWrite(speed2,120) ;
} 
void Stop()
{
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
}
