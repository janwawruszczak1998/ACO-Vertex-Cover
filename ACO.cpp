#include "ACO.h"
#include "Randoms.h"


ACO::ACO(tsp::Graph<double, std::vector>& graph_) : Algorithm(graph_){
    std::cout << "New ACO constructed" << std::endl;
}

ACO::~ACO() {
    for(auto& edges : graph.get_graph()){
        for(auto& edge: edges){
            if(edge.first){
                edge.second = 1.0;
            }
            else{
                edge.second = 0.0;
            }
        }
    }
    std::cout << "Best of ACO:\n";
    for(const auto vertex : solution){
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    std::cout << "ACO deconstructed" << std::endl;
}

void ACO::calculate_solution() {
    const auto iterations = 100;
    std::vector<unsigned> best_solution;
    const unsigned ants_abundance = graph.get_order();
    std::vector<std::vector<unsigned>> solutions(ants_abundance);




    for(auto iter = 0u; iter < iterations; ++iter){

        for(auto& edges : graph.get_graph()){
            for(auto& edge: edges){
                if(edge.first){
                    edge.second = 1.0;
                }
                else{
                    edge.second = 0.0;
                }
            }
        }

        for (auto& solution : solutions) {
            solution.clear();
        }
        for (auto ant_n = 0u; ant_n < ants_abundance; ++ant_n) {
            Ant ant(*this, ant_n, graph.get_order());
            solutions[ant_n] = ant.make_route();
            if(solutions[ant_n].size() < solution.size()){
                solution = solutions[ant_n];
            }
        }
        for(auto& solution : solutions){
            if(!check_if_vertex_cover(solution)){
                solution.clear();
            }
        }
        update_pheromones(solutions);
    }

}

ACO::Ant::Ant(ACO& aco_, unsigned number_, unsigned order_of_graph)
: aco(aco_),
number(number_),
vertex_tabu(order_of_graph, false)
{
    //std::cout << "Ant " << number << " constructed" << std::endl;
}

ACO::Ant::~Ant() {
    vertex_tabu.clear();
    //std::cout << "Ant " << number << " deconstructed" << std::endl;
}

std::vector<unsigned> ACO::Ant::make_route() {
    std::vector<double> probabilites;

    route.reserve(aco.graph.get_order());
    route.push_back(get_number());
    vertex_tabu[get_number()] = true;

    for(auto i = 0u; i < aco.graph.get_order() - 1; ++i){
        unsigned city_i = route[i];  //miasto i-te
        probabilites.clear();
        probabilites.resize(aco.graph.get_order(), 0.0);
        //wylicz prawdopodobienswo przejscia do miasta j-tego
        for (unsigned city_j = 0; city_j < aco.graph.get_order(); ++city_j) {
            if (city_i == city_j){
                continue;  //polaczenie ze samym soba
            }
            if (!vertex_tabu[city_j]) {   //jesli miasto jeszcze nie odwiedzone
                probabilites[city_j] = Phi(city_i, city_j);
            }
        }

        route.push_back(get_next_city(probabilites));
        vertex_tabu[route[i+1]] = true;
        if(aco.check_if_vertex_cover(route)){
            break;
        }
    }

    return route;
}


unsigned ACO::Ant::get_next_city(const std::vector<double> &probabilites) {

    auto vertex = 0u;
    auto xi = aco.randoms.uniform(), sum = probabilites[vertex];
    while (sum < xi) {
        ++vertex;
        sum += probabilites[vertex];
    }

    return vertex;
}

unsigned ACO::Ant::get_number() const {
    return number;
}

double ACO::Ant::Phi(unsigned city_i, unsigned city_j) {
    constexpr auto alpha = 1.1, beta = 4.5;

    auto tau_ij = std::pow(aco.graph.get_pheromones()[city_j], alpha);
    auto eta_ij = std::pow(aco.graph.get_graph()[city_i][city_j].second, beta);
    auto sum = 0.0;

    for(auto other_city = 0u; other_city < aco.graph.get_order(); ++other_city){
        if(city_i == other_city){
            continue;
        }
        if(!vertex_tabu[other_city]){
            auto eta = std::pow(aco.graph.get_pheromones()[other_city], alpha);
            auto tau = std::pow(aco.graph.get_graph()[city_i][other_city].second, beta);
            sum += eta * tau;
        }
    }

    return (eta_ij * tau_ij) / sum;
}

void ACO::update_pheromones(const std::vector<std::vector<unsigned>>& solutions) {
    const auto q = static_cast<double>(graph.get_order());//parametr feromonowy - reguluje ile jest kladzione feromonu
    constexpr double ro = 0.01; //ro - parametr aktualizowanego feromonu < 1
    for(const auto& solution : solutions){
        const auto solution_value = get_solution_value(solution);
        for(auto& pheromone : graph.get_pheromones()){
            pheromone = (1.0 - ro) * pheromone + q / (solution_value);
        }
    }
}
