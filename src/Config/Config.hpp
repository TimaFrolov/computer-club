#pragma once

#include "Time.hpp"
#include <cstdint>

namespace ComputerClub {

/// Configuration of computer club
struct Config {
  std::uint64_t tablesAmount; ///< Amount of tables in the club
  Time openingTime;           ///< Time when the club opens
  Time closingTime;           ///< Time when the club closes, should be greater than opening time
  std::uint64_t costPerHour;  ///< Cost per hour of using the table
};

} // namespace ComputerClub
