#include <SPI.h>

//master in slave out as output
//master out slave in as input 
//clock as input
//slave select as input which is pull up
const int MISO_PIN = 50, MOSI_PIN = 51, SCK_PIN = 52, SS_PIN = 53;
//volatile cause it changes through program
volatile int ind = 0;
volatile boolean finished = false;
char message[20];

void setup() {
  Serial.begin(9600);
  Serial.println("Starting slave");

  pinMode(MOSI_PIN, INPUT);
  pinMode(MISO_PIN, OUTPUT);
  pinMode(SCK_PIN, INPUT);
  pinMode(SS_PIN, INPUT_PULLUP);
  //set slave in spi mode
  SPCR |= _BV(SPE);
  //set the spi to be sensetive to interrupts
  SPI.attachInterrupt();
}

void loop() {
  if (finished) {
    Serial.println(message);
    ind = 0;
    finished = false;
  }
}
//the interrupt routine of interrupt
ISR (SPI_STC_vect)
{
  //read from shift register byte by byte
  byte c = SPDR;
  //set it into message
  if (ind < sizeof message) {
    message[ind++] = c;

    if (c == '\r') {
      finished = true;
    }
  }
}
