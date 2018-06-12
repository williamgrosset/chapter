#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

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
    printf("%s/.git/COMMIT_EDITMSG\n", s_cwd.c_str());

    // Grab current directory and search .git folder
    // Identify branch and last commit NOT on remote
    // Print out text from commit message

    string commit_msg = s_cwd + "./git/COMMIT_EDITMSG";
    ifstream f(commit_msg.c_str());

    if (f.is_open()) {
      cout << f.rdbuf();
    }

    // TODO: AUDIT
    return 0;
}
