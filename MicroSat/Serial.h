/*
 * Serial.h
 *
 * Created: 2012-12-29 02:27:29
 *  Author: rexina
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#define REGGEN0_UBRR0H UBRR0H
#define REGGEN1_UBRR0H UBRR1H
#define REGGEN2_UBRR0H UBRR2H
#define REGGEN3_UBRR0H UBRR3H
#define REGGEN0_UCSZ00 UCSZ00
#define REGGEN1_UCSZ00 UCSZ10
#define REGGEN2_UCSZ00 UCSZ20
#define REGGEN3_UCSZ00 UCSZ30
#define REGGEN0_UBRR0L UBRR0L
#define REGGEN1_UBRR0L UBRR1L
#define REGGEN2_UBRR0L UBRR2L
#define REGGEN3_UBRR0L UBRR3L
#define REGGEN0_RXEN0 RXEN0
#define REGGEN1_RXEN0 RXEN1
#define REGGEN2_RXEN0 RXEN2
#define REGGEN3_RXEN0 RXEN3
#define REGGEN0_TXEN0 TXEN0
#define REGGEN1_TXEN0 TXEN1
#define REGGEN2_TXEN0 TXEN2
#define REGGEN3_TXEN0 TXEN3
#define REGGEN0_UCSR0A UCSR0A
#define REGGEN1_UCSR0A UCSR1A
#define REGGEN2_UCSR0A UCSR2A
#define REGGEN3_UCSR0A UCSR3A
#define REGGEN0_UCSR0B UCSR0B
#define REGGEN1_UCSR0B UCSR1B
#define REGGEN2_UCSR0B UCSR2B
#define REGGEN3_UCSR0B UCSR3B
#define REGGEN0_UCSR0C UCSR0C
#define REGGEN1_UCSR0C UCSR1C
#define REGGEN2_UCSR0C UCSR2C
#define REGGEN3_UCSR0C UCSR3C
#define REGGEN0_UDRE0 UDRE0
#define REGGEN1_UDRE0 UDRE1
#define REGGEN2_UDRE0 UDRE2
#define REGGEN3_UDRE0 UDRE3
#define REGGEN0_UDR0 UDR0
#define REGGEN1_UDR0 UDR1
#define REGGEN2_UDR0 UDR2
#define REGGEN3_UDR0 UDR3
#define REGGEN0_USBS0 USBS0
#define REGGEN1_USBS0 USBS1
#define REGGEN2_USBS0 USBS2
#define REGGEN3_USBS0 USBS3
#define REGGEN0_RXC0 RXC0
#define REGGEN1_RXC0 RXC1
#define REGGEN2_RXC0 RXC2
#define REGGEN3_RXC0 RXC3


#define REGGEN(NAME) (SERIALNUM==0 ? REGGEN0_##NAME : \
						(SERIALNUM==1 ? REGGEN1_##NAME : \
							(SERIALNUM==2 ? REGGEN2_##NAME : \
								(SERIALNUM==3 ? REGGEN3_##NAME : \
									SOMEVAR))))
volatile uint8_t SOMEVAR;

template <int SERIALNUM>
struct SerialX_
{
	char buffer[34];
	void begin(uint32_t _b)
	{
		uint8_t ubrr;
		if( _b <= 10000 )
		{
			ubrr = ((F_CPU / 16) / (_b)) - 1;	
		}
		else ubrr = 8;
		/* Set baud rate */
		REGGEN(UBRR0H) = (uint8_t) (ubrr >> 8);
		REGGEN(UBRR0L) = (uint8_t) ubrr;
		/* Enable receiver and transmitter */ 
		REGGEN(UCSR0B) = (1 << REGGEN(RXEN0)) | (1 << REGGEN(TXEN0));
		/* Set frame format: 8data, 2stop bit */
		REGGEN(UCSR0C) = /*(1 << URSEL) |*/ (1 << REGGEN(USBS0)) | (3 << REGGEN(UCSZ00)); 
	}
	void newline()
	{
		this->put((uint8_t) '\r');
		this->put((uint8_t) '\n');
	}
	void put(uint8_t data)
	{
		while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0))));
		REGGEN(UDR0) = data;
	}
	void put(char data)
	{
		while (!(UCSR0A & (1 << REGGEN(UDRE0))));
		REGGEN(UDR0) = data;
	}
	void print(char data)
	{
		this->put(data);
	}
	void println(char data)
	{
		this->put(data);
		this->newline();
	}
	void print(uint8_t data)
	{
		this->put(data);
	}
	void println(uint8_t data)
	{
		this->put(data);
		this->newline();
	}
	void print(char * out)
	{
		while (*out)
		{
			/* Wait for empty transmit buffer */
			while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0))));
			/* Put data into buffer, sends the data */
			UDR0 = *out;
			out++;
		}
	}
	void print(char * out, uint16_t len)
	{
		uint8_t i = 0;
		while (i != len)
		{
			/* Wait for empty transmit buffer */
			while (!(REGGEN(UCSR0A) & (1 << REGGEN(UDRE0))));
			/* Put data into buffer, sends the data */
			REGGEN(UDR0) = *out;
			++out;
			++i;
		}
	}
	void println(char * out)
	{
		this->print(out);
		this->newline();
	}
	void print(uint16_t data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
	}
	void print(int data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
	}
	void println(int16_t data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
		this->newline();
	}
	void println(uint16_t data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
		this->newline();
	}
	void print(uint32_t data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
	}
	void print(int32_t data)
	{
		//itoa(data, this->buffer, 10);
		sprintf(this->buffer, "%ld", data);
		this->print(this->buffer);
	}
	void println(int32_t data)
	{
		//itoa(data, this->buffer, 10);
		sprintf(this->buffer, "%ld", data);
		this->print(this->buffer);
		this->newline();
	}
	void println(uint32_t data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
		this->newline();
	}
	void print(float data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
	}
	void println(float data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
		this->newline();
	}
	void print(double data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
	}
	void println(double data)
	{
		itoa(data, this->buffer, 10);
		this->print(this->buffer);
		this->newline();
	}
	bool available()
	{
		return ((REGGEN(UCSR0A) & (1 << REGGEN(RXC0))));
	}
	uint8_t read()
	{
		/* Wait for data to be received */
		while (!(REGGEN(UCSR0A) & (1 << REGGEN(RXC0))));
		/* Get and return received data from buffer */
		return REGGEN(UDR0);
	}
};
SerialX_<0> Serial;
SerialX_<1> Serial1;

#endif /* SERIAL_H_ */