// Interface RGB Led and Control with switch ,1st click on the switch Red led On , 2nd click Green led On and 3rd click Blue led On ,if more then 3 click it will be reset again




const int redPin = 12;
const int greenPin = 10;
const int bluePin = 11;
const int buttonPin = 5;

int buttonState = 0;
int lastButtonState = 1;
int count = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  buttonState = digitalRead(buttonPin);

 
  if (lastButtonState == HIGH && buttonState == LOW) {
    count++;
    
  }

  lastButtonState = buttonState;

  if (count == 1) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  else if (count == 2) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }
  else if (count == 3) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }
  else if (count >= 4) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    count = 0;   // Reset counter
  }
}

