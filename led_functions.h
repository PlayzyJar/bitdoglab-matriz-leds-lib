#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "matriz_teste02.pio.h"
#include "init_GPIO.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "letras_3x5.h"
#include "letras_5x5.h"

#define NUM_LEDS 25                         // Número de LEDs na matriz
#define MAX_FRASE_TAMANHO 50                // Número máximo de caracteres na frase
#define MAX_COLUNAS (5 * MAX_FRASE_TAMANHO) // Número máximo de colunas na frase concatenada

// Estrutura para representar uma cor RGB
typedef struct
{
    double r; // Vermelho (0.0 a 1.0)
    double g; // Verde (0.0 a 1.0)
    double b; // Azul (0.0 a 1.0)
} RGBColor;

// enum com as letras
typedef enum {
    CHAR_A, CHAR_B, CHAR_C, CHAR_D, CHAR_E, CHAR_F, CHAR_G, CHAR_H, CHAR_I, CHAR_J,
    CHAR_K, CHAR_L, CHAR_M, CHAR_N, CHAR_O, CHAR_P, CHAR_Q, CHAR_R, CHAR_S, CHAR_T,
    CHAR_U, CHAR_V, CHAR_W, CHAR_X, CHAR_Y, CHAR_Z, CHAR_SPACE, CHAR_EXCLAMATION, CHAR_PONTO
} Caractere;

// Função para codificar a cor no formato G | R | B
uint32_t matriz_rgb(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;                             // Converte vermelho para 0-255
    G = g * 255;                             // Converte verde para 0-255
    B = b * 255;                             // Converte azul para 0-255
    return (G << 24) | (R << 16) | (B << 8); // Codifica no formato G | R | B
}

// Função para converter a função a escala de 0 à 255 para 0.0 à 1.0
void converterCorParaEscala(RGBColor *cor)
{
    // Impede que o número ultrapasse o intervalo [0, 255]
    if (cor->r > 255)
        cor->r = 255;
    if (cor->b > 255)
        cor->b = 255;
    if (cor->g > 255)
        cor->g = 255;

    if (cor->r < 0)
        cor->r = 0;
    if (cor->b < 0)
        cor->b = 0;
    if (cor->g < 0)
        cor->g = 0;

    // cálculo e conversão das escalas para o intervalo [0.0, 1.0]
    cor->r = cor->r / 255.0;
    cor->b = cor->b / 255.0;
    cor->g = cor->g / 255.0;
}

// Função para mapear o índice do array para a posição física na matriz
int mapear_indice_para_posicao(int indice)
{
    int linha = 4 - (indice / 5);  // Linha (0 a 4, de baixo para cima)
    int coluna = 4 - (indice % 5); // Coluna (0 a 4, invertida para corrigir o espelhamento)

    // Inverte a coluna para linhas ímpares (1 e 3)
    if (linha == 1 || linha == 3)
    {
        coluna = 4 - coluna;
    }

    return (linha * 5) + coluna; // Retorna o índice físico
}

// Função para definir a cor de um LED específico
void setar_led(int index, RGBColor cor, PIO pio, uint sm)
{
    // Usa a função matriz_rgb para codificar a cor
    uint32_t valor_led = matriz_rgb(cor.b, cor.r, cor.g);

    // Envia o valor para o LED
    pio_sm_put_blocking(pio, sm, valor_led);
}

double **criar_frase_da_string(const char *texto, int tamanho_matriz) {
    // Define o número máximo de caracteres na frase
    int max_caracteres = strlen(texto);
    // Cada frase é seguida por dois espaços, então o tamanho da lista de frames é (max_caracteres + 2)
    double **frase = (double **)malloc((max_caracteres + 2) * sizeof(double *));

    // Define qual fonte usar (3x5 ou 5x5)
    double **fonte = (tamanho_matriz == 3) ? letras_3x5 : letras_5x5;
    double *espaco = (tamanho_matriz == 3) ? f_01_fino : f_01; // Frame de espaço em branco

    // Adiciona os frames das letras
    for (int i = 0; i < max_caracteres; i++) {
        char c = toupper(texto[i]); // Converte para maiúscula

        switch (c) {
            case 'A': frase[i] = fonte[CHAR_A]; break;
            case 'B': frase[i] = fonte[CHAR_B]; break;
            case 'C': frase[i] = fonte[CHAR_C]; break;
            case 'D': frase[i] = fonte[CHAR_D]; break;
            case 'E': frase[i] = fonte[CHAR_E]; break;
            case 'F': frase[i] = fonte[CHAR_F]; break;
            case 'G': frase[i] = fonte[CHAR_G]; break;
            case 'H': frase[i] = fonte[CHAR_H]; break;
            case 'I': frase[i] = fonte[CHAR_I]; break;
            case 'J': frase[i] = fonte[CHAR_J]; break;
            case 'K': frase[i] = fonte[CHAR_K]; break;
            case 'L': frase[i] = fonte[CHAR_L]; break;
            case 'M': frase[i] = fonte[CHAR_M]; break;
            case 'N': frase[i] = fonte[CHAR_N]; break;
            case 'O': frase[i] = fonte[CHAR_O]; break;
            case 'P': frase[i] = fonte[CHAR_P]; break;
            case 'Q': frase[i] = fonte[CHAR_Q]; break;
            case 'R': frase[i] = fonte[CHAR_R]; break;
            case 'S': frase[i] = fonte[CHAR_S]; break;
            case 'T': frase[i] = fonte[CHAR_T]; break;
            case 'U': frase[i] = fonte[CHAR_U]; break;
            case 'V': frase[i] = fonte[CHAR_V]; break;
            case 'W': frase[i] = fonte[CHAR_W]; break;
            case 'X': frase[i] = fonte[CHAR_X]; break;
            case 'Y': frase[i] = fonte[CHAR_Y]; break;
            case 'Z': frase[i] = fonte[CHAR_Z]; break;
            case ' ': frase[i] = fonte[CHAR_SPACE]; break;
            case '!': frase[i] = fonte[CHAR_EXCLAMATION]; break;
            case '.': frase[i] = fonte[CHAR_PONTO]; break;
            default:  frase[i] = fonte[CHAR_SPACE]; break; // Caractere desconhecido vira espaço
        }
    }

    // Adiciona dois espaços em branco no final da frase
    frase[max_caracteres] = fonte[CHAR_SPACE];
    frase[max_caracteres + 1] = fonte[CHAR_SPACE];

    return frase;
}

