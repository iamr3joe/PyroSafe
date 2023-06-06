# PyroSafe
Sistem za prevenciju i zaštitu od požara koji se fokusira na zaštitu od
požara, upotrebom osnovnih senzora u sprezi sa mikrokontrolerom Arduino. Požari
mogu biti uništavajući, ne samo za ljudske živote, već i za imovinu. Naš cilj je razviti
inovativno rješenje koje će prepoznati (detektovati) početak požara i pružiti korisnicima,
i drugima, najbitnije informacije i alarmirati sve faktore kako bi se spriječila šteta i
gubitak života.
# Komponente projekta
* Arduino Uno mikrokontroler
* NodeMCU ESP8266 WiFi modul
* KY-026 modul senzora plamena
* DS18B20 temperaturni senzor
* MQ-2 senzor gasa
* 2x Piezo(Buzzer) zvučnika 	
* LCD screen 	16pin
* LCM1602 IIC 	22pin
* 3x Crvene LED diode
* 1x Zelena LED dioda
* 4 220Ω otpornika
* 1 10kΩ otpornik
* 2 Push dugmeta
* Jumperi i proto pločica
# Instalacija

  1.  Povežite Arduino Uno sa ESP8266 WiFi modulom koristeći odgovarajuće žice i konektore. Obezbjedite dobar kontakt između pinova.
  2.  Povežite LCD displej na odgovarajuće analogne i napojne pinove.
  3.  Povežite senzor dima, senzor plamena i temperaturni senzor sa odgovarajućim ulazima na Arduino mikrokontroleru.
  4.  Povežite buzzere i LED diode sa odgovarajućim digitalnim pinovima na Arduino mikrokontroleru.
  5.  Povežite jumpere za napajanje sa Arduina na breadboard ili protoboard kako biste omogućili napajanje sistema.
# Konfiguracija

1.  Preuzmite Arduino razvojno okruženje (IDE) sa https://www.arduino.cc/en/software i instalirajte ga na računaru.
2.  Povežite Arduino Uno mikrokontroler sa računarom koristeći USB kabl.
3.  Otvorite Arduino IDE i otvorite projekat PyroSafe.
4.  U meniju Alatke (Tools), izaberite odgovarajući model Arduino mikrokontrolera.
5.  Izaberite pravilan serijski port za komunikaciju sa Arduino mikrokontrolerom.
6.  Uverite se da su sve potrebne biblioteke instalirane. Ako nisu, instalirajte ih iz menija Skeč (Sketch) > Uključi biblioteku (Include Library) > Biblioteke za upotrebu.
7.  U projektu PyroSafe otvorite datoteku config.h i konfigurišite sledeće parametre:
        SSID - Naziv WiFi mreže na koju će se ESP8266 WiFi modul povezati.
        Password - Lozinka za pristup WiFi mreži.
        ServerAddress - IP adresa ili domen udaljenog servera na koji će se slati obaveštenja.
        ServerPort - Port za komunikaciju sa udaljenim serverom.
 8. Sačuvajte promene i učitajte kod na Arduino mikrokontroler pritiskom na dugme Učitaj (Upload).
# Šematski prikaz
<img src="https://i.imgur.com/RvxNfhi.png">
