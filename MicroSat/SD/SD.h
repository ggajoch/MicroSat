/*
 * SD.h
 *
 * Created: 2013-12-30 00:13:26
 *  Author: rexina
 */ 


#ifndef SD_H_
#define SD_H_

extern "C" {
	#include "pff.h"
	#include "diskio.h"
};
#include <stdio.h>

class SD_
{
	private:
		FATFS SDCard;
		BYTE SDResult;
		volatile DWORD SDOffset;
		bool WorkingSDCard;
		WORD written;
		uint32_t TimeStamp;
		char buf[50];
	public:
		void init();
		void tick()
		{
			++TimeStamp;
			uint8_t len = sprintf(buf,"T%d\n",TimeStamp);
			this->write_buffer(len);
		}
		void write_buffer(uint8_t len)
		{
			pf_write(this->buf, len, &written);
		}
		
	#define WRITE_DATA_TO_SD(var) void write_data(uint8_t code, var val) { 	\
								  uint8_t len = sprintf(buf,"%c%d\n",code,val); \
								  this->write_buffer(len); \
								  }
		
		WRITE_DATA_TO_SD(uint8_t)
		WRITE_DATA_TO_SD(uint16_t)
		WRITE_DATA_TO_SD(uint32_t)
		bool check(BYTE result)
		{
			if( result != FR_OK )
			{
				WorkingSDCard = false;
				return false;
			}
			return true;
		}
		void end_block()
		{
			pf_write(0,0,&written);
		}
};

extern SD_ SD;

#endif /* SD_H_ */