const int redLed = 11;      // Definer pinne for den røde LED
const int greenLed = 13;    // Definer pinne for den grønne LED
const int yellowLed = 12;   // Definer pinne for den gule LED
const int buttonPin = 10;   // Definer pinne for knappen

const unsigned long eventInterval = 850; // Tidsintervall for den gule LED som blinker
unsigned long previousTime = 0; // Lagrer forrige tidspunkt for den gule LED-blinkingen
unsigned long currentTime = 0;  // Lagrer nåværende tid

unsigned long lastDebounceTime = 0;  // Lagrer siste tidspunkt ett knappetrykk ble oppdaget
unsigned long debounceDelay = 500;   // Knapp forsinkelse 

bool ledState = LOW;  // Initiell status for den gule LED
bool ledState1 = LOW; // Initiell status for den grønne LED
bool ledState2 = HIGH; // Initiell status for den røde LED
int buttonState;      // Initiell status for knappen
int lastButtonState = LOW; // Status for knappen ved siste sjekk

void setup() {
  Serial.begin(115200);     // Initialiser seriell kommunikasjon
  pinMode(redLed, OUTPUT);   // Setter den røde LED-pinnen som utgang
  pinMode(greenLed, OUTPUT); // Setter den grønne LED-pinnen som utgang
  pinMode(yellowLed, OUTPUT);// Setter den gule LED-pinnen som utgang
  pinMode(buttonPin, INPUT); // Setter knappen som inngang
 
}

void gultLys() {
  unsigned long currentTime = millis();  // Henter nåværende tid og setter det lik millis 
// Kode som gjør at den gule LEDen blinker 
  if (currentTime - previousTime >= eventInterval) {
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(yellowLed, ledState); // Bytter tilstanden til den gule LEDen
    previousTime = currentTime; // Oppdater forrige tidspunkt
  }
}

void mod1() {
  buttonState = digitalRead(buttonPin); // Leser tilstanden til knappen
  unsigned long currentTime = millis(); // Henter nåværende tid

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState == HIGH && (ledState1 == LOW) && (ledState2 == HIGH)) {
      ledState1 = HIGH;
      ledState2 = LOW;
      digitalWrite(redLed, ledState2);   // Slår på den røde LED
      digitalWrite(greenLed, ledState1); // Slår av den grønne LED
      lastDebounceTime = millis();
      Serial.println("Grønt er på"); // Skriver ut en melding som sier om den grønne LEDen har blitt slåt på 
    } else if (buttonState == HIGH && (ledState1 == HIGH) && (ledState2 == LOW)) {
      ledState1 = LOW;
      ledState2 = HIGH;
      digitalWrite(redLed, ledState2);   // Slår av den røde LED
      digitalWrite(greenLed, ledState1); // Slår på den grønne LED
      lastDebounceTime = millis();
      Serial.println("Rødt er på"); // Skriver ut en melding som sier om den røde LEDen har blitt slått på
    } 
  }
}


//Kaller funksjonene 
void loop() {
  gultLys(); 
  mod1();    
  }
