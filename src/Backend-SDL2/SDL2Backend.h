#pragma once

#include "projectMAudioSource/Backend.h"

namespace projectMAudio {

/*!
 * \brief SDL2 audio source
 */
class SDL2Backend : public Backend
{
public:
    explicit SDL2Backend(projectm_handle projectMInstance);

    Device::List AvailableAudioDevices() override;

    std::string Name() const override;

    bool StartCapture(Device::Ptr captureDevice) override;

    void StopCapture() override;
};

} // namespace projectMAudio
