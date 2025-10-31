// Semáforo não-bloqueante (state machine com millis)
// Plataforma: Arduino UNO/Nano (5V)
// Pinos sugeridos: Vermelho=8, Amarelo=9, Verde=10

enum Estado { VERMELHO, VERDE, AMARELO };

const int LED_VERMELHO = 8;
const int LED_AMARELO  = 9;
const int LED_VERDE    = 10;

const unsigned long TEMPO_VERMELHO = 6000; // ms
const unsigned long TEMPO_VERDE    = 4000; // ms
const unsigned long TEMPO_AMARELO  = 2000; // ms

Estado estadoAtual = VERMELHO;
unsigned long t0 = 0;

void aplicaSaidas(Estado e) {
  digitalWrite(LED_VERMELHO, e == VERMELHO ? HIGH : LOW);
  digitalWrite(LED_AMARELO,  e == AMARELO  ? HIGH : LOW);
  digitalWrite(LED_VERDE,    e == VERDE    ? HIGH : LOW);
}

unsigned long tempoDo(Estado e) {
  switch (e) {
    case VERMELHO: return TEMPO_VERMELHO;
    case VERDE:    return TEMPO_VERDE;
    case AMARELO:  return TEMPO_AMARELO;
  }
  return 0;
}

Estado proximo(Estado e) {
  switch (e) {
    case VERMELHO: return VERDE;
    case VERDE:    return AMARELO;
    case AMARELO:  return VERMELHO;
  }
  return VERMELHO;
}

void mudaEstado(Estado novo) {
  estadoAtual = novo;
  t0 = millis();
  aplicaSaidas(estadoAtual);
}

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  mudaEstado(VERMELHO);
}

void loop() {
  unsigned long agora = millis();
  if (agora - t0 >= tempoDo(estadoAtual)) {
    mudaEstado(proximo(estadoAtual));
  }
}

