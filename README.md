# 💡 Teste Modular do Sensor de Luminosidade BH1750

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Plataforma](https://img.shields.io/badge/Plataforma-Raspberry%20Pi%20Pico-purple.svg)
![Sensor](https://img.shields.io/badge/Sensor-BH1750-yellow.svg)

Este repositório contém um código teste para o sensor de luminosidade I2C BH1750, desenvolvido para ser utilizado na BITDOGLAB

O projeto destaca-se pela sua **arquitetura modular**, onde o driver do sensor (`bh1750.c` e `bh1750.h`) é completamente separado da aplicação principal (`main.c`). Essa abordagem facilita a reutilização do driver em projetos maiores e mais complexos.

## ✨ Funcionalidades

* **Leitura de Luminosidade:** Coleta dados de intensidade da luz e os exibe em Lux.
* **Driver Modular:** A lógica de comunicação com o sensor BH1750 é encapsulada em seus próprios arquivos, fornecendo uma API limpa e reutilizável.
* **Configuração Flexível:** Permite alternar facilmente entre os barramentos I2C 0 e I2C 1 da placa através de uma simples alteração no `main.c`.
* **Teste de Presença:** O programa verifica se o sensor está presente no barramento antes de iniciar as leituras, evitando erros.
* **Saída Serial:** Exibe os dados lidos de forma clara e contínua no monitor serial.

## 🛠️ Hardware e Software Necessários

### Hardware
* Placa com Raspberry Pi Pico (neste projeto, foi usada a **BitDogLab**)
* Sensor de Luminosidade I2C **BH1750**

### Software
* [Raspberry Pi Pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk)
* Ambiente de compilação C/C++ (GCC para ARM, CMake)
* Um programa para monitor serial (ex: o integrado no VS Code, PuTTY, etc.)

## Configurar a Porta I2C
* Por padrão, o projeto está configurado para usar o conector I2C 1 (Esquerda) da BitDogLab.
* Para trocar para o conector I2C 0 (Direita), edite o arquivo main.c
* Comente o bloco de configuração do I2C 1.
* Descomente o bloco de configuração do I2C 0.

## Exemplo para usar a porta I2C 0:

```bash
// --- Configuração da Porta I2C 1 da BitDogLab (Comentado) ---
// #define I2C_PORT i2c1
// const uint I2C_SDA_PIN = 2;
// const uint I2C_SCL_PIN = 3;

// --- Configuração da Porta I2C 0 da BitDogLab (Ativo) ---
#define I2C_PORT i2c0
const uint I2C_SDA_PIN = 0;
const uint I2C_SCL_PIN = 1;
```

## Visualizar a Saída
* Conecte o sensor AHT10 na porta I2C configurada
* Abra um monitor serial conectado à porta COM do seu Pico.
* Você verá a seguinte saída, atualizada a cada segundo:
```bash
--- Teste do Sensor de Luminosidade BH1750 ---
Usando a porta I2C com SDA no pino 2 e SCL no pino 3
Sensor inicializado. Coletando dados...
Intensidade da Luz: 152.50 lux
Intensidade da Luz: 153.33 lux
```
