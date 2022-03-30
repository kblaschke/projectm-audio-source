#include "SDL2AudioDevice.h"

#include <SDL2/SDL_audio.h>

namespace projectMAudio {

SDL2AudioDevice::SDL2AudioDevice(const Backend& backend, SDL_AudioSpec& deviceSpecs, std::string driverName,
                                 std::string deviceName)
    : Device(driverName + " - " + deviceName, backend)
    , _audioDriverName(std::move(driverName))
    , _audioDeviceName(std::move(deviceName))
{
    _sampleFrequency = deviceSpecs.freq;
    _channels = deviceSpecs.channels;

    switch (deviceSpecs.format)
    {
        case AUDIO_F32:
            _sampleFormat = SampleFormat::Float32;
            break;

        case AUDIO_S16:
            _sampleFormat = SampleFormat::Int16;
            break;

        case AUDIO_U8:
            _sampleFormat = SampleFormat::UInt8;
            break;

        default:
            // Any other format is currently unsupported by projectM's PCM ingest.
            _sampleFormat = SampleFormat::Unknown;
    }
}

std::string SDL2AudioDevice::AudioDriverName() const
{
    return _audioDriverName;
}

std::string SDL2AudioDevice::AudioDeviceName() const
{
    return _audioDeviceName;
}

} // namespace projectMAudio
