// defines pins numbers
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

SoftwareSerial bt(8, 9); // RX, TX


Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int trigPin = 5;
const int echoPin = 6;
const int buzzer = 11;
const int ledPin = 13;
//const int buzzer2 = 12;
#define SIGNAL_PIN 4



                           
// defines variables
long duration;
int distance;
int safetyDistance;
double temp_amb;
double temp_obj;
double temp;
double hum;
 
            
void setup() 
  {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
pinMode(SIGNAL_PIN, INPUT);
pinMode( 2 , INPUT );   //for hall
pinMode( 12, OUTPUT); // output of hall

  
  //digitalWrite(13,LOW);






Serial.begin(9600);
bt.begin(9600); // Starts the serial communicationh

Serial.println("Temperature Sensor MLX90614");
Serial.println("Ready");

pinMode(8,OUTPUT);// Connect buzzer at D8
 
  //Initialize MLX90614
  mlx.begin();
  digitalWrite(8,LOW);
}
  
 
 
void loop() 
 {


  //int readData = DHT.read11(dataPin);

  hum = mlx.readObjectTempF();
  temp =  mlx.readObjectTempC();

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
 
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
 
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
 
// Calculating the distance
distance= duration*0.034/2;
 
safetyDistance = distance;
if (digitalRead( SIGNAL_PIN)==HIGH && safetyDistance <= 100)   
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
  Serial.println("movement detected");
  Serial.println("Keep safe distance");
  
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
  Serial.println("Did not detect movement.");
  Serial.println("distance is maintaine.");
  
  
  
}
 
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);


//FOT TEMP




  //mlx.readAmbientTempF() , mlx.readObjectTempF() )
  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();
  if(temp_obj > 37.9) 
    {
   digitalWrite(12,HIGH);
   Serial.print("Warning...HIGH TEMP...");
//   lcd.clear();
  // lcd.print("HIGH TEMP...");
   delay(50);
   }
  else{
    digitalWrite(12,LOW);
  }
 
Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); Serial.print("*C\tObject = ");
Serial.print(mlx.readObjectTempC()); Serial.println("*C");
Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); Serial.print("*F\tObject = "); 
Serial.print(mlx.readObjectTempF()); Serial.println("*F");

Serial.println();
delay(500);

 if( digitalRead(2) == LOW )
   {
       digitalWrite(12,HIGH);
       //Serial.print("wear your mask");
   }
   
 else
        {
       digitalWrite(12,LOW);
        //Serial.print("mask is in proper position");
       
        }

  



 bt.print(temp); //send temp to MIT App
 bt.print(";");
 bt.print(hum); //send temp in degree f to MIT App 
 bt.println(";");
  
 delay(100);
}  
