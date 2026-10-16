// exiba no lcd os dados coletados no dht

// etapa 1 : exiba no lcd os dados coletados no dht
// etapa 2 : atualize os dados do lcd a cada 3 segundos
// etapa 3 : atualize no lcd somente o valor que é alterado
// desafio : atualize a cada 3 segundos somente se houver alteração nos valores
#include <Arduino.h>
#include <DHT.h>

#include <LiquidCrystal_I2C.h>

#define pinDHT 4
#define tipoDHT DHT22
//---------------
//---------------
float tempC_anterior = 0.0;
float umidade_anterior = 0.0;

// unsigned long tempoAnterior = 0;
// unsigned long intervalo = 3000;

LiquidCrystal_I2C lcd(0x27, 20, 4);

DHT medidor(pinDHT, tipoDHT);

const int pinoLed = 32;
const int pinoLed1 = 33;
const int pinoLed2 = 25;
//==============================================================
// exemplos
const int pinLed0 = 2;
int intensidade = 0;
int contagem = 5;
unsigned long tempoAnterior = 0;
unsigned long intervalo = 1000;
bool subindo = true;

const int pinLed5 = 4;
const int pinLed6 = 5;
const int pinLed7 = 18;

int fase = 0;
// const int leds[] = {4, 17, 18}; // lista de ints

//==============================================================

void setup()
{
    Serial.begin(115200);
    medidor.begin();
    Serial.println("teste de dht");
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);

    lcd.print("INICIALIZADO");

    lcd.setCursor(0, 1);
    lcd.print("temperatura: ");

    lcd.setCursor(0, 2);
    lcd.print("fahrenheit: ");

    lcd.setCursor(0, 3);
    lcd.print("umidade: ");
    //==============================================================
    // teste leds
    pinMode(pinoLed, OUTPUT);
    pinMode(pinoLed1, OUTPUT);
    pinMode(pinoLed2, OUTPUT);
    //==============================================================
    // exemplos
    pinMode(pinLed0, OUTPUT);
    //==============================================================
    // exemplo
    analogWrite(pinLed5, OUTPUT);
    analogWrite(pinLed6, OUTPUT);
    analogWrite(pinLed7, OUTPUT);
    //==============================================================a=
}

void loop()
{
    //==============================================================
    // teste leds
    // digitalWrite(pinoLed, HIGH); // Liga o LED (3.3V)
    // delay(1000);                 // Espera 1 segundo
    // digitalWrite(pinoLed, LOW);  // Desliga o LED (0V)
    // delay(1000);                 // Espera 1 segundo

    // digitalWrite(pinoLed1, HIGH);
    // delay(1000);
    // digitalWrite(pinoLed1, LOW);
    // delay(1000);

    // digitalWrite(pinoLed2, HIGH);
    // delay(1000);
    // digitalWrite(pinoLed2, LOW);
    // delay(1000);
    //===============================================================
    // TESTE
    // QUANDO ELE CHEGAR EM 255 ELE VOLTA PRO 0
    // QUANDO CHEGAR A 255 VOLTANDO GRADUALMENTE A 0
    // SUBSTITUIR O DELAY POR MILLIS
    //==============================================================
    // exemplo
    unsigned long tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= intervalo) // calcula o tempo
    {
        tempoAnterior = tempoAtual;

        if (subindo)
        {
            intensidade += 51;

            if (intensidade >= 255)
            {
                intensidade = 255;

                if (fase == 0)
                    analogWrite(pinLed5, intensidade);
                else if (fase == 1)
                    analogWrite(pinLed6, intensidade);
                else if (fase == 2)
                    analogWrite(pinLed7, intensidade);

                fase = fase + 1; // passa para o próximo LED

                if (fase >= 3)
                {
                    fase = 2;        // apartir desse led
                    subindo = false; // começa a descer
                }
                else
                {
                    intensidade = 0; // zera a intensidade para o próximo led começar acendendo
                }
            }
            else
            {
                // aplica o brilho atual no pino da fase ativa
                if (fase == 0)
                    analogWrite(pinLed5, intensidade);
                else if (fase == 1)
                    analogWrite(pinLed6, intensidade);
                else if (fase == 2)
                    analogWrite(pinLed7, intensidade);
            }
        }
        else
        {
            intensidade -= 51;

            if (intensidade <= 0)
            {
                intensidade = 0;
                // apaga o led atual
                if (fase == 0)
                    analogWrite(pinLed5, intensidade);
                else if (fase == 1)
                    analogWrite(pinLed6, intensidade);
                else if (fase == 2)
                    analogWrite(pinLed7, intensidade);

                fase = fase - 1;

                if (fase < 0)
                {
                    fase = 0; // começa a subir dnv
                    subindo = true;
                }
                else
                {
                    intensidade = 255; // prepara para descer o led
                }
            }
            else
            {

                if (fase == 0)
                    analogWrite(pinLed5, intensidade);
                else if (fase == 1)
                    analogWrite(pinLed6, intensidade);
                else if (fase == 2)
                    analogWrite(pinLed7, intensidade);
            }
        }
    }

    //===============================================================
    Serial.println(intensidade); // mostra na serial e tb acendi o led
    analogWrite(pinLed0, intensidade);
    //===============================================================
    // unsigned long tempoAtual = millis();
    medidor.readHumidity();
    medidor.readTemperature();

    float tempC = medidor.readTemperature();
    float tempF = medidor.readTemperature(true);
    float umidade = medidor.readHumidity();

    if (tempoAtual - tempoAnterior >= intervalo && (tempC != tempC_anterior || umidade != umidade_anterior))
    {
        Serial.print("temp em C: ");
        Serial.println(tempC);
        Serial.print("temp em f: ");
        Serial.println(tempF);
        Serial.print("umidade: ");
        Serial.println(umidade);
        Serial.println("----------------");

        lcd.setCursor(13, 1);
        lcd.print(tempC);

        lcd.setCursor(12, 2);
        lcd.print(tempF);

        lcd.setCursor(9, 3);
        lcd.print(umidade);

        tempoAnterior = tempoAtual;
    }

    tempC_anterior = tempC;
    umidade_anterior = umidade;
}






