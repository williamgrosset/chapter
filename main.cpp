#include <sstream>
#include <fstream>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <lib/rule_retriever.hpp>
#include <lib/console_printer.hpp>

/*
 * TODO:
 * + Improve error handling
 */

std::ifstream readGitCommitMsgFile() {
    char buffer[255];
    char* cwd = getcwd(buffer, sizeof(buffer));

    if (cwd) {
        std::string s_cwd(cwd);
        std::ifstream f(s_cwd + "/.git/COMMIT_EDITMSG");
        return f;
    } else {
        std::ifstream f("/.git/COMMIT_EDITMSG");
        return f;
    }
}

int main(int argc, char* argv[]) {
    std::ifstream f = readGitCommitMsgFile();
    std::ostringstream s_stream;

    if (f.is_open()) {
        s_stream << f.rdbuf();
    }

    std::string commit_msg = s_stream.str();
    nlohmann::json rulesJSON = convertFileToJson();

    displayAuditResults(rulesJSON, commit_msg);

    return 0;
}
