#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <unistd.h>
#include <boost/regex.hpp>

/*
 * TODO:
 * + Update regex patterns
*/

bool containsTypos(const std::string msg) {
    // TODO: Generate warning (instead of error) outlining all typos
    return true;
}

bool isFirstLetterCapitalized(const std::string msg) {
    // TODO: If includes "Nit " or "WIP ", exclude and check summary
    const boost::regex summary_pattern("([a-zA-Z0-9_:\\.\\s]*)\\n*[a-zA-Z0-9_:\\.\\s]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (isupper(submatch[0])) {
            return true;
        }
    }

    return false;
}

bool isSummaryMinLength(const std::string msg, const int length) {
    const boost::regex summary_pattern("([a-zA-Z0-9_:,\\.\\s]*)\\n*[a-zA-Z0-9_:\\.\\s]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}

bool isSummaryMaxLength(const std::string msg, const int length) {
    const boost::regex summary_pattern("([a-zA-Z0-9_:,\\.\\s]*)\\n*[a-zA-Z0-9_:\\.\\s]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > length) {
            return true;
        }
    }

    return false;
}

bool containsCorrectNitFormat(const std::string msg) {
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

bool containsCorrectWIPFormat(const std::string msg) {
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

bool containsDescription(const std::string msg) {
    const boost::regex desc_pattern("[a-zA-Z0-9_:\\.\\s]*\\n\\n([a-zA-Z0-9_:\\.\\s]*)");

    if (!regex_match(msg, desc_pattern)) {
        return false;
    }

    return true;
}

bool isDescriptionMaxLength(const std::string msg, const int length) {
    // TODO: Pass in length
    const boost::regex desc_pattern("[a-zA-Z0-9_:\\.\\s]*\\n\\n([a-zA-Z0-9_:\\.\\s]*)");
    boost::smatch result;

    if (boost::regex_search(msg, result, desc_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > length) {
            return true;
        }
    }

    return false;
}

bool containsBulletPoints(const std::string msg, const int length) {
    const boost::regex point_pattern("[a-zA-Z0-9_\\s]*\\n\\n[a-zA-Z0-9_\\s]*\\n\\n([[\\+|-|\\*]a-zA-Z0-9_\\s]{" + std::to_string(length) + "})");

    if (!regex_match(msg, point_pattern)) {
        return false;
    }

    return true;
}

void displayAuditResults(const std::string commit_msg) {
    printf("/************   \U00002699 Commit message audit...   ************/\n\n");

    if (!isFirstLetterCapitalized(commit_msg)) {
        printf("\U0000274C Error: First letter of summary must be capitalized. \n");
    } else {
        printf("\U00002705 Success: First letter of summary must be capitalized. \n");
    }

    if (!containsCorrectNitFormat(commit_msg)) {
        printf("\U0000274C Error: \"Nit:\" commits must have the correct format. \n");
    }

    if (!containsCorrectWIPFormat(commit_msg)) {
        printf("\U0000274C Error: \"WIP:\" commits must have the correct format. \n");
    }

    if (isSummaryMinLength(commit_msg, 18)) {
        printf("\U0000274C Error: Summary must be above 18 characters. \n");
    } else {
        printf("\U00002705 Success: Summary must be above 18 characters. \n");
    }

    if (isSummaryMaxLength(commit_msg, 50)) {
        printf("\U0000274C Error: Summary must not exceed 50 characters. \n");
    } else {
        printf("\U00002705 Success: Summary must not exceed 50 characters. \n");
    }

    if (containsDescription(commit_msg)) {
        printf("\U00002705 Success: Description is required. \n");
        if (!isDescriptionMaxLength(commit_msg, 72)) {
            printf("\U0000274C Error: Description must not exceed 72 characters. \n");
        } else {
            printf("\U00002705 Success: Description must not exceed 72 characters. \n");
        }
    } else {
        printf("\U0000274C Error: Description is required. \n");
    }

    if (!containsBulletPoints(commit_msg, 3)) {
        printf("\U0000274C Error: 3 bullet points are required. \n");
    } else {
        printf("\U00002705 Success: 3 bullet points are required. \n");
    }

    printf("\n/************        \U00002699 End of audit.        ************/\n");
}
