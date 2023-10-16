
const int redLed = 8;
const int sensorPin = A0;

const unsigned long eventInterval = 150;
unsigned long previousTime = 0;
unsigned long currentTime = 0;


const unsigned long eventInterval2 = 1000;
unsigned long previousTime2 = 0;
unsigned long currentTime2 = 0;

const unsigned long eventInterval3 = 1000;
unsigned long previousTime3 = 0;
unsigned long currentTime3 = 0;

const unsigned long eventInterval4 = 1000/6;
unsigned long previousTime4 = 0;
unsigned long currentTime4 = 0;

int gammelVerdi = 0;
int sensorValInn = 0; 
int sensorValOut = 0;
int gjennomsnitt = 0;
int verdi =0;
int index = 0; 
int ledState = LOW;

int sensorValList[4]; 




void setup(){
Serial.begin(115200);
pinMode(redLed,OUTPUT);
pinMode(sensorPin,INPUT);

}

void sensorVerdi(){

unsigned long currentTime = millis();


if (currentTime - previousTime >= eventInterval){
     verdi = verdi - sensorValList[index];
     sensorValInn = analogRead(sensorPin);
     sensorValInn = map (sensorValInn, 0, 1023, 0, 150);
     sensorValList [index] = sensorValInn;
     //verd = 0 ;
     verdi =verdi + sensorValInn;
     index = (index +1) % 4;
     //Serial.println(verdi);
     previousTime = currentTime; 

       //Serial.println(sensorValList[i]);
       
    }


}



void snittverdi(){
    unsigned long currentTime2 = millis();
    if (currentTime2 - previousTime2 >= eventInterval2){
        gjennomsnitt = (verdi ) /5;
        Serial.println(gjennomsnitt);
        previousTime2 = currentTime2; 
    }
}

void blink1(){

        unsigned long currentTime3 = millis();
    if (currentTime3 - previousTime3 >= eventInterval3){
        previousTime3 = currentTime3; 
    
    if (gjennomsnitt >= 100){
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
      digitalWrite(redLed, ledState);
    }


    // set the LED with the ledState of the variable:
    
}
}

void blink6(){
        unsigned long currentTime4 = millis();
    if (currentTime4 - previousTime4 >= eventInterval4){
        previousTime4 = currentTime4; 
        
    if (gjennomsnitt <= 100) {

    if (ledState == LOW){
      ledState = HIGH;
    
    } else {
      ledState = LOW;
    }
    
    digitalWrite(redLed, ledState);
}
}
}

void loop(){
sensorVerdi();
snittverdi();
blink1();
blink6();
}




