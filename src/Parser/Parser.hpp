#pragma once

#include "Config.hpp"
#include "Events.hpp"
#include <istream>
#include <stdexcept>

namespace ComputerClub::Parser {

/// Exception thrown when parsing fails.
class ParsingError final : public std::runtime_error {
public:
  ParsingError(const std::string &message) : runtime_error(message) {}
};

/// Parse the configuration of computer club from @p stream.
/// @param stream The input stream to read the configuration from.
/// @returns The parsed configuration.
/// @throws ParsingError If the configuration is invalid. Message contains the line that caused the
///         error.
auto parseConfig(std::istream &stream) -> Config;

/// Parse the input event from @p line.
/// @param line The line to parse the event from.
/// @returns The parsed event.
/// @throws ParsingError If the event is invalid. Message contains the @p line.
auto parseInputEvent(std::string line) -> InputEvent;

} // namespace ComputerClub::Parser
