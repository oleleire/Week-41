const int redLed = 8;
const int sensorPin = A0;
int sensorValue = 0; 
const int unsigned long eventInterval = 1000;
unsigned long previousTime = 0;



void setup(){
Serial.begin(115200);
pinMode(redLed,OUTPUT);
pinMode(sensorPin,INPUT);

}

void sensorVerdi(){

unsigned long currentTime = millis();

if (currentTime - previousTime >= eventInterval){
sensorValue = analogRead(sensorPin);
     Serial.println(sensorValue);
    
    previousTime = currentTime; 
}

} 






void loop(){
sensorVerdi();
}



/*

Oppgaven: 

- Kaller gjennomsnittfunksjonen (snittet av 5 sensoravlesinger)
- Kaller en av LED-blinke-funksjonene,og hvilken avhenger av verdien gjennomsnittfunksjonen returnerer:

Dersom verdien er 100 eller større skal LEDen blinke 1 gang hvert sekund.
Dersom verdien er mindre enn 100 skal den blinke 6 ganger merkbart raskere
*/

