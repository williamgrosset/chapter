#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <unistd.h>
#include <boost/regex.hpp>
#include <jamspell/spell_corrector.hpp>

// TODO: Place audit methods in lib/
bool containsTypos(std::string msg) {
    return true;
}

bool isFirstLetterCapitalized(std::string msg) {
    if (isupper(msg[0])) {
        return true;
    } else {
        return false;
    }
}

bool containsCorrectNitFormat(std::string msg) {
    std::string lowered_msg = msg;
    const boost::regex nit_pattern(".*\\s(nit)\\s.*");
    const boost::regex nit_format_pattern("Nit:.*");
    std::transform(lowered_msg.begin(), lowered_msg.end(), lowered_msg.begin(), ::tolower);

    if (regex_match(lowered_msg, nit_pattern)) {
        if (!regex_match(msg, nit_format_pattern)) {
            return false;
        }
    }

    return true;
}

bool isMaxLength(std::string msg) {
    // Entire commit message
    return true;
}

bool containsSummary(std::string msg) {
    // Formatting and character length
    return true;
}

bool containsKeyPoints(std::string msg) {
    // Formatting and character length and # of bullets
    return true;
}

int main(int argc, char* argv[]) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model.bin");
    char buffer[255];
    char* answer = getcwd(buffer, sizeof(buffer));
    std::string s_cwd;

    if (answer) {
        s_cwd = answer;
    }

    std::string commit_msg_path = s_cwd + "/.git/COMMIT_EDITMSG";
    std::ifstream f(commit_msg_path.c_str());
    std::ostringstream out;

    if (f.is_open()) {
        out << f.rdbuf();
    }

    std::string commit_msg = out.str();
    printf("%s", commit_msg.c_str());
    
    printf("Beginning audit... \U00002699\n");

    commit_msg = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commit_msg)));

    if (!isFirstLetterCapitalized(commit_msg)) {
        printf("Error: First letter must be capitalized. \U0000274C\n");
    }


    if (!containsCorrectNitFormat(commit_msg)) {
        printf("Error: \"Nit:\" commits must have the correct format. \U0000274C\n");
    }

    return 0;
}
