#pragma once

#include <istream>

namespace ComputerClub::Simulator {

/// Simulate the computer club's operation.
/// @param input  The input stream to read the configuration and events from.
/// @param output The output stream to write the results to.
/// @param err    The error stream to write parsing errors to.
/// @returns @c true if the simulation was successful, does not write anything to @p err, writes
///          the results to @p output.
/// @returns @c false on parsing error, writes first encountered incorrect line to @p err. Writes
///          nothing to @p output.
auto simulate(std::istream &input, std::ostream &output, std::ostream &err) -> bool;

} // namespace ComputerClub::Simulator
