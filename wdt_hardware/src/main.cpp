#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

bool pb1_state;
bool pb2_state;
volatile uint16_t pb2_count;

// Оброботчик прерывания по таймеру TIMER0
ISR(TIM0_OVF_vect)
{
  pb2_count++;
}

int main()
{
  // Устанавливаем выход PB0
  // Перезагрузка основного микроконтроллера (reset out)
  DDRB |= (1 << PB0);   // pinMode(PB0, OUTPUT);
  PORTB &= ~(1 << PB0); // digitalWrite(PB0, LOW);}

  // Устанавливаем вход PB1
  // Обновление WDT MAX1232 (init out)
  DDRB |= (1 << PB1);   // pinMode(PB1, OUTPUT);
  PORTB &= ~(1 << PB1); // digitalWrite(PB1, LOW);}

  // Устанавливаем вход PB2 с подтягиванием
  // Обновление WDT ATtiny13 (init in)
  DDRB &= ~(1 << PB2); // pinMode(PB2, INPUT_PULLUP);
  PORTB |= (1 << PB2);

  // Устанавливаем входы PB3 с подтягиванием
  // Контроль времени задержки до порезагрузки 1
  DDRB &= ~(1 << PB3); // pinMode(PB3, INPUT_PULLUP);
  PORTB |= (1 << PB3);
  
  // Устанавливаем входы PB4 с подтягиванием
  // Контроль времени задержки до порезагрузки 2
  DDRB &= ~(1 << PB4); // pinMode(PB4, INPUT_PULLUP);
  PORTB |= (1 << PB4);

  // Определяам время срабатывание таймера по входам PB2,PB3,PB4 (перемычки подтягивают к земле) (период, сек = TM/4 )
  uint16_t TM = 0;
  bool pb3 = false;
  bool pb4 = false;
  if (PINB & (1 << PINB3))
    pb3 = true;
  if (PINB & (1 << PINB4))
    pb4 = true;

  if (pb3 == true && pb4 == true)
    TM = 40; //Таймаут 10 сек
  else if (pb3 == true && pb4 == false)
    TM = 120; //Таймаут 30 сек
  else if (pb3 == false && pb4 == true)
    TM = 240; //Таймаут 60 сек
  else if (pb3 == false && pb4 == false)
    TM = 480; //Таймаут 120 сек

  pb2_count = 0;
  pb2_state = false;
  // Настраиваем таймер
  TIMSK0 = (1 << TOIE0);              // Включаем таймер TIMER0
  TCCR0B = (1 << CS02) | (1 << CS00); // Пределитель таймера на 1/1024

  MCUCR &= ~(1 << SM1); // idle mode
  MCUCR &= ~(1 << SM0); // idle mode
  MCUCR |= (1 << SE);
  sei();
  while (1)
  {
    //Смена состояния выхода (init out) для WDT MAX1232
    pb1_state = !pb1_state;
    if (pb1_state == true)
      PORTB |= (1 << PB1);
    else
      PORTB &= ~(1 << PB1);

    // Зпсываем до прерывания по таймеру
    asm("sleep");
    // Таймер сработал
    TIMSK0 &= ~(1 << TOIE0); // Останавливаем TIMER0
                             // Считываем состояние PB1
    bool pb2 = false;
    if (PINB & (1 << PINB2))
      pb2 = true;
    // Если состояние входа инвертировалось, сбрасываем время
    if (pb2 != pb2_state)
      pb2_count = 0;
    pb2_state = pb2;
    // Если превышено время установки таймера
    if (pb2_count >= TM)
    {
      PORTB |= (1 << PB0);  // digitalWrite(PB0, HIGH);}
      _delay_ms(100);       // Ждем 100 ms
      PORTB &= ~(1 << PB0); // digitalWrite(PB0, LOW);}
      pb2_count = 0;        // Сбрасываем счетчик
    }

    TIMSK0 = (1 << TOIE0); // Включаем таймер TIMER0
    sei();
  }
  return 0;
}
