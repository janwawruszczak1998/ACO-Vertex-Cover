#include "InputOutput.h"

template <template <typename...> typename Container>
InputOutput<Container>::InputOutput(std::string &&input_file_path_,
                                    std::string &&output_directory_)
    : input_file_path(std::move(input_file_path_)),
      output_dir{output_directory_}, vertices{}, edges{} {
  std::filesystem::create_directory(output_dir);
}

template <template <typename...> typename Container>
void InputOutput<Container>::open_file_to_read() {
  file_stream.open(input_file_path, std::ios::in);
  if (!file_stream.good()) {
    throw std::runtime_error("Error reading from file " +
                             input_file_path.filename().string() + '\n');
  }
}

template <template <typename...> typename Container>
void InputOutput<Container>::read_from_file() {
  if (file_stream.is_open()) {
    file_stream >> vertices;
    file_stream >> edges;
    unsigned i = edges, a{}, b{};
    while (i--) {
      file_stream >> a >> b;
      container.emplace_back(a, b);
    }
    file_stream.close();
  }
}

template <template <typename...> typename Container>
void InputOutput<Container>::process_input_file() {
  try {
    open_file_to_read();
    read_from_file();
  } catch (const std::exception &e) {
    std::cout << e.what();
    std::exit(1);
  }
}

template <template <typename...> typename Container>
unsigned InputOutput<Container>::get_vertices() const {
  return vertices;
}

template <template <typename...> typename Container>
unsigned InputOutput<Container>::get_edges() const {
  return edges;
}

template <template <typename...> typename Container>
const Container<std::pair<unsigned, unsigned>> &
InputOutput<Container>::get_container() const {
  return container;
}

template <template <typename...> typename Container>
void InputOutput<Container>::display_container() const {
  std::cout << "Size of container is: " << container.size()
            << " and stored values are:\n";
  for (const auto &pair : container) {
    std::cout << pair.first << " " << pair.second << std::endl;
  }
}

template <template <typename...> typename Container>
void InputOutput<Container>::open_file_to_write(
    const std::string &context_name) {
  auto filename = input_file_path.filename().string();
  auto dot = filename.find_last_of('.');
  auto name = filename.substr(0, dot);
  auto extension = filename.substr(dot + 1);
  auto output_file_path =
      output_dir.string() + name + "_o_" + context_name + "." + extension;

  file_stream.open(output_file_path, std::ios::out | std::ios::trunc);
  if (!file_stream.good()) {
    throw std::runtime_error("Error writing to file " + output_file_path +
                             '\n');
  }
}

template <template <typename...> typename Container>
void InputOutput<Container>::write_time_to_file(double time) {
  if (file_stream.good()) {
    file_stream << time << '\n';
  }
}

template <template <typename...> typename Container>
void InputOutput<Container>::write_container_to_file(
    const std::vector<unsigned> &v) {
  if (file_stream.good()) {
    for (auto &i : v) {
      file_stream << i << " ";
    }
    file_stream << '\n';
  }
}

template <template <typename...> typename Container>
void InputOutput<Container>::process_output_file(
    const std::string &context_name, const std::vector<unsigned> &solution,
    double time) {
  try {
    open_file_to_write(context_name);
    write_container_to_file(solution);
    write_time_to_file(time);
    file_stream.close();
  } catch (const std::exception &e) {
    std::cout << e.what();
  }
}