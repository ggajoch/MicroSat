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
#include "MicroSat.h"
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
	public:
		void init();
		void tick()
		{
			++this->TimeStamp;
			sprintf(buffer,"T%ld\n",(long)(this->TimeStamp));
			this->write_buffer();
		}
		void write_buffer()
		{
			uint8_t len = strlen(buffer);
			pf_write(buffer, len, &written);
		}
		
		void log(const char* c) {
			strcpy(buffer, c);
			write_buffer();
		}
		
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