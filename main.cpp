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
    // TODO: Capture summary out of msg (REGEX)
    if (isupper(msg[0])) {
        return true;
    } else {
        return false;
    }
}

bool isSummaryMinLength(std::string msg) {
    // TODO: Capture summary out of msg (REGEX)
    if (msg.length() > 18) return true;
    return false;
}

bool isSummaryMaxLength(std::string msg) {
    // TODO: Capture summary out of msg (REGEX)
    if (msg.length() > 50) return true;
    return false;
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

bool containsCorrectWIPFormat(std::string msg) {
    std::string lowered_msg = msg;
    const boost::regex WIP_pattern(".*\\s(wip)\\s.*");
    const boost::regex WIP_format_pattern("WIP:.*");
    std::transform(lowered_msg.begin(), lowered_msg.end(), lowered_msg.begin(), ::tolower);

    if (regex_match(lowered_msg, WIP_pattern)) {
        if (!regex_match(msg, WIP_format_pattern)) {
            return false;
        }
    }

    return true;
}

bool containsDescription(std::string msg) {
    const boost::regex desc_pattern("[a-zA-Z0-9_\\s]*\\n\\n([a-zA-Z0-9_\\s]*)");

    if (!regex_match(msg, desc_pattern)) {
        return false;
    }

    return true;
}

bool isDescriptionMaxLength(std::string msg) {
    const boost::regex desc_pattern("[a-zA-Z0-9_\\s]*\\n\\n([a-zA-Z0-9_\\s]*)");

    if (regex_match(msg, desc_pattern)) {
        /*
        if (desc.length() > 72) {
            return true;
        }*/
        return true;
    }

    return false;
}

bool containsBulletPoints(std::string msg) {
    // TODO: Formatting and # of bullets (default 3)
    const boost::regex point_pattern("[a-zA-Z0-9_\\s]*\\n\\n[a-zA-Z0-9_\\s]*\\n\\n([[\\+|-|\\*]a-zA-Z0-9_\\s]*)");

    if (!regex_match(msg, point_pattern)) {
        return false;
    }

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
    
    printf("/************ Commit message audit... \U00002699 ************/\n\n");

    commit_msg = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commit_msg)));

    if (!isFirstLetterCapitalized(commit_msg)) {
        printf("Error: First letter of summary must be capitalized. \U0000274C\n");
    }

    if (!containsCorrectNitFormat(commit_msg)) {
        printf("Error: \"Nit:\" commits must have the correct format. \U0000274C\n");
    }

    if (!containsCorrectWIPFormat(commit_msg)) {
        printf("Error: \"WIP:\" commits must have the correct format. \U0000274C\n");
    }

    if (isSummaryMinLength(commit_msg)) {
        printf("Error: Summary must be above 18 characters. \U0000274C\n");
    }

    if (isSummaryMaxLength(commit_msg)) {
        printf("Error: Summary must not exceed 50 characters. \U0000274C\n");
    }

    if (!containsDescription(commit_msg)) {
        printf("Error: Description is required. \U0000274C\n");
    }

    if (!isDescriptionMaxLength(commit_msg)) {
        printf("Error: Description must not exceed 72 characters. \U0000274C\n");
    }

    if (!containsBulletPoints(commit_msg)) {
        printf("Error: 3 bullet points are required. \U0000274C\n");
    }

    printf("\n/************ End of audit. \U00002699 ************/\n");

    return 0;
}
