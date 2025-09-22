#define PIN_WIRE_SDA (22u)
#define PIN_WIRE_SCL (21u)

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2_for_Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_PIN_SDA (22u)
#define SCREEN_PIN_SCL (21u)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

int x, minX;
const String message = F("Hello ^0^ World ^O^");

void setup() {
  Wire.setPins(SCREEN_PIN_SDA, SCREEN_PIN_SCL);
  // put your setup code here, to run once:
  Serial.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  u8g2_for_adafruit_gfx.begin(display);
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds 

  // Clear the buffer
  display.clearDisplay();
  display.setTextWrap(false);
  display.setTextColor(SSD1306_WHITE);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_wqy16_t_gb2312a); // Draw 2X-scale text
    // Show initial text
  delay(100);
  x = display.width();
  minX = -16 * (int) message.length() / 2; //message.length()
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  u8g2_for_adafruit_gfx.setCursor(x, 30);
  u8g2_for_adafruit_gfx.print(message);
  display.display();

  if(--x < minX) x = display.width();
}

