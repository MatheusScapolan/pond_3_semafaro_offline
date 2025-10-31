// Semáforo simples (com delay)
// Plataforma: Arduino UNO/Nano (5V)
// Pinos sugeridos: Vermelho=8, Amarelo=9, Verde=10

const int LED_VERMELHO = 8;
const int LED_AMARELO  = 9;
const int LED_VERDE    = 10;

const unsigned long TEMPO_VERMELHO = 6000; // ms
const unsigned long TEMPO_VERDE    = 4000; // ms
const unsigned long TEMPO_AMARELO  = 2000; // ms

void apagaTodos() {
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, LOW);
}

void acendeVermelho() {
  apagaTodos();
  digitalWrite(LED_VERMELHO, HIGH);
}

void acendeVerde() {
  apagaTodos();
  digitalWrite(LED_VERDE, HIGH);
}

void acendeAmarelo() {
  apagaTodos();
  digitalWrite(LED_AMARELO, HIGH);
}

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  apagaTodos();
}

void loop() {
  // Vermelho 6s
  acendeVermelho();
  delay(TEMPO_VERMELHO);

  // Verde 4s
  acendeVerde();
  delay(TEMPO_VERDE);

  // Amarelo 2s
  acendeAmarelo();
  delay(TEMPO_AMARELO);
}

