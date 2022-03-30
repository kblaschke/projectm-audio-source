# projectM Audio Backend Library

This library contains shared code for use with standalone projectM applications to enumerate and use different
platform-specific audio backends with a single interface.

## Supported backends

The library currently supports the following backends:

- SDL2: Windows, macOS, Linux, *BSD, Android, iOS
- PulseAudio: Windows, Linux, *BSD
- JACK: Windows, macOS, Linux, *BSD
- WASAPI: Windows

There is also a Fake backend available on all platforms which generates random noise and can be used to make the
visualisation more appealing if no audio sources are available.

## Directory structure

The library is split into subdirectories:

- `projectMAudioSource` contains the public interface classes used by a frontend application. Its purpose is to fully
  abstract the implementation details of the different audio backends.
- `Backend-*` directories implement a single audio backend each, depending on build configuration and availability.

## Using the Audio Backend Library

### Get a list of available backends

While applications can theoretically hard-code the backend names, it is recommended to check available backends using
the static `projectMAudio::Backend::Enumerate()` function. It returns a vector of strings, each identifying an available
audio capture backend that can be instantiated.

### Create an audio backend

Use the `projectMAudio::Backend::Create()` factory function to create a new instance of a backend. If the provided
backend name is not supported, the function will return a NULL pointer.

### Get a list of audio devices

To get a list of available audio capture devices for a backend, first create an instance of it. Then call
the `AvailableAudioDevices()` function to get a list of possible audio sources:

```C++
auto backend = projectMAudio::Backend::Create("SDL2");
if (backend)
{
    auto availableDevices = backend->AvailableAudioDevices();
    std::cout << "Devices for backend SDL2:" << std::endl;
    for (const auto& device : availableDevices)
    {
        std::cout << " - " << device->Name() << std::endl;
    }
}
```

### Capture from a device

After enumerating the available devices, the application can select a device from the list

## Known issues

This is a list of known issues that either can't be solved due to a bug in the backend or a missing feature in the
library:

- There is currently no way of getting feedback from a backend if the current audio device fails, for example if the
  input device is unplugged or the backend's audio server has been shut down.
- The SDL backend is missing PulseAudio monitor device support and can only use specific capture devices like
  microphones or line-in jacks. A fix will probably make it into SDL 2.0.16, but earlier versions are broken.
