#include <Arduino.h>
#include <scheduler.h>
#include <task_queue.h>

int LED_STATE = 1;
const int NUM_OF_TASKS = 2;

TaskQueue* q;

void print()
{
  Serial.println("Test task code");
}

/**
 * Why use the prescalar?
 * Since the CPU runs ate 16MHz, a timer would increase by one every 1/16MHz seconds
 * Timer1 can only count up to 2^16 so, if we want to count up to a value > 2^16, we use a prescalar
 * For example, when using a prescalar of 256, a timer will increase by one every 1 / (16MHz / 256)
 */

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  cli(); // disable interrupts while configuring timer

  TCCR1A = 0; // reset control register A
  TCCR1B = 0; // reset control register B
  TCCR1B |= (1 << CS12); // set CS12 to 1 to get a prescalar of 256
  TCNT1 = 0; // reset timer value

  TIMSK1 |= (1 << OCIE1A); // set interrupt when timer matches OCR1A value

  OCR1A = 62500; // match every 1 second

  sei(); // enable interrupts

  q = new TaskQueue();
  q->enqueue(new Task{1, 1, 4, print});
  q->enqueue(new Task{2, 2, 3, print});
}

void loop() {
  scheduler(q);

  delay(2000);
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;
  LED_STATE = !LED_STATE;
  digitalWrite(LED_BUILTIN, LED_STATE);
}
