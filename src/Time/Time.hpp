#pragma once

#include <compare>
#include <cstdint>
#include <ostream>

namespace ComputerClub {

/// Time of the day
struct Time {
  std::uint8_t hour;
  std::uint8_t minute;
};

constexpr auto operator<=>(const Time &lhs, const Time &rhs) -> std::strong_ordering {
  auto hourCmp = lhs.hour <=> rhs.hour;
  return hourCmp == std::strong_ordering::equal ? lhs.minute <=> rhs.minute : hourCmp;
}

/// Subtracts two times
/// @param lhs First time
/// @param rhs Second time
/// @returns Time difference between two times if @p lhs >= @p rhs
/// @returns Time{0, 0} otherwise
constexpr auto operator-(const Time &lhs, const Time &rhs) -> Time {
  auto hourDifference = lhs.hour - rhs.hour;
  auto minuteDifference = lhs.minute - rhs.minute;
  if (minuteDifference < 0) {
    hourDifference--;
    minuteDifference += 60;
  }
  return (hourDifference < 0) ? Time{0, 0}
                              : Time{std::uint8_t(hourDifference), std::uint8_t(minuteDifference)};
};

/// Adds two times
/// @param lhs First time
/// @param rhs Second time
/// @returns Sum of two times mod 256 hours
constexpr auto operator+(const Time &lhs, const Time &rhs) -> Time {
  auto hourSum = lhs.hour + rhs.hour;
  auto minuteSum = lhs.minute + rhs.minute;
  if (minuteSum >= 60) {
    hourSum++;
    minuteSum -= 60;
  }
  return Time{std::uint8_t(hourSum), std::uint8_t(minuteSum)};
}

/// Equivalent to @c lhs = lhs + rhs
constexpr auto operator+=(Time &lhs, const Time &rhs) -> Time & { return lhs = lhs + rhs; }

/// Prints @p time to the @p stream in format "HH:MM" 
/// @returns @p stream
std::ostream &operator<<(std::ostream &stream, const Time &time);

}; // namespace ComputerClub
