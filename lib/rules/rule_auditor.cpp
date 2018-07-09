#include <iostream>
#include <regex>

using namespace std::regex_constants;

const std::string VALID_MSG_CHARS = "\u0020-\u007E";

void normalizeEndOfCapture(std::string& capture) {
    // Remove last '\n' character if captured with double new line
    const int length = capture.length();
    if (capture[length - 2] == '\n' && capture[length - 1] == '\n') {
        capture.replace(length - 1, 1, "");
    }
}

void removePointsFromDesc(std::string& msg) {
    for (int i = 0; i < msg.length(); i++) {
        if ((msg[i - 1] == '\n' || i == 0) && (msg[i] == '+' || msg[i] == '*' || msg[i] == '-')) {
            int j = i;

            // Look for end of line
            while (msg[j] != '\n') {
                j++;
            }

            msg.replace(i, j - i + 1, "");
            i = i - 1;
        }
    }

    normalizeEndOfCapture(msg);
}

void removeDescFromPoints(std::string& msg) {
    for (int i = 0; i < msg.length(); i++) {
        if ((msg[i - 1] == '\n' || i == 0) && msg[i] != '+' && msg[i] != '*' && msg[i] != '-') {
            int j = i;

            // Look for end of line
            while (msg[j] != '\n') {
                j++;
            }

            msg.replace(i, j - i + 1, "");
            i = i - 1;
        }
    }

    normalizeEndOfCapture(msg);
}

int getBulletPointCount(const std::string points) {
    const int length = points.length();
    int count = 0;

    for (int i = 0; i < length; i++) {
        if (points[i] == '\n') count++;
    }

    if (length > 0 && count == 0) {
        count++;
    }

    return count;
}

bool containsBulletPoints(const std::string msg, const int requiredCount) {
    const std::regex pointPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    std::smatch pointResult;

    if (std::regex_search(msg, pointResult, pointPattern)) {
        std::string points(pointResult[1].str());
        removeDescFromPoints(points);

        return getBulletPointCount(points) == requiredCount;
    }

    return false;
}

std::string getBulletPoints(const std::string msg) {
    const std::regex pointPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    std::smatch pointResult;

    if (std::regex_search(msg, pointResult, pointPattern)) {
        std::string points(pointResult[1].str());
        removeDescFromPoints(points);

        return points;
    }

    return "";
}

bool isBulletPointsMaxLength(const std::string msg, const int length) {
    const std::regex pointPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    std::smatch pointResult;

    if (std::regex_search(msg, pointResult, pointPattern)) {
        std::string points(pointResult[1].str());
        removeDescFromPoints(points);

        return points.length() - getBulletPointCount(points) > length;
    }

    return false;
}

bool isBulletPointsMinLength(const std::string msg, const int length) {
    const std::regex pointPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    std::smatch pointResult;

    if (std::regex_search(msg, pointResult, pointPattern)) {
        std::string points(pointResult[1].str());
        removeDescFromPoints(points);

        return points.length() - getBulletPointCount(points) < length;
    }

    return false;
}

bool containsCorrectDocFormat(const std::string msg) {
    const std::regex docPattern("\\s?(documentation|doc[s]|todo|readme|[a-zA-Z0-9]+\\.md|[a-zA-Z0-9]+\\.txt):?\\s",
                                      ECMAScript | icase);

    if (std::regex_search(msg, docPattern)) {
        return msg.substr(0, 6).compare("Docs: ") == 0;
    }

    return true;
}

bool containsCorrectNitFormat(const std::string msg) {
    const std::regex nitPattern("\\s?(nit):?\\s", ECMAScript | icase);

    if (std::regex_search(msg, nitPattern)) {
        return msg.compare(0, 5, "Nit: ") == 0;
    }

    return true;
}

bool containsCorrectWIPFormat(const std::string msg) {
    const std::regex WIPPattern("\\s?(wip|work\\sin\\sprogress):?\\s", ECMAScript | icase);

    if (std::regex_search(msg, WIPPattern)) {
        return msg.substr(0, 5).compare("WIP: ") == 0;
    }

    return true;
}

std::string getDescription(const std::string msg) {
    const std::regex descPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    std::smatch descResult;

    if (std::regex_search(msg, descResult, descPattern)) {
        std::string description(descResult[1].str());
        removePointsFromDesc(description);

        return description;
    }

    return "";
}

bool isDescriptionMaxLength(const std::string msg, const int length) {
    const std::regex descPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    std::smatch descResult;

    if (std::regex_search(msg, descResult, descPattern)) {
        std::string description(descResult[1].str());
        removePointsFromDesc(description);

        return description.length() > length;
    }

    return false;
}

bool isDescriptionMinLength(const std::string msg, const int length) {
    const std::regex descPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    std::smatch descResult;

    if (std::regex_search(msg, descResult, descPattern)) {
        std::string description(descResult[1].str());
        removePointsFromDesc(description);

        return description.length() < length;
    }

    return false;
}

bool isFirstLetterCapitalized(const std::string msg) {
    const std::vector<std::string> excludedStrings = { "Nit:", "WIP:", "Docs:" };
    const std::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}.*");
    std::smatch summaryResult;

    if (std::regex_search(msg, summaryResult, summaryPattern)) {
        std::string summary(summaryResult[1].str());

        // If one of excludedStrings is included, remove from string
        for (const std::string formatWord : excludedStrings) {
            const size_t initialPos = summary.find(formatWord);
            if (initialPos != summary.npos) {
                summary.replace(initialPos, formatWord.length(), "");
                break;
            }
        }

        // Capture initial word in summary 
        const std::regex wordPattern("$\\s?([a-zA-Z]+).*");
        std::smatch initialWordResult;

        if (std::regex_search(summary, initialWordResult, wordPattern)) {
            const std::string initialWord(initialWordResult[1].str());

            return isupper(initialWord[0]);
        }

        // Return true if first set of characters is not a word
        return true;
    }

    return false;
}

bool containsSummary(const std::string msg) {
    const std::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}");
    return std::regex_search(msg, summaryPattern);
}

std::string getSummary(const std::string msg) {
    const std::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}");
    std::smatch summaryResult;

    if (std::regex_search(msg, summaryResult, summaryPattern)) {
        return summaryResult[1].str();
    }

    return "";
}

bool isSummaryMaxLength(const std::string msg, const int length) {
    const std::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}.*");
    std::smatch summaryResult;

    if (std::regex_search(msg, summaryResult, summaryPattern)) {
        return summaryResult[1].str().length() > length;
    }

    return false;
}

bool isSummaryMinLength(const std::string msg, const int length) {
    const std::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}.*");
    std::smatch summaryResult;

    if (std::regex_search(msg, summaryResult, summaryPattern)) {
        return summaryResult[1].str().length() < length;
    }

    return false;
}
