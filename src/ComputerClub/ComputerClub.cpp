#include "ComputerClub.hpp"
#include "Events.hpp"
#include <cassert>

namespace ComputerClub {

template <> auto State::process(ClientArrivalEvent event) -> void {
  if (event.time < this->config.openingTime) {
    this->events.emplace_back(std::make_unique<ErrorEvent>(event.time, "NotOpenYet"));
    return;
  }
  if (this->clients.contains(event.client)) {
    this->events.emplace_back(std::make_unique<ErrorEvent>(event.time, "YouShallNotPass"));
    return;
  }

  this->clients[event.client] = {};
}

template <> auto State::process(ClientSitInputEvent event) -> void {
  if (!this->clients.contains(event.client)) {
    this->events.emplace_back(std::make_unique<ErrorEvent>(event.time, "ClientUnknown"));
    return;
  }
  if (this->tables.contains(event.table) && this->tables[event.table].currentStart.has_value()) {
    this->events.emplace_back(std::make_unique<ErrorEvent>(event.time, "PlaceIsBusy"));
    return;
  }

  this->clientSit(event.time, event.client, event.table);
}

template <> auto State::process(ClientWaitingEvent event) -> void {
  if (!this->clients.contains(event.client)) {
    this->events.emplace_back(std::make_unique<ErrorEvent>(event.time, "ClientUnknown"));
    return;
  }
  ClientData &client = this->clients[event.client];
  if (this->usedTables < this->config.tablesAmount) {
    this->events.emplace_back(std::make_unique<ErrorEvent>(event.time, "ICanWaitNoLonger!"));
    return;
  }
  if (this->clientsQueue.size() >= this->config.tablesAmount) {
    this->clients.erase(event.client);
    this->events.emplace_back(
        std::make_unique<ClientLeavingOutputEvent>(event.time, std::move(event.client)));
    return;
  }

  if (!client.waiting) {
    this->clientsQueue.emplace(std::move(event.client));
    client.waiting = true;
  }
}

template <> auto State::process(ClientLeavingInputEvent event) -> void {
  if (!this->clients.contains(event.client)) {
    this->events.emplace_back(std::make_unique<ErrorEvent>(event.time, "ClientUnknown"));
    return;
  }

  this->tableLeave(event.time, this->clients.at(event.client).currentTable);
  this->clients.erase(event.client);
}

auto State::clientSit(Time time, const std::string &client, std::uintmax_t table) -> void {
  ClientData &clientData = this->clients.at(client);

  if (clientData.currentTable != 0) {
    this->tableLeave(time, clientData.currentTable);
  }
  clientData.currentTable = table;
  clientData.waiting = false;

  this->usedTables++;
  if (!this->tables.contains(table)) {
    this->tables[table] = {.currentStart = time};
  } else {
    this->tables[table].currentStart = time;
  }
}

auto State::tableLeave(Time time, std::uintmax_t table) -> void {
  if (!this->tables.contains(table)) {
    return;
  }

  TableData &tableData = this->tables[table];

  if (!tableData.currentStart.has_value()) {
    return;
  }

  Time diff = time - tableData.currentStart.value();
  tableData.usedTime += diff;
  std::uintmax_t hoursSpent = diff.minute == 0 ? diff.hour : diff.hour + 1;
  tableData.revenue += hoursSpent * this->config.costPerHour;
  tableData.currentStart = std::nullopt;

  if (this->clientsQueue.empty()) {
    this->usedTables--;
  } else {
    std::string client = this->clientsQueue.front();
    this->events.emplace_back(std::make_unique<ClientSitOutputEvent>(time, client, table));
    this->clientsQueue.pop();
    this->clientSit(time, client, table);
  }
}

auto State::processEvent(InputEvent event) -> void {
  auto eventToPtr = [](auto event) -> std::unique_ptr<Event> {
    return std::make_unique<decltype(event)>(std::move(event));
  };

  this->events.emplace_back(std::visit(eventToPtr, event));

  std::visit([this](const auto &event) { return this->process(event); }, std::move(event));
}

auto State::endDay() -> void {
  Time time = this->config.closingTime;

  this->clientsQueue = {};
  for (auto &&[client, data] : std::move(this->clients)) {
    this->tableLeave(time, data.currentTable);
    this->events.emplace_back(std::make_unique<ClientLeavingOutputEvent>(time, std::move(client)));
  }
  this->clients = {};
}

auto State::print(std::ostream &stream) -> void {
  stream << this->config.openingTime << '\n';
  for (const auto &event : this->events) {
    event->print(stream);
    stream << '\n';
  }
  stream << this->config.closingTime << '\n';
  for (std::uintmax_t i = 1; i <= this->config.tablesAmount; i++) {
    if (this->tables.contains(i)) {
      stream << i << ' ' << this->tables[i].revenue << ' ' << this->tables[i].usedTime << '\n';
    } else {
      stream << i << " 0 00:00\n";
    }
  }
}

} // namespace ComputerClub
