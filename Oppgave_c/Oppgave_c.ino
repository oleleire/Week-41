const int redLed = 11;      // Definerer pinne for den røde LED
const int greenLed = 13;    // Definerer pinne for den grønne LED
const int yellowLed = 12;   // Definerer pinne for den gule LED
const int buttonPin = 10;   // Definerer pinne for knappen

const unsigned long eventInterval = 850; // Tidsintervall for den gule LEDen som blinker
unsigned long previousTime = 0; // Lagrer forrige tidspunkt for den gule LED-blinkingen
bool ledState = LOW;  // Status for den gule LEDen
bool ledState1 = LOW; // Status for den grønne LEDen
bool ledState2 = HIGH; // Status for den røde LEDen
int buttonState;      // Status for knappen
int lastButtonState = LOW; // Status for knappen ved siste sjekk
int counter = 0; // En teller for å bytte mellom moduser
unsigned long pressedTime = 0; // Tidspunkt for når knappen ble trykket sist
unsigned long debounceDelay = 1000; // Debounce forsinkelse
int lastDebounceTime = 0; // Tidspunkt for siste knappavlesning
int currentTime3 = 0; // Lagrer nåværende tid for funksjonen gultLys()
int currentTime = 0; // Lagrer nåværende tid for funksjonen switchCase()

void setup() {
  Serial.begin(115200);     // Initialiser seriell kommunikasjon
  pinMode(redLed, OUTPUT);   // Setter den røde LED-pinnen som utgang
  pinMode(greenLed, OUTPUT); // Setter den grønne LED-pinnen som utgang
  pinMode(yellowLed, OUTPUT);// Setter den gule LED-pinnen som utgang
  pinMode(buttonPin, INPUT); // Setter knappen som inngang
}

void gultLys() {
  unsigned long currentTime3 = millis();

  if (currentTime3 - previousTime >= eventInterval) {
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(yellowLed, ledState); // Bytter tilstanden til den gule LED
    previousTime = currentTime3; // Oppdater forrige tidspunkt
  }
}

//Modus en som gjør at begge lysene skrur seg på 
void mod2() {
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
}
//Modus to som gjør at den grønne LEDen og den røde LEDen skrur seg av og på vekselsvis ved knappetrykk 

void mod1() {
  buttonState = digitalRead(buttonPin);
  currentTime = millis();

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState == HIGH && (ledState1 == LOW) && (ledState2 == HIGH)) {
      ledState1 = HIGH;
      ledState2 = LOW;
      digitalWrite(redLed, ledState2);   // Slår på den røde LED
      digitalWrite(greenLed, ledState1); // Slår av den grønne LED
      lastDebounceTime = millis();
      //Serial.println("Grønt er på");
    } else if (buttonState == HIGH && (ledState1 == HIGH) && (ledState2 == LOW)) {
      ledState1 = LOW;
      ledState2 = HIGH;
      digitalWrite(redLed, ledState2);   // Slår av den røde LED
      digitalWrite(greenLed, ledState1); // Slår på den grønne LED
      lastDebounceTime = millis();
      //Serial.println("Grønt er av");
    } else {
      Serial.println();
    }
  }
}

void switchCase() {
  unsigned long currentTime2 = millis();
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      if (millis() - pressedTime >= 2000) {
        counter++;
        if (counter == 2) {
          counter = 0;
        }
      }
      //Serial.println("på");
      Serial.println(counter);
    } else {
      //Serial.println("av");
    }
    lastButtonState = buttonState;
    pressedTime = millis();
  }

  switch (counter) {
    case 0:
      mod1();
      //Serial.println("case 0");
      break;
    case 1:
      mod2();
      //Serial.println("case 1");
      break;
  }
}
//Kaller funksjonene 
void loop() {
  gultLys();
  switchCase();
}


/*
Jeg fikk nesten til denne bonusoppgaven, det funket av og til at den greide å bytte moduser, men ikke hele tiden.
Det jeg ikke fikk til var at modus ble endret når knappen blir holdt inne. Ellers funker koden som den skal. 


*/