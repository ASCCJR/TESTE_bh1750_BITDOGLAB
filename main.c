#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// --- DEFINIÇÕES DE PINO CORRIGIDAS CONFORME O MANUAL DA BITDOGLAB ---
#define I2C_PORT i2c1              // O conector I2C 1 usa o controlador i2c1
const uint I2C_SDA_PIN = 2;        // Manual: Conector I2C 1 usa GPIO2 para SDA
const uint I2C_SCL_PIN = 3;        // Manual: Conector I2C 1 usa GPIO3 para SCL
const uint8_t BH1750_ADDR = 0x23;
const uint8_t BH1750_CMD_POWER_ON = 0x01;
const uint8_t BH1750_CMD_RESET = 0x07;
const uint8_t BH1750_CMD_HIRES1 = 0x20;

void bh1750_init() {
    i2c_write_blocking(I2C_PORT, BH1750_ADDR, &BH1750_CMD_POWER_ON, 1, false);
    sleep_ms(10);
    i2c_write_blocking(I2C_PORT, BH1750_ADDR, &BH1750_CMD_RESET, 1, false);
    sleep_ms(10);
}

float bh1750_read_lux() {
    uint8_t raw_data[2];
    i2c_write_blocking(I2C_PORT, BH1750_ADDR, &BH1750_CMD_HIRES1, 1, false);
    sleep_ms(180);
    int bytes_read = i2c_read_blocking(I2C_PORT, BH1750_ADDR, raw_data, 2, false);
    if (bytes_read < 2) {
        return -1.0;
    }
    uint16_t raw_value = (raw_data[0] << 8) | raw_data[1];
    float lux_value = (float)raw_value / 1.2f;
    return lux_value;
}

int main() {
    stdio_init_all();
    printf("BitDogLab - Conectado ao conector I2C 1 (SDA=2, SCL=3)\n");

    // Configuração do I2C com os pinos corretos
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    printf("Verificando se o sensor BH1750 (0x23) esta presente...\n");
    sleep_ms(1000); // Pausa para ler a mensagem

    uint8_t rxdata;
    int ret = i2c_read_blocking(I2C_PORT, BH1750_ADDR, &rxdata, 1, false);
    if (ret < 0) {
        printf("ERRO: Sensor nao encontrado no endereço 0x23. Verifique a conexao fisica.\n");
        while(true); // Trava aqui
    }
    
    printf("Sensor BH1750 encontrado! Iniciando leituras...\n");
    bh1750_init();

    while (1) {
        float lux = bh1750_read_lux();
        printf("Intensidade da Luz: %.2f lux\n", lux);
        sleep_ms(2000);
    }
    return 0;
}