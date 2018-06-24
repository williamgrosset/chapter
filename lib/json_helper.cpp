#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

/*
 * TODO:
 */

nlohmann::json readConfigFile() {
  std::ifstream i("COMMIT_MSG_RULES.json");
  nlohmann::json j;
  i >> j;

  for (auto& element : j) {
      std::cout << element << '\n';
  }

  return j;
}
