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
        m_Graph[index].name = name;
    }
    for (const std::string& name : m_Loader.GetNames())
    {
        int index = m_Loader.GetIndex(name);
        nlohmann::json info_json = m_Loader.GetJson(name);
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
    std::vector<int> indexes(Themes.size());
    int index = 0;
    for (const auto& theme : Themes)
    {
        indexes[index] = m_Loader.GetIndex(theme);
        index++;
    }
    for (auto i : indexes)
    {
        for (auto edge : m_Graph.m_vertices.at(i).m_out_edges)
        {
            if (edge.get_property().m_value > static_cast<float>(difficulty) / 3)
            {
                nlohmann::json js = m_Loader.GetJson(m_Loader.GetName(edge.get_target()));
                if (js["Type"] == "Theme" || js["Type"] == "Article")
                {
                    break;
                }
                return js;
            }
        }
    }

    return nullptr;
}

nlohmann::json DataHandler::RequestArticle(const std::vector<std::string>& Themes, int difficulty)
{
    std::vector<int> indexes(Themes.size());
    int index = 0;
    for (const auto& theme : Themes)
    {
        indexes[index] = m_Loader.GetIndex(theme);
        index++;
    }
    for (auto i : indexes)
    {
        for (auto edge : m_Graph.m_vertices.at(i).m_out_edges)
        {
            if (edge.get_property().m_value > static_cast<float>(difficulty) / 3)
            {
                nlohmann::json js = m_Loader.GetJson(m_Loader.GetName(edge.get_target()));
                if (js["Type"] == "Theme" || js["Type"] == "Task")
                {
                    break;
                }
                return js;
            }
        }
    }

    return nullptr;
}

nlohmann::json DataHandler::RequestLiterature(const std::vector<std::string>& Themes, int difficulty)
{
    return nullptr;
}

std::vector<std::string> DataHandler::GetAllThemes()
{
    std::vector<std::string> themes;
    for (const auto& file : m_Loader.GetNames())
    {
        nlohmann::json json = m_Loader.GetJson(file);
        if (json["Type"] == "Theme")
        {
            themes.push_back(json["Name"]);
        }
    }
    return themes;
}

std::vector<std::string> DataHandler::GetAllTasks()
{
    std::vector<std::string> themes;
    for (const auto& file : m_Loader.GetNames())
    {
        nlohmann::json json = m_Loader.GetJson(file);
        if (json["Type"] == "Task")
        {
            themes.push_back(file);
        }
    }
    return themes;
}
