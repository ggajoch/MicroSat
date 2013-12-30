#include <stdint.h>
#include <stdlib.h>
#include "TWI.h"

uint8_t TWI_Init(uint32_t TWI_Bitrate)
{
  TWBR = ((F_CPU / TWI_Bitrate) - 16) / 2;
  if (TWBR < 11)
    return 0;

  return 1;
}
uint8_t TWI_Start(uint8_t address, uint8_t TWI_Type)
{
  uint8_t twst;
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  twst = TW_STATUS;
  if ((twst != TW_START) && (twst != TW_REP_START))
    return 0;
  TWDR = (address << 1) + TWI_Type;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  twst = TW_STATUS;
  if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK))
    return 0;

  return 1;
}
void TWI_Stop ()
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  while (TWCR & (1 << TWSTO));
}
uint8_t TWI_Write(uint8_t toSend)
{
  uint8_t   twst;
  TWDR = toSend;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  twst = TW_STATUS;
  if (twst != TW_MT_DATA_ACK)
    return 1;

  return 0;
}
uint8_t TWI_ReadAck()
{
  TWCR =  (1 << TWINT)| (1 << TWEN)| (1 << TWEA);
  while (!(TWCR &  (1 << TWINT)));

  return TWDR;
}
uint8_t TWI_ReadNack()
{
  TWCR =  (1 << TWINT)| (1 << TWEN);
  while (!(TWCR &  (1 << TWINT)));

  return TWDR;
}


/*uint8_t TMP100_Init(uint8_t tmpAddress, const uint8_t ResolutionBits)
{
  if (!TWI_Start (tmpAddress, TW_WRITE))
  {
    TWI_Stop ();
    Serial.println ("Could not start TWI Bus for WRITE\n");
    return 0;
  }
  else
  {
    TWI_Write (1);
    TWI_Write ((ResolutionBits-9) << 5);
    TWI_Stop ();
  }
  if (!TWI_Start (tmpAddress, TW_WRITE))
  {
    TWI_Stop ();
    Serial.println ("Could not start TWI Bus for WRITE\n");
        return 0;
  }
  else
  {
    TWI_Write (0);		
    TWI_Stop ();
  }
  return 1;
}

uint32_t TMP100_GetTemperature(uint8_t tmpAddress)
{
  if (!TWI_Start (tmpAddress, TW_READ))
  {
    TWI_Stop ();
    Serial.println ("Could not start TWI Bus for WRITE\n");
    return 0;
  }
  else
  {
    uint16_t MSB = TWI_ReadAck ();
    uint16_t LSB = TWI_ReadNack ();
    uint16_t TemperatureSum = ((MSB << 8) | LSB) >> 4;
    uint32_t celsius = ((double)TemperatureSum * 62.5);
    TWI_Stop ();
    return celsius;
  }
}
uint16_t TMP100_GetRawData(uint8_t tmpAddress)
{
  if (!TWI_Start (tmpAddress, TW_READ))
  {
    TWI_Stop ();
    Serial.println ("Could not start TWI Bus for WRITE\n");
    return 0;
  }
  else
  {
    uint16_t MSB = TWI_ReadAck ();
    uint16_t LSB = TWI_ReadNack ();
    uint16_t TemperatureSum = ((MSB << 8) | LSB) >> 4;
    TWI_Stop ();
    return TemperatureSum;
  }
}
*/