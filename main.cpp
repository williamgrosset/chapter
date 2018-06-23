#include <sstream>
#include <fstream>
#include <unistd.h>
#include <lib/results_logger.hpp>

const std::string getGitCommitMsgPath() {
    char buffer[255];
    char* answer = getcwd(buffer, sizeof(buffer));
    std::string s_cwd;

    if (answer) {
        s_cwd = answer;
    }

    return s_cwd + "/.git/COMMIT_EDITMSG";
}

int main(int argc, char* argv[]) {
    const std::string commit_msg_path = getGitCommitMsgPath();
    std::ifstream f(commit_msg_path.c_str());
    std::ostringstream out;

    if (f.is_open()) {
        out << f.rdbuf();
    }

    std::string commit_msg = out.str();
    printf("%s", commit_msg.c_str());
    
    displayAuditResults(commit_msg);

    return 0;
}
