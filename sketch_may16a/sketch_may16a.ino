#include <TM1638.h>
// define a module on data pin 8, clock pin 9 and strobe pin 10
TM1638 module(8, 9, 10);
unsigned long a=1;
 
void setup()
{
}
 
void loop()
{
  module.setDisplayToString("x1x xxxx");
  /*
for (a=1; a<=10000; a++)
{
module.setDisplayToDecNumber(a,2,false);
delay(10);
}
module.setDisplayToString("Complete");
delay(1000);
*/
}
