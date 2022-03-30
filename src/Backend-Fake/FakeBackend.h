#pragma once

#include "FakeCaptureThread.h"

#include "projectMAudioSource/Backend.h"

#include <thread>

namespace projectMAudio {

class FakeBackend : public Backend
{
public:
    explicit FakeBackend(projectm_handle projectMInstance);

    Device::List AvailableAudioDevices() override;

    std::string Name() const override;

    bool StartCapture(Device::Ptr captureDevice) override;

    void StopCapture() override;

protected:
    std::unique_ptr<std::thread> _thread;

    FakeCaptureThread _fakeDataGenerator{ _projectMInstance };
};

} // namespace projectM