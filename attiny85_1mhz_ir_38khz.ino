//
// attiny85_1mhz_ir_38khz.ino
//
// see also... http://forum.arduino.cc/index.php?PHPSESSID=hvsfmjo2l66kv9g9rhaigftje4&topic=139729.msg1049431#msg1049431
//
void setFrequency(uint16_t freq)
{
  uint32_t requiredDivisor = (F_CPU/2)/(uint32_t)freq;

  uint16_t prescalerVal = 1;
  uint8_t prescalerBits = 1;
  while ((requiredDivisor + prescalerVal/2)/prescalerVal > 256) {
    ++prescalerBits;
    prescalerVal <<= 1;
  }

  uint8_t top = ((requiredDivisor + (prescalerVal/2))/prescalerVal) - 1;
  TCCR1 = (1 << CTC1) | prescalerBits;
  GTCCR = 0;
  OCR1C = top;
}

void on() {
  TCNT1 = 0;
  TCCR1 |= (1 << COM1A0);
}
void off() {
  TCCR1 &= ~(1 << COM1A0);
}

void setup() {
  PORTB = 0;
  DDRB = (1 << PB1); // output is PIN6 (D1)

  setFrequency(38000);
}

void loop() {
    on();
    delay(1);
    off();
    delay(3);
}

