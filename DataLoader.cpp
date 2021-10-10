//
// Created by kolya on 10/10/2021.
//

#include "DataLoader.h"

DataLoader::DataLoader(const std::string &DataDirectory)
{

}

nlohmann::json DataLoader::GetJson(const std::string &name) const
{
    return nullptr;
}

std::vector<std::string>& DataLoader::GetNames()
{
    return m_Names;
}
