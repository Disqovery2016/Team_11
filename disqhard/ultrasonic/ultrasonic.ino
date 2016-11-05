/* Ping))) Sensor

 */
const int trig = 8;
const int echo = 7;
const int buzzer = 13;
void setup() {
  // initialize serial communication: 
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(buzzer,OUTPUT);
  delay(100); 
}

void loop()
{
  
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
  
  if(cm<30){
    Serial.print("alert approaching an object \n ");
    digitalWrite(buzzer,HIGH);
  }
    
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
