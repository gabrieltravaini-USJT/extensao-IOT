// Projeto Termometro - Sensor de gas automatico
//
#include <LiquidCrystal.h>

//seta variáveis
int gas_reading = 0;
int temp_reading_raw = 0;
int temp_reading = 0;

//seta quais os pinos de operação do LCD
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
 //seta os pinos que serão operados
  lcd_1.begin(16, 2); 
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(6, OUTPUT);

 //exibe tela de boas vindas por 5s e depois prepara os cabeçalhos
  lcd_1.print("   Bem-vindo!");
  delay(5000); 
  lcd_1.clear();
  lcd_1.print("TEMP:");
  lcd_1.setCursor(0, 1);
  lcd_1.print("GAS:");
}

void loop()
{
  //faz a leitura do sensor de gás e escala ele para numeros mais interpretáveis
  gas_reading = analogRead(A5);
  gas_reading = map(gas_reading, 300, 750, 0, 100);
  
  //faz a leitura do sensor de temperatura, converte e escala de F para C 
  temp_reading_raw = analogRead(A4);
  temp_reading = ((temp_reading_raw - 20) * 3.04);
  temp_reading = map(temp_reading, 0, 1023, -40, 125);
  
  //exibe os valores de leitura na tela
  lcd_1.setCursor(5, 0);
  lcd_1.print("   ");
  lcd_1.setCursor(5, 0);
  lcd_1.print(temp_reading);
  lcd_1.setCursor(9, 0);
  lcd_1.print("C");
  lcd_1.setCursor(4, 1);
  lcd_1.print(gas_reading);
  
  //caso o sensor de gás acuse leitura maior que 50, soe o buzzer 
  if (gas_reading >= 50) {
    digitalWrite(6, HIGH);
    lcd_1.print(" - PERIGO!");
  } else {
    digitalWrite(6, LOW);
    lcd_1.print(" - Seguro!");
  }
  //atualiza a leitura a cada meio segundo.
  delay(500); 
}