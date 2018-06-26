#include <boost/regex.hpp>

/*
 * TODO:
 * + Complete typos identification
 * + Fix all regex patterns (lot of work here)
 * + Fix regex for identifying # of bullet points
 * + Improve initial regex for nit/WIP
 * + Combine min/max and nit/WIP functions
 */

const std::string COMMIT_MSG_PATTERN = "\u0021-\u007E\\s";

bool containsBulletPoints(const std::string msg, const int count) {
    // const boost::regex point_pattern("[" + COMMIT_MSG_PATTERN + "]+\n\n[" + COMMIT_MSG_PATTERN + "]*\n\n([\\+|-|\\*"
                                        // + COMMIT_MSG_PATTERN + "]{" + std::to_string(count) + "})");
    const boost::regex pointPattern("[" + COMMIT_MSG_PATTERN + "]+\n\n[" + COMMIT_MSG_PATTERN + "]*\n\n(["
                                        + COMMIT_MSG_PATTERN + "\n]+)");

    if (regex_match(msg, pointPattern)) {
        return true;
    }

    return false;
}

bool containsCorrectDocFormat(const std::string msg) {
    std::string loweredMsg = msg;
    const boost::regex docPattern(".*(documentation).*");
    const boost::regex docFormatPattern("Documentation:\\s.*");
    std::transform(loweredMsg.begin(), loweredMsg.end(), loweredMsg.begin(), ::tolower);

    if (regex_match(loweredMsg, docPattern)) {
        if (!regex_match(msg, docFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsCorrectNitFormat(const std::string msg) {
    std::string loweredMsg = msg;
    const boost::regex nitPattern(".*(nit).*");
    const boost::regex nitFormatPattern("Nit:\\s.*");
    std::transform(loweredMsg.begin(), loweredMsg.end(), loweredMsg.begin(), ::tolower);

    if (regex_match(loweredMsg, nitPattern)) {
        if (!regex_match(msg, nitFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsCorrectWIPFormat(const std::string msg) {
    std::string loweredMsg = msg;
    const boost::regex WIPPattern(".*(wip).*");
    const boost::regex WIPFormatPattern("WIP:\\s.*");
    std::transform(loweredMsg.begin(), loweredMsg.end(), loweredMsg.begin(), ::tolower);

    if (regex_match(loweredMsg, WIPPattern)) {
        if (!regex_match(msg, WIPFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsDescription(const std::string msg) {
    const boost::regex descPattern("[" + COMMIT_MSG_PATTERN + "]+\n\n([" + COMMIT_MSG_PATTERN + "]+)");

    if (regex_match(msg, descPattern)) {
        return true;
    }

    return false;
}

bool containsTypos(const std::string msg) {
    // TODO:
    //  + Generate warning (instead of error) outlining all typos
    //  + Ignore nit and WIP
    return true;
}

bool isDescriptionMaxLength(const std::string msg, const int length) {
    const boost::regex descPattern("[" + COMMIT_MSG_PATTERN + "]+\n\n([" + COMMIT_MSG_PATTERN + "]+)");
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
    const boost::regex descPattern("[" + COMMIT_MSG_PATTERN + "]+\n\n([" + COMMIT_MSG_PATTERN + "]+)");
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
    // TODO: If includes "Nit " or "WIP ", exclude and check summary
    const boost::regex summaryPattern("([" + COMMIT_MSG_PATTERN + "]+)[\n" + COMMIT_MSG_PATTERN + "]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summaryPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (isupper(submatch[0])) {
            return true;
        }
    }

    return false;
}

bool isSummaryMaxLength(const std::string msg, const int length) {
    const boost::regex summaryPattern("([" + COMMIT_MSG_PATTERN + "]+)[\n" + COMMIT_MSG_PATTERN + "]*");
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
    const boost::regex summaryPattern("([" + COMMIT_MSG_PATTERN + "]+)[\n" + COMMIT_MSG_PATTERN + "]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summaryPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}
