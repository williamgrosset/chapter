#include <sstream>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rule_retriever.hpp>
#include <lib/console_printer.hpp>

std::ifstream readGitCommitMsgFile() {
    char buffer[255];
    char* cwd = getcwd(buffer, sizeof(buffer));

    try {
        if (cwd) {
            std::string s_cwd(cwd);
            std::ifstream f(s_cwd + "/test.txt");
            return f;
        } else {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Commit Msg File Error: Could not find Git commit message file.\n";
        std::exit(EXIT_FAILURE);
    }
}

// TODO: Also remove '\n' characters
void removeComments(std::string& msg) {
    for (int i = 0; i < msg.length(); i++) {
        if (i != 0) {
            if (msg[i - 1] == '\n' && msg[i] == '#') {
                int j = i;

                // Look for position of next "\n"
                while (msg[j] != '\n') {
                    j++;
                }

                msg.replace(i, j - i, "");
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream f = readGitCommitMsgFile();
    std::ostringstream s_stream;
    boost::smatch comments;

    if (f.is_open()) {
        s_stream << f.rdbuf();
    }

    std::string commitMsg = s_stream.str();
    nlohmann::json rulesJSON = convertFileToJSON();

    removeComments(commitMsg);
    std::cout << "RESULT: " << commitMsg << "\n";
    displayAuditResults(rulesJSON, commitMsg);

    return 0;
}
