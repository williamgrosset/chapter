#include <fstream>
#include <iostream>
#include <exception>
#include <unistd.h>
#include <nlohmann/json.hpp>

std::ifstream readConfigFile() {
    char buffer[255];
    char* cwd = getcwd(buffer, sizeof(buffer));

    try {
        if (cwd) {
            std::string s_cwd(cwd);
            std::ifstream f(s_cwd + "/COMMIT_MSG_RULES.json");
            return f;
        } else {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Config File Error: Reading configuration file failed.\n";
        std::exit(EXIT_FAILURE);
    }
}

nlohmann::json convertFileToJson() {
    std::ifstream f = readConfigFile(); 
    nlohmann::json j;
    f >> j;

    return j;
}

int getSummaryMinLength(nlohmann::json rulesJSON) {
    try {
        const int minLength = rulesJSON["sum_min_len"];

        if (minLength <= 1) {
            throw std::exception();
        }

        return minLength;
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Summary min length must be a non-zero, positive integer.\n";
        std::exit(EXIT_FAILURE);
    }
}

int getSummaryMaxLength(nlohmann::json rulesJSON) {
    try {
        const int maxLength = rulesJSON["sum_max_len"];

        if (maxLength <= 1) {
            throw std::exception();
        }

        return maxLength;
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Summary max length must be a non-zero, positive integer.\n";
        std::exit(EXIT_FAILURE);
    }
}

bool requiresDescription(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["desc"]["required"];
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Description required must be a boolean.\n";
        std::exit(EXIT_FAILURE);
    }
}

int getDescriptionMaxLength(nlohmann::json rulesJSON) {
    try {
        const int descMaxLength = rulesJSON["desc"]["max_len"];

        if (descMaxLength <= 1) {
            throw std::exception();
        }

        return descMaxLength;
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Description max length must be a non-zero, positive integer.\n";
        std::exit(EXIT_FAILURE);
    }
}

int getDescriptionMinLength(nlohmann::json rulesJSON) {
    try {
        const int descMinLength = rulesJSON["desc"]["min_len"];

        if (descMinLength <= 1) {
            throw std::exception();
        }

        return descMinLength;
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Description min length must be a non-zero, positive integer.\n";
        std::exit(EXIT_FAILURE);
    }
}

int getBulletPoints(nlohmann::json rulesJSON) {
    try {
        const int bulletPointsVal = rulesJSON["bullet_points"];

        if (bulletPointsVal < 2) {
            throw std::exception();
        }

        return bulletPointsVal;
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Bullet points must be a positive integer above 1.\n";
        std::exit(EXIT_FAILURE);
    }
}

bool allowsTypos(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["allows_typos"];
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Allow typos must be a boolean.\n";
        std::exit(EXIT_FAILURE);
    }
}

bool requiresSummaryCapital(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["sum_capital"];
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Summary capital must be a boolean.\n";
        std::exit(EXIT_FAILURE);
    }
}

bool requiresDocFormat(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["doc_format"];
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Documentation format must be a boolean.\n";
        std::exit(EXIT_FAILURE);
    }
}

bool requiresNitFormat(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["nit_format"];
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: Nit format must be a boolean.\n";
        std::exit(EXIT_FAILURE);
    }
}

bool requiresWIPFormat(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["wip_format"];
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Rule Error: WIP format must be a boolean.\n";
        std::exit(EXIT_FAILURE);
    }
}
