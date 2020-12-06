const int echoPin = 13;
const int trigPin = 12;   
const int speakerPin =  10;
const int greenLED = 9;  
const int redLED = 8;
const int switchPin = 7; 
const int yellowButton = 5;

void setup() {
  Serial.begin(9600);   
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);  
  pinMode(speakerPin, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
}

float distance = 0;      
bool reset = true;     
bool idle = true;
bool armed = false;
int held_time = 0;
unsigned long start_time = 0;
unsigned long stop_time = 0;
unsigned long elapsed_time = 0;
unsigned long trigger_time = 0;

void loop() {
  distance = getDistance();   

  if (digitalRead(yellowButton) == LOW) {
    reset = true; 
  }

  if (reset == true){ 

    if (distance < 5) {
      
      if (idle == true) {
        trigger_time = millis();
        digitalWrite(redLED, HIGH);
        armed = true;
        idle = false;
      }
      
      if (idle == false and armed == false) {
        stop_time = millis();
        elapsed_time = stop_time - start_time;
        Serial.println(elapsed_time);
        
        if (digitalRead(7)== LOW) {
          tone(speakerPin, 247, 100);
        }
        
        digitalWrite(redLED, HIGH);
        delay(100);
        digitalWrite(redLED, LOW);

        reset = false;
        idle = true;
        held_time = 0;
      }
      
      held_time += 1;
      if (held_time >= 5) {
        digitalWrite(greenLED, HIGH);
        if (held_time == 5 && digitalRead(7) == LOW) {
            tone(speakerPin, 294, 100);
        }
      }
    }
    
    else {
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, LOW);
      if (millis() - trigger_time < 500) {
        held_time = 0;
        idle = true;
        armed = false;
      }
      else if (idle == false and armed == true) {
        start_time = millis();
        armed = false;
      }
    }
  }
  delay(100);
}

float getDistance(){
  float echoTime;                   
  float calculatedDistance;      

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);     
                                         
  calculatedDistance = echoTime / 148.0; 

  return calculatedDistance;             
}
