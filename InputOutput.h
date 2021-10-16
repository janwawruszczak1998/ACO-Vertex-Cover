#ifndef AOIN_INPUTOUTPUT_H
#define AOIN_INPUTOUTPUT_H

#include <fstream>
#include <iostream>
#include <vector>

class InputOutput {

public:
    InputOutput(const std::string &file_name) : file_name(file_name) {}

    void process_file();

    const unsigned get_v() const;

    const unsigned get_e() const ;

    const std::vector<std::pair<unsigned, unsigned>> &get_g() const;

private:
    std::ifstream file_stream;
    const std::string file_name;
    unsigned v, e;
    std::vector<std::pair<unsigned, unsigned>> g;

    void open_file();

    void read_file();


};

#endif //AOIN_INPUTOUTPUT_H