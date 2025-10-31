#include <Arduino.h>

// Semáforo OO com ponteiros e máquina de estados (millis)
// Plataforma: Arduino UNO/Nano (5V)
// Pinos: Vermelho=8, Amarelo=9, Verde=10
// Tempos: Vermelho=6000 ms, Verde=4000 ms, Amarelo=2000 ms

class Led {
public:
  explicit Led(uint8_t pin) : _pin(pin) {}
  void begin() { pinMode(_pin, OUTPUT); off(); }
  void on()  { digitalWrite(_pin, HIGH); }
  void off() { digitalWrite(_pin, LOW);  }
private:
  uint8_t _pin;
};

class Semaforo {
public:
  typedef void (Semaforo::*StateFn)(); // ponteiro para função-membro de estado

  Semaforo(Led* r, Led* y, Led* g,
           unsigned long tv, unsigned long tg, unsigned long ta)
    : _r(r), _y(y), _g(g), TV(tv), TG(tg), TA(ta), _state(&Semaforo::estadoVermelho) {}

  void begin() {
    _r->begin(); _y->begin(); _g->begin();
    setState(&Semaforo::estadoVermelho); // inicia em vermelho
  }

  void update() {
    unsigned long dt = millis() - _t0;
    if (_state == &Semaforo::estadoVermelho && dt >= TV)      setState(&Semaforo::estadoVerde);
    else if (_state == &Semaforo::estadoVerde && dt >= TG)    setState(&Semaforo::estadoAmarelo);
    else if (_state == &Semaforo::estadoAmarelo && dt >= TA)  setState(&Semaforo::estadoVermelho);
  }

private:
  Led* _r; Led* _y; Led* _g;         // uso de ponteiros para objetos
  unsigned long _t0 = 0;             // instante de entrada no estado
  const unsigned long TV, TG, TA;    // tempos de cada estado
  StateFn _state;                    // ponteiro para a função-estado atual

  void setState(StateFn s) { _state = s; (this->*_state)(); _t0 = millis(); }

  // Estados (funções-membro)
  void estadoVermelho() { _r->on();  _y->off(); _g->off(); }
  void estadoVerde()    { _r->off(); _y->off(); _g->on();  }
  void estadoAmarelo()  { _r->off(); _y->on();  _g->off(); }
};

// Pinos dos LEDs
const uint8_t PIN_R = 8;
const uint8_t PIN_Y = 9;
const uint8_t PIN_G = 10;

// Tempos exigidos (ms)
const unsigned long TEMPO_VERMELHO = 6000;
const unsigned long TEMPO_VERDE    = 4000;
const unsigned long TEMPO_AMARELO  = 2000;

// Objetos criados dinamicamente (uso de ponteiros explícito)
Led* ledR = new Led(PIN_R);
Led* ledY = new Led(PIN_Y);
Led* ledG = new Led(PIN_G);
Semaforo* semaforo = new Semaforo(ledR, ledY, ledG,
                                  TEMPO_VERMELHO, TEMPO_VERDE, TEMPO_AMARELO);

void setup() {
  semaforo->begin();
}

void loop() {
  semaforo->update();
}
