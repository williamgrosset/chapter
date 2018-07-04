#include <fstream>
#include <iostream>
#include <exception>
#include <unistd.h>
#include <nlohmann/json.hpp>

/*
 * TODO:
 * + Convert to Class (remove global var)
 */

// Temp global variable
bool errorExists = false;

std::ifstream readConfigFile() {
    try {
        char buffer[255];
        char* cwd = getcwd(buffer, sizeof(buffer));

        if (cwd) {
            std::string s_cwd(cwd);
            std::ifstream f(s_cwd + "/COMMIT_MSG_RULES.json");
            return f;
        } else {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Config File Error: Could not find configuration rules file.\n";
        std::exit(EXIT_FAILURE);
    }
}

nlohmann::json convertFileToJSON() {
    std::ifstream f = readConfigFile();
    nlohmann::json j;

    try {
        f >> j;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Config File Error: Ensure your JSON file has correct syntax.\n";
        std::exit(EXIT_FAILURE);
    }

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
        std::cout << "  \U0001F6A8 Rule Error: Summary min length must be a non-zero, positive integer.\n";
        if (!errorExists) errorExists = true;
        return -1;
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
        std::cout << "  \U0001F6A8 Rule Error: Summary max length must be a non-zero, positive integer.\n";
        if (!errorExists) errorExists = true;
        return -1;
    }
}

bool requiresDescription(nlohmann::json rulesJSON) {
    try {
        nlohmann::json j = rulesJSON["desc"];

        if (j.is_null()) {
            return false;
        } else if (!j.is_object()) {
            throw std::exception();
        } else if (j.empty()) {
            return false;
        }

        return true;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Description must be an object.\n";
        if (!errorExists) errorExists = true;
        return false;
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
        std::cout << "  \U0001F6A8 Rule Error: Description max length must be a non-zero, positive integer.\n";
        if (!errorExists) errorExists = true;
        return -1;
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
        std::cout << "  \U0001F6A8 Rule Error: Description min length must be a non-zero, positive integer.\n";
        if (!errorExists) errorExists = true;
        return -1;
    }
}

bool requiresBulletPoints(nlohmann::json rulesJSON) {
    try {
        nlohmann::json j = rulesJSON["bullet_points"];

        if (j.is_null()) {
            return false;
        } else if (!j.is_object()) {
            throw std::exception();
        } else if (j.empty()) {
            return false;
        }

        return true;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Bullet points must be an object.\n";
        if (!errorExists) errorExists = true;
        return false;
    }
}

int getBulletPointsCount(nlohmann::json rulesJSON) {
    try {
        const int bulletPointsCount = rulesJSON["bullet_points"]["count"];

        if (bulletPointsCount < 0) {
            throw std::exception();
        }

        return bulletPointsCount;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Bullet points count must be zero or a positive integer.\n";
        if (!errorExists) errorExists = true;
        return -1;
    }
}

int getBulletPointsMinLength(nlohmann::json rulesJSON) {
    try {
        const int minLength = rulesJSON["bullet_points"]["min_len"];

        if (minLength <= 1) {
            throw std::exception();
        }

        return minLength;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Bullet points min length must be a non-zero, positive integer.\n";
        if (!errorExists) errorExists = true;
        return -1;
    }
}

int getBulletPointsMaxLength(nlohmann::json rulesJSON) {
    try {
        const int maxLength = rulesJSON["bullet_points"]["max_len"];

        if (maxLength <= 1) {
            throw std::exception();
        }

        return maxLength;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Bullet points max length must be a non-zero, positive integer.\n";
        if (!errorExists) errorExists = true;
        return -1;
    }
}

bool identifyTypos(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["identify_typos"];
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Allow typos must be a boolean.\n";
        if (!errorExists) errorExists = true;
        return false;
    }
}

bool requiresSummaryCapital(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["sum_capital"];
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Summary capital must be a boolean.\n";
        if (!errorExists) errorExists = true;
        return false;
    }
}

bool requiresDocFormat(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["doc_format"];
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Documentation format must be a boolean.\n";
        if (!errorExists) errorExists = true;
        return false;
    }
}

bool requiresNitFormat(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["nit_format"];
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Nit format must be a boolean.\n";
        if (!errorExists) errorExists = true;
        return false;
    }
}

bool requiresWIPFormat(nlohmann::json rulesJSON) {
    try {
        return rulesJSON["wip_format"];
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: WIP format must be a boolean.\n";
        if (!errorExists) errorExists = true;
        return false;
    }
}

bool hasRuleErrorThrown(nlohmann::json rulesJSON) {
    if (requiresBulletPoints(rulesJSON)) {
        getBulletPointsCount(rulesJSON);
        getBulletPointsMaxLength(rulesJSON);
        getBulletPointsMinLength(rulesJSON);
    }

    if (requiresDescription(rulesJSON)) {
        getDescriptionMaxLength(rulesJSON);
        getDescriptionMinLength(rulesJSON);
    }

    getSummaryMaxLength(rulesJSON);
    getSummaryMinLength(rulesJSON);
    identifyTypos(rulesJSON);
    requiresSummaryCapital(rulesJSON);
    requiresDocFormat(rulesJSON);
    requiresNitFormat(rulesJSON);
    requiresWIPFormat(rulesJSON);

    return errorExists;
}
