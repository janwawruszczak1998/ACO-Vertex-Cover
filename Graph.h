#ifndef AOIN_GRAPH_H
#define AOIN_GRAPH_H

#include <iostream>
#include <algorithm>
#include <cmath>

#include "InputOutput.cpp"

namespace tsp {

    template<typename T, template<typename, typename = std::allocator <T>> class Container>
    class Graph {
    public:
        Graph() = default;
        Graph(InputOutput<Container>&& io) {
            auto size_of_container = io.get_container().size();
            while(size_of_container-- > 0){
                add_vertex();
            }
            for(const auto& pair : io.get_container()){
                add_edge(pair.first, pair.second);
            }
        }
        Graph(Graph const&) = default;
        Graph(Graph&&) = delete;

        void add_vertex();

        void add_edge(unsigned, unsigned);

        void remove_vertex(unsigned);

        void display_graph() const;

        auto get_order() const;

    private:
        unsigned order_{0};

        // in graph_representation[a][b] we store pair of adj. vertex with vertex no. 'a', and pheromones on edge
        Container<Container<std::pair<unsigned, T>>>
                graph_representation;
    };


    template<typename T, template<typename, typename> class Container>
    auto Graph<T, Container>::get_order() const {
        return order_;
    }

    template<typename T, template<typename, typename> class Container>
    void Graph<T, Container>::add_edge(unsigned int first, unsigned int second) {
        graph_representation[first].push_back(std::make_pair(second, 0.0));
        graph_representation[second].push_back(std::make_pair(first, 0.0));
    }

    template<typename T, template<typename, typename> class Container>
    void Graph<T, Container>::add_vertex() {
        order_++;
        graph_representation.push_back(Container<std::pair<unsigned, T>, std::allocator < T >>{});
    }

    template<typename T, template<typename, typename> class Container>
    void Graph<T, Container>::display_graph() const {
        std::cout << "============= Graph =============" << std::endl;
        auto vertex_id = 0u;
        for(auto const& adj_list : graph_representation){
            std::cout << vertex_id << ": ";
            for(auto const& adj_vertex : adj_list){
                std::cout << "(" << adj_vertex.first << ", " << adj_vertex.second << ") ";
            }
            std::cout << std::endl;
            vertex_id++;
        }
    }

    template<typename T, template<typename, typename> class Container>
    void Graph<T, Container>::remove_vertex(const unsigned index) {
        if (index < 0 || index >= order_) return;

        if (--order_ == 0) {
            graph_representation.clear();
        } else {
            graph_representation.erase(
                    std::find_if(graph_representation.begin(), graph_representation.end(), [&index](auto &distances) {
                        return std::any_of(distances.begin(), distances.end(), [&index](auto &vertex) {
                            return vertex.first == index && static_cast<unsigned>(vertex.second) == 0;
                        });
                    }));
        }


        for (auto &distances : graph_representation) {
            for (auto iterator = distances.begin(); iterator != distances.end();) {
                if (iterator->first == index) {
                    iterator = distances.erase(iterator);
                } else {
                    if (iterator->first > index) {
                        --iterator->first;
                    }
                    ++iterator;
                }
            }
        }

    }
}

#endif //AOIN_GRAPH_H