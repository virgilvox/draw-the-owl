#include <Arduino.h>

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "GxEPD2_display_selection_new_style.h"
#include "GxEPD2_display_selection.h"
#include "GxEPD2_display_selection_added.h"

#include "twilio_owl.h"


WiFiMulti wifiMulti;


void setup() {
  Serial.begin(115200);
  wifiMulti.addAP("Fawkes", "letmedothatforyou");

  display.init();
  helloWorld("Hello Twilio!");
  display.hibernate();
}

//const char HelloWorld[] = "Hello Twilio!";

void helloWorld(char *phrase)
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(phrase, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(phrase);
    display.drawBitmap(115, 50, epd_bitmap_twer, 212, 176, GxEPD_RED);
  }
  while (display.nextPage());
}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("http://dog-facts-api.herokuapp.com/api/v1/resources/dogs?number=1"); //HTTP
        int httpCode = http.GET();
        if(httpCode > 0) {
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);

                int str_len = payload.length() + 1; 
                char char_array[str_len];
                payload.toCharArray(char_array, str_len);
                helloWorld(char_array);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    delay(5000);
}
