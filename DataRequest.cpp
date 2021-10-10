//
// Created by kolya on 10/10/2021.
//

#include "DataRequest.h"

DataRequest::DataRequest(const nlohmann::json &Task)
{

}

nlohmann::json DataRequest::GetData() const
{
    return m_Data;
}
