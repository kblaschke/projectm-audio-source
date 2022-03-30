#include "SDL2Backend.h"

namespace projectMAudio {

SDL2Backend::SDL2Backend(projectm_handle projectMInstance)
    : Backend(projectMInstance)
{
}

Device::List SDL2Backend::AvailableAudioDevices()
{
    return projectMAudio::Device::List();
}

std::string SDL2Backend::Name() const
{
    return std::string();
}

bool SDL2Backend::StartCapture(Device::Ptr captureDevice)
{
    return false;
}

void SDL2Backend::StopCapture()
{

}

} // namespace projectM
