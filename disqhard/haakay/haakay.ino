
const int trig = 8;
const int echo = 7;
const int buzzer = 13;
const int xpin = A3;                  // x-axis of the accelerometer

const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

void setup()
{
  // initialize the serial communications:
 pinMode(11,OUTPUT); 
 Serial.begin(9600);
 pinMode(buzzer,OUTPUT);
 delay(100); 
}

void loop()
{
  // print the sensor values:
  Serial.print(analogRead(xpin));

  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(ypin));

  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(zpin));
  Serial.println();

 if(analogRead(ypin)<335)
 {
   digitalWrite(11,HIGH);
   delay(1000);
   digitalWrite(11,LOW);
 }
  
  digitalWrite(buzzer,LOW);
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if(cm<10){
    Serial.print("alert approaching an object \n ");
    digitalWrite(buzzer,HIGH);
  }
  // delay before next reading:
  delay(100);
  
}


long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
