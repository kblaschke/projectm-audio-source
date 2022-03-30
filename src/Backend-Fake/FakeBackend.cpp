#include "FakeBackend.h"

namespace projectMAudio {

FakeBackend::FakeBackend(projectm_handle projectMInstance)
    : Backend(projectMInstance)
{
}

Device::List FakeBackend::AvailableAudioDevices()
{
    return { std::make_shared<Device>("Fake", *this) };
}

std::string FakeBackend::Name() const
{
    return std::string();
}

bool FakeBackend::StartCapture(Device::Ptr captureDevice)
{
    if (!captureDevice->BelongsToBackend(*this))
    {
        return false;
    }

    if (!_thread)
    {
        _thread = std::make_unique<std::thread>(&FakeCaptureThread::GenerateFakeAudio, &_fakeDataGenerator);
    }

    return true;
}

void FakeBackend::StopCapture()
{
    if(_thread)
    {
        _fakeDataGenerator.Stop();
        _thread->join();
        _thread.reset();
    }
}

} // namespace projectM
