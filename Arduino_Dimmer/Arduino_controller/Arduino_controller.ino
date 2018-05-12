int lights[8]{0,0,0,0,0,0,0,0};
int lightsID[8]{8,7,6,5,4,0,0,0};
int lightsIndicatorID[8]{8,7,6,5,4,0,0,0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");

  pinMode(lightsID[0], OUTPUT);
  pinMode(lightsID[1], OUTPUT);
  pinMode(lightsID[2], OUTPUT);
  pinMode(lightsID[3], OUTPUT);
  pinMode(lightsID[4], OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  fadeLight(0,90,0);
 
  delay(1000);
  fadeLight(1,0,90);
  delay(1000);
  fadeLight(2,90,5);
  delay(1000);
  fadeLight(3,0,20);
  delay(1000);
  fadeLight(4,90,2);

    // watch from wifi if there is change. 

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
    Serial.print(" Light pin: ");
    Serial.print(lightsID[LightID]); 
    Serial.print(" value: ");
    Serial.print(value); 
    

    if(value > 5)
    {
      digitalWrite(lightsID[LightID], HIGH);
      Serial.print(" ON");
    }
    if(value <= 5)
    {
      digitalWrite(lightsID[LightID], LOW);
      Serial.print(" OFF");
    }

    Serial.println();  
}

