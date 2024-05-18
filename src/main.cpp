#include "Simulator.hpp"
#include <fstream>
#include <iostream>

auto main(int argc, char *argv[]) -> int {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Failed to open file " << argv[1] << std::endl;
    return 1;
  }

  return ComputerClub::Simulator::simulate(input, std::cout, std::cerr) ? 0 : 1;
}
