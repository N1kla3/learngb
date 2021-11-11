//
// Created by kolya on 10/10/2021.
//

#pragma once

#include "nlohmann/json.hpp"

class DataHandler;

class DataRequest
{
public:
    explicit DataRequest(const nlohmann::json& Request, const std::weak_ptr<DataHandler>& Handler);

    [[nodiscard]] nlohmann::json GetData() const;
private:
    nlohmann::json m_Data;
};


