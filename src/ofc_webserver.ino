// ofc_webserver.ino

#include "arduino_secrets.h"
#include "ofc_webserver.h"
#include "html.pages.h"
#include "leds.h"

MultiWiFi multi;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

unsigned char buffer[3000];

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  ledset(iled1, LED1, 0x20);
  ledset(iled2, LED2, 0x00);
  ledset(iled3, LED3, 0x00);

  Serial.begin(115200);
  // while (!Serial)
  // {
  // }
  delay(200);
  Serial.println("Serial connected");

  digitalWrite(LED_BUILTIN, HIGH);
  ledset(iled1, LED1, 0x02);
  ledset(iled2, LED2, 0x20);

  multi.add(SECRET_NID, SECRET_NPW);

  Serial.println("Looking for a network...");
  if (multi.run() == WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    ledset(iled2, LED2, 0x02);
    ledset(iled3, LED3, 0x20);
    printwifidetails(Serial, WiFi);
    server.begin();
  }
  else
  {
    Serial.println("Failed to connect to a WiFi network");
  }
  ledset(iled1, LED1, 0x00);
  ledset(iled2, LED2, 0x00);
  ledset(iled3, LED3, 0x00);
  FastLED.addLeds<WS2811, 10>(leds, NUM_LEDS);
  FastLED.setBrightness(60);
}

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    String currentLine = "";
    String getPath = "";

    while (client.connected())
    {
      digitalWrite(LED_BUILTIN, HIGH);

      if (client.available())
      {
        currentLine = client.readStringUntil('\n');
        if (currentLine.startsWith("GET "))
        {
          // Serial.println(currentLine);
          getPath = currentLine.substring(4, currentLine.lastIndexOf(' '));
          if (getPath.length() == 0)
          {
            getPath = "/";
          }
          if (getPath.endsWith("/"))
          {
            getPath += "index.html";
          }

          PAGE_DATA *ptrPageData = HtmlFindPage(getPath);

          if (!ptrPageData)
          {
            HtmlSendPage404(client);
          }
          if (ptrPageData)
          {
            // Serial.println(ptrPageData->path);
            HtmlSendPage200(client, ptrPageData);
          }
        }
      }
    }
    // close the connection:
    client.stop();
    digitalWrite(LED_BUILTIN, LOW);
  }
}
