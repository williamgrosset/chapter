#include <fstream>
#include <iostream>
#include <exception>
#include <unistd.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool ruleErrorExists = false;

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
        std::cout << "  \U0001F6A8 Could not find COMMIT_MSG_RULES.json file." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

json convertFileToJSON(std::ifstream f) {
    json j;

    try {
        f >> j;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Converting configuration file to JSON failed." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return j;
}

int getSummaryMinLength(json rulesJSON) {
    try {
        json minLength = rulesJSON["sum_min_len"];

        if (minLength <= 1) {
            throw std::exception();
        }

        return minLength;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Summary min length must be a positive integer." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return -1;
    }
}

int getSummaryMaxLength(json rulesJSON) {
    try {
        const int maxLength = rulesJSON["sum_max_len"];

        if (maxLength <= 1) {
            throw std::exception();
        }

        return maxLength;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Summary max length must be a positive integer." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return -1;
    }
}

bool requiresDescription(json rulesJSON) {
    try {
        json j = rulesJSON["desc"];

        if (j.is_null()) {
            return false;
        } else if (!j.is_object() || j.empty()) {
            throw std::exception();
        }

        return true;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Description must be an object with max_length and min_length." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return false;
    }
}

int getDescriptionMaxLength(json rulesJSON) {
    try {
        const int descMaxLength = rulesJSON["desc"]["max_len"];

        if (descMaxLength <= 1) {
            throw std::exception();
        }

        return descMaxLength;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Description max length must be a positive integer." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return -1;
    }
}

int getDescriptionMinLength(json rulesJSON) {
    try {
        const int descMinLength = rulesJSON["desc"]["min_len"];

        if (descMinLength <= 1) {
            throw std::exception();
        }

        return descMinLength;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Description min length must be a positive integer." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return -1;
    }
}

bool requiresBulletPoints(json rulesJSON) {
    try {
        json j = rulesJSON["bullet_points"];

        if (j.is_null()) {
            return false;
        } else if (!j.is_object() || j.empty()) {
            throw std::exception();
        }

        return true;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Bullet points must be an object with count, max_length, and min_length." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return false;
    }
}

int getBulletPointsCount(json rulesJSON) {
    try {
        const int bulletPointsCount = rulesJSON["bullet_points"]["count"];

        if (bulletPointsCount < 0) {
            throw std::exception();
        }

        return bulletPointsCount;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Bullet points count must be zero or a positive integer." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return -1;
    }
}

int getBulletPointsMinLength(json rulesJSON) {
    try {
        const int minLength = rulesJSON["bullet_points"]["min_len"];

        if (minLength <= 1) {
            throw std::exception();
        }

        return minLength;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Bullet points min length must be a positive integer." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return -1;
    }
}

int getBulletPointsMaxLength(json rulesJSON) {
    try {
        const int maxLength = rulesJSON["bullet_points"]["max_len"];

        if (maxLength <= 1) {
            throw std::exception();
        }

        return maxLength;
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Bullet points max length must be a positive integer." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return -1;
    }
}

bool identifyTypos(json rulesJSON) {
    try {
        json j = rulesJSON["identify_typos"];

        if (j.is_null()) {
            return false;
        }

        return bool(j);
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Identify typos must be a boolean." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return false;
    }
}

bool requiresSummaryCapital(json rulesJSON) {
    try {
        json j = rulesJSON["sum_capital"];

        if (j.is_null()) {
            return false;
        }

        return bool(j);
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Summary capital must be a boolean." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return false;
    }
}

bool requiresDocFormat(json rulesJSON) {
    try {
        json j = rulesJSON["doc_format"];

        if (j.is_null()) {
            return false;
        }

        return bool(j);
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Documentation format must be a boolean." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return false;
    }
}

bool requiresNitFormat(json rulesJSON) {
    try {
        json j = rulesJSON["nit_format"];

        if (j.is_null()) {
            return false;
        }

        return bool(j);
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: Nit format must be a boolean." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return false;
    }
}

bool requiresWIPFormat(json rulesJSON) {
    try {
        json j = rulesJSON["wip_format"];

        if (j.is_null()) {
            return false;
        }

        return bool(j);
    } catch (const std::exception& e) {
        std::cout << "  \U0001F6A8 Rule Error: WIP format must be a boolean." << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
        return false;
    }
}

void verifyLengthRule(int maxLength, int minLength, const std::string attribute) {
    if (maxLength < minLength) {
        std::cout << "  \U0001F6A8 Rule Error: Max length must be less than min length for " << attribute << std::endl;
        if (!ruleErrorExists) ruleErrorExists = true;
    }
}

bool doesRuleErrorExist(json rulesJSON) {
    if (requiresBulletPoints(rulesJSON)) {
        getBulletPointsCount(rulesJSON);
        int bpMaxLength = getBulletPointsMaxLength(rulesJSON);
        int bpMinLength = getBulletPointsMinLength(rulesJSON);

        verifyLengthRule(bpMaxLength, bpMinLength, "bullet points");
    }

    if (requiresDescription(rulesJSON)) {
        int descMaxLength = getDescriptionMaxLength(rulesJSON);
        int descMinLength = getDescriptionMinLength(rulesJSON);

        verifyLengthRule(descMaxLength, descMinLength, "description");
    }

    int sumMaxLength = getSummaryMaxLength(rulesJSON);
    int sumMinLength = getSummaryMinLength(rulesJSON);

    verifyLengthRule(sumMaxLength, sumMinLength, "summary");
    requiresSummaryCapital(rulesJSON);
    requiresDocFormat(rulesJSON);
    requiresNitFormat(rulesJSON);
    requiresWIPFormat(rulesJSON);
    identifyTypos(rulesJSON);

    return ruleErrorExists;
}
