#include <SPI.h>

// Hardware SPI connections
#define CLK	13
#define DIN	11
#define DC	5
#define CE	4
#define RST	3
  
void command(byte c)
{
  digitalWrite(DC, LOW);
  digitalWrite(CE, LOW);
  SPI.transfer(c);
  digitalWrite(CE, HIGH);
}

void setup()   
{
  Serial.begin(115200);

  // Setup hardware SPI.
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  // Set common pin outputs.
  pinMode(DC, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
 
  digitalWrite(RST, HIGH);
  
  command(0x20 | 0x01 ); //  EXTENDED mode
  command(0x10 | 4);     //  Set bias = 4 
  command(0x80 | 50);    //  Set contrast = 50
  command(0x20);         //  NORMAL mode
  command(0x08 | 0x4);   //  Set display to Normal
  
  digitalWrite(DC, HIGH);
  digitalWrite(CE, LOW);
}

void loop() 
{
  while (Serial.available())
  {
    SPI.transfer(Serial.read());
  }
}
