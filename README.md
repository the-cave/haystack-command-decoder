# Haystack Command Decoder

## What is it?
It is a library that adds a layer of safety to an existing serial interface so that end-users can handle device connections by themself plug-and-play style.  
Complements [Haystack Command Encoder](https://github.com/the-cave/haystack-command-encoder)

## Why do we need this?

[UART](https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter) is fine when used by professionals, but for end-users, there are so many things that can go wrong.  
Users can, and will, plug UART devices together and then launch a totally unrelated application from the host device resulting in unexpected or unpredictable behaviors.

The issue stemmed from the UART itself.  
Unlike [USB](https://en.wikipedia.org/wiki/USB) devices, which have descriptors, UART devices do not have a standard or a convention to provide distinguishing between devices.
This library was designed to addresses this shortcoming.
Simply put, the library brings USB VID/PID equivalent to the UART devices.

## More explanations, please.

The author wrote an article about this library at [Slime Systems' website](https://slime.systems/content/usb-liked-uart/).

## How does this library works, anyway?

The library works by prefixing each command with a 128-bit key. The number was deliberately chosen because it is [long enough for everyone](https://en.wikipedia.org/wiki/Universally_unique_identifier#Collisions).
And provide sufficient collision resistance against all currently utilized UART protocols.

## Compatibilities

Although originally designed for UART on STM8, the library is agnostic to underlying serial protocols and [ISAs](https://en.wikipedia.org/wiki/Instruction_set_architecture).

The library will work anywhere as long as the standard C language works.  
[SDCC](http://sdcc.sourceforge.net/) takes first-class priority.

It should run fine on AVR, Arm Cortex-M, PIC, MCS-51, etc.
if not, please open an issue on GitHub, you just found a bug.

The compatibility also spans beyond UART, the library works on any 8-bit serial interface.

## How to use this?

This is a very tiny software, it is bothersome to write a formal document for it. Plus, who would read it anyway?  
Please proceed to [the article](https://slime.systems/content/usb-liked-uart/) for an informal guide, and if you need more info, looking into the source code would be a very quick grok.

Or you can also see a working example [in another GitHub repository](https://github.com/midnight-wonderer/uart-ping-pong-example).  
You may also want to see the complementary library, [Haystack Command Encoder](https://github.com/the-cave/haystack-command-encoder).

## License

Haystack Command Decoder is released under the [BSD 3-Clause License](LICENSE.md). :tada:
