const int trigPin = 12;         
const int echoPin = 13;
const int speakerPin =  10;
const int switchPin = 7;   
const int redLED = 8;
const int greenLED = 9;
const int yellowButton = 5;
float distance = 0;           

void setup() {

  Serial.begin (9600);   
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowButton, INPUT_PULLUP);
}

bool idle = true;
bool armed = false;
bool reset = true;
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
        held_time = 0;
        stop_time = millis();
        elapsed_time = stop_time - start_time;
        Serial.println(elapsed_time);
        idle = true;
        reset = false;
        
        if (digitalRead(7)== LOW) {
          tone(speakerPin, 247, 100);
        }
        digitalWrite(redLED, HIGH);
        delay(100);
        digitalWrite(redLED, LOW);
        delay(900);
      }
      held_time += 100;
      if (held_time >= 500) {
        digitalWrite(greenLED, HIGH);
        if (held_time == 500 && digitalRead(7) == LOW) {
            tone(speakerPin, 294, 100);
        }
      }
    }
    else {
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, LOW);
      if (millis() - trigger_time < 500) {
        held_time = 0;
        armed = false;
        idle = true;
      }
      else if (idle == false and armed == true) {
        start_time = millis();
        armed = false;
      }
    }
  }
  delay(100);
}

float getDistance()
{
  float echoTime;                   
  float calculatedDistance;      

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);     
                                         
  calculatedDistance = echoTime / 148.0; 

  return calculatedDistance;             
}
