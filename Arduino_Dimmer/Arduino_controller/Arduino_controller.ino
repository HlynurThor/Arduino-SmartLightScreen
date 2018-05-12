int lights[8]{0,0,0,0,0,0,0,0};

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

  fadeLight(0,10,96);
delay(1000);
  fadeLight(1,90,22);


  delay(10000);
}

void fadeLight(int lightID,int from,int to)
{
  int stepSize = 5;
  int delayTime = 100;

if (from < to)
{
  for(int i=from;i<to;i=i+stepSize)
  {
   
    changeLightStatus(lightID,i);
    delay(delayTime);
  }
   changeLightStatus(lightID,to);
}
else
{
  for(int i=from;i>to;i=i-stepSize)
  {
    changeLightStatus(lightID,i);
    delay(delayTime);
  }
  changeLightStatus(lightID,to);
}

}

void changeLightStatus(int LightID,int value){

    Serial.print("LightID: ");
    Serial.print(LightID); 
    Serial.print(" value: ");
    Serial.print(value); 
    Serial.println();
}

