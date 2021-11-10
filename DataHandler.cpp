//
// Created by kolya on 10/10/2021.
//

#include "DataHandler.h"

DataHandler::DataHandler()
    : m_Graph(),
      m_Loader("../Data/")
{
    m_Graph = Graph(m_Loader.GetNames().size());
    for (const std::string& name : m_Loader.GetNames())
    {
        int index = m_Loader.GetIndex(name);
        nlohmann::json info_json = m_Loader.GetJson(name);
        m_Graph[index].name = name;
        auto theme = info_json["Theme"];
        if (theme.is_array())
        {
            for (auto item : theme)
            {
                int second_index = m_Loader.GetIndex(item["Name"].get<std::string>());
                if (second_index >= 0)
                {
                    boost::add_edge(index, second_index, {item["Weight"].get<float>() },m_Graph);
                }
            }
        }
    }
}

nlohmann::json DataHandler::RequestTask(const std::vector<std::string>& Themes, int difficulty)
{
    // TODO graph thing..
    return m_Loader.GetJson("");
}

nlohmann::json DataHandler::RequestArticle(const std::vector<std::string>& Theme, int difficulty)
{
    // TODO graph thing..
    return m_Loader.GetJson("");
}

nlohmann::json DataHandler::RequestLiterature(const std::vector<std::string>& Theme, int difficulty)
{
    // TODO graph thing..
    return m_Loader.GetJson("");
}
