#include "projectMAudioSource/Backend.h"

#include "BackendList_Generated.h"

#include <algorithm>

namespace projectMAudio {

Backend::Backend(projectm_handle projectMInstance)
    : _projectMInstance(projectMInstance)
{
}

Backend::List Backend::Enumerate(bool includeFakeBackend/* = false */)
{
    Backend::List backendList(s_backendNames.begin(), s_backendNames.end());

    if(!includeFakeBackend)
    {
        std::remove_if(backendList.begin(),
                       backendList.end(),
                       [](const std::string& name) { return name == "Fake"; });
    }

    return backendList;
}

Backend::Ptr Backend::Create(const std::string& backendName, projectm_handle projectMInstance)
{
    return s_BackendFactory(backendName, projectMInstance);
}

} // namespace projectMAudio
