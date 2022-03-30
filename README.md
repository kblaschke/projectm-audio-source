# projectM Audio Backend Library

This library contains shared code for use with standalone projectM applications to enumerate and use different
platform-specific audio backends with a single interface.

## Supported Backends

The library currently supports the following backends:

- SDL2: Windows, macOS, Linux, *BSD, Android, iOS
- PulseAudio: Windows, Linux, *BSD
- JACK: Windows, macOS, Linux, *BSD
- WASAPI: Windows

There is also a Fake backend available on all platforms which generates random noise and can be used to make the
visualisation more appealing if no audio sources are available.

## Directory Structure

The library is split into subdirectories:

- `projectMAudioSource` contains the public interface classes used by a frontend application. Its purpose is to fully
  abstract the implementation details of the different audio backends.
- `Backend-*` directories implement a single audio backend each, depending on build configuration and availability.

## Using the Audio Backend Library

### Get a list of available backends

While applications can theoretically hard-code the backend names, it is recommended to check available backends using
the static `projectMAudio::Backend::Enumerate()` function. It returns a vector of strings, each identifying an available
audio capture backend that can be instantiated.

