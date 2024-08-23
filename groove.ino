#include <TFT_eSPI.h>
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>

GAS_GMXXX<TwoWire> gas;
TFT_eSPI tft; 
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite 

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize TFT
  tft.begin();
  tft.setRotation(3);
  spr.createSprite(tft.width(), tft.height()); 

  // Initialize gas sensor
  gas.begin(Wire, 0x08); // use the hardware I2C
}

void loop() {
  int val;

  // Clear sprite background
  spr.fillSprite(TFT_BLACK);
  
  // Draw header
  spr.setFreeFont(&FreeSansBoldOblique18pt7b); 
  spr.setTextColor(TFT_BLUE);
  spr.drawString("Gas Terminal", 60 - 15, 10 , 1); // Print the test text in the custom font

  // Draw lines
  for(int8_t line_index = 0; line_index < 5; line_index++) {
    spr.drawLine(0, 50 + line_index, tft.width(), 50 + line_index, TFT_GREEN);
  }
  
  // GM102B NO2 sensor
  val = gas.getGM102B();
  if (val > 999) val = 999;
  spr.setFreeFont(&FreeSansBoldOblique9pt7b);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("NO2:", 60 - 24, 100 - 24 , 1); // Print the test text in the custom font
  spr.drawRoundRect(60 - 24, 100, 80, 40, 5, TFT_WHITE); 
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(val, 60 - 20, 100 + 10, 1);
  spr.setTextColor(TFT_GREEN);
  
  // Print NO2 value to Serial Monitor
  Serial.print("NO2: ");
  Serial.println(val);

  // GM302B C2H5CH sensor
  val = gas.getGM302B();
  if (val > 999) val = 999;
  spr.setTextColor(TFT_WHITE);
  spr.drawString("C2H5CH:", 230 - 24, 100 - 24 , 1); // Print the test text in the custom font
  spr.drawRoundRect(230 - 24, 100, 80, 40, 5, TFT_WHITE);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(val, 230 - 20, 100 + 10, 1);
  spr.setTextColor(TFT_GREEN);
  
  // Print C2H5CH value to Serial Monitor
  Serial.print("C2H5CH: ");
  Serial.println(val);

  // GM502B VOC sensor
  val = gas.getGM502B();
  if (val > 999) val = 999;
  spr.setTextColor(TFT_WHITE);
  spr.drawString("VOC:", 60 - 24, 180 - 24 , 1); // Print the test text in the custom font
  spr.drawRoundRect(60 - 24, 180, 80, 40, 5, TFT_WHITE);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(val, 60 - 20, 180 + 10, 1);
  spr.setTextColor(TFT_GREEN);
  
  // Print VOC value to Serial Monitor
  Serial.print("VOC: ");
  Serial.println(val);

  // GM702B CO sensor
  val = gas.getGM702B();
  if (val > 999) val = 999;
  spr.setTextColor(TFT_WHITE);
  spr.drawString("CO:", 230 - 24 , 180 - 24, 1); // Print the test text in the custom font
  spr.drawRoundRect(230 - 24, 180, 80, 40, 5, TFT_WHITE);
  spr.setTextColor(TFT_WHITE);
  spr.drawNumber(val , 230 - 20 , 180 + 10, 1);
  spr.setTextColor(TFT_GREEN);
  
  // Print CO value to Serial Monitor
  Serial.print("CO: ");
  Serial.println(val);

  // Push sprite to TFT display
  spr.pushSprite(0, 0);
  
  // Add delay to reduce flickering
  delay(1000);
}
