# ESPHome Light Gradient 🌈
An example how to create color (or brightness) gradient with regular [FastLED](https://esphome.io/components/light/fastled.html) and [Home Assistant](https://esphome.io/guides/getting_started_hassio.html) (HASS)

<img width="40%" src="https://github.com/a0s/esphome-light-gradient/assets/418868/ddd13978-b596-45c1-b3b1-fd2ce66dc9f5">
<img width="40%" src="https://github.com/a0s/esphome-light-gradient/assets/418868/0ad3c38d-1cdf-456a-947e-2c53c720e060">

## Devices
- [WiFi Smart LED Light Bar RGB Atmosphere Light Music Synchronization 12 Modes TV Wall Computer Game Room Decoration Night Light](https://www.aliexpress.com/item/1005004983859307.html)
- [RGB Bluetooth LED Hexagon Light Indoor Wall Light APP Remote Control Night Light Computer Game Room Bedroom Bedside Decoration
](https://www.aliexpress.com/item/1005003380581309.html)

In both devices, I was forced to replace their native controllers (Tuya and Magic Home) with regular esp8266. No additional power tricks were needed. Both devices use ws2812b, or their clones. The pinout was determined with the help of an oscilloscope.

## How it works

Each device in the HASS interface is represented by three entities. Two [RGB Lights](https://esphome.io/components/light/rgb.html) determine the color at the beginning and end of the gradient. And the [Template Select](https://esphome.io/components/select/template.html) allows you to switch modes of operation of the LED strip, as well as turn it off.

<img width="90%" alt="HASS entity list" src="https://github.com/a0s/esphome-light-gradient/assets/418868/2410da65-ff24-4ebd-9c83-258cff03907e">

<img width="40%" alt="Screenshot 2023-05-24 at 00 26 45" src="https://github.com/a0s/esphome-light-gradient/assets/418868/c805eeef-70bb-4d85-a751-4c98f6aa0b5f"><img width="40%" alt="Screenshot 2023-05-24 at 00 26 30" src="https://github.com/a0s/esphome-light-gradient/assets/418868/63f27b74-5b3e-4d77-a1b5-3ee0279f5905">


The RGB Light isn't real, we're just using this entity as an interface for color selection on the HASS side. To use it, we need a [fake output](/esphome/NullOutputComponent.h):

```yaml
esphome:
  includes:
    - esphome/NullOutputComponent.h
output:
  - platform: custom
    type: float
    lambda: |-
      auto my_output = new NullOutputComponent();
      App.register_component(my_output);
      return {my_output};
    outputs:
      id: null_output_float
```

⚠️ To be able to set a specific color for each LED, we use [Addressable Light](https://esphome.io/components/display/addressable_light.html) over FastLED Light. Addressable Light supports so-called pages, on which different content can be presented. It's these pages that we [switch](/esphome/set_action.yaml) using Template Select. All the magic of rendering happens in the [description of the pages](/esphome/display_pages.yaml). The RGB Lights are used as a color source for the start and end of the gradient.

The LED strip is defined using fastled_clockless. The `restore_mode: ALWAYS_ON` mode is used so as not to interfere with the operation of addressable_light.

Don't forget to update the [mosaic_leds_count](https://github.com/a0s/esphome-light-gradient/blob/main/esphome.yaml#L2) variable with the actual number of LEDs.

## Disadvantages

- To control one light source, you need to visit three popup dialogs in HASS. Here, [scenes help a little](/home-assistant/scenes.yaml).
- To control two different light sources, you need to have a full copy of the source codes with differing IDs. This is quite error-prone when copy-pasting.
- It's impossible to adequately control the colors from the ESPHome web interface: <img width="400" alt="Screenshot 2023-05-24 at 10 59 43" src="https://github.com/a0s/esphome-light-gradient/assets/418868/69883e08-2be6-4bca-a82f-0208fafb7bab">

