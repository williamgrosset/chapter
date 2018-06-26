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
    try {
      nlohmann::json j = convertFileToJson();
      int minLength = j["sum_min_len"];

      if (minLength <= 1) {
          throw std::exception();
      }

      return minLength;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"sum_min_len\" must be a non-zero, positive integer." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

int getSummaryMaxLength() {
    try {
      nlohmann::json j = convertFileToJson();
      int maxLength = j["sum_max_len"];

      if (maxLength <= 1) {
          throw std::exception();
      }

      return maxLength;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"sum_max_len\" must be a non-zero, positive integer." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

bool requiresDescription() {
    try {
      nlohmann::json j = convertFileToJson();
      bool requiresDesc = j["desc"]["required"];

      return requiresDesc;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"desc_required\" must be a boolean." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

int getDescriptionMaxLength() {
    try {
      nlohmann::json j = convertFileToJson();
      int descMaxLength = j["desc"]["max_len"];

      if (descMaxLength <= 1) {
          throw std::exception();
      }

      return descMaxLength;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"desc_max_len\" must be a non-zero, positive integer." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

int getDescriptionMinLength() {
    try {
      nlohmann::json j = convertFileToJson();
      int descMinLength = j["desc"]["min_len"];

      if (descMinLength <= 1) {
          throw std::exception();
      }

      return descMinLength;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"desc_min_len\" must be a non-zero, positive integer." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

int getBulletPoints() {
    try {
      nlohmann::json j = convertFileToJson();
      int bulletPointsVal = j["bullet_points"];

      if (bulletPointsVal <= 1) {
          throw std::exception();
      }

      return bulletPointsVal;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"bullet_points\" must be a non-zero, positive integer." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

bool allowsTypos() {
    try {
      nlohmann::json j = convertFileToJson();
      bool allowsTypos = j["allows_typos"];

      return allowsTypos;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"allows_typos\" must be a boolean." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

bool requiresSummaryCapital() {
    try {
      nlohmann::json j = convertFileToJson();
      bool requiresSumCapital = j["sum_capital"];

      return requiresSumCapital;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"sum_capital\" must be a boolean." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

bool requiresDocFormat() {
    try {
      nlohmann::json j = convertFileToJson();
      bool requiresDocFormat = j["doc_format"];

      return requiresDocFormat;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"doc_format\" must be a boolean." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

bool requiresNitFormat() {
    try {
      nlohmann::json j = convertFileToJson();
      bool requiresNitFormat = j["nit_format"];

      return requiresNitFormat;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"nit_format\" must be a boolean." << "\n";
      std::exit(EXIT_FAILURE);
    }
}

bool requiresWIPFormat() {
    try {
      nlohmann::json j = convertFileToJson();
      bool requiresWIPFormat = j["wip_format"];

      return requiresWIPFormat;
    } catch(const std::exception& e) {
      std::cout << "\U0001F6A8 Error: Rule \"wip_format\" must be a boolean." << "\n";
      std::exit(EXIT_FAILURE);
    }
}
