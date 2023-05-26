#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte Stepen[] = {
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

int led1 = 13;
int led2 = 12;
int led3 = 11;
int zelena = 10;
int uzbuna = 9;
int buzzer1 = 6;
int buzzer2 = 5;
int plamenPin = 3;
int senzor = A0;
int trenutnostanje;
int senzorThresh = 400;
int i, set;

double value;
double temp;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(zelena, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(senzor, INPUT);
  pinMode(plamenPin, INPUT);
  pinMode(uzbuna, INPUT_PULLUP);
  Serial.begin(9600);
  sensors.begin();
  // Ukljucit LCD
  lcd.init();
  lcd.backlight();
  // Znak stepena
  lcd.createChar(0, Stepen);
}

void loop() {

  sensors.requestTemperatures();

  float tempC = sensors.getTempCByIndex(0); // index 0 oznacava prvi uredjaj
  
  trenutnostanje = digitalRead(uzbuna);

  if(trenutnostanje == LOW)
  {
    digitalWrite(led1, HIGH);
    tone(buzzer1, 1000, 30000);
    digitalWrite(led2, HIGH);
    tone(buzzer2, 1000, 30000);
    digitalWrite(led3, HIGH);
    digitalWrite(zelena, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UZBUNA");
    lcd.setCursor(0, 1);
    lcd.print("EVAKUISI");
    i = 0;
    set = 1;
    while(i < 30000)
    {
      trenutnostanje = digitalRead(uzbuna);
      if(trenutnostanje == HIGH)
      {
        set = 0;
      }
      if(trenutnostanje == LOW && set == 0)
      {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(zelena, HIGH);
        noTone(buzzer1);
        noTone(buzzer2);
        break;  
      }
      delay(10);
      i += 10;
    }
  }

  int gasSenzor = analogRead(senzor);
  int senzorPlamena = digitalRead(plamenPin);
  
  Serial.print("gasPin vrijednost: ");
  Serial.println(gasSenzor);
  Serial.print("plamenPin vrijednost: ");
  Serial.println(senzorPlamena);
  
  if(tempC > 30)
  {
    digitalWrite(led1, HIGH);
    tone(buzzer1, 500);
    digitalWrite(zelena, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UZBUNA");
    lcd.setCursor(0, 1);
    lcd.print("EVAKUISI");
    delay(60000);
  }

  if(senzorPlamena == HIGH)
  {
    digitalWrite(led2, HIGH);
    tone(buzzer2, 500);
    digitalWrite(zelena, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UZBUNA");
    lcd.setCursor(0, 1);
    lcd.print("EVAKUISI");
  }

  if(gasSenzor > senzorThresh)
  {
    digitalWrite(led3, HIGH);
    tone(buzzer2, 500);
    digitalWrite(zelena, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UZBUNA");
    lcd.setCursor(0, 1);
    lcd.print("EVAKUISI");
  }
  
  if(tempC <= 30 && senzorPlamena == LOW && gasSenzor <= senzorThresh)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(zelena, HIGH);
    noTone(buzzer1);
    noTone(buzzer2);

    // Ispis na LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura:");
    lcd.setCursor(0, 1);
    lcd.print(tempC);
    lcd.write(0); // ispis stepena
    lcd.print("C");   
  }
}
