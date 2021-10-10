//
// Created by kolya on 10/10/2021.
//

#pragma once

#include "nlohmann/json.hpp"

class DataRequest
{
public:
    explicit DataRequest(const nlohmann::json& Task);

    [[nodiscard]] nlohmann::json GetData() const;
private:
    nlohmann::json m_Data;
};


