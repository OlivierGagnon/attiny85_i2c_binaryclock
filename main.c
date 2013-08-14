//#define F_CPU 8000000 //Needed for delay.h
//Include libraries necessary for project

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <compat/twi.h>
#include <avr/power.h>
#include "hc4094.h"
#include "SoftI2C.h"
#include "DS1307.h"
#include "rs232_debug.h"


//comment out to disable debugging
//#define DEBUGGING

void Timer0_Init(void) // Setup the timer0
{
    TCCR0B = (1<<CS00)|(1<<CS02); // 1024 prescaler, longest delay
    TCNT0 = 0; // initialize counter
    TIMSK |= (1 << TOIE0); // enable overflow interrupt
    sei(); // enable global interrupts
}

ISR(TIMER0_OVF_vect) // Overflow interrupt routine
{
    DualHC4094Write(GetBinMinutes(), GetBinHours()); // Update both 4094

    #ifdef DEBUGGING
    SendChar(0xff);
    #endif
}

/*
*
* Start main loop here
*
*/

int main(void)
{
    //sleep mode test



	DS1307Init();
	HC4094Init();
	Timer0_Init();

	#ifdef DEBUGGING
	TXInit();
	#endif

	//SetTime();
    while (1)
	{

		#ifdef DEBUGGING
		TXRegisters();
		//TXTime();
		//TXBinTime();
		_delay_ms(500);
		#endif
	}
}
