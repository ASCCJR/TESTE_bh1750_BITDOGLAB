#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "bh1750.h" // Incluindo a nossa nova biblioteca

// --- Configuração da Porta I2C da BitDogLab ---
// Alterne os comentários para escolher entre I2C 1 (padrão) e I2C 0
#define I2C_PORT i2c1
const uint I2C_SDA_PIN = 2;
const uint I2C_SCL_PIN = 3;

// #define I2C_PORT i2c0
// const uint I2C_SDA_PIN = 0;
// const uint I2C_SCL_PIN = 1;


int main() {
    stdio_init_all();
    while(!stdio_usb_connected()) {
        sleep_ms(100);
    }

    printf("--- Teste do Sensor de Luminosidade BH1750 ---\n");
    printf("Usando a porta I2C com SDA no pino %d e SCL no pino %d\n", I2C_SDA_PIN, I2C_SCL_PIN);

    // Inicializa o barramento I2C
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    
    // Inicializa o sensor usando a função do nosso driver
    bh1750_init(I2C_PORT);
    
    printf("Sensor inicializado. Coletando dados...\n");

    while (1) {
        // Lê os dados do sensor usando a função do nosso driver
        float lux = bh1750_read_lux(I2C_PORT);
        
        if (lux >= 0) {
            printf("Intensidade da Luz: %.2f lux\n", lux);
        } else {
            printf("Falha ao ler os dados do sensor.\n");
        }
        
        sleep_ms(1000); // Lê a cada 1 segundo
    }
    return 0;
}