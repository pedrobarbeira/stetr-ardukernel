#include <utils.h>

/**
 * Why use the prescalar?
 * Since the CPU runs ate 16MHz, a timer would increase by one every 1/16MHz seconds
 * Timer1 can only count up to 2^16 so, if we want to count up to a value > 2^16, we use a prescalar
 * For example, when using a prescalar of 256, a timer will increase by one every 1 / (16MHz / 256)
 */
void config_timer1_interrupts()
{
    cli(); // disable interrupts while configuring timer

    TCCR1A = 0; // reset control register A
    TCCR1B = 0; // reset control register B
    TCCR1B |= (1 << CS12); // set CS12 to 1 to get a prescalar of 256
    TCNT1 = 0; // reset timer value

    TIMSK1 |= (1 << OCIE1A); // set interrupt when timer matches OCR1A value

    OCR1A = 62500; // match every 1 second

    sei(); // enable interrupts
}
