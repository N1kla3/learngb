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
    for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(DataDirectory), {}))
    {
        if (boost::filesystem::is_regular_file(entry.path()) && boost::filesystem::extension(entry.path()) == ".json")
        {
            std::ifstream ifs(entry.path().string());
            if (ifs.is_open())
            {
                json jf = json::parse(ifs);
                m_Data[jf["Name"]] = jf;
                m_Names.push_back(jf["Name"]);
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
}

std::vector<std::string>& DataLoader::GetNames()
{
    return m_Names;
}
