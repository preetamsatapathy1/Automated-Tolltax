
#include <SPI.h>
#include <RFID.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define size 2

RFID RC522(SS_PIN, RST_PIN); 
String a="";

String id[size]={"24214915322927","54237151229169"};
String nam[size]={"Shashank","Preetam"};
String num[size]={"9003853891","9003756805"};
int bal[size]={1000,1500};
int balance=0;
int rem=0;
String b="jhk";


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);
  lcd.print("Wireless Project");
  delay(2000);
  SPI.begin(); 
  RC522.init();
  

}

void loop() {
 
 int k=-1; 
  if (RC522.isCard())
  {
    String a="";
    RC522.readCardSerial();
    for(int i=0;i<5;i++)
    {
      a.concat(RC522.serNum[i]);
    }
    if(a.length()>11){
    if(b!=a)
    {
    b=a;
       
    //Serial.println(a);
    
    
    for (int j=0;j<size;j++)
    {
      if(a==id[j]){
        k=j;
      }
    }
    
    if(k>=0)
    {
      Serial.println(num[k]);
      lcd.clear();
      lcd.print("Name: ");
      lcd.print(nam[k]);
      
      
      String h=num[k];
      balance=bal[k]-200;
      bal[k]=bal[k]-200;
      rem=bal[k];
      if(rem>=1000){
      lcd.setCursor(0, 1);
  lcd.print("Balance: ");
  lcd.print(rem);
  gsm(h);}
  
  else if(rem>=0){
    lcd.setCursor(0, 1);
  lcd.print("!!LOW BALANCE!!");
  lcd.setCursor(0,0);
  for (int i = 0; i < 16; ++i)
  {
  lcd.write(' ');
  }
  lcd.setCursor(0,0);
  lcd.print("Balance: ");
  lcd.print(rem);
  gsm(h);
    }
    
  else{
    lcd.setCursor(0, 1);
    lcd.print("No Balance");
    digitalWrite(8, HIGH);
    delay(3000);
    digitalWrite(8,LOW);
    bal[k]=bal[k]+200;
     rem=bal[k];
    gsm1(h);}
      
      k=-1;
      
    }
    else
    {
      lcd.clear();
      lcd.print("NOT REGISTERED");
      lcd.setCursor(0, 1);
      lcd.print("PAY BY CASH");
      Serial.println("not in database");
      
      digitalWrite(8, HIGH);
      delay(3000);
      digitalWrite(8,LOW);
      k=-1;
    }
    
  }
  }
  }
}
  void gsm(String number){
  Serial.println("AT+CMGF=1");   
      delay(1000);  
      Serial.println("AT+CMGS=\"+91"+number+"\"\r");
      delay(1000);
      Serial.println("!!TOLL TAX AT VIT GATE!!");
      delay(100);
      Serial.print("A TOLL OF RS 200 IS DEDUCTED FROM YOUR ACCOUNT.BALANCE REMAINING IS ");
      delay(100);
      Serial.print(rem);
      delay(100);
      Serial.println((char)26);
      delay(1000);
  }

void gsm1(String number){
  Serial.println("AT+CMGF=1");   
      delay(1000);  
      Serial.println("AT+CMGS=\"+91"+number+"\"\r");
      delay(1000);
      Serial.println("!!TOLL TAX AT VIT GATE!!");
      delay(100);
      Serial.print("NO BALANCE IN PREPAID ACCOUNT.PLEASE PAY BY CASH ");
      delay(100);
      Serial.println((char)26);
      delay(1000);
  }



