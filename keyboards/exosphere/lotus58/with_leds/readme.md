# lotus58

*This is firmware for my customised Lotus58 keyboard. It features 5 RGB LEDs on each side of the keyboard, these LEDs show which layer the keyboard is in. It also has two keymaps - one for macOS and one for Windows/Linux. I load one keymap to one half, and the other to the other half. This lets me switch between OSes by just plugging the USB to another half of the keyboard.*

For the keyboard hardware design and original firmware, please refer to the original developer [Markus Knutsson](https://github.com/TweetyDaBird/).

* Keyboard Maintainer: [TweetyDaBird](https://github.com/TweetyDaBird)
* Hardware Supported: *Lotus 58 Glow v1.11 - 1.24 PCB, Pro Micro or pin-compatible*
* Hardware Availability: [Lectronz Store](https://lectronz.com/stores/tweetys-wild-thinking)
* Hardware Design: [GitHub](https://github.com/TweetyDaBird/Lotus58)

Make example for this keyboard (after setting up your build environment):

    make exosphere/lotus58/with_leds:default

Flashing example for this keyboard:

    make exosphere/lotus58/with_leds:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 1 way:

* **Physical reset**: Briefly short the marked pads on PCB
