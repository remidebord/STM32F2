#include "main.h"

/* SPI config (CS, SCK, MOSI, MISO) */
SPI spi(SPI1, PA4, PA5, PA7, PA6);

int main(void)
{
  Systick_Init();
	
  while (1)
  {	
		spi.cs(0);
		spi.write(0xA5);
		spi.cs(1);
		
		Delay(1);
  }
}
