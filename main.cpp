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
            std::ifstream f(s_cwd + "/.git/COMMIT_EDITMSG");
            return f;
        } else {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        std::cout << "\U0001F6A8 Commit Msg File Error: Could not find Git commit message file.\n";
        std::exit(EXIT_FAILURE);
    }
}

void removeComments(std::string& msg) {
    for (int i = 0; i < msg.length(); i++) {
        if ((msg[i - 1] == '\n' || i == 0) && msg[i] == '#') {
            int j = i;

            // Look for end of comment
            while (msg[j] != '\n') {
                j++;
            }

            msg.replace(i, j - i + 1, "");
            i = i - 1;
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
    displayAuditResults(rulesJSON, commitMsg);

    return 0;
}
