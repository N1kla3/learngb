//
// Created by kolya on 10/10/2021.
//

#include "DataRequest.h"
#include "DataHandler.h"
#include "spdlog/spdlog.h"

DataRequest::DataRequest(const nlohmann::json& Request, const std::weak_ptr<DataHandler>& Handler)
    : m_Data("{\"None\": \"None\"}")
{
    if (Handler.expired())
    {
        spdlog::get("Core")->error("Handler expired on request");
        return;
    }
    std::string type = Request["Type"];
    if (type == "Task")
    {
        if (Request["Theme"].empty())
        {
            nlohmann::json js(Handler.lock()->GetAllTasks());
            m_Data = js;
        }
        else
        {
            std::vector<std::string> theme_names;
            for (const auto& item : Request["Theme"])
            {
                theme_names.push_back(item.get<std::string>());
            }
            m_Data = Handler.lock()->RequestTask(theme_names, Request["Difficulty"].get<int>());
        }
    }
    else if (type == "Article")
    {
        if (Request["Theme"].empty())
        {
            nlohmann::json js(Handler.lock()->GetAllThemes());
            m_Data = js;
        }
        else
        {
            std::vector<std::string> theme_names;
            for (const auto& item : Request["Theme"])
            {
                theme_names.push_back(item.get<std::string>());
            }
            m_Data = Handler.lock()->RequestArticle(theme_names, Request["Difficulty"].get<int>());
        }
    }
    else
    {
        spdlog::get("Core")->warn("Unsupported request type - " + type);
    }
}

nlohmann::json DataRequest::GetData() const
{
    return m_Data;
}
