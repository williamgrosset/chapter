#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <jamspell/spell_corrector.hpp>
using namespace std;

int main(int argc, char* argv[]) {
    char buffer[255];
    char* answer = getcwd(buffer, sizeof(buffer));
    string s_cwd;

    if (answer) {
        s_cwd = answer;
    }

    string commit_msg_path = s_cwd + "/.git/COMMIT_EDITMSG";
    ifstream f(commit_msg_path.c_str());
    ostringstream out;

    if (f.is_open()) {
        out << f.rdbuf();
    }

    string commit_msg = out.str();
    printf("%s", commit_msg.c_str());

    return 0;
}

// TODO: Place audit methods in lib/
bool containsTypos(string msg) {
    return true;
}

bool isFirstLetterCapital(string msg) {
    return true;
}

bool containsPeriod(string msg) {
    return true;
}

bool isMaxLength(string msg) {
    return true;
}

bool containsSummary(string msg) {
    return true;
}

bool containsKeyPoints(string msg) {
    return true;
}
