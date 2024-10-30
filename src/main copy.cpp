

// #include <Wifi.h>
// #include <ArduinoWebsockets.h>


// using namespace websockets;

// // Configurações de Wi-Fi
// const char* ssid = "S23+";
// const char* password = "amopavao";

// // Configurações do WebSocket
// const char* websockets_server_host = "192.168.202.23"; // IP do servidor
// const uint16_t websockets_server_port = 420;        // Porta do servidor

// WebsocketsClient client;

// void onMessageCallback(WebsocketsMessage message) {
//   Serial.print("Mensagem recebida do servidor: ");
//   Serial.println(message.data());
// }

// void onEventsCallback(WebsocketsEvent event, String data) {
//   if (event == WebsocketsEvent::ConnectionOpened) {
//     Serial.println("Conexão WebSocket aberta");
//     client.send("{\"type\":\"device\",\"device\":\"esp32\"}");

//     Serial.println("Aproxime o cartão do leitor...");
//     // client.send("Olá do ESP32!");
//   } else if (event == WebsocketsEvent::ConnectionClosed) {
//     Serial.println("Conexão WebSocket fechada");
//   } else if (event == WebsocketsEvent::GotPing) {
//     Serial.println("Ping recebido");
//   } else if (event == WebsocketsEvent::GotPong) {
//     Serial.println("Pong recebido");
//   } else {
//     Serial.println("Evento WebSocket desconhecido");
//   }
// }

// void setup() {
//   Serial.begin(115200);

//   // Conectar ao Wi-Fi
//   Serial.print("Conectando ao Wi-Fi...");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("Conectado!");

//   // Configurar eventos do WebSocket
//   client.onMessage(onMessageCallback);
//   client.onEvent(onEventsCallback);

//   // Conectar ao servidor WebSocket
//   String url = String("ws://") + websockets_server_host + ":" + websockets_server_port;
//   client.connect(url);
// }

// void loop() {    
// }
