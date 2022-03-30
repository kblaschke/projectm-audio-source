#pragma once

#include "SDL2Capture.h"

#include "projectMAudioSource/Backend.h"

namespace projectMAudio {

class SDL2Capture;

/**
 * @brief SDL2 audio capturing backend.
 *
 * Uses SDL2 audio functions to capture audio data from any SDL-supported API.
 *
 * Some driver-specific functionality, e.g. the input file of the "disk" driver, can be configured using
 * SDL environment variables. Please refer to the SDL source and documentation for further details.
 *
 */
class SDL2Backend : public Backend
{
public:
    /**
     * @brief Constructor. Creates the SDL2 backend.
     * @param projectMInstance The projectM instance that will receive audio data from this backend.
     */
    explicit SDL2Backend(projectm_handle projectMInstance);

    Device::List AvailableAudioDevices() override;

    std::string Name() const override;

    bool StartCapture(Device::Ptr captureDevice) override;

    void StopCapture() override;

private:
    std::unique_ptr<SDL2Capture> _capture; //!< The SDL capture class that owns the audio device.

};

} // namespace projectMAudio
