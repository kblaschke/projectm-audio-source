#pragma once

#include "projectMAudioSource/Backend.h"

namespace projectMAudio {

class PulseAudioBackend : public Backend
{
public:
    explicit PulseAudioBackend(projectm_handle projectMInstance);

    Device::List AvailableAudioDevices() override;

    std::string Name() const override;

    bool StartCapture(Device::Ptr captureDevice) override;

    void StopCapture() override;
};

} // namespace projectM