#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

/*
 * TODO:
 * + Read file initially and pass in JSON parameter
 * + Verify type for each rule
 */

void verifyFormat() {}

nlohmann::json readConfigFile() {
  std::ifstream i("COMMIT_MSG_RULES.json");
  nlohmann::json j;
  i >> j;

  return j;
}

int getSummaryMaxLength() {
  nlohmann::json j = readConfigFile();
  // if (isInt(j["sum_max_len"]))
  // if (j["sum_max_len"] > getSummaryMinLen())
  return j["sum_max_len"];
}

int getSummaryMinLength() {
  nlohmann::json j = readConfigFile();
  return j["sum_min_len"];
}

bool requiresDescription() {
  nlohmann::json j = readConfigFile();
  return j["desc"]["required"];
}

int getDescriptionMaxLength() {
  nlohmann::json j = readConfigFile();
  return j["desc"]["max_len"];
}

int getDescriptionMinLength() {
  nlohmann::json j = readConfigFile();
  return j["desc"]["min_len"];
}

int getBulletPoints() {
  nlohmann::json j = readConfigFile();
  return j["bullet_points"];
}

bool allowsTypos() {
  nlohmann::json j = readConfigFile();
  return j["allows_typos"];
}

bool requiresSummaryCapital() {
  nlohmann::json j = readConfigFile();
  return j["sum_capital"];
}

bool requiresNitFormat() {
  nlohmann::json j = readConfigFile();
  return j["nit_format"];
}

bool requiresWIPFormat() {
  nlohmann::json j = readConfigFile();
  return j["wip_format"];
}
