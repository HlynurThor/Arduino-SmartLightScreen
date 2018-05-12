#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

// text box where numbers go
#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 50
#define TEXT_TSIZE 3
#define TEXT_TCOLOR ILI9341_MAGENTA
// the data (phone #) we store in the textfield
#define TEXT_LEN 12
char textfield[TEXT_LEN+1] = "";
uint8_t textfield_i=0;

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//Touch For New ILI9341 TP
#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920
// We have a status line for like, is FONA working
#define STATUS_X 10
#define STATUS_Y 65

int DimmerValue =5;

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Elegoo_GFX_Button buttons[30];
bool buttonOn[30] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                             
void setup(void) {

  setupScreen();

 // create 'text field'
  tft.drawRect(10, 10, 220, 50, ILI9341_WHITE);

  // id,width,height,locationX,locationY,spaceX,spaceY,color,text[10]
  int width = 22;
  for(int i=1;i<11;i++)
  {   
        createButton(i,
                    width,40,
                    (width*i),85,
                    0,0,
                    ILI9341_BLACK,"");
   }
         
        width = 105;
        createButton(21,
                    width,60,
                    60,160,
                    10,10,
                    ILI9341_BLACK,"Svefn");

        createButton(22,
                    width,60,
                    180,160,
                    10,10,
                    ILI9341_BLACK,"Stofa");

        createButton(23,
                    width,60,
                    60,240,
                    10,10,
                    ILI9341_BLACK,"Eldhus");

        createButton(24,
                    width,60,
                    180,240,
                    10,10,
                    ILI9341_BLACK,"Bad");


     setDimmer();               
}
// Print something in the mini status bar with either flashstring
void status(const __FlashStringHelper *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}
// or charstring
void status(char *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}
#define MINPRESSURE 10
#define MAXPRESSURE 1000
void loop(void) {

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

   if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
   }
   
 whatButtonPress(p);
  
}

void setupScreen()
{
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;
   
  }

  tft.begin(identifier);
  tft.setRotation(2);
  tft.fillScreen(BLACK);  
}
void ButtonPress(int b,int value)
{
  /*
  Serial.print("Button Id: "); 
  Serial.print(b);
  Serial.print(" value: "); 
  //Serial.print(buttonValue[b]);
  Serial.println();

  if (b == 0)
  {
    setText("1");
  }
  else if (b == 1)
  {
    setText("2");
  }
  else if (b == 2)
  {
    setText("3");
  }
  */
}

void setText(String textInput)
{
   // update the current text field
   Serial.println(textfield);
   tft.setCursor(TEXT_X + 2, TEXT_Y+10);
   tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
   tft.setTextSize(TEXT_TSIZE);
   tft.print(textInput);
}

void setDimmer()
{
  for(int i=1;i<11;i++)
      {
        if (i<=DimmerValue)
        buttons[i].drawButton(true);
        else
        buttons[i].drawButton(false);
        }
}
void whatButtonPress(TSPoint p)
{
   // go thru all the buttons, checking if they were pressed
  for (uint8_t b=1; b<11; b++) {
    if (buttons[b].contains(p.x, p.y)) {
      //Serial.print("Pressing: "); Serial.println(b);
      buttons[b].press(true);  // tell the button it is pressed
      DimmerValue = b;
      setDimmer();
      
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }
 setText(DimmerValue +"");
  
for (uint8_t b=20; b<25; b++) {
    if (buttons[b].contains(p.x, p.y)) {
      buttons[b].press(true);  // tell the button it is pressed     
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }
for(uint8_t b=20;b<25;b++)
{
  if (buttons[b].justPressed()) 
  {
    if (!buttonOn[b])
    {
      buttons[b].drawButton(true); 
      buttonOn[b] = 1;
    }      
    else
    {
      buttons[b].drawButton(false); 
      buttonOn[b] = 0;
    }
     delay(1000);  
  }
      

}

}
void createButton(int buttonId,
                    int width,int height,
                    int locationX,int locationY,
                    int spaceX,int spaceY,
                    uint16_t color,char text[10])
{
  // x, y, w, h, outline, fill, text
  buttons[buttonId].initButton(&tft, locationX, 
                 locationY,    
                  width, height, ILI9341_WHITE, color, ILI9341_WHITE,
                  text, 2); 
                  
      buttons[buttonId].drawButton();
}




