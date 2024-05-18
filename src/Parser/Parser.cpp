#include "Parser.hpp"
#include "Events.hpp"
#include <algorithm>
#include <charconv>
#include <optional>

namespace {
auto tryParseTwoDigits(std::string_view str) -> std::optional<std::uint8_t> {
  if (str.size() != 2) {
    return std::nullopt;
  }
  if (str[0] < '0' || str[0] > '9' || str[1] < '0' || str[1] > '9') {
    return std::nullopt;
  }
  return (str[0] - '0') * 10 + (str[1] - '0');
}

constexpr std::size_t TimeLength = 5;

auto tryParseTime(std::string_view str) -> std::optional<ComputerClub::Time> {
  if (str.size() != TimeLength) {
    return std::nullopt;
  }
  std::optional<uint8_t> hour = tryParseTwoDigits(str.substr(0, 2));
  std::optional<uint8_t> minute = tryParseTwoDigits(str.substr(3, 2));
  if (!hour.has_value() || !minute.has_value() || str[2] != ':') {
    return std::nullopt;
  }
  return ComputerClub::Time{.hour = hour.value(), .minute = minute.value()};
}

auto tryParseNumber(std::string_view str) -> std::optional<std::uint64_t> {
  std::uint64_t result;
  std::from_chars_result parseTablesResult = std::from_chars(str.begin(), str.end(), result);
  if (parseTablesResult.ptr != str.end() || parseTablesResult.ec == std::errc::invalid_argument ||
      parseTablesResult.ec == std::errc::result_out_of_range) {
    return std::nullopt;
  }
  return result;
}

auto validClientName(std::string_view str) -> bool {
  return std::ranges::all_of(str, [](char c) {
    return ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_' || c == '-');
  });
}

} // namespace

namespace ComputerClub::Parser {

auto parseConfig(std::istream &stream) -> Config {
  std::string line;

  if (stream.eof()) {
    throw ParsingError("");
  }
  std::getline(stream, line);
  auto tablesAmount = tryParseNumber(line);
  if (!tablesAmount.has_value()) {
    throw ParsingError(std::move(line));
  }

  if (stream.eof()) {
    throw ParsingError("");
  }
  std::getline(stream, line);
  if (line.size() != TimeLength + 1 + TimeLength) {
    throw ParsingError(std::move(line));
  }
  auto openingTime = tryParseTime(std::string_view(line).substr(0, TimeLength));
  auto closingTime = tryParseTime(std::string_view(line).substr(TimeLength + 1, TimeLength));
  if (!openingTime.has_value() || !closingTime.has_value() || line[TimeLength] != ' ' ||
      openingTime.value() > closingTime.value()) {
    throw ParsingError(std::move(line));
  }

  if (stream.eof()) {
    throw ParsingError("");
  }
  std::getline(stream, line);
  auto costPerHour = tryParseNumber(line);
  if (!costPerHour.has_value()) {
    throw ParsingError(std::move(line));
  }
  return {
      .tablesAmount = tablesAmount.value(),
      .openingTime = openingTime.value(),
      .closingTime = closingTime.value(),
      .costPerHour = costPerHour.value(),
  };
}

auto parseInputEvent(std::string line) -> InputEvent {
  if (line.size() < TimeLength + 3 /* space, event number, space */) {
    throw ParsingError(std::move(line));
  }
  if (line[TimeLength] != ' ' || line[TimeLength + 2] != ' ') {
    throw ParsingError(std::move(line));
  }
  auto time = tryParseTime(std::string_view(line).substr(0, TimeLength));
  if (!time.has_value()) {
    throw ParsingError(std::move(line));
  }

  std::uint8_t eventNumber = line[TimeLength + 1] - '0';
  auto eventBody = std::string_view(line).substr(TimeLength + 3);
  switch (eventNumber) {
  case 1: {
    if (!validClientName(eventBody)) {
      throw ParsingError(std::move(line));
    }
    return ClientArrivalEvent(time.value(), std::string(eventBody));
  }
  case 2: {
    auto spacePos = eventBody.find(' ');
    auto name = eventBody.substr(0, spacePos);
    auto table = tryParseNumber(eventBody.substr(spacePos + 1));
    if (!table.has_value() || !validClientName(name)) {
      throw ParsingError(std::move(line));
    }
    return ClientSitInputEvent(time.value(), std::string(name), table.value());
  }
  case 3: {
    if (!validClientName(eventBody)) {
      throw ParsingError(std::move(line));
    }
    return ClientWaitingEvent(time.value(), std::string(eventBody));
  }
  case 4: {
    if (!validClientName(eventBody)) {
      throw ParsingError(std::move(line));
    }
    return ClientLeavingInputEvent(time.value(), std::string(eventBody));
  }
  default:
    throw ParsingError(std::move(line));
  }
}
} // namespace ComputerClub::Parser
