#include <sstream>
#include <fstream>
#include <unistd.h>
#include <lib/results_logger.hpp>

/*
 * TODO:
 * + Improve error handling
 */

const std::string getGitCommitMsgPath() {
    char buffer[255];
    char* cwd = getcwd(buffer, sizeof(buffer));

    if (cwd) {
        std::string s_cwd(cwd);
        return s_cwd + "/.git/COMMIT_EDITMSG";
    } else {
        return "";
    }
}

int main(int argc, char* argv[]) {
    const std::string commit_msg_path = getGitCommitMsgPath();
    std::ifstream f(commit_msg_path.c_str());
    std::ostringstream s_stream;

    if (f.is_open()) {
        s_stream << f.rdbuf();
    }

    std::string commit_msg = s_stream.str();
    
    displayAuditResults(commit_msg);

    return 0;
}
