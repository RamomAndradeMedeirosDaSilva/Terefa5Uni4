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


// #include <stdio.h>
// #include "pico/stdlib.h"


// int main()
// {
//     stdio_init_all();

//     while (true) {
//         printf("Hello, world!\n");
//         sleep_ms(1000);
//     }
// }
