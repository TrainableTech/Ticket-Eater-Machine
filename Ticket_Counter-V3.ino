/////////////////////////////////////////////////
#include <LiquidCrystal.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define TX_PIN 1 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 0 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define button 8
#define revbutton 10
#define sensor 9
#define Motor 7
#define Motor2 6
int Count = 0;
int flag = 0;
unsigned long waitTime = 0;//

void setup() {
  // put your setup code here, to run once:
// Serial.begin(9600);
mySerial.begin(9600);  // Initialize SoftwareSerial
printer.begin();    
pinMode(button, INPUT_PULLUP);
pinMode(revbutton, INPUT_PULLUP);
pinMode(sensor, INPUT);
pinMode(Motor, OUTPUT);
pinMode(Motor2, OUTPUT);
digitalWrite(Motor, LOW);
digitalWrite(Motor2, LOW);
printer.setDefault(); // Restore printer to defaults
 lcd.begin(16, 2);
 lcd.print("Hello!");
 delay(1000);
 printer.setFont('B');
 printer.justify('L');
 printer.setSize('L'); 
//Serial.println("Starting");
}

void loop() {
  // put your main code here, to run repeatedly:
int ButtonState = digitalRead(button);
int RevButtonState = 1;//digitalRead(revbutton);
lcd.setCursor(12,0);

 if(ButtonState==0){

 if (RevButtonState==0) { digitalWrite(Motor, LOW); digitalWrite(Motor2, HIGH); }
 else { digitalWrite(Motor, HIGH); digitalWrite(Motor2, LOW);}
  if(digitalRead(sensor) && flag == 0) {Count++;flag = 1; }
  if(!digitalRead(sensor)){flag = 0;}//
  lcd.setCursor(2,1);
  lcd.print("Tickets = ");
  lcd.print(Count);
  Serial.println(Count);
}
 
 if(ButtonState==1 && Count != 0){
//  digitalWrite(Motor, LOW);
//  digitalWrite(Motor2, LOW);
 printer.wake();       // MUST wake() before printing again, even if reset
 printer.justify('C');
 printer.println(" INDROYDLABS ");
 printer.justify('L');
 printer.println("|  Ticket Counted  |");
 printer.justify('C');
 printer.print("Tickets = ");
 printer.println(Count);
 printer.println(" ");
 delay(2000);
//  flag = 0;
 lcd.clear(); // Clears the display 
 lcd.print("Ticket Counter");
//  printer.justify('L');
 printer.feed(3);
 printer.sleep();      // Tell printer to sleep
  // delay(3000L);         // Sleep for 3 seconds
 Count = 0;
}

if(ButtonState==1 && Count == 0){
 digitalWrite(Motor, LOW);
 digitalWrite(Motor2, LOW);
 flag = 0;
 Count = 0;
}

}
