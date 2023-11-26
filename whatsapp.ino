#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* ssid = "SUA REDE WIFI";
const char* password = "SENHA DO SEU WIFI";

#define Sensor 36
bool flag = 1;

// +international_country_code + phone number
// Brasil +55, example: +5511988888888
String phoneNumber = "+55SEUNUMERO";
String apiKey = "SUA APIKEY";

void sendMessage(String message) {

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Mensagem enviada com sucesso");
  } else {
    Serial.println("Erro no envio da mensagem");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);

  pinMode(Sensor, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado ao WiFi neste IP ");
  Serial.println(WiFi.localIP());
}

void loop() {

  int Porta = digitalRead(Sensor);


  if (Porta == 1) {
    
    if (flag) {
      sendMessage("Porta Aberta!");
      flag = 0;
    }
  } else {
    
    flag = 1;
  }
}