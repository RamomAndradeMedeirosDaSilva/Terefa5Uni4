# Tarefa 2 - Dia 29/01 - Projeto: Semáforo com Timer Periódico no RP2040

## Primeira Atividade

### 📌 Introdução

Olá, neste projeto vamos implementar um semáforo utilizando o microcontrolador **Raspberry Pi Pico W** e a função `add_repeating_timer_ms()` do **Pico SDK**. O semáforo alterna entre as cores **vermelho**, **amarelo** e **verde**, com um intervalo de 3 segundos para cada sinal. Utilizaremos o LED RGB da placa **BitDogLab** para representar as cores do semáforo.

### 🛠️ Materiais Utilizados

- **Microcontrolador:** Raspberry Pi Pico W (Placa BitDogLab)
- **LED RGB** (usando os GPIOs da BitDogLab):
  - Vermelho → GPIO 11  
  - Amarelo → GPIO 12  
  - Verde → GPIO 13
- **3 Resistores de 330 Ω**

### 🔥 Características do Projeto

- 🚦 Inicia com o sinal **vermelho** aceso.
- ⏱️ Timer configurado para alternar o sinal a cada **3 segundos**.
- 🔄 Controle do semáforo através de uma função **callback** associada ao timer.
- 🖨️ Envio de mensagem de status pela porta serial a cada **1 segundo**.
- 💡 Compatível com a **ferramenta BitDogLab**, utilizando o LED RGB integrado.

### 📄 Organização dos Arquivos

- `main.c` → Código principal que implementa o semáforo e controla os LEDs.
- `CMakeLists.txt` → Arquivo de configuração para a compilação do projeto.

### 🖥️ Como Executar o Projeto

#### Passo 1: Clonar o Repositório

Clone o repositório do projeto para o seu ambiente local e abra-o no VS Code.

#### Passo 2: Preparar o Ambiente

Certifique-se de que o **Pico SDK** está instalado corretamente e que o **VS Code** está configurado com a extensão **Raspberry Pi Pico**.

#### Passo 3: Compilar o Projeto

Compile o projeto no VS Code utilizando a extensão Raspberry Pi Pico.

#### Passo 4: Carregar o Código na Placa

1. Conecte a placa **BitDogLab** via USB.
2. Coloque-a no modo **bootsel**.
3. Utilize a opção "**Run Project (USB)**" da extensão para carregar o arquivo `.uf2`.

#### Passo 5: Verificar o Funcionamento

Após o upload, o semáforo iniciará com o LED vermelho aceso e alternará para amarelo e verde a cada 3 segundos. As mensagens de status serão exibidas pela **porta serial**.

### 📜 Código Fonte

Aqui está o código do arquivo `main.c`:

```c
#include <stdio.h>
#include "pico/stdlib.h"

#define RED_PIN     11
#define YELLOW_PIN  12
#define GREEN_PIN   13

typedef enum {
    RED,
    YELLOW,
    GREEN
} traffic_light_state_t;

traffic_light_state_t current_state = RED;

bool repeating_timer_callback(struct repeating_timer *t) {
    // Atualiza o estado dos LEDs
    gpio_put(RED_PIN, current_state == RED);
    gpio_put(YELLOW_PIN, current_state == YELLOW);
    gpio_put(GREEN_PIN, current_state == GREEN);

    // Exibe o estado atual na porta serial
    switch(current_state) {
        case RED:
            printf("Sinal vermelho\n");
            current_state = GREEN;
            break;
        case YELLOW:
            printf("Sinal amarelo\n");
            current_state = RED;
            break;
        case GREEN:
            printf("Sinal verde\n");
            current_state = YELLOW;
            break;
    }
    return true;
}

int main() {
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_init(YELLOW_PIN);
    gpio_set_dir(YELLOW_PIN, GPIO_OUT);
    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);

    // Inicia com o LED vermelho aceso
    gpio_put(RED_PIN, 1);
    gpio_put(YELLOW_PIN, 0);
    gpio_put(GREEN_PIN, 0);

    // Configura o timer para alternar o semáforo a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (1) {
        // Envia mensagem pela porta serial a cada 1 segundo
        printf("Semáforo operando...\n");
        sleep_ms(1000);
    }

    return 0;
}
```
## 📌 Autor
<table>
  <tr>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/60956248?v=4" width="100px;" alt=""/><br /><sub><b> Ramom Silva </b></sub></a><br />👨‍💻</a></td>
  </tr>
</table>



<!-- # Tarefa 2 - Dia 29/01 - Projeto: Semáforo com Temporizador Periódico no RP2040

## Atividade 1

## 📌 Descrição
Este projeto implementa um semáforo utilizando o microcontrolador **Raspberry Pi Pico W** com a função `add_repeating_timer_ms()` do **Pico SDK**. O semáforo alterna entre as cores **vermelho**, **amarelo** e **verde**, com temporização de 3 segundos para cada mudança de sinal. O LED RGB da placa **BitDogLab** é utilizado para representar as cores do semáforo.

## 🛠️ Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico W (Placa BitDogLab)
- **LED RGB** (usando os GPIOs da BitDogLab):
  - Vermelho → GPIO 11  
  - Amarelo → GPIO 12  
  - Verde → GPIO 13
- **3 Resistores de 330 Ω**

## 🔥 Funcionalidades
- ✅ O semáforo inicia no sinal **vermelho**.
- ✅ O temporizador é configurado para alternar o sinal a cada **3 segundos**.
- ✅ O estado do semáforo é controlado por uma função de **callback** associada ao temporizador.
- ✅ A cada **1 segundo**, uma mensagem de alerta é enviada pela porta serial.
- ✅ O código é compatível com a **ferramenta BitDogLab**, utilizando o LED RGB da placa.

## 📄 Estrutura do Projeto
- `main.c` → Implementação principal do semáforo e controle dos LEDs.
- `CMakeLists.txt` → Configuração do CMake para compilação do projeto.

## 🖥️ Como Executar o Projeto

### Passo 1: Clone o repositório do projeto para o seu ambiente local e abra-o no VS Code.

### Passo 2: Configurar o Ambiente
Garanta que o **Pico SDK** está instalado corretamente e que o **VS Code** está configurado com a extensão **Raspberry Pi Pico**.

### Passo 3: Compilar o Código
Compile o projeto no VS Code utilizando a extensão Raspberry Pi Pico.

### Passo 4: Carregar o Código na Placa
1. Conecte a placa **BitDogLab** via USB.
2. Coloque-a no modo **bootsel**.
3. Use a opção "**Run Project (USB)**" da extensão para carregar o arquivo `.uf2`.

### Passo 5: Verificar o Funcionamento
Após o upload, o semáforo iniciará com o LED vermelho aceso e alternará para amarelo e verde a cada 3 segundos. As mensagens de status serão exibidas via **porta serial**.

## 📌 Autor
<table>
  <tr>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/60956248?v=4" width="100px;" alt=""/><br /><sub><b> Ramom Silva </b></sub></a><br />👨‍💻</a></td>
  </tr>
</table>
 -->
