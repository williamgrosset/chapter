#include <fstream>
#include <iostream>
#include <unistd.h>
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

int getSummaryMaxLength() {
    nlohmann::json j = convertFileToJson();
    // if (isInt(j["sum_max_len"]))
    // if (j["sum_max_len"] > getSummaryMinLen())
    return j["sum_max_len"];
}

int getSummaryMinLength() {
    nlohmann::json j = convertFileToJson();
    return j["sum_min_len"];
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
