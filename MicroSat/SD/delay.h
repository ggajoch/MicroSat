
#ifndef __delay_h
#define __delay_h

#define DELAY(us)			(DelayAA(((us*(XTAL/1000000))-16)/6))

// ------------------------------------------------------------------
//	Quick and dirty Delay (Chris Efstathiou)
// ------------------------------------------------------------------
void DelayAA(unsigned long us)
{
	// 6 cpu cycles per loop + 16 cycles overhead

	__asm__ volatile (
	"L_%=: \n\t" \
	"subi %A0,lo8(-(-1)) \n\t" \
	"sbci %B0,hi8(-(-1)) \n\t" \
	"sbci %C0,hlo8(-(-1)) \n\t" \
	"sbci %D0,hhi8(-(-1)) \n\t" \
	"brne L_%= \n\t" \
	: /* NO OUTPUT */ \
	: "r" (us) \
	); \

	return;
}

#endif
