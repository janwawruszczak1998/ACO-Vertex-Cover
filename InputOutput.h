#ifndef AOIN_INPUTOUTPUT_H
#define AOIN_INPUTOUTPUT_H

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

template <template <typename...> typename Container> class InputOutput {

public:
  explicit InputOutput(std::string &&, std::string &&);

  void process_input_file();

  void process_output_file(const std::string &, const std::vector<unsigned> &,
                           double);

  void display_container() const;

  unsigned get_vertices() const;

  unsigned get_edges() const;

  const Container<std::pair<unsigned, unsigned>> &get_container() const;

private:
  std::fstream file_stream;
  const std::filesystem::path input_file_path;
  const std::filesystem::path output_dir;
  unsigned vertices, edges;
  Container<std::pair<unsigned, unsigned>> container;

  void open_file_to_read();

  void open_file_to_write(const std::string &);

  void read_from_file();

  void write_container_to_file(const std::vector<unsigned> &);

  void write_time_to_file(double);
};

#endif // AOIN_INPUTOUTPUT_H