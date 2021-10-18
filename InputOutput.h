#ifndef AOIN_INPUTOUTPUT_H
#define AOIN_INPUTOUTPUT_H

#include <fstream>
#include <iostream>
#include <vector>

template<template <typename...> typename Container>
class InputOutput {

public:
    InputOutput(const std::string& file_name) : file_name(file_name) {}

    void process_file();

    void display_container() const;

    const unsigned get_vertices() const;

    const unsigned get_edges() const ;

    const Container<std::pair<unsigned, unsigned>> &get_container() const;

private:
    std::ifstream file_stream;
    const std::string file_name;
    unsigned vertices, edges;
    Container<std::pair<unsigned, unsigned>> container;

    void open_file();

    void read_file();


};

#endif //AOIN_INPUTOUTPUT_H