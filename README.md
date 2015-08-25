# U8glib-ArduinoESP
Modifications of the U8glib library for Arduino on the ESP8266.

Currently using source from: https://github.com/olikraus/u8glib

To use this, replace platform.txt in C:\Users\\(YOUR_USERNAME)\AppData\Roaming\Arduino15\packages\esp8266\hardware\esp8266\1.6.5-947-g39819f0 with the one included.  This will allow the library to build, but it still may not run properly.

In order to use the library in sketches, you'll need to create the u8g object using the "new" keyword within your code- creating it on the stack will not work (all of the existing u8g examples create it on the stack).

If you want to improve support, look for the preprocessor directive \_\_XTENSA\_\_ in the source files- that's how the preprocessor identifies the ESP8266 hardware.
