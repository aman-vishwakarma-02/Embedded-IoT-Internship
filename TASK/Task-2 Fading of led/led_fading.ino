int ledPin = 11;
int potPin = A5;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int Value = analogRead(potPin);  
  int B = Value / 10;               

  Serial.println(B);

  
  digitalWrite(ledPin, HIGH);
  delayMicroseconds(B * 20);        

  digitalWrite(ledPin, LOW);
  delayMicroseconds((102 - B) * 20); 
}

