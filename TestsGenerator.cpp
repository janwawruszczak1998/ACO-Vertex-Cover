#include "TestsGenerator.h"
#include <string_view>
#include <filesystem>
#include <unordered_set>
#include "Randoms.h"


void TestsGenerator::generate_tests() {
    const std::string dense_graph = "dense_graph_";
    const std::string sparse_graph = "sparse_graph_";
    const std::string extension = ".txt";

    const std::filesystem::path path{ "./input/" };
    re::Randoms random_engine;

    struct pair_hash {
        inline std::size_t operator()(const std::pair<int,int> & v) const {
            return v.first*31+v.second;
        }
    };

    for(auto lower_bound = lower_bound_size; lower_bound <= upper_bound_size; lower_bound += step){
        std::cout << "Creating files with " << lower_bound << " verticles\n";

        const std::string file_name_sparse{sparse_graph + std::to_string(lower_bound) + extension};
        std::random_device rd;
        std::mt19937 g(rd());
        file_stream.open(path.string() + file_name_sparse, std::ios::out | std::ios::trunc);
        if (file_stream.good()) {
            file_stream << lower_bound << " " << 5 * lower_bound << "\n";

            std::vector<unsigned> spanning_path(lower_bound);
            for(auto vertex = 0u; vertex < lower_bound; ++vertex){
                spanning_path[vertex] = vertex;
            }
            std::shuffle(spanning_path.begin(), spanning_path.end(), g);
            for(auto vertex = 0u; vertex < lower_bound - 1; ++vertex){
                file_stream << spanning_path[vertex] << " " << spanning_path[vertex + 1] << "\n";
            }

            std::unordered_set<std::pair<unsigned,unsigned>, pair_hash> edges;
            for (auto edge = 0u; edge < 4 * lower_bound + 1; ++edge) {
                unsigned edge_end, edge_start = random_engine.random_in_range(0u, lower_bound - 1);
                do{
                    edge_end = random_engine.random_in_range(0u, lower_bound - 1);
                } while (edge_start == edge_end);
                if(edge_start > edge_end){
                    std::swap(edge_start, edge_end);
                }

                if(edges.find(std::make_pair(edge_start, edge_end)) == std::end(edges)){
                    edges.insert(std::make_pair(edge_start, edge_end));
                    file_stream << edge_start << " " << edge_end << "\n";
                }
                else{
                    edge--;
                }


            }
            file_stream << '\n';

        }
        file_stream.close();


        const std::string file_name_dense{dense_graph + std::to_string(lower_bound) + extension};
        file_stream.open(path.string() + file_name_dense, std::ios::out | std::ios::trunc);
        if (file_stream.good()) {
            file_stream << lower_bound << " " << lower_bound * lower_bound / 10 << "\n";

            std::vector<unsigned> spanning_path(lower_bound);
            for(auto vertex = 0u; vertex < lower_bound; ++vertex){
                spanning_path[vertex] = vertex;
            }
            std::shuffle(spanning_path.begin(), spanning_path.end(), g);
            for(auto vertex = 0u; vertex < lower_bound - 1; ++vertex){
                file_stream << spanning_path[vertex] << " " << spanning_path[vertex + 1] << "\n";
            }



            std::unordered_set<std::pair<unsigned,unsigned>, pair_hash> edges;
            for (auto edge = 0u; edge < lower_bound * lower_bound / 10 - lower_bound + 1; ++edge) {
                unsigned edge_end, edge_start = random_engine.random_in_range(0u, lower_bound - 1);
                do{
                    edge_end = random_engine.random_in_range(0u, lower_bound - 1);
                } while (edge_start == edge_end);
                if(edge_start > edge_end){
                    std::swap(edge_start, edge_end);
                }

                if(edges.find(std::make_pair(edge_start, edge_end)) == std::end(edges)){
                    edges.insert(std::make_pair(edge_start, edge_end));
                    file_stream << edge_start << " " << edge_end << "\n";
                }
                else{
                    edge--;
                }


            }
            file_stream << '\n';

        }
        file_stream.close();
    }
}
