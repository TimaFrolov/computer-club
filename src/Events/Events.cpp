#include "Events.hpp"

namespace ComputerClub {

auto ClientArrivalEvent::print(std::ostream &stream) const -> void {
  stream << this->time << ' ' << 1 << ' ' << this->client;
}

auto ClientSitInputEvent::print(std::ostream &stream) const -> void {
  stream << this->time << ' ' << 2 << ' ' << this->client << ' ' << this->table;
}

auto ClientWaitingEvent::print(std::ostream &stream) const -> void {
  stream << this->time << ' ' << 3 << ' ' << this->client;
}

auto ClientLeavingInputEvent::print(std::ostream &stream) const -> void {
  stream << this->time << ' ' << 4 << ' ' << this->client;
}

auto ClientLeavingOutputEvent::print(std::ostream &stream) const -> void {
  stream << this->time << ' ' << 11 << ' ' << this->client;
}

auto ClientSitOutputEvent::print(std::ostream &stream) const -> void {
  stream << this->time << ' ' << 12 << ' ' << this->client << ' ' << this->table;
}

auto ErrorEvent::print(std::ostream &stream) const -> void {
  stream << this->time << ' ' << 13 << ' ' << this->message;
}

} // namespace ComputerClub
