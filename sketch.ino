/////////--------IOT--------FIAP------------///////////

#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";  // Substitua pelo sua senha

// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "crotopus_sprint_mqtt";
const char *TOPIC_SUBSCRIBE_LED = "sprint4/iot/led";
const char *TOPIC_PUBLISH_LDR = "sprint4/iot/ldr";
const char *TOPIC_SUBSCRIBE_SERVO1 = "sprint4/iot/servo1";
const char *TOPIC_SUBSCRIBE_SERVO2 = "sprint4/iot/servo2";

// Configurações de Hardware
#define PIN_LDR 12
#define PIN_LEDRED 15
#define PIN_LEDGREEN 4
#define PIN_SERVO1 2
#define PIN_SERVO2 5
#define PUBLISH_DELAY 2000

// Variáveis globais
WiFiClient espClient;
PubSubClient MQTT(espClient);
unsigned long publishUpdate = 0;
const int TAMANHO = 200;
Servo servo1;
Servo servo2;

// Protótipos de funções
void updateSensorValues();
void initWiFi();
void initMQTT();
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT();
void reconnectWiFi();
void checkWiFIAndMQTT();


void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);
}

void callbackMQTT(char *topic, byte *payload, unsigned int length) {
  String msg = String((char*)payload).substring(0, length);

  Serial.printf("Mensagem recebida via MQTT: %s do tópico: %s\n", msg.c_str(), topic);

  if (strcmp(topic, TOPIC_SUBSCRIBE_SERVO1) == 0) {
    int angle = atoi(msg.c_str());
    if (angle >= 0 && angle <= 180) {
      servo1.write(angle);
      Serial.printf("Servo 1 movido para o ângulo %d\n", angle);
    } else {
      Serial.println("Ângulo fora do intervalo válido (0-180) para o Servo 1");
    }
  } else if (strcmp(topic, TOPIC_SUBSCRIBE_SERVO2) == 0) {
    int angle = atoi(msg.c_str());
    if (angle >= 0 && angle <= 180) {
      servo2.write(angle);
      Serial.printf("Servo 2 movido para o ângulo %d\n", angle);
    } else {
      Serial.println("Ângulo fora do intervalo válido (0-180) para o Servo 2");
    }
  }
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar com o Broker MQTT: ");
    Serial.println(BROKER_MQTT);

    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
      MQTT.subscribe(TOPIC_SUBSCRIBE_SERVO1);
      MQTT.subscribe(TOPIC_SUBSCRIBE_SERVO2);
    } else {
      Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void reconnectWiFi(void) {
  if (WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wifi conectado com sucesso");
  Serial.print(SSID);
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_LEDRED, OUTPUT);
  pinMode(PIN_LEDGREEN, OUTPUT);
  digitalWrite(PIN_LEDRED, LOW);
  digitalWrite(PIN_LEDGREEN, LOW);
  initWiFi();
  initMQTT();
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
}

void loop() {
  checkWiFIAndMQTT();
  MQTT.loop();


  if (digitalRead(PIN_LDR) == LOW ) {

    servo1.write(180);
    servo2.write(180);
    digitalWrite(PIN_LEDGREEN, HIGH);
    digitalWrite(PIN_LEDRED, LOW);


  } else if (digitalRead(PIN_LDR) == HIGH) {
    servo1.write(0);
    servo2.write(0);
    digitalWrite(PIN_LEDRED, HIGH);
    digitalWrite(PIN_LEDGREEN, LOW);
  }

  if ((millis() - publishUpdate) >= PUBLISH_DELAY) {
    publishUpdate = millis();
    int ldrValue = digitalRead(PIN_LDR);
    StaticJsonDocument<TAMANHO> doc;
    doc["ldr"] = ldrValue;
    char buffer[TAMANHO];
    serializeJson(doc, buffer);
    MQTT.publish(TOPIC_PUBLISH_LDR, buffer);
    Serial.println(buffer);
  }
}
