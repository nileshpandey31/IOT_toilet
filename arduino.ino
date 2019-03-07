#define trig 9
#define echo 13   // dustbin


#define trig2 12   // basin
#define echo2 8

#define trig1 2
#define echo1 7   // urinal
#define relay 4

#define dled 3
#define bled 5


void setup() {
  Serial.begin (9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  
  pinMode(relay, OUTPUT);
  
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(relay, OUTPUT);

  pinMode(bled, OUTPUT);
  pinMode(dled, OUTPUT);
  

  
}

void loop() {

//DUSTBIN
  float duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration / 58;
  Serial.print("dustbin distance :");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 5)
  {
    
    digitalWrite(dled, HIGH);
    
  }
  else
  {
    digitalWrite(dled, LOW);
  }

  //  delay(3000); 

  //basin

  float duration2, distance2;
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = duration2 / 58;
  Serial.print("basin distance:");
  Serial.print(distance2);
  Serial.println(" cm");
  if (distance2 <= 8)
  {
    
    digitalWrite(bled, HIGH);
    
  }
  else
  {
    digitalWrite(bled, LOW);
  }

  
  
  float duration1, distance1;
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = duration1 / 58;
  Serial.print("urinal distance:");
  Serial.print(distance1);
  Serial.println(" cm");
  if (distance1 <= 7)
  {
    delay(3000);
    digitalWrite(relay, HIGH);
    delay(3000);
    digitalWrite(relay,LOW);
  }
  else
  {
    digitalWrite(relay, LOW);
  }

    
  delay(1000);



}
