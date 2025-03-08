#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"
#include "matriz_teste02.pio.h"
#include "init_GPIO.h"
#include "frames_5x5.h"
#include "frames_3x5.h"
#include "letras_5x5.h"
#include "letras_3x5.h"
#include "led_functions.h"

#define DEBOUNCE_TIME 400 // Tempo de debounce em milissegundos

// Função para inicializar o sistema
bool inicializar_sistema(PIO *pio, uint *sm, uint *offset)
{
    // Configura o clock do sistema para 128 MHz
    if (!set_sys_clock_khz(128000, false))
    {
        printf("Erro ao configurar o clock do sistema!\n");
        return false;
    }

    // Configuração da PIO
    *pio = pio0;
    *offset = pio_add_program(*pio, &matriz_teste02_program);
    *sm = pio_claim_unused_sm(*pio, true);

    if (*offset == -1 || *sm == -1)
    {
        printf("Erro ao configurar a PIO!\n");
        return false;
    }

    matriz_teste02_program_init(*pio, *sm, *offset, OUT_PIN);
    return true;
}

int main()
{
    // Inicializa o stdio (para debug via USB, se necessário)
    stdio_init_all();
    init_GPIO();

    // Variáveis para PIO
    PIO pio;
    uint sm, offset;

    // Inicializa o sistema (clock e PIO)
    if (!inicializar_sistema(&pio, &sm, &offset))
    {
        return 1; // Encerra o programa se a inicialização falhar
    }

    // Define a cor (R, G, B - 0 à 255)
    RGBColor cor = {219, 0, 91}; 

    // variável de controle qualquer
    uint32_t cont = 0;

    // Define a intensidade dos LEDs (0.0 a 1.0)
    double intensidade = 0.2; // controle da intensidade (0.0 até 1.0)
    uint16_t vel = 150; // taxa de atualizações em ms
    uint8_t largura_fonte = 5; // tamanho da fonte (3 ou 5)

    // Loop principal
    while (1)
    {
        exibir_frase_rolagem("BY CARLOS ELIAS", cor, pio, sm, intensidade, vel, largura_fonte);
    }
}
