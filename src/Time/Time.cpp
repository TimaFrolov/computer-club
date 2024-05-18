#include "Time.hpp"
#include <iomanip>

namespace ComputerClub {
std::ostream &operator<<(std::ostream &stream, const Time &time) {
  return stream << std::setw(2) << std::setfill('0') << int(time.hour) << ':' << std::setw(2)
                << std::setfill('0') << int(time.minute);
}
} // namespace ComputerClub