//CODIGO CORRETO



// #include <Arduino.h>
// #include <DHT.h>
// #include <LiquidCrystal_I2C.h>

// #define pinDHT 4
// #define tipoDHT DHT22

// DHT medidorzinho(pinDHT, tipoDHT);

// LiquidCrystal_I2C lcd(0x27, 20, 4);

// void setup() {
//   Serial.begin(115200);

//   medidorzinho.begin();
//   Serial.println("Teste de DHT22");

//   lcd.init();
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("LCD Iniciado");
// }

// void loop() {
//   float tempC = medidorzinho.readTemperature();
//   float tempF = medidorzinho.readTemperature(true);
//   float umi = medidorzinho.readHumidity();

//   Serial.print("Temp em C: ");
//   Serial.println(tempC);
//   Serial.print("Temp em F: ");
//   Serial.println(tempF);
//   Serial.print("Umidade: ");
//   Serial.println(umi);
//   Serial.println("--------------------");

//   delay(3000);
// }

// Etapa 1 : Exiba no LCD os dados coletados no DHT
// Etapa 2 : Atualize os dados do LCD a cada 3 segundos
// Etapa 3 : Atualize no LCD somente o valor que é alterado
// Desafio : Atualize a cada 3 segundos somente se
//   houver alteração nos valores

// #include <Arduino.h>

// int pinLed = 2;
// int intensidade = 0;

// void setup()
// {
//   pinMode(pinLed, OUTPUT);

// ledcSetup(0, 5000, 8);
// ledcAttachPin(ledPin, 0);

// analogWrite(pinLed, 5);//0 a 255
// ledcWrite(0, 10);
// }

// void loop()
// {
//   analogWrite(pinLed, intensidade);// 0 a 255

//   intensidade += 5;

//   delay(250);
// }

// Ex - 1
// Etapa 1 - Se chegar a 255 volta a 0
// Etapa 2 - Quando chegar a 255 começa a diminuir
//  voltando gradualmente a 0
// Etapa 3 - substituiur o delay por millis
// Etapa 4 - Utilizando 3 LEDs, faça os LEDs acenderem em sequencia
//  e de forma gradual.
// #include <Arduino.h>

// #define pinLed1 4
// #define pinLed2 18
// #define pinLed3 22

// int intensidade1 = 0;
// int intensidade2 = 0;
// int intensidade3 = 0;

// bool aumentandoInt = false;
// int fase = 1;

// unsigned long tempoAnterior = 0;
// int intervalo = 200;

// void setup()
// {
//   pinMode(pinLed1, OUTPUT);
//   pinMode(pinLed2, OUTPUT);
//   pinMode(pinLed3, OUTPUT);

//   Serial.begin(115200);
// }

// void loop()
// {
//   unsigned long tempoAtual = millis();

//   if (aumentandoInt) // == true
//   {
//     if (fase == 1 && intensidade1 >= 255)
//     {
//       fase = 2;
//     }
//     else if (fase == 2 && intensidade2 >= 255)
//     {
//       fase = 3;
//     }
//     else if (fase == 3 && intensidade3 >= 255)
//     {
//       aumentandoInt = false;
//     }
//   }
//   else // Intensidade diminuindo
//   {
//     if (fase == 3 && intensidade3 <= 0)
//     {
//       fase = 2;
//     }
//     else if (fase == 2 && intensidade2 <= 0)
//     {
//       fase = 1;
//     }
//     else if (fase == 1 && intensidade1 <= 0)
//     {
//       aumentandoInt = true;
//     }
//   }

  

//   if (tempoAtual - tempoAnterior >= intervalo)
//   {
//     tempoAnterior = tempoAtual;

//     if (fase == 1)
//     {
//       if (aumentandoInt && intensidade1 < 255)
//       {
//         intensidade1 += 5;
//       }
//       else if (!aumentandoInt && intensidade1 > 0)
//       {
//         intensidade1 -= 5;
//       }
//     }
//     else if (fase == 2)
//     {
//       if (aumentandoInt && intensidade2 < 255)
//       {
//         intensidade2 += 5;
//       }
//       else if (!aumentandoInt && intensidade2 > 0)
//       {
//         intensidade2 -= 5;
//       }
//     }
//     else if (fase == 3)
//     {
//       if (aumentandoInt && intensidade3 < 255)
//       {
//         intensidade3 += 5;
//       }else if (!aumentandoInt && intensidade3 > 0)
//       {
//         intensidade3 -= 5;
//       }
//     }


//     analogWrite(pinLed1, intensidade1);
//     analogWrite(pinLed2, intensidade2);
//     analogWrite(pinLed3, intensidade3);

//     Serial.println(intensidade1);
//     Serial.println(intensidade2);
//     Serial.println(intensidade3);
//   }
// }
// Ex - 2
// Etapa 1 - Ler os dados do DHT e acender um
// LED vermelho caso a temperatura ultrapasse um valor e um
// LED azul caso a umidade ultrapasse um valor
// Etapa 2 - Aumentar e diminuir a intensidade do led de acordo
//  com os dados lidos no DHT