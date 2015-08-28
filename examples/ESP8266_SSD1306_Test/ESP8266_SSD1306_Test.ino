#include "U8glib.h"

//U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1306_128X64 u8g(4, 5, 6, 7);	// SW SPI Com: SCK = 4, MOSI = 5, CS = 6, A0 = 7 (new white HalTec OLED)
//U8GLIB_SSD1306_128X64 u8g(10, 9);		// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);	// Display which does not send AC
//U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(13, 11, 10, 9);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(10, 9);		// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X32 u8g(13, 11, 10, 9);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1306_128X32 u8g(10, 9);             // HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 
//U8GLIB_SSD1306_64X48 u8g(13, 11, 10, 9);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1306_64X48 u8g(10, 9);             // HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_64X48 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

U8GLIB_SSD1306_128X64 *u8g = NULL;
bool pinVal = true;
bool drawn = false;

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g->setFont(u8g_font_unifont);
  //u8g->setFont(u8g_font_osb21);
  u8g->drawStr( 0, 22, "Hello World!");
}

void setup(void) {
  pinMode(16, OUTPUT);
  //digitalWrite(16, LOW);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  
  Serial.println("Setup complete");
  //digitalWrite(16, HIGH);
}

void setupDisplay()
{
  if (u8g == NULL)
  {
    //digitalWrite(16, HIGH);
    u8g = new U8GLIB_SSD1306_128X64(U8G_I2C_OPT_NO_ACK);
    // flip screen, if required
    // u8g.setRot180();
    
    // set SPI backup if required
    //u8g.setHardwareBackup(u8g_backup_avr_spi);
  
    // assign default color value
    if ( u8g->getMode() == U8G_MODE_R3G3B2 ) {
      u8g->setColorIndex(255);     // white
    }
    else if ( u8g->getMode() == U8G_MODE_GRAY2BIT ) {
      u8g->setColorIndex(3);         // max intensity
    }
    else if ( u8g->getMode() == U8G_MODE_BW ) {
      u8g->setColorIndex(1);         // pixel on
    }
    else if ( u8g->getMode() == U8G_MODE_HICOLOR ) {
      u8g->setHiColorByRGB(255,255,255);
    }
  }
}

void loop(void) {
  pinVal = !pinVal;
  //digitalWrite(16, pinVal);
  if (u8g == NULL)
  {
    //digitalWrite(16, true);
    setupDisplay();
  }
  if ((u8g != NULL) && !drawn)
  {
    // picture loop
    u8g->firstPage();  
    do {
      draw();
    } while( u8g->nextPage() );
    Serial.println("Draw done");
    drawn = true;
  }
  
  // rebuild the picture after some delay
  delay(500);
}

