//
// Created by kolya on 10/10/2021.
//

#pragma once

#include "nlohmann/json.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "DataLoader.h"

class DataHandler
{
public:
    typedef boost::property<boost::edge_weight_t, int> EdgeProperty;
    typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty , EdgeProperty> Graph;
    typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;

    DataHandler();

    nlohmann::json RequestTask(const std::string& Theme);

    nlohmann::json RequestArticle(const std::string& Theme);

    nlohmann::json RequestLiterature(const std::string& Theme);

private:
    Graph m_Graph;

    DataLoader m_Loader;
};


