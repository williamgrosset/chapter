#include <fstream>
#include <nlohmann/json.hpp>

/*
 * TODO:
 */

nlohmann::json readFile() {
  std::ifstream i("COMMIT_MSG_RULES.json");
  nlohmann::json j;
  i >> j;

  return j;
}
