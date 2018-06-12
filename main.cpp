#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <unistd.h>
#include <jamspell/spell_corrector.hpp>
using namespace std;

// TODO: Place audit methods in lib/
bool containsTypos(string msg) {
    return true;
}

bool isFirstLetterCapitalized(int c) {
    if (isupper(c)) {
       return true;
    } else {
       return false;
    }
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
    
    printf("Beginning audit...\n");

    if (isFirstLetterCapitalized(commit_msg[0])) {
        printf("No errors found.\n");
    } else {
        printf("Error: First letter must be capitalized.\n");
    }

    return 0;
}
