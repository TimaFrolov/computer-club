#include "Time.hpp"
#include <format>

namespace ComputerClub {
std::ostream &operator<<(std::ostream &stream, const Time &time) {
  return stream << std::format("{:02}:{:02}", time.hour, time.minute);
}
} // namespace ComputerClub
