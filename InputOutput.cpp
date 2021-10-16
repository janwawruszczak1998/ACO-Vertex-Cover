#include "InputOutput.h"

void InputOutput::open_file() {
    file_stream.open(file_name);
    if (!file_stream.good()) throw std::runtime_error("Error opening file " + file_name + '\n');
}

void InputOutput::read_file() {
    if (file_stream.is_open()) {
        file_stream >> v;
        file_stream >> e;
        int i = e, a, b;
        while (i--) {
            file_stream >> a >> b;
            g.emplace_back(a, b);
        }
        file_stream.close();
    }
}

void InputOutput::process_file() {
    try {
        open_file();
        read_file();
    } catch (const std::exception &e) {
        std::cout << e.what();
        std::exit(1);
    }
}

unsigned InputOutput::get_v() {
    return v;
}

unsigned InputOutput::get_e() {
    return e;
}

std::vector<std::pair<unsigned, unsigned >> &InputOutput::get_g() {
    return g;
}