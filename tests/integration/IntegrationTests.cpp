
#include "Simulator.hpp"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

static const char *testCases[] = {
    "example", /// Example from the task description.
};

class IntegrationTest : public ::testing::TestWithParam<const char *> {};

INSTANTIATE_TEST_SUITE_P(IntegrationTests, IntegrationTest, ::testing::ValuesIn(testCases));

TEST_P(IntegrationTest, Main) {
  auto testName = GetParam();

  auto testInput = std::ifstream(fs::path{TEST_DATA_PATH} / testName += ".in");
  auto testOutputStream = std::ifstream(fs::path{TEST_DATA_PATH} / testName += ".out");
  auto testErrStream = std::ifstream(fs::path{TEST_DATA_PATH} / testName += ".err");

  std::string testOutput(std::istreambuf_iterator<char>(testOutputStream), {});
  std::string testErr(std::istreambuf_iterator<char>(testErrStream), {});

  std::stringstream output;
  std::stringstream err;

  ASSERT_EQ(ComputerClub::Simulator::simulate(testInput, output, err), !testOutput.empty());
  ASSERT_EQ(output.str(), testOutput);
  ASSERT_EQ(err.str(), testErr);
}
