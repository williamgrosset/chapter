#include <fstream>
#include <iostream>
#include <unistd.h>
#include <exception>
#include <nlohmann/json.hpp>

/*
 * TODO:
 * + Read file initially and pass in JSON parameter
 * + Verify type for each rule
 * + Improve error handling
 */

class IntException: public std::exception {
    virtual const char* what() const throw() {
      return "\U0001F6A8 Error: Rule \"sum_max_len\" must be a positive integer.";
    }
} intExcp;

std::ifstream readConfigFile() {
    char buffer[255];
    char* cwd = getcwd(buffer, sizeof(buffer));

    if (cwd) {
        std::string s_cwd(cwd);
        std::ifstream f(s_cwd + "/COMMIT_MSG_RULES.json");
        return f;
    } else {
        std::ifstream f("/COMMIT_MSG_RULES.json");
        return f;
    }
}

nlohmann::json convertFileToJson() {
    std::ifstream f = readConfigFile(); 
    nlohmann::json j;
    f >> j;

    return j;
}

int getSummaryMinLength() {
    nlohmann::json j = convertFileToJson();
    return j["sum_min_len"];
}

int getSummaryMaxLength() {
    nlohmann::json j = convertFileToJson();
    try {
      int maxLength = j["sum_max_len"];
      if (maxLength <= 0 || maxLength < getSummaryMinLength()) {
          throw intExcp;
      }

      return maxLength;
    } catch(std::exception& e) {
      std::cout << e.what() << "\n";
      std::exit(EXIT_FAILURE);
    }
}

bool requiresDescription() {
    nlohmann::json j = convertFileToJson();
    return j["desc"]["required"];
}

int getDescriptionMaxLength() {
    nlohmann::json j = convertFileToJson();
    return j["desc"]["max_len"];
}

int getDescriptionMinLength() {
    nlohmann::json j = convertFileToJson();
    return j["desc"]["min_len"];
}

int getBulletPoints() {
    nlohmann::json j = convertFileToJson();
    return j["bullet_points"];
}

bool allowsTypos() {
    nlohmann::json j = convertFileToJson();
    return j["allows_typos"];
}

bool requiresSummaryCapital() {
    nlohmann::json j = convertFileToJson();
    return j["sum_capital"];
}

bool requiresNitFormat() {
    nlohmann::json j = convertFileToJson();
    return j["nit_format"];
}

bool requiresWIPFormat() {
    nlohmann::json j = convertFileToJson();
    return j["wip_format"];
}
