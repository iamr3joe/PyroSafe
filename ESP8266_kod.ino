#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

// WiFi postavke za spajanje
const char* ssid = "PyroSafe"; // Naziv mreže
const char* password = "pyrosafe1"; // Šifra

String brojtelefona = "38762000000"; // Broj telefona za notifikacije
String apiKey = "12345678"; // API ključ bota

void posaljiPoruku(String poruka){

  String url = "http://api.callmebot.com/whatsapp.php?phone=" + brojtelefona + "&apikey=" + apiKey + "&text=" + urlEncode(poruka);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpResponseKod = http.POST(url);
  if (httpResponseKod == 200){
    Serial.print("Poruka poslana uspjesno");
  }
  else{
    Serial.println("Greska pri slanju poruke");
    Serial.print("HTTP response kod: ");
    Serial.println(httpResponseKod);
  }

  http.end();
}

int led1 = 16;
int led2 = 5;
int led3 = 4;
int zelena = 0;
int stanjeled1, stanjeled2, stanjeled3, stanjeledzelena;
int poslano = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(zelena, OUTPUT);

  //WIFI
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Povezivanje");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Povezan na WIFI sa IP adresom: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  stanjeled1 = digitalRead(led1);
  stanjeled2 = digitalRead(led2);
  stanjeled3 = digitalRead(led3);
  stanjeledzelena = digitalRead(zelena);

  if(stanjeledzelena == HIGH && poslano == 1)
  {
      poslano = 0;
      posaljiPoruku("STANJE U REDU!");
  }
  if(stanjeled1 == HIGH && poslano == 0)
  {
    posaljiPoruku("UZBUNA! TEMPERATURA VISOKA!");
    poslano = 1;
  }
  if(stanjeled2 == HIGH && poslano == 0)
  {
    posaljiPoruku("UZBUNA! PLAMEN U PROSTORIJI!");
    poslano = 1;
  }
  if(stanjeled3 == HIGH && poslano == 0)
  {
    posaljiPoruku("UZBUNA! DIM U PROSTORIJI!");
    poslano = 1;
  }
}
