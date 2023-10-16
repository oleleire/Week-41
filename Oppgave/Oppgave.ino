
const int redLed = 8;          // Definerer pin-nummeret for LED-en
const int sensorPin = A0;      // Definerer pin-nummeret for photoresistor 


const unsigned long eventInterval = 150;   // Intervall for å lese sensoren
unsigned long previousTime = 0;            // Lagrer forrige tidspunkt for eventInterval
unsigned long currentTime = 0;             // Lagrer gjeldende tidspunkt for eventInterval

const unsigned long eventInterval2 = 1000; // Intervall for å beregne gjennomsnittet
unsigned long previousTime2 = 0;          
unsigned long currentTime2 = 0;            

const unsigned long eventInterval3 = 1000; // Intervall for å blinke LED-en når gjennomsnittet >= 100
unsigned long previousTime3 = 0;           
unsigned long currentTime3 = 0;            

const unsigned long eventInterval4 = 1000/6; // Intervall for å blinke LED-en når gjennomsnittet <= 100
unsigned long previousTime4 = 0;            
unsigned long currentTime4 = 0;             

//Lager globale variabler
int sensorValInn = 0;    
int gjennomsnitt = 0;    
int verdi = 0;           
int ledState = LOW;      

int sensorValList[5];    // Array for å lagre de siste 5 sensormålingene

void setup() {
  Serial.begin(115200);   // Initialiser seriekommunikasjon
  pinMode(redLed, OUTPUT); // Setter den røde LED-en som UTGANG
  pinMode(sensorPin, INPUT); // Setter sensoren som en INNGANG
}

// Leser sensormålingene og oppdaterer listen med de siste 5 målingene
void sensorVerdi() {
  unsigned long currentTime = millis(); 

  if (currentTime - previousTime >= eventInterval) {
    sensorValInn = analogRead(sensorPin); // Leser sensormålingen
    sensorValInn = map(sensorValInn, 0, 1023, 0, 150); // Omgjør sensormålingene fra 0-1023 til 0-150
    previousTime = currentTime; // Oppdater forrige tidspunkt
    verdi = 0; // Nullstiller summen

    for (int i = 0; i < 5; i++) {
      sensorValList[i] = sensorValInn; // Lagrer sensormålingen i arrayen
      verdi = verdi + sensorValList[i]; // Beregn summen av målingene
    }
  }
}

// Beregn og skriv ut gjennomsnittlig sensormåling
void snittverdi() {
  unsigned long currentTime2 = millis(); // Henter gjeldende tid

  if (currentTime2 - previousTime2 >= eventInterval2) {
    gjennomsnitt = verdi / 5; // Beregner gjennomsnittet
    Serial.println(gjennomsnitt); // Skriver ut gjennomsnittet til seriemonitoren 
    previousTime2 = currentTime2; // Oppdaterer forrige tidspunkt
  }
}

// Blink LED-en når gjennomsnittet er større enn eller lik 100
void blink1() {
  unsigned long currentTime3 = millis(); 

  if (currentTime3 - previousTime3 >= eventInterval3) {
    previousTime3 = currentTime3; 

    if (gjennomsnitt >= 100) { //Hvis gjennomsnittet av sensorverdiene er større eller lik 100, blinker led-en en gang hvert sekund 
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(redLed, ledState); 
    }
  }
}

// Blink LED-en når gjennomsnittet er mindre enn eller lik 100
void blink6() {
  unsigned long currentTime4 = millis(); 

  if (currentTime4 - previousTime4 >= eventInterval4) {
    previousTime4 = currentTime4; 

    if (gjennomsnitt <= 100) { //Hvis gjennomsnittet av sensorverdiene er mindre eller lik, blinker led-en seks ganger raskere. 
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(redLed, ledState); 
    }
  }
}

void loop() {
  sensorVerdi();  
  snittverdi();   
  blink1();      
  blink6();       
}
