#include <Arduino.h> 
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "gloraiaatas";
const char* password = "k1t4p4st1b1s4";
const char* mqtt_server = "test.mosquitto.org"; 
const int RELAY_PIN = 23; 

WiFiClient espClient;
PubSubClient client(espClient);


String last_booking_id = "";
String last_event = "";


void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); 

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("\n[DEVICE] Menerima Pesan di Topik: ");
  Serial.println(topic);


  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)payload[i];
  }


  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, messageTemp);
  if (error) {
    Serial.println("[ERROR] Gagal baca JSON!");
    return;
  }

  String event = doc["event"];
  String booking_id = doc["booking_id"];


  if (booking_id == last_booking_id && event == last_event) {
    Serial.println("[DEVICE] WARNING: Pesan dobel! Mengabaikan perintah.");
    return; 
  }

  if (event == "booking_started") {
    digitalWrite(RELAY_PIN, HIGH); 
    Serial.println("[DEVICE] RELAY ON! Lampu Menyala.");
  } 
  else if (event == "booking_ended") {
    digitalWrite(RELAY_PIN, LOW); 
    Serial.println("[DEVICE] RELAY OFF! Lampu Mati.");
  }


  last_booking_id = booking_id;
  last_event = event;
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Konek ke MQTT...");
    if (client.connect("ESP32_Bay07_Client")) { 
      Serial.println("Berhasil!");
      client.subscribe("venue/golf/bay-07/light/command", 1); 
    } else {
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}