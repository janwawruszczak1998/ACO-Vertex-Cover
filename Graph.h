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
        explicit Graph(InputOutput<Container>&& io) {
            auto size_of_container = io.get_vertices();
            graph_representation.reserve(size_of_container);
            pheromones.resize(size_of_container, T{1.0/size_of_container});
            while(size_of_container-- > 0){
                add_vertex();
            }
            for(auto& neighbours : graph_representation){
                neighbours.resize(order_, std::make_pair(false, T{0.0}));
            }
            for(const auto& pair : io.get_container()){
                add_edge(pair.first, pair.second);
            }
        }
        Graph(Graph const&) = default;
        Graph(Graph&&) = delete;

        void add_vertex();

        void add_edge(unsigned, unsigned);

        void display_graph() const;

        auto get_order() const;

        auto get_size() const;

        auto& get_graph() {
            return graph_representation;
        }

        auto& get_pheromones(){
            return pheromones;
        }

    private:
        unsigned order_{0};
        unsigned size_{0};

        Container<Container<std::pair<bool, T>>> graph_representation;
        Container<T> pheromones;
    };


    template<typename T, template<typename, typename> class Container>
    auto Graph<T, Container>::get_order() const {
        return order_;
    }
    template<typename T, template<typename, typename> class Container>
    auto Graph<T, Container>::get_size() const {
        return size_;
    }

    template<typename T, template<typename, typename> class Container>
    void Graph<T, Container>::add_edge(unsigned int first, unsigned int second) {
        size_++;
        graph_representation[first][second] = std::make_pair(true, T{1.0});
        graph_representation[second][first] = std::make_pair(true, T{1.0});
    }

    template<typename T, template<typename, typename> class Container>
    void Graph<T, Container>::add_vertex() {
        order_++;
        graph_representation.push_back(Container<std::pair<bool, T>, std::allocator < T >>{});
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
}

#endif //AOIN_GRAPH_H