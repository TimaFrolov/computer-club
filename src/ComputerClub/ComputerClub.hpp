#pragma once

#include "Config.hpp"
#include "Events.hpp"
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <unordered_map>
#include <vector>

namespace ComputerClub {

/// State of the computer club
class State {
public:
  /// Creates a new computer club
  /// @param config configuration of the club
  explicit State(Config config) : config(config) {}

  /// Processes the event
  /// @param event event to process. Event time should be greater or equal to the time of the last
  ///        event.
  auto processEvent(InputEvent event) -> void;

  /// Ends the day. All clients are kicked out and the club is closed
  auto endDay() -> void;

  /// Prints opening time of the computer club on the first line.
  /// Prints all events and the end of the day each on it's own line.
  /// Prints closing time of the computer club.
  /// Prints revenue of all tables and time spent at table in the club each on it's own line.
  auto print(std::ostream &stream) -> void;

private:
  /// Processes the event
  /// @tparam T type of the event to process
  /// @param event event to process
  template <IsInputEvent T> auto process(T event) -> void = delete;

  /// Processes client leaving table. Calculates client's time spent at the table and revenue.
  /// If there are clients waiting in the queue, the first one is seated at the table.
  /// @param time time of the event
  /// @param table table number
  auto tableLeave(Time time, std::uintmax_t table) -> void;

  /// Processes client sitting at the table. If client is currently sitting at other table, he is
  /// leaving previous table and moving to the new one.
  /// Caller should check whether @p table is occupied or not
  /// @param time time of the event
  /// @param client client name
  /// @param table table number
  auto clientSit(Time time, const std::string &client, std::uintmax_t table) -> void;

private:
  /// Data of the table
  struct TableData {
    /// Start time of the current client at the table
    std::optional<Time> currentStart = std::nullopt;

    /// Total revenue of the table
    std::uintmax_t revenue = 0;

    /// Total time spent at the table
    Time usedTime = {.hour = 0, .minute = 0};
  };

  /// Data of the client
  struct ClientData {
    std::uintmax_t currentTable = 0; ///< Table client sitting at. 0 if client is not sitting.
    bool waiting = false;            ///< Whether client is waiting in the queue.
  };

private:
  /// Configuration of the club
  Config config;

  /// Data of the tables
  std::unordered_map<std::uintmax_t, TableData> tables = {};

  /// Number of used tables
  std::uintmax_t usedTables = 0;

  /// Data of the clients
  std::map<std::string, ClientData> clients = {};

  /// Queue of clients waiting for a table
  std::queue<std::string> clientsQueue = {};

  /// List of events happened in the club
  std::vector<std::unique_ptr<Event>> events = {};
};

} // namespace ComputerClub
