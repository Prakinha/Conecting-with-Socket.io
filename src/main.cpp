#include <Wifi.h>
#include <ArduinoWebsockets.h>
#include <MFRC522.h>
#include <SPI.h>
#include <ArduinoJson.h>

#define SS_PIN    21
#define RST_PIN   22
MFRC522 mfrc522(SS_PIN, RST_PIN); 

using namespace websockets;
JsonDocument doc;

// Configurações de Wi-Fi
const char* ssid = "S23+";
const char* password = "amopavao";

// Configurações do WebSocket
const char* websockets_server_host = "192.168.202.23"; // IP do servidor
const uint16_t websockets_server_port = 420;        // Porta do servidor

String targetDevice = "frontend";

WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Mensagem recebida do servidor: ");

  

  DeserializationError error = deserializeJson(doc, message.data());
  const String msg = doc["content"];
  Serial.println(msg);
  if(msg=="i"){
    String uid = "c37137aa";
    String message = "{\"type\":\"card\",\"uid\":\"" + uid + "\",\"targetName\":\"" + targetDevice + "\"}";
        client.send(message);
  }
  if(msg=="o"){
    String uid = "3b5bb280";
    String message = "{\"type\":\"card\",\"uid\":\"" + uid + "\",\"targetName\":\"" + targetDevice + "\"}";
        client.send(message);
  }
  //Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    Serial.println("Conexão WebSocket aberta");
    SPI.begin();       // Inicia o barramento SPI
    mfrc522.PCD_Init(); // Inicializa o leitor RFID
    client.send("{\"type\":\"device\",\"device\":\"espUSBc\"}");

    Serial.println("Aproxime o cartão do leitor...");
    // client.send("Olá do ESP32!");
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    Serial.println("Conexão WebSocket fechada");
  } else if (event == WebsocketsEvent::GotPing) {
    Serial.println("Ping recebido");
  } else if (event == WebsocketsEvent::GotPong) {
    Serial.println("Pong recebido");
  } else {
    Serial.println("Evento WebSocket desconhecido");
  }
}

void setup() {
  Serial.begin(115200);

  // Conectar ao Wi-Fi
  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");

  // Configurar eventos do WebSocket
  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);

  // Conectar ao servidor WebSocket
  String url = String("ws://") + websockets_server_host + ":" + websockets_server_port;
  client.connect(url);
}

void loop() {
  client.poll();
   // Verifica se há um novo cartão presente
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        // Exibe o UID do cartão lido
        Serial.print("UID do cartão: ");
        String uid = "";
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            uid += String(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.println(uid);

        // Para a leitura do cartão e desabilita a comunicação segura
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
  String message = "{\"type\":\"card\",\"uid\":\"" + uid + "\",\"targetName\":\"" + targetDevice + "\"}";
        client.send(message);

        // Aguarda um pouco para evitar leituras repetidas
        delay(1000);
    }
}
