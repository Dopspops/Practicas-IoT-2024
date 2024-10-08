#include <WiFi.h>
#include <WiFiClient.h>
const char* ssid = "IoT";
const char* password = "1t3s0IoT23";

WiFiServer server(80);

WiFiClient client;

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

void setup()
{
  Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  Serial.println("Iniciando");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(800);
    Serial.print(".");
  }
  Serial.println("Conexion establecida con el SSID");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{

    client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.flush();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title> MiESP32 </title>");
    client.println("</head>");
    client.println("<body>");
      client.println("<h1 style=""color:#3333ff"">");
      client.println("");
      client.println("</h1>");
      client.println("<span style=""color:#009900;font-size:14px"">");
      client.println("Bienvenidos a mi Pagina Web");
      client.println("</span>");
      client.println("<br>");
      client.println("<span style=""color:#ff6600;font-size:14px"">");
      client.println("Esta pagina web a sido activa por");
      client.println("</span>");
      client.println("<span style=""color:#33ff33;font-size:24px"">");
      client.println((millis()/1000));
      client.println("</span>");
      client.println("<span style=""color:#ff6600;font-size:14px"">");
      client.println("segundos");
      client.println("</span>");
      client.println("<br>");
      client.println("<span style=""color:#999900;font-size:14px"">");
      client.println("La temperatura interna del ESP32 es de: ");
      client.println("</span>");
      client.println("<span style=""color:#000000;font-size:14px"">");
      client.println(((temprature_sens_read() - 32 ) / 1.8));
      client.println("</span>");
      client.println("<span style=""color:#999900;font-size:14px"">");
      client.println("grados");
      client.println("</span>");
    client.println("</body>");
    client.println("</html>");
    delay(1);

}