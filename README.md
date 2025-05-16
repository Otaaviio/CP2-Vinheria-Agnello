# 🌡️ Projeto Arduino - Monitoramento de Ambiente (Temperatura, Umidade e Luminosidade)

Este projeto foi desenvolvido com Arduino para monitorar as condições ambientais de **temperatura**, **umidade** e **luminosidade**, exibindo os dados em um **display LCD 16x2** com I2C e acionando **LEDs** e **buzzer** com base em faixas ideais ou críticas dos sensores.

A simulação e testes foram realizados na plataforma [Wokwi](https://wokwi.com/projects/431150077331782657), que permite emular circuitos de Arduino online.

## 📋 Requisitos Atendidos

### 🔆 Luminosidade
- 🌑 **Ambiente escuro**: LED **Verde** aceso.
- 🌗 **Ambiente com meia luz**: LED **Amarelo** aceso + mensagem no display.
- ☀️ **Ambiente muito claro**: LED **Vermelho** aceso + mensagem no display.
- 🔊 Quando totalmente iluminado, o buzzer é acionado continuamente.

### 🌡️ Temperatura
- ✅ Faixa ideal: **10°C a 15°C**
  - Mostra “Temperatura OK” no display.
- 🔺 Acima de 15°C:
  - LED Amarelo aceso, buzzer ligado e display com mensagem “Temp. ALTA”.
- 🔻 Abaixo de 10°C:
  - Display exibe “Temp. BAIXA” + temperatura atual.

### 💧 Umidade
- ✅ Faixa ideal: **50% a 70%**
  - Mostra “Umidade OK” no display.
- 🔺 Acima de 70%:
  - LED Vermelho aceso, buzzer ligado, e display com “Umidade ALTA”.
- 🔻 Abaixo de 50%:
  - Display exibe “Umidade BAIXA” + valor da umidade.

### 📊 Apresentação dos dados
- As leituras são a **média de 5 medições**.
- Os dados são atualizados a cada **5 segundos**.

## 👨‍💻 Colaboradores

- Fernando Bellegarde
- Otavio Inaba
- Henrique Guedes
- Eduardo Ulisses
- Eduardo Duran
- Henrique Castro
