#include <TM1638.h>
// define a module on data pin 8, clock pin 9 and strobe pin 10
TM1638 module(8, 9, 10);
unsigned long a=1;

int lights[8]{0,0,0,0,0,0,0,0};
int lightsID[8]{8,7,6,5,4,0,0,0};
int lightsIndicatorID[8]{8,7,6,5,4,0,0,0};

int val; 
int ledpin=13; 
byte buttons;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");

  pinMode(lightsID[0], OUTPUT);
  pinMode(lightsID[1], OUTPUT);
  pinMode(lightsID[2], OUTPUT);
  pinMode(lightsID[3], OUTPUT);
  pinMode(lightsID[4], OUTPUT);


  pinMode(ledpin,OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:

   
  fadeLight(0,lights[0],90);
  fadeLight(1,lights[1],random(0, 100));
  fadeLight(2,lights[2],0);
  fadeLight(3,lights[3],random(0, 100));
  fadeLight(4,lights[4],random(0, 100));
  fadeLight(5,lights[5],random(0, 100));
  fadeLight(6,lights[6],random(0, 100));
  fadeLight(7,lights[7],random(0, 100));



for(int i=0;i<100;i++)
{
  buttonPress();
  delay(100);
}
}

void buttonPress()
{
    int buttonId =-1;
    buttons=module.getButtons();
    
    if(buttons == 1)
      buttonId =0;
    else if(buttons == 2)
      buttonId =1;
    else if(buttons == 4)
      buttonId =2;
    else if(buttons == 8)
      buttonId =3;
   else if(buttons == 16)
      buttonId =4;
   else if(buttons == 32)
      buttonId =5;
   else if(buttons == 64)
      buttonId =6;
   else if(buttons == 128)
      buttonId =7;
      
  if (buttonId != -1)
   {  
      if (lights[buttonId] > 0)
        fadeLight(buttonId,lights[buttonId],0);
      else
        fadeLight(buttonId,lights[buttonId],99);
   }
}

void fadeLight(int lightID,int from,int to)
{
  int stepSize = 5;
  int delayTime = 50;

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

    lights[LightID] = value;
    /*
    Serial.print("LightID: ");
    Serial.print(LightID); 
    Serial.print(" Light pin: ");
    Serial.print(lightsID[LightID]); 
    Serial.print(" value: ");
    Serial.print(value); 
    */

    if(value > 5)
    {
      //digitalWrite(lightsID[LightID], HIGH);
      //Serial.print(" ON");
      module.setLED(HIGH, LightID);
           
    }
    if(value <= 5)
    {
      //digitalWrite(lightsID[LightID], LOW);
      //Serial.print(" OFF");
      module.setLED(LOW, LightID);
    }

    String t = ""; 
    for(int i = 0;i<sizeof(lights);i++)
    {
      t+= lights[i]/10;   
    }
    module.setDisplayToString(t);
    Serial.println(t);  
}

