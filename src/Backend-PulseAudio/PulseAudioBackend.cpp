#include "PulseAudioBackend.h"

namespace projectMAudio {

PulseAudioBackend::PulseAudioBackend(projectm_handle projectMInstance)
    : Backend(projectMInstance)
{
}

Device::List PulseAudioBackend::AvailableAudioDevices()
{
    return projectMAudio::Device::List();
}

std::string PulseAudioBackend::Name() const
{
    return std::string();
}

bool PulseAudioBackend::StartCapture(Device::Ptr captureDevice)
{
    return false;
}

void PulseAudioBackend::StopCapture()
{

}


} // namespace projectM
