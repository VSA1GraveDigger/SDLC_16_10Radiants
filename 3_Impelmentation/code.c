//Gas and water level management

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
#include "DHT.h"

#define DHTPIN 37  
#define DHTTYPE DHT11

#define echo 9
#define trigger 8
#define waterValve 25
#define gasValve 26
#define gasSensor 23
#define light 22
#define Password_Lenght 7
long duration;
int distance;
int gasleak;
int ldr;
int percentageDistance;

int pos = 0;    // variable to store the servo position

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "147258";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool door = true;

byte rowPins[ROWS] = {35,34,33,32}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 30, 29}; //connect to the column pinouts of the keypad


float h;
float t;

Servo myservo;
LiquidCrystal lcd1(24,7,50,51,52,53);

LiquidCrystal lcd2(24, A1, 50, 51, 52, 53);

LiquidCrystal lcd3(24, 39, 41, 42, 43, 44);
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

DHT dht(DHTPIN, DHTTYPE);

void setup () {
    Serial.begin(9600); 
  Serial.println("DHTxx test!");
 lcd3.begin(16,2);
  dht.begin();

  
myservo.attach(28);
ServoClose();
lcd1.begin(20,4);
pinMode(echo,INPUT);
pinMode(trigger,OUTPUT);
pinMode(gasValve, OUTPUT);
pinMode(waterValve ,OUTPUT);
pinMode(48,OUTPUT);
pinMode(light,INPUT);
pinMode(40,OUTPUT);
digitalWrite(trigger,LOW);
digitalWrite(gasValve,LOW);
digitalWrite(waterValve,LOW);


lcd1.setCursor(0,0);
lcd1.print(" TEAM 16 ");
lcd1.setCursor(0,2);
lcd1.print("    GAS AND WATER");
lcd1.setCursor(0,3);
lcd1.print("  MONITORING SYSTEM");
lcd2.begin(22, 4);
lcd2.print(" Keypad Security");
lcd2.setCursor(0, 1);
lcd2.print("----Door lock---");


delay(10);
lcd1.clear();
lcd2.clear();

}

void loop() {
// ultrasonic reading
  h = dht.readHumidity();
  t = dht.readTemperature();

  
digitalWrite(trigger,LOW);
delayMicroseconds(2);
digitalWrite(trigger,HIGH);
delayMicroseconds(10);
digitalWrite(trigger,LOW);
duration=pulseIn(echo,HIGH);
distance=duration*0.017;
percentageDistance=map(distance,0,1024,0,100);
// gas leakage reading
gasleak=digitalRead(gasSensor);
ldr=digitalRead(light);

if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
 
  lcd3.setCursor(0,0);
  lcd3.print("Temp=");
  lcd3.print(t);
  lcd3.print(" *C");
  lcd3.setCursor(0,1);
  lcd3.print("Humidity=");
  lcd3.print(h);
  lcd3.print("% ");
  delay(50);

  }

  

 if (door == 0)
  {
    customKey = customKeypad.getKey();
    if (customKey == '*')

    {
      lcd2.clear();
      ServoClose();
      lcd2.print(" Door is closed");
      delay(5);
      door = 1;
    }
  }

  else Open();


    if(t>=30)
  {
    digitalWrite(40,HIGH);
  }
  else
  {
    digitalWrite(40,LOW);
  }
  
//call functions
cond1();
cond2();
cond3();
cond4();
cond5();
cond9();
cond10();
cond11();
cond12();
cond13();
cond14();


water();
gas();
lt();
delay(1);
}

void lt(){
  if(ldr==HIGH)
  {
    digitalWrite(48,LOW);
  }
  else
  {
    digitalWrite(48,HIGH);
  }
}



void water(){
if (percentageDistance<50){
digitalWrite(waterValve,HIGH);
}
else
{digitalWrite(waterValve,LOW);
}
}

void gas(){
if (gasleak==HIGH){
digitalWrite(gasValve,LOW);
}
else
{digitalWrite(gasValve,HIGH);
}
}




void cond1(){
if (percentageDistance>50&& gasleak==HIGH)
displayAlloff();
}

void cond2()
{
if(percentageDistance<50&& gasleak==LOW)
displayAllon();
}

void cond3(){
if (percentageDistance<50&& gasleak==HIGH)
displayWon();
}

void cond4(){
if (percentageDistance>50&& gasleak==HIGH)
displayPon();
}

void cond5(){
if (percentageDistance>50&& gasleak==LOW)
displayGon();
}

//OFFS

void cond6(){
if (percentageDistance>50&& gasleak==HIGH)
displayGoff();
}

void cond7(){
if (percentageDistance>50&& gasleak==LOW)
displayPoff();
}
void cond8(){ 
if (percentageDistance>50&& gasleak==HIGH)
displayWoff();
}



void cond9(){
if (percentageDistance<50&& gasleak==LOW)
displayGandWon();
}
void cond10(){ 
if (percentageDistance<50&& gasleak==HIGH)
displayPandWon();
}
void cond11(){
if (percentageDistance>50&& gasleak==LOW)
displayGandPon();
} 
void cond12(){ 
if (percentageDistance>50&& gasleak==HIGH)
displayGandWoff();
}
void cond13(){
if (percentageDistance<50&& gasleak==HIGH)
displayGandPoff();
}
void cond14(){ 
if (percentageDistance>50&& gasleak==LOW)
displayPandWoff();
}

void displayAlloff(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  OFF");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  OFF");
}

void displayPon(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  OFF");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  OFF");
}
void displayWon(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  ON");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  OFF");
}
void displayGon(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  OFF");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  ON");
}
void displayAllon(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  ON");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  ON");
}





void displayGandWon(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  ON");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  ON");
}


void displayPandWon(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  ON");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  OFF");
}
void displayGandPon(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  OFF");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  ON");
}

void displayGandWoff(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  OFF");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  OFF");
}




void displayPandWoff(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  OFF");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  ON");
}

void displayGandPoff(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  ON");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  OFF");
}


void displayGoff(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  ON");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  OFF");
}
void displayPoff(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  ON");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  ON");
}

void displayWoff(){
lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("Water= ");
lcd1.print( percentageDistance);
lcd1.print("%");
lcd1.setCursor(11,0);
lcd1.print("Gas Lk= ");
lcd1.print( gasleak);

lcd1.setCursor(0,2);
lcd1.print("W-VALVE STATUS");
lcd1.print ("  OFF");
lcd1.setCursor(0,3);
lcd1.print("G-VALVE STATUS ");
lcd1.print ("  ON");
}


void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}

void ServoOpen()
{
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void ServoClose()
{
  for (pos = 0; pos <= 180; pos += 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void Open()
{
  lcd2.setCursor(0, 0);
  lcd2.print(" Enter Password");
  
  customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd2.setCursor(data_count, 1); // move cursor to show each new char
    lcd2.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
      lcd2.clear();
      ServoOpen();
      lcd2.print("  Door is Open  ");
      door = 0;
    }
    else
    {
      lcd2.clear();
      lcd2.print(" Wrong Password ");
      delay(10);
      door = 1;
    }
    clearData();
  }
}
