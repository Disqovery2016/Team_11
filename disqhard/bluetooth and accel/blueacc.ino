#include <SoftwareSerial.h>

const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

// PIN that the sensor or potentiometer is connected to
//int analogPin = A3;

// Setup the SoftwareSerial connection for our bluemate
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps - Just so we can see on the serial monitor
 pinMode(11,OUTPUT);
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$$$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
}

void loop()
{
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    // Just informational
    Serial.print((char)bluetooth.read());
  }

   // Simply read the value and print it out via println.  This will send the value as ASCII
  int analogValue = analogRead(xpin);
  bluetooth.println(analogValue);
  // Also prints it to the serial monitor, just informational
  Serial.println(analogValue);
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
  delay(3000);
}

