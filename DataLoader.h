//
// Created by kolya on 10/10/2021.
//

#pragma once

#include "nlohmann/json.hpp"
#include <map>

class DataLoader
{
public:
    explicit DataLoader(const std::string& DataDirectory);

    [[nodiscard]] nlohmann::json GetJson(const std::string& name) const;

    std::vector<std::string>& GetNames();

    int GetIndex(const std::string& inName);

private:
    std::vector<std::string> m_Names;
    std::map<std::string, int> m_NamesMap;
    std::map<std::string, nlohmann::json> m_Data;
};


