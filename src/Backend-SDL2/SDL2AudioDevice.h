#pragma once

#include "projectMAudioSource/Device.h"

struct SDL_AudioSpec;

namespace projectMAudio {

/**
 * @brief SDL2-specific audio device class.
 *
 * Holds some additional information about SDL2 audio devices so the backend can re-map the device when
 * starting to capture. Audio device indices may change (if devices are (un)plugged), so we store the
 * name to match it later.
 */
class SDL2AudioDevice : public Device
{
public:
    /**
     * @brief Constructor. Initializes the device and sets some SDL-specific members.
     * @param name The SDL2 driver and device name combined.
     * @param backend The backend that created this device.
     * @param deviceSpecs The SDL2 device specs as returned by SDL_OpenAudioDevice().
     * @param driverName The name of the SDL2 audio driver that own this device.
     * @param deviceName The name of this SDL2 audio device.
     */
    explicit SDL2AudioDevice(const Backend& backend, SDL_AudioSpec& deviceSpecs,
                             std::string driverName, std::string deviceName);

    /**
     * @brief Returns the audio driver name this device belongs to.
     * @return The audio driver name this device belongs to.
     */
    std::string AudioDriverName() const;

    /**
     * @brief Returns the SDL2 audio device name.
     * @return The SDL2 audio device name.
     */
    std::string AudioDeviceName() const;

private:
    std::string _audioDriverName; //!< The SDL2 audio driver name as accepted by SDL_AudioInit()
    std::string _audioDeviceName; //!< The SDL2 driver-specific audio device name as accepted by SDL_OpenAudioDevice().
};

} // namespace projectMAudio
