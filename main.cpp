#include <sstream>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <lib/rules/rule_retriever.hpp>
#include <lib/ui/results_logger.hpp>

using json = nlohmann::json;

std::ifstream readGitCommitMsgFile() {
    try {
        char buffer[255];
        char* cwd = getcwd(buffer, sizeof(buffer));

        if (cwd) {
            std::string s_cwd(cwd);
            std::ifstream f(s_cwd + "/.git/COMMIT_EDITMSG");
            return f;
        } else {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Could not find Git commit message file." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

std::string convertFileToStr(std::ifstream f) {
    std::ostringstream s_stream;

    if (f.is_open()) {
        s_stream << f.rdbuf();
    }

    return s_stream.str();
}

void removeComments(std::string& msg) {
    for (int i = 0; i < msg.length(); i++) {
        if ((msg[i - 1] == '\n' || i == 0) && msg[i] == '#') {
            int j = i;

            // Look for end of line
            while (msg[j] != '\n') {
                j++;
            }

            msg.replace(i, j - i + 1, "");
            i = i - 1;
        }
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Commit message audit..." << std::endl << std::endl;

    std::string commitMsg = convertFileToStr(readGitCommitMsgFile()); 
    json rulesJSON = convertFileToJSON(readConfigFile());

    removeComments(commitMsg);
    printAuditResults(commitMsg, rulesJSON);

    return 0;
}
