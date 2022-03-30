#include "FakeBackend.h"

namespace projectMAudio {

FakeBackend::FakeBackend(projectm_handle projectMInstance)
    : Backend(projectMInstance)
{
}

FakeBackend::~FakeBackend()
{
    PrivateStopCapture();
}

Device::List FakeBackend::AvailableAudioDevices()
{
    return {
        std::make_shared<Device>("Random", *this),
        std::make_shared<Device>("Beat", *this)
    };
}

std::string FakeBackend::Name() const
{
    return "Fake";
}

bool FakeBackend::StartCapture(Device::Ptr captureDevice)
{
    if (!captureDevice->BelongsToBackend(*this))
    {
        return false;
    }

    if (!_thread)
    {
        if (captureDevice->Name() == "Random")
        {
            _thread = std::make_unique<std::thread>(&FakeAudioGenerator::GenerateRandomNoise, &_fakeDataGenerator);
        }
        else if (captureDevice->Name() == "Beat")
        {
            _thread = std::make_unique<std::thread>(&FakeAudioGenerator::GenerateBeat, &_fakeDataGenerator);
        }
        else
        {
            return false;
        }
    }

    return true;
}

void FakeBackend::StopCapture()
{
    PrivateStopCapture();
}

void FakeBackend::PrivateStopCapture()
{
    if (_thread)
    {
        _fakeDataGenerator.Stop();
        _thread->join();
        _thread.reset();
    }
}


} // namespace projectM
