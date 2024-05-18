#pragma once

#include <concepts>
#include <ostream>
#include <variant>

#include "Time.hpp"

namespace ComputerClub {

/// Event in the computer club
class Event {
public:
  /// Print the event to the stream.
  virtual auto print(std::ostream &stream) const -> void = 0;

  /// Virtual destructor for inheritance.
  virtual ~Event() = default;

protected:
  /// Default constructor for inheritance.
  Event() = default;

  /// Rule of five
  Event(const Event &) = default;
  Event(Event &&) = default;
  auto operator=(const Event &) -> Event & = default;
  auto operator=(Event &&) -> Event & = default;
};

/// Concept that checks if the type is an event.
/// @tparam T Type to check.
template <typename T>
concept IsEvent = std::derived_from<T, Event>;

/// Event representing client arrival.
class ClientArrivalEvent final : public Event {
public:
  /// @copydoc Event::print
  auto print(std::ostream &stream) const -> void override;

  /// Create a new client arrival event.
  /// @param time   Time of the event.
  /// @param client Name of the client.
  ClientArrivalEvent(Time time, std::string client) : time(time), client(std::move(client)) {}

public:
  Time time;          ///< Time of the event.
  std::string client; ///< Name of the client.
};

/// Event representing client sitting at the table.
class ClientSitInputEvent final : public Event {
public:
  /// @copydoc Event::print
  auto print(std::ostream &stream) const -> void override;

  /// Create a new client sit event.
  /// @param time   Time of the event.
  /// @param client Name of the client.
  /// @param table  Number of the table.
  ClientSitInputEvent(Time time, std::string client, std::uintmax_t table)
      : time(time), client(std::move(client)), table(table) {}

public:
  Time time;            ///< Time of the event.
  std::string client;   ///< Name of the client.
  std::uintmax_t table; ///< Number of the table.
};

/// Event representing client waiting for a table.
class ClientWaitingEvent final : public Event {
public:
  /// @copydoc Event::print
  auto print(std::ostream &stream) const -> void override;

  /// Create a new client waiting event.
  /// @param time   Time of the event.
  /// @param client Name of the client.
  ClientWaitingEvent(Time time, std::string client) : time(time), client(std::move(client)) {}

public:
  Time time;          ///< Time of the event.
  std::string client; ///< Name of the client.
};

/// Event representing client leaving the club.
class ClientLeavingInputEvent final : public Event {
public:
  /// @copydoc Event::print
  auto print(std::ostream &stream) const -> void override;

  /// Create a new client leaving event.
  /// @param time   Time of the event.
  /// @param client Name of the client.
  ClientLeavingInputEvent(Time time, std::string client) : time(time), client(std::move(client)) {}

public:
  Time time;          ///< Time of the event.
  std::string client; ///< Name of the client.
};

/// Input event that can happen in the club.
using InputEvent = std::variant<ClientArrivalEvent, ClientSitInputEvent, ClientWaitingEvent,
                                ClientLeavingInputEvent>;

/// Concept that checks if the type is an input event.
/// @tparam T Type to check.
template <typename T>
concept IsInputEvent =
    std::is_same_v<T, ClientArrivalEvent> || std::is_same_v<T, ClientSitInputEvent> ||
    std::is_same_v<T, ClientWaitingEvent> || std::is_same_v<T, ClientLeavingInputEvent>;

/// Event representing client leaving the club.
class ClientLeavingOutputEvent final : public Event {
public:
  /// @copydoc Event::print
  auto print(std::ostream &stream) const -> void override;

  /// Create a new client leaving event.
  /// @param time   Time of the event.
  /// @param client Name of the client.
  ClientLeavingOutputEvent(Time time, std::string client) : time(time), client(client) {}

public:
  Time time;          ///< Time of the event.
  std::string client; ///< Name of the client.
};

/// Event representing client sitting at the table.
class ClientSitOutputEvent final : public Event {
public:
  /// @copydoc Event::print
  auto print(std::ostream &stream) const -> void override;

  /// Create a new client sit event.
  /// @param time   Time of the event.
  /// @param client Name of the client.
  /// @param table  Number of the table.
  ClientSitOutputEvent(Time time, std::string client, uintmax_t table)
      : time(time), client(std::move(client)), table(table) {}

public:
  Time time;          ///< Time of the event.
  std::string client; ///< Name of the client.
  uintmax_t table;    ///< Number of the table.
};

/// Event representing an error.
class ErrorEvent final : public Event {
public:
  /// @copydoc Event::print
  auto print(std::ostream &stream) const -> void override;

  /// Create a new error event.
  /// @param time    Time of the event.
  /// @param message Error message.
  ErrorEvent(Time time, std::string message) : time(time), message(std::move(message)) {}

public:
  Time time;
  std::string message;
};

/// Output event that can be generated during work of club simulator.
using OutputEvent = std::variant<ClientLeavingOutputEvent, ClientSitOutputEvent, ErrorEvent>;

/// Concept that checks if the type is an output event.
/// @tparam T Type to check.
template <typename T>
concept IsOutputEvent = std::is_same_v<T, ClientLeavingOutputEvent> ||
                        std::is_same_v<T, ClientSitOutputEvent> || std::is_same_v<T, ErrorEvent>;
} // namespace ComputerClub
