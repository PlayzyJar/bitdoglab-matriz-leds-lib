📘 Biblioteca para Matriz de LEDs 5x5 da BitDogLab
Bem-vindo à biblioteca para controle de matrizes de LEDs 5x5 da BitDogLab! 🎉
Este projeto foi desenvolvido para facilitar a exibição de textos, animações e efeitos visuais em matrizes de LEDs, especialmente para a Placa de Desenvolvimento BitDogLab com Raspberry Pi Pico W. Com uma interface simples e intuitiva, você pode criar displays incríveis para seus projetos! 🚀

🛠️ Recursos
Exibição de textos com rolagem 📜
Exiba mensagens com efeito de rolagem, começando com o display vazio e surgindo da direita.

Suporte a múltiplas fontes 🔤
Escolha entre fontes 3x5 e 5x5 para exibir seus textos com diferentes estilos.

Controle de cores RGB 🎨
Defina cores personalizadas para cada frame ou texto, com suporte a intensidade ajustável.

Animação de frames 🎬
Exiba animações pré-definidas, como corações pulsantes, com transições suaves.

Integração com BitDogLab 🔌
Projetada especificamente para a Placa de Desenvolvimento BitDogLab com Raspberry Pi Pico W.

🚀 Como usar
1. Instalação
Clone este repositório para o seu ambiente de desenvolvimento:

git clone https://github.com/seu-usuario/sua-biblioteca-led.git

3. Configuração
Certifique-se de que o SDK da Raspberry Pi Pico está configurado corretamente no seu ambiente. Se ainda não configurou, siga o guia oficial.

4. Exemplo básico
Aqui está um exemplo simples para exibir uma mensagem com rolagem na BitDogLab:

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"
#include "main.pio.h"
#include "init_GPIO.h"
#include "frames_5x5.h"
#include "frames_3x5.h"
#include "letras_5x5.h"
#include "letras_3x5.h"
#include "led_functions.h"

#define DEBOUNCE_TIME 400 // Tempo de debounce em milissegundos

/**
 * Inicializa o sistema, configurando o clock e a PIO.
 * @param pio Ponteiro para a instância do PIO.
 * @param sm Ponteiro para o estado da máquina de estados (state machine).
 * @param offset Ponteiro para o offset do programa PIO.
 * @return true se a inicialização for bem-sucedida, false caso contrário.
 */
bool inicializar_sistema(PIO *pio, uint *sm, uint *offset) {
    // Configura o clock do sistema para 128 MHz
    if (!set_sys_clock_khz(128000, false)) {
        printf("Erro ao configurar o clock do sistema!\n");
        return false;
    }

    // Configuração da PIO
    *pio = pio0;
    *offset = pio_add_program(*pio, &main_program);
    *sm = pio_claim_unused_sm(*pio, true);

    if (*offset == -1 || *sm == -1) {
        printf("Erro ao configurar a PIO!\n");
        return false;
    }

    // Inicializa o programa PIO na matriz de LEDs
    main_program_init(*pio, *sm, *offset, OUT_PIN);
    return true;
}

/**
 * Função principal do programa.
 * Inicializa o sistema, exibe animações e texto na matriz de LEDs.
 */
int main() {
    // Inicializa o stdio (para debug via USB, se necessário)
    stdio_init_all();
    init_GPIO(); // Inicializa os GPIOs

    // Variáveis para PIO
    PIO pio;
    uint sm, offset;

    // Inicializa o sistema (clock e PIO)
    if (!inicializar_sistema(&pio, &sm, &offset)) {
        return 1; // Encerra o programa se a inicialização falhar
    }

    // Define a cor (R, G, B - 0 à 255)
    RGBColor cor = {0, 156, 255}; // Azul ciano

    // Define a intensidade dos LEDs (0.0 a 1.0)
    double intensidade = 0.1; // Controle da intensidade (0.0 até 1.0)
    uint16_t vel = 150;       // Taxa de atualizações em ms
    uint8_t largura_fonte = 5; // Tamanho da fonte (3 ou 5)

    // Loop infinito (o programa fica rodando após exibir a frase)
    while (1) {
        // Verifica se o botão foi pressionado
        if (!gpio_get(JSTICK)) {
            reset_usb_boot(0, 0);
        }

        // Exibe uma frase com efeito de rolagem na matriz de LEDs
        exibir_frase_rolagem("VIRTUS CC", cor, pio, sm, intensidade, vel, largura_fonte);

        sleep_ms(DEBOUNCE_TIME);
    }
}

4. Personalização
Cores: Altere os valores de RGBColor para criar cores personalizadas.

Velocidade: Ajuste o valor de velocidade para controlar a rolagem.

Fontes: Escolha entre fontes 3x5 ou 5x5 com o parâmetro tamanho_matriz.

🎨 Exemplos de uso
Exibir uma animação

exibir_frame(heart_01, cor, pio, sm, 0.1);
sleep_ms(500);
exibir_frame(heart_02, cor, pio, sm, 0.2);
sleep_ms(500);
Exibir texto estático

exibir_frame(letra_A, cor, pio, sm, 0.8);


Exibir texto com rolagem

exibir_frase_rolagem("OLA MUNDO!", cor, pio, sm, 0.8, 150, 5);


🧩 Estrutura do projeto
led_functions.h: Biblioteca principal com funções para controle da matriz de LEDs.

frames_5x5.h e frames_3x5.h: Frames pré-definidos para animações e fontes.

main.c: Exemplo de uso da biblioteca.

init_GPIO.h: Configuração dos pinos GPIO da BitDogLab.

🤝 Contribuição
Contribuições são bem-vindas! Se você tem ideias para melhorar esta biblioteca, siga os passos abaixo:

Faça um fork do repositório.

Crie uma branch com sua feature: git checkout -b minha-feature.

Commit suas mudanças: git commit -m 'Adicionando nova feature'.

Push para a branch: git push origin minha-feature.

Abra um pull request.

📄 Licença
Este projeto está licenciado sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.

🙌 Créditos
Desenvolvido por PlayzyJar (Carlos Elias) 🚀

Inspirado em projetos open-source da comunidade Raspberry Pi Pico.

Compatível com a Placa de Desenvolvimento BitDogLab.

🌟 Dúvidas ou sugestões?
Sinta-se à vontade para abrir uma issue no repositório ou entrar em contato diretamente comigo. Vamos construir algo incrível juntos! 💡
