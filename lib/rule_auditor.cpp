#include <iostream>
#include <boost/regex.hpp>

/*
 * TODO:
 * + Move typo checking logic into seperate file
 *   + Keep containsTypo(msg) in rule_auditor.cpp
 * + Fix, audit, and clean-up all regex patterns
 *   + Description & min/max
 *   + Summary & min/max
 *   + Summary capitalization
 *   + Bullet points
 */

const std::string VALID_MSG_CHARS = "\u0021-\u007E\\s";

void removePointsFromDesc(std::string& description) {
    // Remove bullet points from description
    for (int i = 0; i < description.length(); i++) {
        if ((description[i - 1] == '\n' || i == 0) && description[i] == '+') {
            int j = i;

            // Look for end of comment
            while (description[j] != '\n') {
                j++;
            }

            description.replace(i, j - i + 1, "");
            i = i - 1;
        }
    }

    const int length = description.length();

    // Remove last '\n' character if captured with double new line
    if (description[length - 2] == '\n' && description[length - 1] == '\n') {
        description.replace(length - 1, 1, "");
    }
}

bool containsTypos(const std::string msg) {
    // TODO:
    //  + Generate warning (instead of error) outlining all typos
    //  + Ignore nit and WIP
    return true;
}

bool containsBulletPoints(const std::string msg, const int count) {
    const boost::regex pointPattern("[" + VALID_MSG_CHARS + "]+\n\n[" + VALID_MSG_CHARS + "]*\n\n([" + VALID_MSG_CHARS 
                                        + "\n]+)");

    if (regex_match(msg, pointPattern)) {
        return true;
    }

    return false;
}

bool containsCorrectDocFormat(const std::string msg) {
    const boost::regex docPattern("\\s?(documentation|doc[s]|todo|readme|[a-zA-Z0-9]+\\.md|[a-zA-Z0-9]+\\.txt):?\\s",
                                      boost::regex::icase);

    if (regex_match(msg, docPattern)) {
        if (msg.substr(0, 6).compare("Docs: ") != 0) {
            return false;
        }
    }

    return true;
}

bool containsCorrectNitFormat(const std::string msg) {
    const boost::regex nitPattern("\\s?(nit):?\\s", boost::regex::icase);

    if (regex_match(msg, nitPattern)) {
        if (msg.substr(0, 5).compare("Nit: ") != 0) {
            return false;
        }
    }

    return true;
}

bool containsCorrectWIPFormat(const std::string msg) {
    const boost::regex WIPPattern("\\s?(wip|work\\sin\\sprogress):?\\s", boost::regex::icase);

    if (regex_match(msg, WIPPattern)) {
        if (msg.substr(0, 5).compare("WIP: ") != 0) {
            return false;
        }
    }

    return true;
}

bool containsDescription(const std::string msg) {
    const boost::regex descPattern("^(?:[\u0020-\u007E]+\\n\\n){1}([\u0020-\u007E\\n]+)");
    boost::smatch descResult;

    if (boost::regex_search(msg, descResult, descPattern)) {
        std::string description(descResult[1].first, descResult[1].second);
        removePointsFromDesc(description);

        if (description.length() > 0) {
            return true;
        }
    }

    return false;
}

bool isDescriptionMaxLength(const std::string msg, const int length) {
    const boost::regex descPattern("[" + VALID_MSG_CHARS + "]+\n\n([" + VALID_MSG_CHARS + "\n]+)");
    boost::smatch result;

    if (boost::regex_search(msg, result, descPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > length) {
            return true;
        }
    }

    return false;
}

bool isDescriptionMinLength(const std::string msg, const int length) {
    const boost::regex descPattern("[" + VALID_MSG_CHARS + "]+\n\n([" + VALID_MSG_CHARS + "\n]+)");
    boost::smatch result;

    if (boost::regex_search(msg, result, descPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}

bool isFirstLetterCapitalized(const std::string msg) {
    const std::vector<std::string> excludedStrings = { "Nit:", "WIP:", "Docs:" };
    const boost::regex summaryPattern("([" + VALID_MSG_CHARS + "]+)[\n" + VALID_MSG_CHARS + "]*");
    boost::smatch summaryResult;

    if (boost::regex_search(msg, summaryResult, summaryPattern)) {
        std::string summary(summaryResult[1].first, summaryResult[1].second);

        // If one of the excludedStrings is included, remove from the string
        for (const std::string formatWord : excludedStrings) {
            const size_t initialPos = summary.find(formatWord);
            if (initialPos != summary.npos) {
                summary.replace(initialPos, formatWord.length(), "");
                break;
            }
        }

        // Capture initial word in summary 
        const boost::regex wordPattern("$\\s?([a-zA-Z]+).*");
        boost::smatch initialWordResult;

        if (boost::regex_search(summary, initialWordResult, wordPattern)) {
            const std::string initialWord(initialWordResult[1].first, initialWordResult[1].second);

            if (isupper(initialWord[0])) {
                return true;
            }

            return false;
        }

        // Return true if first set of characters is not a word
        return true;
    }

    return false;
}

bool containsSummary(const std::string msg) {
    const boost::regex summaryPattern("^([\u0020-\u007E]+\n?){1}");

    if (regex_match(msg, summaryPattern)) {
        return true;
    }

    return false;
}

bool isSummaryMaxLength(const std::string msg, const int length) {
    const boost::regex summaryPattern("^([\u0020-\u007E]+\n?){1}");
    boost::smatch result;

    if (boost::regex_search(msg, result, summaryPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > length) {
            return true;
        }
    }

    return false;
}

bool isSummaryMinLength(const std::string msg, const int length) {
    const boost::regex summaryPattern("^([\u0020-\u007E]+\n?){1}");
    boost::smatch result;

    if (boost::regex_search(msg, result, summaryPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}
