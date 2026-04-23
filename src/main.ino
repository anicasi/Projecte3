#include <WiFi.h>
const char* ssid = "ProjectesSMX";
const char* password = "Hola1234";
const int pinLDR = 35; 
const int pinLM35 = 34;
const int LED = 27;

#include <WebServer.h>
WebServer server(80);

void credits() { server.send(200, "text/html", "<h1>Fet per Alex i jonathan</h1>"); }

void setup() {
pinMode(LED, OUTPUT);
Serial.begin(115200);
WiFi.begin(ssid, password);
Serial.print("Connectant...");
server.on("/credits", credits);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("\n Connectat!");
Serial.print("IP: ");
Serial.println(WiFi.localIP());
server.begin();
server.on("/", enviarPaginaPrincipal);
}

void loop() {
server.handleClient();
}
void enviarPaginaPrincipal() {
int valorLDR = analogRead(pinLDR);
float tempC = (analogRead(pinLM35) * 5.0 / 4095.0) * 100.0;

String colorTemp = "#28a745"; // Verd
digitalWrite(LED, LOW); 

if (tempC > 24.0) { 
  colorTemp = "#dc3545"; // Vermell
  digitalWrite(LED, HIGH);
}

String html = "<html><head><meta charset='UTF-8'>";
html += "<style>body{font-family:sans-serif; text-align:center;} .card{padding:20px; color:white; display:inline-block; margin:10px; border-radius:10px;}</style>";
html += "</head><body><h1>Monitor CPD</h1>";
html += "<div class='card' style='background:" + colorTemp + ";'><h3>Temp</h3><p>" + String(tempC, 1) + " ºC</p></div>";
html += "</body></html>";
server.send(200, "text/html", html);
}

