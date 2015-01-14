#include "main.h"

#define PCA9554A_ADDRESS 0x70

//I2C	i2c(I2C1, PB7, PB6);
I2C	i2c(I2C1, PB9, PB6);

int main(void)
{
	char buffer[255] = "";
	char i = 0x01;
	
	Systick_Init();

	buffer[0] = 0x03;	// Control/Status Register
	buffer[1] = 0x00; // All in outputs
	
	i2c.write_b(PCA9554A_ADDRESS, buffer, 2);
	
	buffer[0] = 0x01; // Outputs Register
	buffer[1] = 0x00; // Off
	
	i2c.write_b(PCA9554A_ADDRESS, buffer, 2);
	
  while (1)
  {
		buffer[0] = 0x01;
		buffer[1] = i;
		
		if(i < 0x08) i = i << 1;
		else i = 0x01;
		
		i2c.write_b(PCA9554A_ADDRESS, buffer, 2);
	
		Delay(250);
  }
}