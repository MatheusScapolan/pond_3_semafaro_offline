# Semáforo de Trânsito (Butantã) — Montagem e Programação

Este repositório contém o guia completo para montar e programar um semáforo com LEDs em protoboard, seguindo tempos reais de operação:


- Vermelho: 6 segundos
- Verde: 4 segundos
- Amarelo: 2 segundos

Inclui documentação detalhada, cálculo de resistores, esquemas de ligação, código-fonte para Arduino (versão simples e não-bloqueante), checklist de validação, roteiro de vídeo e template de avaliação por pares.

## Sumário


- Objetivo e requisitos
- Materiais e especificações (BOM)
- Cálculo dos resistores
- Ligações elétricas (passo a passo e tabela de conexões)
- Código e lógica de temporização
- Como compilar e gravar no Arduino
- Validação dos tempos e testes
- Vídeo de demonstração (entrega)
- Avaliação de pares (barema e template)
- Solução de problemas (FAQ)

## Objetivo e requisitos


Desenvolver um semáforo funcional com três LEDs (vermelho, amarelo e verde), montado em protoboard e controlado por microcontrolador Arduino, repetindo continuamente o ciclo:
1) Vermelho 6 s → 2) Verde 4 s → 3) Amarelo 2 s → reinicia.

## Materiais e especificações (BOM)
Tabela de componentes recomendados:

| Item | Quantidade | Especificação | Observações |
|---|---:|---|---|
| LED 5 mm vermelho | 1 | Vf≈2.0 V, If 10–20 mA | Indicação de PARE |
| LED 5 mm amarelo | 1 | Vf≈2.0 V, If 10–20 mA | Indicação de ATENÇÃO |
| LED 5 mm verde | 1 | Vf≈2.1–2.2 V, If 10–20 mA | Indicação de SIGA |
| Resistores | 3 | 330 Ω, 1/4 W | Um por LED |
| Protoboard | 1 | 400+ pontos | |
| Jumpers macho-macho | 6+ | 10–20 cm | Cores distintas ajudam |
| Arduino Uno (ou Nano) | 1 | 5 V | Qualquer Arduino 5 V funciona |
| Cabo USB | 1 | Compatível | Para alimentação e upload |

Observação: 330 Ω limita a corrente a ~8–10 mA, preservando o LED e o pino do Arduino.

## Cálculo dos resistores
Partindo de Vcc=5 V e corrente alvo I≈10 mA:


- LED vermelho (Vf≈2.0 V): R=(5−2.0)/0.010≈300 Ω → comercial: 330 Ω
- LED verde (Vf≈2.2 V): R=(5−2.2)/0.010≈280 Ω → comercial: 330 Ω
- LED amarelo (Vf≈2.0 V): R≈300 Ω → comercial: 330 Ω

Utilize um resistor por LED (não compartilhe resistores entre LEDs).

## Ligações elétricas
Pinos sugeridos (Arduino UNO/Nano):


- Vermelho → D8
- Amarelo → D9
- Verde → D10
- Catodos dos LEDs → GND comum
- Cada LED deve ter seu próprio resistor em série (pode ficar no anodo ou no catodo)

Tabela de conexões (exemplo com resistor no catodo):

| Sinal | Arduino | Série | LED (ânodo→catodo) | GND |
|---|---|---|---|---|
| Vermelho | D8 | — | D8 → LED_R Ânodo | LED_R Catodo → 330 Ω → GND |
| Amarelo | D9 | — | D9 → LED_Y Ânodo | LED_Y Catodo → 330 Ω → GND |
| Verde | D10 | — | D10 → LED_G Ânodo | LED_G Catodo → 330 Ω → GND |

Dicas de montagem:


- Mantenha os resistores próximos aos LEDs para clareza visual.
- Agrupe GNDs em um barramento da protoboard ligado ao GND do Arduino.
- Verifique polaridade do LED: perna longa = anodo (+), perna curta = catodo (−).



Para fotos de referência, consulte `docs/guia_imagens.md`.

## Código e lógica de temporização
O repositório fornece duas implementações:


1) Simples (com `delay`) — mais direta para iniciantes.
2) Não-bloqueante (máquina de estados com `millis`) — permite evoluir o projeto (sensores, botões, etc.).

Caminhos dos códigos:


- `arduino/semaforo_simple/semaforo_simple.ino`
- `arduino/semaforo_state_machine/semaforo_state_machine.ino`

Tempos programados:


- Vermelho: 6000 ms
- Verde: 4000 ms
- Amarelo: 2000 ms

## Como compilar e gravar no Arduino


Opção A — Arduino IDE:


1. Abra a IDE Arduino.
2. Arquivo → Abrir → selecione uma das pastas de sketch acima.
3. Ferramentas → Placa: “Arduino Uno” (ou a sua placa compatível 5 V).
4. Ferramentas → Porta: selecione a porta COM do seu Arduino.
5. Clique em “Upload” e aguarde a mensagem de sucesso.

Opção B — Arduino CLI (opcional):


```bash
arduino-cli compile --fqbn arduino:avr:uno arduino/semaforo_simple
arduino-cli upload  --fqbn arduino:avr:uno -p COM3 arduino/semaforo_simple
```


Ajuste a porta serial (COMx) conforme seu sistema.

## Validação dos tempos e testes


- Utilize um cronômetro (celular) e meça a duração de cada fase.
- Realize três medições por cor e calcule a média.
- Tolerância aceitável: ±100 ms em cada fase para esta aplicação didática.
- Confirme a ordem: Vermelho → Verde → Amarelo → Vermelho (loop contínuo).

Checklist rápido:


- [ ] LEDs ligam isoladamente (apenas uma cor por vez)
- [ ] Tempos: 6 s / 4 s / 2 s
- [ ] Fios organizados e polaridades corretas

## Vídeo de demonstração (entrega)


Grave um vídeo curto demonstrando o funcionamento:
- Mostre a protoboard e as conexões (close-ups).
- Mostre você (autor(a)) no vídeo, afirmando seu nome e turma.
- Demonstre claramente a alternância das fases e os tempos.
- Faça upload para uma plataforma (YouTube não listado, Google Drive, etc.).
- Adicione o link aqui:

Link do vídeo: <COLE AQUI O LINK DO VÍDEO>

## Avaliação de pares


Critérios (barema 0–2 por item):


1) Montagem física correta (ligações e polaridade)
2) Resistores adequados e cálculo justificado
3) Organização da protoboard e clareza visual
4) Código funcional (compila, sobe e roda)
5) Tempos corretos (V=6s, G=4s, A=2s)
6) Vídeo com autoria e demonstração clara
7) Documentação completa (tabela, fotos, explicações)



Use o template em `peer-review/avaliacoes.md` para registrar os nomes completos dos avaliadores, comentários e pontuações.

## Solução de problemas (FAQ)


- LED não acende: verifique polaridade e o resistor em série; confirme o pino no Arduino.
- Todos acendem fracos: GND pode estar desconectado; revise barramento e aterramento.
- Tempos errados: confirme que o sketch correto foi carregado; cheque constantes em ms.
- Upload falha: feche monitores seriais; confirme a porta COM e o cabo USB funcional.

---
Autor(a): <SEU NOME COMPLETO> — Departamento de Engenharia de Trânsito
