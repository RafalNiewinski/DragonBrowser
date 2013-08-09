#include "cloudmanager.h"

CloudManager::CloudManager()
{
    state = NONE;
}

CloudManager::CloudState CloudManager::getCloudState()
{
    return state;
}
