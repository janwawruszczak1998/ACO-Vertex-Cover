#include "InputOutput.h"

template<template <typename...> typename Container>
InputOutput<Container>::InputOutput(std::string&& name) : file_name(std::move(name))
{

};

template<template <typename...> typename Container>
void InputOutput<Container>::open_file() {
    file_stream.open(file_name);
    if (!file_stream.good()) throw std::runtime_error("Error opening file " + file_name + '\n');
}

template<template <typename...> typename Container>
void InputOutput<Container>::read_file() {
    if (file_stream.is_open()) {
        file_stream >> vertices;
        file_stream >> edges;
        unsigned i = edges, a, b;
        while (i--) {
            file_stream >> a >> b;
            container.emplace_back(a, b);
        }
        file_stream.close();
    }
}

template<template <typename...> typename Container>
void InputOutput<Container>::process_file() {
    try {
        open_file();
        read_file();
    } catch (const std::exception &e) {
        std::cout << e.what();
        std::exit(1);
    }
}


template<template <typename...> typename Container>
unsigned InputOutput<Container>::get_vertices() const {
    return vertices;
}

template<template <typename...> typename Container>
unsigned InputOutput<Container>::get_edges() const {
    return edges;
}

template<template <typename...> typename Container>
const Container<std::pair<unsigned, unsigned >> &InputOutput<Container>::get_container() const {
    return container;
}

template<template <typename...> typename Container>
void InputOutput<Container>::display_container() const {
    std::cout << "Size of container is: " << container.size() << " and stored values are:\n";
    for(const auto& pair : container){
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}