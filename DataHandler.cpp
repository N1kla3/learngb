//
// Created by kolya on 10/10/2021.
//

#include "DataHandler.h"

DataHandler::DataHandler()
    : m_Graph(),
      m_Loader("../Data/")
{
    for (const std::string& name : m_Loader.GetNames())
    {
         nlohmann::json info_json = m_Loader.GetJson(name);
         auto theme = info_json["Theme"];
         if (theme.is_array())
         {
             for (auto item : theme)
             {
                 boost::add_edge(1, 1, m_Graph);
             }
         }
    }
}

nlohmann::json DataHandler::RequestTask(const std::string &Theme)
{
    return nullptr;
}

nlohmann::json DataHandler::RequestArticle(const std::string &Theme)
{
    return nullptr;
}

nlohmann::json DataHandler::RequestLiterature(const std::string &Theme)
{
    return nullptr;
}
