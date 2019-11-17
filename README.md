# Haystack Command Decoder

## What is it?
It is a library that adds a layer of safety to an existing serial interface so that end-users can handle device connections by themself plug-and-play style.

## Why do we need this?

[UART](https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter) is fine when used by professionals, but for end-users, there are so many things that can go wrong. They can plug a pair of UART devices together but launch an unrelated application that attempts to communicate via UART, resulting in unexpected or unpredictable behaviors.

The issue stemmed from the UART itself.  
Unlike [USB](https://en.wikipedia.org/wiki/USB) devices, which have descriptors, UART devices do not have a standard or a convention to provide distinguishing between devices.
This library was designed to addresses this shortcoming.
Simply put, the library brings USB VID/PID equivalent to the UART devices.
 
The library works by prefixing each command with a 128-bit key, which [long enough for everyone to randomly generated and used by themself without a centralized device registry](https://en.wikipedia.org/wiki/Universally_unique_identifier#Collisions), and provide collision resistance against all currently utilized UART protocols.

## Compatabilities

Although originally designed for UART on STM8, the library is agnostic to underlying serial protocols and [ISAs](https://en.wikipedia.org/wiki/Instruction_set_architecture).

The library will work anywhere as long as the standard C language works.  
[SDCC](http://sdcc.sourceforge.net/) takes first-class priority.

It should run fine on AVR, Arm Cortex-M, PIC, MCS-51, etc.
if not, please open an issue on GitHub, you just found a bug.

## How to use this?

The best way to utilize the library now is to look at [its source code](src/haystack_command_decoder.c). It has the same usage style as [Button Debounce](https://github.com/the-cave/button-debounce), to get you some ideas.

I will come back and write up more details in this README when I have time. In the meantime, you can keep using the library as it is very stable and robust.

## License

Time Prescaler is released under the [BSD 3-Clause License](LICENSE.md). :tada:
