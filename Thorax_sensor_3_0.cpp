/*


*/


#include "ThoraxSensors.h"
#include <Wire.h>
#include "wiring_private.h" // pinPeripheral() function

TwoWire myWire(&sercom2, 4, 3);

static uint8_t i2cread(void) {
  return myWire.read();
}

static void i2cwrite(uint8_t x) {
	myWire.write((uint8_t)x);
}

static uint16_t readRegister(uint8_t i2cAddress, uint8_t reg) {
	myWire.beginTransmission(i2cAddress);
	myWire.requestFrom(i2cAddress, (uint8_t)1);
	return (myWire.read());
}

static void writeRegister(uint8_t i2cAddress, uint8_t registerAdress, uint8_t registerValue)
{
	myWire.beginTransmission(i2cAddress);
	myWire.write((uint8_t)0x08);
	myWire.write((uint8_t)registerAdress);
	myWire.write((uint8_t)(registerValue));
	myWire.endTransmission();
}

void ThoraxSensors::sensorAddress(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
}

uint16_t ThoraxSensors::i2cstatus()
{
	return readRegister(SYSTEM_STATUS_REG_MASKadd, SYSTEM_STATUS_I2C_SPEED);
}

uint8_t ThoraxSensors::getI2caddr()
{
	return m_i2cAddress;
}

 void ThoraxSensors::begin()
{
	myWire.begin();
	pinPeripheral(4, PIO_SERCOM_ALT);
	pinPeripheral(3, PIO_SERCOM_ALT);
}

void ThoraxSensors::setup()
{	
	writeRegister(m_i2cAddress, PIN_CFG_MASKadd, PIN_CFG_RESET);					// Sets all Pins to AIN Functionality
	writeRegister(m_i2cAddress, OPMODE_CFG_MASKadd, OPMODE_CFG_CONV_MODE_MANUAL);		// Sets ADC to autonomous							
	writeRegister(m_i2cAddress, SEQUENCE_CFG_MASKadd, SEQUENCE_CFG_SEQ_MODE_MANUAL);	// Sets Sequence in auto mode	
	
}

uint16_t ThoraxSensors::readAIN(uint8_t channel)
{
	switch(channel)
	{
		case 0:
			writeRegister(m_i2cAddress, CHANNEL_SEL_MASKadd, CHANNEL_SEL_AIN_0);
			break;
		
		case 1:
			writeRegister(m_i2cAddress, CHANNEL_SEL_MASKadd, CHANNEL_SEL_AIN_1);
			break;

		case 2:
			writeRegister(m_i2cAddress, CHANNEL_SEL_MASKadd, CHANNEL_SEL_AIN_2);
			break;

		case 3:
			writeRegister(m_i2cAddress, CHANNEL_SEL_MASKadd, CHANNEL_SEL_AIN_3);
			break;

		case 4:
			writeRegister(m_i2cAddress, CHANNEL_SEL_MASKadd, CHANNEL_SEL_AIN_4);
			break;

		case 5:
			writeRegister(m_i2cAddress, CHANNEL_SEL_MASKadd, CHANNEL_SEL_AIN_5);
			break;

		case 6:
			writeRegister(m_i2cAddress, CHANNEL_SEL_MASKadd, CHANNEL_SEL_AIN_6);
			break;

		case 7:
			writeRegister(m_i2cAddress, CHANNEL_SEL_MASKadd, CHANNEL_SEL_AIN_7);
			break;
			
		default:
			return 9999;
			break;

	}
	//channel = 2 * channel;
	//uint8_t address = 0x60 + channel;
	
	return readRegister(m_i2cAddress, 0x62);
}