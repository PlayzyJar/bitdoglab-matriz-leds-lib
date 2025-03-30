# 📟 LED Matrix Control Library for Raspberry Pi Pico

![Pico SDK](https://img.shields.io/badge/Pico_SDK-1.5.0-blue)
![License](https://img.shields.io/badge/License-MIT-green)

## 📌 Visão Geral

Biblioteca completa em C para controle de matrizes LED RGB utilizando o Raspberry Pi Pico via PIO. Desenvolvida para projetos educacionais e profissionais.

## 🚀 Recursos Principais

- 🎨 Controle RGB individual por LED
- 📜 Scrolling de texto suave
- 🖼️ Exibição de frames pré-renderizados
- ⚡ Aceleração via PIO (Programmable I/O)
- 📱 Suporte a múltiplos tamanhos de matriz (3x5 e 5x5)

## 📦 Estrutura do Código

```plaintext
bitdoglab-matriz-leds-lib/
├── inc/
│├── drivers/ 
│|├── frames_3x5.h # Frames para matriz 3x5
│|├── frames_5x5.h # Frames para matriz 5x5
│|├── letras_3x5.h # Letras 3x5
│|└── letras_5x5.h # Letras 5x5
│├── define_pins.h # Definição de pinos
│└── led_functions.h # Biblioteca principal
├── src/
│├── drivers/
││├── frames_3x5.c # Implementação frames 3x5
││├── frames_5x5.c # Implementação frames 5x5
││├── letras_3x5.c # Implementação letras 3x5
││└── letras_5x5.c # Implementação letras 5x5
│├── define_pins.c # Configuração de pinos
│├── led_functions.c # Implementação da biblioteca
│├── main_pio.c # Código PIO
│└── main.c # Aplicação principal
```