// Função para exibir um frame na matriz de LEDs com controle de intensidade
void exibir_frame(double *frame, RGBColor cor, PIO pio, uint sm, double intensidade)
{
    // Garante que a intensidade esteja no intervalo [0.0, 1.0]
    if (intensidade < 0.0)
        intensidade = 0.0;
    if (intensidade > 1.0)
        intensidade = 1.0;

    converterCorParaEscala(&cor);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        // Mapeia o índice lógico para o índice físico
        int indice_fisico = mapear_indice_para_posicao(i);

        // Aplica a cor ao LED, multiplicando pela intensidade do frame e pela intensidade geral
        RGBColor cor_led = {
            cor.r * frame[indice_fisico] * intensidade, // Vermelho
            cor.g * frame[indice_fisico] * intensidade, // Verde
            cor.b * frame[indice_fisico] * intensidade  // Azul
        };

        // Define a cor do LED
        setar_led(i, cor_led, pio, sm);
    }
}

// Função para concatenar os frames das letras da frase
void concatenar_frase(double *frase[], int tamanho_frase, double frase_concatenada[5][MAX_COLUNAS])
{
    for (int i = 0; i < tamanho_frase; i++)
    {
        for (int linha = 0; linha < 5; linha++)
        {
            for (int coluna = 0; coluna < 5; coluna++)
            {
                frase_concatenada[linha][(i * 5) + coluna] = frase[i][linha * 5 + coluna];
            }
        }
    }
}

void exibir_frase_rolagem(const char *texto, RGBColor cor, PIO pio, uint sm, double intensidade, int velocidade, int tamanho_matriz) {
    // Cria a lista de frames a partir da string
    double **frase = criar_frase_da_string(texto, tamanho_matriz);
    int tamanho_frase = strlen(texto) + 2; // Inclui os dois espaços adicionais

    // Define o número de colunas por letra com base no tamanho da matriz
    int colunas_por_letra = (tamanho_matriz == 3) ? 3 : 5;

    // Calcula a largura total da frase concatenada
    int largura_frase = colunas_por_letra * tamanho_frase;

    // Cria o array concatenado da frase
    double frase_concatenada[5][largura_frase]; // 5 linhas, largura variável
    memset(frase_concatenada, 0, sizeof(frase_concatenada)); // Inicializa com zeros

    // Concatena os frames das letras e dos espaços
    for (int i = 0; i < tamanho_frase; i++) {
        for (int linha = 0; linha < 5; linha++) {
            for (int coluna = 0; coluna < colunas_por_letra; coluna++) {
                frase_concatenada[linha][(i * colunas_por_letra) + coluna] = frase[i][linha * colunas_por_letra + coluna];
            }
        }
    }

    int posicao_inicial = 0; // Posição inicial da "janela" de rolagem

    while (1) {
        // Cria um frame temporário para exibir na matriz
        double frame[5][5] = {0}; // Sempre 5x5 para exibição

        // Preenche o frame com a "janela" atual da frase concatenada
        for (int linha = 0; linha < 5; linha++) {
            for (int coluna = 0; coluna < 5; coluna++) {
                int coluna_frase = (posicao_inicial + coluna) % largura_frase; // Calcula a coluna na frase concatenada
                frame[linha][coluna] = frase_concatenada[linha][coluna_frase];
            }
        }

        // Exibe o frame na matriz de LEDs
        exibir_frame((double *)frame, cor, pio, sm, intensidade);

        // Atualiza a posição inicial para a próxima iteração
        posicao_inicial = (posicao_inicial + 1) % largura_frase;

        // Verifica se o botão foi pressionado (exemplo)
        if (!gpio_get(JSTICK)) {
            reset_usb_boot(0, 0);
        }

        // Aguarda um tempo para controlar a velocidade da rolagem
        sleep_ms(velocidade);
    }

    // Libera a memória alocada para a frase
    free(frase);
}

#endif