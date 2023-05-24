# ESPHome Light Gradient 🌈
An example how to create color (or brightness) gradient with regular [FastLED](https://esphome.io/components/light/fastled.html) and [Home Assistant](https://esphome.io/guides/getting_started_hassio.html)

<img width="40%" src="https://github.com/a0s/esphome-light-gradient/assets/418868/ddd13978-b596-45c1-b3b1-fd2ce66dc9f5">
<img width="40%" src="https://github.com/a0s/esphome-light-gradient/assets/418868/0ad3c38d-1cdf-456a-947e-2c53c720e060">

## Devices
- [WiFi Smart LED Light Bar RGB Atmosphere Light Music Synchronization 12 Modes TV Wall Computer Game Room Decoration Night Light](https://www.aliexpress.com/item/1005004983859307.html)
- [RGB Bluetooth LED Hexagon Light Indoor Wall Light APP Remote Control Night Light Computer Game Room Bedroom Bedside Decoration
](https://www.aliexpress.com/item/1005003380581309.html)

In both devices, I was forced to replace their native controllers (Tuya and Magic Home) with regular esp8266. No additional power tricks were needed. Both devices use ws2812b, or their clones. The pinout was determined with the help of an oscilloscope.

## How it works

Each device in the HASS interface is represented by three entities. Two RGB Lights determine the color at the beginning and end of the gradient. And the Select Template allows you to switch modes of operation of the LED strip, as well as turn it off.

<img width="90%" alt="HASS entity list" src="https://github.com/a0s/esphome-light-gradient/assets/418868/2410da65-ff24-4ebd-9c83-258cff03907e">

## Disadvantages

- To control one light source, you need to visit three popup dialogs in HASS. Here, scenes help a little
- It's impossible to adequately control the colors from the ESPHome web interface.
