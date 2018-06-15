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
    const boost::regex summary_pattern("([a-zA-Z0-9_:\\.\\s]*)\\n*[a-zA-Z0-9_:\\.\\s]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        std::string submatch(result[1].first, result[1].second);
        if (isupper(submatch[0])) {
            return true;
        }
    }

    return false;
}

bool isSummaryMinLength(std::string msg) {
    const boost::regex summary_pattern("([a-zA-Z0-9_:\\.\\s]*)\\n*[a-zA-Z0-9_:\\.\\s]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < 18) {
            return true;
        }
    }

    return false;
}

bool isSummaryMaxLength(std::string msg) {
    const boost::regex summary_pattern("([a-zA-Z0-9_:\\.\\s]*)\\n*[a-zA-Z0-9_:\\.\\s]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > 50) {
            return true;
        }
    }

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
    const boost::regex desc_pattern("[a-zA-Z0-9_:\\.\\s]*\\n\\n([a-zA-Z0-9_:\\.\\s]*)");

    if (!regex_match(msg, desc_pattern)) {
        return false;
    }

    return true;
}

bool isDescriptionMaxLength(std::string msg) {
    const boost::regex desc_pattern("[a-zA-Z0-9_:\\.\\s]*\\n\\n([a-zA-Z0-9_:\\.\\s]*)");
    boost::smatch result;

    if (boost::regex_search(msg, result, desc_pattern)) {
        std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > 72) {
            return true;
        }
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
    
    printf("/************   \U00002699 Commit message audit...   ************/\n\n");

    commit_msg = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commit_msg)));

    if (!isFirstLetterCapitalized(commit_msg)) {
        printf("\U0000274C Error: First letter of summary must be capitalized. \n");
    }

    if (!containsCorrectNitFormat(commit_msg)) {
        printf("\U0000274C Error: \"Nit:\" commits must have the correct format. \n");
    }

    if (!containsCorrectWIPFormat(commit_msg)) {
        printf("\U0000274C Error: \"WIP:\" commits must have the correct format. \n");
    }

    if (isSummaryMinLength(commit_msg)) {
        printf("\U0000274C Error: Summary must be above 18 characters. \n");
    }

    if (isSummaryMaxLength(commit_msg)) {
        printf("\U0000274C Error: Summary must not exceed 50 characters. \n");
    }

    if (containsDescription(commit_msg)) {
        if (!isDescriptionMaxLength(commit_msg)) {
            printf("\U0000274C Error: Description must not exceed 72 characters. \n");
        }
    } else {
        printf("\U0000274C Error: Description is required. \n");
    }

    if (!containsBulletPoints(commit_msg)) {
        printf("\U0000274C Error: 3 bullet points are required. \n");
    }

    printf("\n/************        \U00002699 End of audit.        ************/\n");

    return 0;
}
