//
// Created by kolya on 10/10/2021.
//

#include <boost/range/iterator_range_core.hpp>
#include "DataLoader.h"
#include "boost/filesystem.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

using namespace nlohmann;

DataLoader::DataLoader(const std::string &DataDirectory)
{
    int index = 0;
    for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(DataDirectory), {}))
    {
        if (boost::filesystem::is_regular_file(entry.path()) && boost::filesystem::extension(entry.path()) == ".json")
        {
            std::ifstream ifs(entry.path().string());
            if (ifs.is_open())
            {
                std::string name = entry.path().stem().string();
                json jf = json::parse(ifs);
                m_Data[name] = jf;
                m_Names.push_back(name);
                m_NamesMap[name] = index;
                index++;
            }
            else
            {
                spdlog::get("Core")->warn("File cannot be opened " + entry.path().string());
            }
        }
    }
}

nlohmann::json DataLoader::GetJson(const std::string &name) const
{
    if (m_Data.find(name) != m_Data.end())
    {
        return m_Data.at(name);
    }
    return nullptr;
}

std::vector<std::string>& DataLoader::GetNames()
{
    return m_Names;
}

int DataLoader::GetIndex(const std::string &inName)
{
    if (m_NamesMap.find(inName) != m_NamesMap.end())
    {
        return m_NamesMap[inName];
    }
    return -1;
}
