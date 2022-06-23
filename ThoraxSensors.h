#include "Arduino.h"
#include "ADS7138.h"
#include <Wire.h>

class ThoraxSensors
{
	protected:
	uint8_t	m_i2cAddress;
	uint8_t	m_bitShift;
	
	public:
	uint8_t getI2caddr();
	void sensorAddress(uint8_t i2cAddress); //= i2c_address of the ADS7138 chip
	void begin(void);
	void setup();
	uint16_t i2cstatus();
	uint16_t readAIN(uint8_t channel);
	
};
