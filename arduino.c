#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definições de pinos e constantes
#define DHTPIN 2
#define DHTTYPE DHT22
#define sensorLuminosidade A0
#define buzzer 12
#define ledVermelho 4
#define ledAmarelo 5
#define ledVerde 6
#define ende 0x27
#define col 16
#define lin 2

// Inicialização dos objetos
LiquidCrystal_I2C lcd(ende, col, lin);
DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensorLuminosidade, INPUT);

  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
}

// Função para desligar tudo
void clearAll() {
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
  noTone(buzzer);
  lcd.clear();
}

void loop() {
  float temperatura = 0;
  float umidade = 0;
  int luzBruta = 0;
  clearAll();

  // Leitura de 5 amostras
  for (int i = 0; i < 5; i++) {
    sensors_event_t tempEvent, humEvent;
    dht.temperature().getEvent(&tempEvent);
    dht.humidity().getEvent(&humEvent);

    if (!isnan(tempEvent.temperature)) {
      temperatura += tempEvent.temperature;
    }

    if (!isnan(humEvent.relative_humidity)) {
      umidade += humEvent.relative_humidity;
    }

    luzBruta += analogRead(sensorLuminosidade);
    delay(1000);
  }

  temperatura /= 5;
  umidade /= 5;
  luzBruta /= 5;

  // Conversão da luz para percentual de claridade
  int luzPercentual = map(luzBruta, 0, 1023, 100, 0); // 100 = escuro, 0 = claro

  // --- Luz ---
  if (luzPercentual < 50) {
    digitalWrite(ledVerde, HIGH);
  } else if (luzPercentual >= 50 && luzPercentual <= 70) {
    digitalWrite(ledAmarelo, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Ambiente");
    lcd.setCursor(0, 1);
    lcd.print("a meia luz");
  } else {
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 1000);
    lcd.setCursor(0, 0);
    lcd.print("Ambiente");
    lcd.setCursor(0, 1);
    lcd.print("muito claro");
  }

  delay(2000);
  lcd.clear();

  // --- Temperatura ---
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatura, 1);
  lcd.print(" C");

  if (temperatura >= 10 && temperatura <= 15) {
    lcd.setCursor(0, 0);
    lcd.print("Temperatura OK");
  } else if (temperatura > 15) {
    digitalWrite(ledAmarelo, HIGH);
    tone(buzzer, 1200);
    lcd.setCursor(0, 0);
    lcd.print("Temp. ALTA");
  } else {
    digitalWrite(ledAmarelo, HIGH);
    tone(buzzer, 800);
    lcd.setCursor(0, 0);
    lcd.print("Temp. BAIXA");
  }

  delay(2000);
  lcd.clear();

  // --- Umidade ---
  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(umidade, 1);
  lcd.print(" %");

  if (umidade >= 50 && umidade <= 70) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK");
  } else if (umidade > 70) {
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 2000);
    lcd.setCursor(0, 0);
    lcd.print("Umid. ALTA");
  } else {
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 600);
    lcd.setCursor(0, 0);
    lcd.print("Umid. BAIXA");
  }

  delay(2000);
}
