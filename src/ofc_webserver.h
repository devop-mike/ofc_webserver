// ofc_webserver.h
#include <WiFiNINA.h>
#include <Arduino_MultiWiFi.h>

void printwifidetails(Stream &target, WiFiClass &wifi)
{
  target.print("sid : ");
  target.println(wifi.SSID());

  target.print("ip  : ");
  target.println(wifi.localIP());

  target.print("gw  : ");
  target.println(wifi.gatewayIP());

  target.print("mac : ");
  uint8_t macval[WL_MAC_ADDR_LENGTH];
  wifi.macAddress(macval);
  for (int i = WL_MAC_ADDR_LENGTH; i > 0; i--)
  {
    target.print(macval[i], HEX);
    target.print(":");
  }
  target.println(macval[0], HEX);
}
