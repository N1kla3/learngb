//
// Created by kolya on 10/10/2021.
//

#pragma once

#include "nlohmann/json.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "DataLoader.h"

struct VertexData
{
    std::string name;
};

class DataHandler
{
public:
    typedef boost::property<boost::edge_weight_t, float> EdgeProperty;
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexData, EdgeProperty> Graph;
    typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;

    DataHandler();

    nlohmann::json RequestTask(const std::vector<std::string>& Themes, int difficulty);

    nlohmann::json RequestArticle(const std::vector<std::string>& Themes, int difficulty);

    nlohmann::json RequestLiterature(const std::vector<std::string>& Themes, int difficulty);

    std::vector<std::string> GetAllThemes();

    std::vector<std::string> GetAllTasks();

private:
    Graph m_Graph;

    DataLoader m_Loader;
};


//TODO: handle client request
//TODO: Read DB
//TODO: create graph