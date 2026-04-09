#include <WiFi.h>
const char* ssid = "ProjectesSMX";
const char* password = "Hola1234";

#include <WebServer.h>
WebServer server(80);


void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
Serial.print("Connectant...");

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("\n Connectat!");
Serial.print("IP: ");
Serial.println(WiFi.localIP());
  
server.on("/", enviarPaginaPrincipal);
server.begin();
}

void loop() {
server.handleClient();
}
void enviarPaginaPrincipal() {
  server.send(200, "text/plain", "Hola, soc el teu ESP32");
}
