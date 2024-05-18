#include "Simulator.hpp"

#include "ComputerClub.hpp"
#include "Parser.hpp"

namespace ComputerClub::Simulator {
auto simulate(std::istream &input, std::ostream &output, std::ostream &err) -> bool {
  ComputerClub::Config config;
  try {
    config = ComputerClub::Parser::parseConfig(input);
  } catch (const ComputerClub::Parser::ParsingError &e) {
    err << e.what() << std::endl;
    return false;
  }

  ComputerClub::State state{config};
  Time lastEventTime{0, 0};
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    if (input.eof()) {
      break;
    }
    try {
      InputEvent event = ComputerClub::Parser::parseInputEvent(line);
      Time eventTime = std::visit([](const auto &event) { return event.time; }, event);
      if (eventTime < lastEventTime) {
        err << line << std::endl;
        return false;
      }
      lastEventTime = eventTime;
      state.processEvent(std::move(event));
    } catch (const ComputerClub::Parser::ParsingError &e) {
      err << e.what() << std::endl;
      return false;
    }
  }

  state.endDay();
  state.print(output);
  return true;
}
} // namespace ComputerClub::Simulator
