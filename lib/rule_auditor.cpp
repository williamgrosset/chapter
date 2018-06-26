#include <boost/regex.hpp>

/*
 * TODO:
 * + Combine min/max and nit/WIP functions
 * + Improve initial regex for nit/WIP
 * + Fix regex for identifying # of bullet points
 */

const std::string COMMIT_MSG_PATTERN = "\u0021-\u007E\\s";

bool containsBulletPoints(const std::string msg, const int count) {
    // const boost::regex point_pattern("[" + COMMIT_MSG_PATTERN + "]+\n\n[" + COMMIT_MSG_PATTERN + "]*\n\n([\\+|-|\\*"
                                        // + COMMIT_MSG_PATTERN + "]{" + std::to_string(count) + "})");
    const boost::regex point_pattern("[" + COMMIT_MSG_PATTERN + "]+\n\n[" + COMMIT_MSG_PATTERN + "]*\n\n(["
                                        + COMMIT_MSG_PATTERN + "\n]+)");

    if (regex_match(msg, point_pattern)) {
        return true;
    }

    return false;
}

bool containsCorrectDocFormat(const std::string msg) {
    std::string lowered_msg = msg;
    const boost::regex doc_pattern(".*(documentation).*");
    const boost::regex doc_format_pattern("Documentation:\\s.*");
    std::transform(lowered_msg.begin(), lowered_msg.end(), lowered_msg.begin(), ::tolower);

    if (regex_match(lowered_msg, doc_pattern)) {
        if (!regex_match(msg, doc_format_pattern)) {
            return false;
        }
    }

    return true;
}

bool containsCorrectNitFormat(const std::string msg) {
    std::string lowered_msg = msg;
    const boost::regex nit_pattern(".*(nit).*");
    const boost::regex nit_format_pattern("Nit:\\s.*");
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
    const boost::regex WIP_pattern(".*(wip).*");
    const boost::regex WIP_format_pattern("WIP:\\s.*");
    std::transform(lowered_msg.begin(), lowered_msg.end(), lowered_msg.begin(), ::tolower);

    if (regex_match(lowered_msg, WIP_pattern)) {
        if (!regex_match(msg, WIP_format_pattern)) {
            return false;
        }
    }

    return true;
}

bool containsDescription(const std::string msg) {
    const boost::regex desc_pattern("[" + COMMIT_MSG_PATTERN + "]+\n\n([" + COMMIT_MSG_PATTERN + "]+)");

    if (regex_match(msg, desc_pattern)) {
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
    const boost::regex desc_pattern("[" + COMMIT_MSG_PATTERN + "]+\n\n([" + COMMIT_MSG_PATTERN + "]+)");
    boost::smatch result;

    if (boost::regex_search(msg, result, desc_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > length) {
            return true;
        }
    }

    return false;
}

bool isDescriptionMinLength(const std::string msg, const int length) {
    const boost::regex desc_pattern("[" + COMMIT_MSG_PATTERN + "]+\n\n([" + COMMIT_MSG_PATTERN + "]+)");
    boost::smatch result;

    if (boost::regex_search(msg, result, desc_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}

bool isFirstLetterCapitalized(const std::string msg) {
    // TODO: If includes "Nit " or "WIP ", exclude and check summary
    const boost::regex summary_pattern("([" + COMMIT_MSG_PATTERN + "]+)[\n" + COMMIT_MSG_PATTERN + "]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (isupper(submatch[0])) {
            return true;
        }
    }

    return false;
}

bool isSummaryMaxLength(const std::string msg, const int length) {
    const boost::regex summary_pattern("([" + COMMIT_MSG_PATTERN + "]+)[\n" + COMMIT_MSG_PATTERN + "]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > length) {
            return true;
        }
    }

    return false;
}

bool isSummaryMinLength(const std::string msg, const int length) {
    const boost::regex summary_pattern("([" + COMMIT_MSG_PATTERN + "]+)[\n" + COMMIT_MSG_PATTERN + "]*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summary_pattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}
