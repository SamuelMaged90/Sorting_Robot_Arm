/************* Project Libraries **************************************************/
#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>
/*************** Ultrasonic Pins ***************************************************/
int trig = 7;
int echo = 11;
/********* Max Distance For Ultrasonic ********************************************/
int max_dis = 200;
/********* Initial Value For Bluetooth Module variables ***************************/
int Red = 0;
int Green = 0;
int Yellow = 0;
/****************** Configurations Functions****************************************/
SoftwareSerial bluetooth(A0, A1);  /* RX , TX */
NewPing sonic(trig, echo, max_dis); /* For Ultrasonic */
/****************** Color Sensor Pins **********************************************/
#define s0 13
#define s1 9
#define s2 10
#define s3 12
#define SensorOut 8
/****************** Initial Variable for The Reading Of Color Sensor ***************/
int red = 0;
int green = 0;
int blue = 0;
/****************** Initialize 5 Servo *********************************************/
Servo base;
Servo sholder;
Servo elbow;
Servo base2;
Servo gribber;
/**************** Base Initail Pos**************************************************/
int pos = 168;
/***********************************************************************************/
void setup() 
{
  /********************* Data Sending Speed ****************************************/
  Serial.begin(9600);
  bluetooth.begin(9600);
  /**************** configuration Color Sensor pins ********************************/
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(SensorOut, INPUT);
  /************************ Scale of the Color Sensor ******************************/
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  /******************* Attaching each servo to arduino pin *************************/
  base.attach(2);
  sholder.attach(3);
  elbow.attach(4);
  base2.attach(5);
  gribber.attach(6);
  /**************** Initial Position to each servo *********************************/
  base2.write(155);
  sholder.write(10);
  elbow.write(80);
  gribber.write(80);
  base.write(pos);
}
void loop() 
{
  /*************** Calculating Distance and print it on serial monitor *************/ 
  int us = sonic.ping();
  int dis = us / US_ROUNDTRIP_CM;
  Serial.print("ping :");
  Serial.println(dis);
  delay(500);
  /* Check if there is an object in front of the ultrasonic sensor , and take action between 9 --> 11 cm only */
  if (dis >= 9 && dis <= 11) {
    /**** Start sensing red color and print it on serial monitor ****/
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = pulseIn(SensorOut, LOW); 
    Serial.print("R= ");
    Serial.print(red);
    Serial.print("   ");
    delay(100);
    /**** Start sensing blue color and print it on serial monitor ****/  
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    blue = pulseIn(SensorOut, LOW); 
    Serial.print("B= ");
    Serial.print(blue);
    Serial.print("   ");
    delay(100);
    /**** Start sensing green color and print it on serial monitor ****/
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    green = pulseIn(SensorOut, LOW); 
    Serial.print("G= ");
    Serial.print(green);
    Serial.print("   ");
    delay(300);
    /* Check if the object was red , take it by the robot and move to the location that 
       i determined , and send numbers of red objects to mobile application every time */
    if ((red >= 11 && red <= 18)) {  
      Red++;
      bluetooth.print(Red);
      bluetooth.print(",");
            bluetooth.print(Green);
      bluetooth.print(",");
            bluetooth.print(Yellow);
      bluetooth.print(";");
      delay(30);      
      for (int i = 10; i < 25; i++) {
        sholder.write(i);
        delay(20);
      }
      for (int i = 80; i >55; i--) {
        elbow.write(i);
        delay(20);
      }
      gribber.write(5);
      delay(700);
      for (int i = 25; i > 10; i--) {
        sholder.write(i);
        delay(20);
      }
      for (int i = 55; i < 80; i++) {
        elbow.write(i);
        delay(20);
      }
      for (int i = pos; i > 80; i--) {
        base.write(i);
        delay(20);
      }
      for (int i = 10; i <= 25; i++) {
        sholder.write(i);
        delay(20);
      }
      for (int i = 80; i > 65; i--) {
        elbow.write(i);
        delay(20);
      }
      for (int i = 155; i > 120; i--) {
        base2.write(i);
        delay(20);
      }
      delay(700);
      gribber.write(90);
      delay(700);
      for (int i = 120; i <= 155; i++) {
        base2.write(i);
        delay(20);
      }
      delay(800);
      for (int i = 25; i >= 10; i--) {
        sholder.write(i);
        delay(20);
      }
      for (int i = 65; i < 80; i++) {
        elbow.write(i);
        delay(20);
      }
      for (int i = 80; i <= pos; i++) {
        base.write(i);
        delay(20);
      }
    }
    /* Check if the object was green , take it by the robot and move to the location that 
       i determined , and send numbers of green objects to mobile application every time */
    else if (red >= 35 && red <= 44) 
    {
      Green++;
      bluetooth.print(Red);
      bluetooth.print(",");
            bluetooth.print(Green);
      bluetooth.print(",");
            bluetooth.print(Yellow);
      bluetooth.print(";");
      delay(30);      
      for (int i = 10; i < 25; i++) {
        sholder.write(i);
        delay(20);
      }
      delay(300);
      for (int i = 80; i >55; i--) {
        elbow.write(i);
        delay(20);
      }
      gribber.write(5);
      delay(800);
      for (int i = 25; i > 10; i--) {
        sholder.write(i);
        delay(20);
      }
      delay(300);
      for (int i = 55; i < 80; i++) {
        elbow.write(i);
        delay(20);
      }
      for (int i = pos; i > 35; i--) {
        base.write(i);
        delay(20);
      }
      for (int i = 10; i <= 25; i++) {
        sholder.write(i);
        delay(20);
      }
      delay(300);
      for (int i = 80; i >65; i--) {
        elbow.write(i);
        delay(20);
      }
      delay(300);
      for (int i = 155; i > 120; i--) {
        base2.write(i);
        delay(20);
      }
      delay(600);
      gribber.write(90);
      delay(600);
      for (int i = 120; i <= 155; i++) {
        base2.write(i);
        delay(20);
      }
      delay(300);
      for (int i = 25; i >= 10; i--) {
        sholder.write(i);
        delay(20);
      }
      delay(300);
      for (int i = 65; i < 80; i++) {
        elbow.write(i);
        delay(20);
      }
      for (int i = 35; i <= pos; i++) {
        base.write(i);
        delay(20);
      }
    }
     /* Check if the object was Yellow , take it by the robot and move to the location that 
       i determined , and send numbers of Yellow objects to mobile application every time */   
     else if (blue >= 12 && blue <= 18)  
    {
      Yellow++;
      bluetooth.print(Red);
      bluetooth.print(",");
            bluetooth.print(Green);
      bluetooth.print(",");
            bluetooth.print(Yellow);
      bluetooth.print(";");
      delay(30);      
      for (int i = 10; i < 25; i++) {
        sholder.write(i);
        delay(20);
      }
      for (int i = 80; i > 55; i--) {
        elbow.write(i);
        delay(20);
      }
      gribber.write(0);
      delay(800);
      for (int i = 25; i > 10; i--) {
        sholder.write(i);
        delay(20);
      }
      for (int i = 55; i < 80; i++) {
        elbow.write(i);
        delay(20);
      }
      for (int i = pos; i > 130; i--) {
        base.write(i);
        delay(20);
      }
      for (int i = 10; i <= 25; i++) {
        sholder.write(i);
        delay(20);
      }
      for (int i = 80; i > 65; i--) {
        elbow.write(i);
        delay(20);
      }
      for (int i = 155; i > 120; i--) {
        base2.write(i);
        delay(20);
      }
      delay(800);
      gribber.write(90);
      delay(800);
      for (int i = 120; i <= 155; i++) {
        base2.write(i);
        delay(20);
      }
      delay(800);
      for (int i = 25; i >= 10; i--) {
        sholder.write(i);
        delay(20);
      }
      for (int i = 65; i < 80; i++) {
        elbow.write(i);
        delay(20);
      }
      for (int i = 130; i <= pos; i++) {
        base.write(i);
        delay(20);
      }
    }
  }
}
