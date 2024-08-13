#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>

#include <SPI.h>

#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

LiquidCrystal_I2C lcd(0x27, 16, 2);
int BuzzerPin = 5; // Connect Buzzer to Arduino pin 5
int count = 0;

int a;
int p1 = 0, p2 = 0;

int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

double total = 0;
int count_prod = 0;

void setup() {

  pinMode(3, INPUT_PULLUP); //Push Switch

  pinMode(4, OUTPUT); //RED LED

  pinMode(5, OUTPUT); //BUZZER

  pinMode(6, OUTPUT); //GREEN LED

  // Initialization
  Serial.begin(9600);

  // lcd.begin();
  digitalWrite(4, LOW);

  digitalWrite(5, LOW);

  digitalWrite(6, LOW);

  lcd.init();

  lcd.backlight();

  lcd.setCursor(0, 0);

  lcd.print(" AUTOMATIC BILL");

  delay(2000);

  lcd.setCursor(0, 1);

  lcd.print(" SHOPPING CART ");

  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print(" WELCOME TO ");

  lcd.setCursor(0, 1);

  lcd.print("BVM ELECTROSHOP");

  digitalWrite(4, HIGH);

  digitalWrite(5, HIGH);

  digitalWrite(6, LOW);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

}

void loop()

{
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  count = 0;
  int a = digitalRead(3);

  String content = "";

  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if ((content.substring(1) == "23 64 8C 13") && (a == 1))

  {
    lcd.setCursor(0, 0);
    count_prod++;
    p1++;
    lcd.print("DIODE Added  ");
    lcd.print(p1);
    lcd.setCursor(0, 1);

    lcd.print("Price:4.00 ");

    digitalWrite(4, LOW);

    digitalWrite(5, LOW);

    //  digitalWrite(6,LOW);

    delay(2000);

    total = total + 4.00;

    digitalWrite(4, HIGH);

    digitalWrite(5, HIGH);

    //   digitalWrite(6,HIGH);

  } else if ((content.substring(1) == "23 64 8C 13") && (a == 0))

  {

    if (p1 > 0)

    {

      lcd.clear();

      lcd.setCursor(0, 0);

      lcd.print("DIODE Removed!!! ");

      digitalWrite(4, LOW);

      digitalWrite(5, LOW);

      // digitalWrite(6,HIGH);

      delay(2000);

      total = total - 4.00;
      count_prod--;
      p1--;
      lcd.clear();

      digitalWrite(4, HIGH);

      digitalWrite(5, HIGH);

      //digitalWrite(6,LOW);
      lcd.clear();
      lcd.print("DIODE COUNT:");
      lcd.setCursor(0, 1);
      lcd.print(p1);
    } else

    {

      lcd.clear();

      lcd.setCursor(0, 0);

      lcd.print("Not in cart!!! ");

      digitalWrite(4, LOW);

      digitalWrite(5, LOW);

      //    digitalWrite(6,HIGH);

      delay(2000);

      digitalWrite(4, HIGH);

      digitalWrite(5, HIGH);

      //  digitalWrite(6,LOW);
      lcd.clear();
      lcd.print("DIODE COUNT:");
      lcd.setCursor(0, 1);
      lcd.print(p1);

    }

  }
  if ((content.substring(1) == "13 FC 70 0D") && (a == 1))

  {
    count_prod++;
    p2++;

    lcd.setCursor(0, 0);

    lcd.print("WIRE Added   ");
    lcd.print(p2);
    lcd.setCursor(0, 1);

    lcd.print("Price:6.00 ");

    digitalWrite(4, LOW);

    digitalWrite(5, LOW);

    //        digitalWrite(6,HIGH);

    delay(2000);

    total = total + 6.00;

    digitalWrite(4, HIGH);

    digitalWrite(5, HIGH);

    //      digitalWrite(6,LOW);

  } else if ((content.substring(1) == "13 FC 70 0D") && (a == 0))

  {

    if (p2 > 0)

    {

      lcd.clear();

      lcd.setCursor(0, 0);

      lcd.print("WIRE Removed!!! ");

      digitalWrite(4, LOW);

      digitalWrite(5, LOW);

      //    digitalWrite(6,HIGH);

      delay(2000);

      count_prod--;
      p2--;
      total = total - 6.00;
      lcd.clear();

      digitalWrite(4, HIGH);

      digitalWrite(5, HIGH);

      //  digitalWrite(6,LOW);
      lcd.clear();
      lcd.print("WIRE COUNT:");
      lcd.setCursor(0, 1);
      lcd.print(p2);

    } else

    {

      lcd.clear();

      lcd.setCursor(0, 0);

      lcd.print("Not in cart!!! ");

      digitalWrite(4, LOW);

      digitalWrite(5, LOW);

      //  digitalWrite(6,HIGH);

      delay(2000);

      digitalWrite(4, HIGH);

      digitalWrite(5, HIGH);

      //      digitalWrite(6,LOW);

      lcd.clear();
      lcd.print("WIRE COUNT:");
      lcd.setCursor(0, 1);
      lcd.print(p2);

    }

  }

  if ((content.substring(1) == "CA A3 37 2B"))

  {

    lcd.clear();

    lcd.setCursor(0, 0);

    lcd.print("Total Price :-");
    digitalWrite(4, LOW);

    digitalWrite(5, LOW);

    //      digitalWrite(6,HIGH);

    delay(2000);

    digitalWrite(4, HIGH);

    digitalWrite(5, HIGH);

    //    digitalWrite(6,LOW);

    lcd.setCursor(0, 1);

    lcd.print(total);

    delay(5000);
    lcd.clear();

    lcd.setCursor(0, 0);

    lcd.print("Total product :-");

    lcd.setCursor(0, 1);

    lcd.print(count_prod);
    delay(5000);
    lcd.clear();

    lcd.setCursor(0, 0);

    lcd.print(" THANKS FOR ");

    lcd.setCursor(0, 1);

    lcd.print(" VISITING ");

    lcd.clear();
    count_prod = 0;
    total = 0;
    p1 = 0;
    p2 = 0;
  }

}
