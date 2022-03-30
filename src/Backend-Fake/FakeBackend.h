#pragma once

#include "FakeAudioGenerator.h"

#include "projectMAudioSource/Backend.h"

#include <thread>

namespace projectMAudio {

class FakeBackend : public Backend
{
public:
    explicit FakeBackend(projectm_handle projectMInstance);

    ~FakeBackend() override;

    Device::List AvailableAudioDevices() override;

    std::string Name() const override;

    bool StartCapture(Device::Ptr captureDevice) override;

    void StopCapture() override;

private:
    /**
     * @brief Non-virtual StopCapture method which can also be safely called from the destructor.
     */
    void PrivateStopCapture();

    std::unique_ptr<std::thread> _thread;

    FakeAudioGenerator _fakeDataGenerator{ _projectMInstance };
};

} // namespace projectM