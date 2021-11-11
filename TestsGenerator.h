#ifndef AOIN_TESTSGENERATOR_H
#define AOIN_TESTSGENERATOR_H

#include <fstream>

class TestsGenerator{
public:
    void generate_tests();

private:
    constexpr static auto lower_bound_size = 30u;
    constexpr static auto upper_bound_size = 40u;
    constexpr static auto step = 10u;
    std::fstream file_stream;
};

#endif // AOIN_TESTSGENERATOR_H