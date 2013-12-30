/*
 * SD.cpp
 *
 * Created: 2013-12-30 00:13:06
 *  Author: rexina
 */ 
#include "SD.h"
extern "C" {
	#include "pff.h"
	#include "diskio.h"
};
__attribute__((always_inline))
void SD_::init()
{
#ifdef SKIPBLANKSD
	this->WorkingSDCard = true;
	while ( ! check( pf_mount(&this->SDCard) ) );


	while ( ! check( pf_open("data.txt") ));

	this->SDOffset = 0;
	while ( ! check( pf_lseek(this->SDOffset) ));
	WORD written;
	while ( ! check (pf_write(0,0,&written));

	if( WorkingSDCard )
	{
		char InputBuffer[512];
		WORD size;
		while(true)
		{
			pf_read(&InputBuffer, 512, &size);
			if((InputBuffer[0] == '%' && InputBuffer[1] == '$') || (InputBuffer[1] == '%' && InputBuffer[0] == '$'))
			{
				this->SDOffset += 512;
				pf_lseek(this->SDOffset);
				return;
			}
			this->SDOffset += 512;
			pf_lseek(this->SDOffset);
		}
	}
#else
	WorkingSDCard = true;
	while ( ! check( pf_mount(&this->SDCard) ));


	while ( ! check( pf_open("data.txt") ));

	this->SDOffset = 0;
	while ( ! check( pf_lseek(this->SDOffset) ));
#endif
}
