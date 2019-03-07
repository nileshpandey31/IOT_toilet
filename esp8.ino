#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
#define FIREBASE_HOST "finalmq135.firebaseio.com"
#define WIFI_SSID "MI A1"//change the name of your WIFI
#define WIFI_PASSWORD "00000000" // Change the password of your WIFI
#define FIREBASE_AUTH "68dtvxJjmUYoy4RGbxqGOKWoAFPM4sQskDd5sBFy"
  
#define fled 5//d1
#define sled 16//d0;
#define wled 3//RX

int x = 0;
int pbuttonPin = 2;// D4 connect output to push button
int relayPin = 14;//D5 Connected to relay (LED)
int relaypinf = 10; //fan relay
int val = 0; // push value from pin 2
int lightON = 0;//light status
int pushed = 0;
float a,b,c,d,e,f,g,h,l,n;

int y = 0;
float m[10];
int k = 0;
int sensorValue1[10];
float sum = 0;
int i;
int j = 1;
float average[11];
int Irsensor = 13; //D7
int sensorValue;
int Floatsensor = 4; //D2
int Buttonstate = 1; //
int laststate = HIGH;
int count = 0;

#define trig1 12//d6int 
#define echo1 15//d8

void setup() {
  Serial.begin(9600);
  pinMode(fled,OUTPUT);
  pinMode(sled,OUTPUT);
  pinMode(wled,OUTPUT);
  pinMode(pbuttonPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  pinMode(relaypinf, OUTPUT);
 
  pinMode(Irsensor, INPUT);
  pinMode(0, INPUT);
  pinMode(Floatsensor, INPUT_PULLUP);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  Firebase.setFloat ("average1", 0);
  Firebase.setFloat ("average2", 0);
  Firebase.setFloat ("average3", 0);
  Firebase.setFloat ("average4", 0);
  Firebase.setFloat ("average5", 0);
  Firebase.setFloat ("average6", 0);
  Firebase.setFloat ("average7", 0);
  Firebase.setFloat ("average8", 0);
  Firebase.setFloat ("average9", 0);
  Firebase.setFloat ("average10", 0);

  // put your setup code here, to run once:

}

void loop() {

  // for irsensor

 
  float duration, distance;
  val = digitalRead(pbuttonPin);// read the push button value
  long state = digitalRead(Irsensor);
  if (state == HIGH)
  { Serial.println(" stall unoccupied");

  }

  else
  { Serial.println(" stall occupied");
  }
  // This segment is for auto flush



  if (val == HIGH && lightON == LOW) {

    pushed = 1 - pushed;
    delay(100);
  }

  lightON = val;

  if (pushed == HIGH) {
    Serial.println("Light OFF");
    digitalWrite(relayPin, LOW);
    digitalWrite(relaypinf, LOW);
    Serial.println(pushed);
  } else {
    
    Serial.println("Light ON");
    digitalWrite(relayPin, HIGH);
    delay(5000);
    
    x = 1;
    Serial.println(pushed);
   
    pushed = 1;}
  



  // only count on a LOW-> HIGH transition


  if (laststate == LOW && state == HIGH)
  {
    count++;
    Serial.print("count:");
    Serial.println(count);
    Firebase.setFloat ("count", count);

    if (x == 0)
    {

      Serial.println("not flushed");
      digitalWrite(relayPin, HIGH);
      delay(2000);
      digitalWrite(relayPin, LOW);


    }
    else
    {
      x = 0;
    }
    //delay(1000);
  }
  laststate = state;  // remember last state



  // for septic tank

  Buttonstate = digitalRead(Floatsensor);
  if (Buttonstate == HIGH)
  {

    Serial.println( "Septic WATER LEVEL - HIGH");
    Firebase.setString("septic", "High");
    digitalWrite(fled, HIGH);


  }
  else
  {

    Serial.println( "Septic WATER LEVEL - LOW" );
    Firebase.setString("septic", "Low");
    digitalWrite(fled, LOW);



  }


  //water level


  digitalWrite(trig1, LOW);

  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);

  duration = pulseIn(echo1, HIGH);

  distance = duration / 58;
  Serial.print(distance);
  Serial.println(" cm");
  if (distance <= 10)
  {Serial.println("water tank level high");
    Firebase.setString("waterlevel", "high");
    digitalWrite(wled, LOW);
    
  }
  else
  {
    Serial.println("water tank level low");
    Firebase.setString("waterlevel", "low");
    digitalWrite(wled, HIGH);


  }



  // for smell sensor


  sensorValue = analogRead(0);
  m[k] = sensorValue;
  Serial.print("MQ135:");
  Serial.println(sensorValue);

  if (sensorValue >= 250)
  {
    Serial.println("high smell");
    digitalWrite(relaypinf, HIGH);
    digitalWrite(sled, HIGH);

    delay(5000);
    

  }

  else
  {
    Serial.println("low smell");
    digitalWrite(relayPin, LOW);
    digitalWrite(sled, LOW);

  }
  Firebase.setFloat ("mq", sensorValue);

  

  // AVERAGE OF MQ135


  while (true)
  {
    sum = sum + m[k];
    k = k + 1;
    break;
    // Serial.println(sum);
    //delay(1000);
  }
  if (k == 10)
  {  
    average[j] = sum / 10;
    sum = 0;
    Serial.print("average:");
    Serial.print(j);
    Serial.print("\t");
    Serial.println(average[j]);
    if(j==1)
    {
       a=average[1];
    Firebase.setFloat ("average1",a);
      }
   else if(j==2)
   {
    b=average[2];
    Firebase.setFloat ("average2",b);
   }
    else if(j==3)
    {c=average[3];
    Firebase.setFloat ("average3",c);
    }
    else if(j==4)
    {
    d=average[4];
    Firebase.setFloat ("average4",d);
    }
    else if(j==5)
    {e=average[5];
    Firebase.setFloat ("average5",e);
    }
    else if(j==6)
    {
    f=average[6];
    Firebase.setFloat ("average6",f);
    }
    else if(j==7)
    {
    g=average[7];
    Firebase.setFloat ("average7",g);
    }
    else if(j==8)
    {
    h=average[8];
    Firebase.setFloat ("average8",h);
    }
    else if(j==9)
    {
    l=average[9];
    Firebase.setFloat ("average9",l);
    }
    else if(j==10)
    {
    n=average[10];
    Firebase.setFloat ("average10",n);
    delay(2000);
    Firebase.setFloat ("average1", 0);
  Firebase.setFloat ("average2", 0);
  Firebase.setFloat ("average3", 0);
  Firebase.setFloat ("average4", 0);
  Firebase.setFloat ("average5", 0);
  Firebase.setFloat ("average6", 0);
  Firebase.setFloat ("average7", 0);
  Firebase.setFloat ("average8", 0);
  Firebase.setFloat ("average9", 0);
  Firebase.setFloat ("average10", 0);

    j=0;
      
    }
    
    j = j + 1;
    k = 0;

    delay(100);
  }
  
  Serial.print("reading");
  y = y + 1;
  Serial.println(y);

  /*

    // DUSTBIN


    digitalWrite(trig2, LOW);

    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);

    duration2 = pulseIn(echo2, HIGH);

    distance2 = duration2 / 58;
    Serial.print("Dustbin level:");
    Serial.print(distance2);
    Serial.println(" cm");
    if (distance2 <= 5)
    {
      Serial.println("dustin is full");
      Firebase.setString("dustbin", "full");
    }
    else
    {
      Serial.println("dustbin is not full");
      Firebase.setString("dustbin", "not full");
    }

  */
}
