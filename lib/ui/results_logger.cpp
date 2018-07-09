#include <ctype.h>
#include <nlohmann/json.hpp>
#include <lib/rules/rule_retriever.hpp>
#include <lib/rules/rule_auditor.hpp>
#include <lib/rules/typo_handler.hpp>
#include <jamspell/spell_corrector.hpp>

using json = nlohmann::json;

bool hasErrorOrWarning = false;

void printTypos(const std::string str, const std::string section) {
    const std::vector<std::string> typos = getTypos(str);
    const int size = typos.size();

    if (size > 0) {
        if (!hasErrorOrWarning) hasErrorOrWarning = true;
        std::cout << "  \U0001F530 Warning: " << size << " potential "
                  << (size > 1 ? "typos" : "typo")
                  << " found in " << section << ": " << std::endl;

        for (int i = 0; i < size; i++) {
            std::cout << "        " << i + 1 << ". " << typos[i] << std::endl;
        }

        std::cout << std::endl;
    }
}

void printAuditResults(const std::string commitMsg, json rulesJSON) {
    if (verifyIfRuleErrorExists(rulesJSON)) {
        std::cout << std::endl << "    Please fix your rules configuration file for" << std::endl
                  << "    correct attributes and value types." << std::endl << std::endl
                  << "    See https://github.com/williamgrosset/chapter/README.md" << std::endl;
    } else {
        const int summaryMinLength = getSummaryMinLength(rulesJSON);
        const int summaryMaxLength = getSummaryMaxLength(rulesJSON);
        const bool reqNitFormat = requiresNitFormat(rulesJSON);
        const bool reqWIPFormat = requiresWIPFormat(rulesJSON);
        const bool reqDocFormat = requiresDocFormat(rulesJSON);
        const bool reqDescription = requiresDescription(rulesJSON);
        const bool reqBulletPoints = requiresBulletPoints(rulesJSON);
        const bool reqIdentifyTypos = identifyTypos(rulesJSON);
        const std::string description = getDescription(commitMsg);

        if (reqIdentifyTypos) {
            const std::string summary = getSummary(commitMsg);
            const std::string description = getDescription(commitMsg);

            if (summary.compare("") != 0) {
                printTypos(summary, "summary");
            }

            if (reqDescription && description.compare("") != 0) {
                printTypos(description, "description");
            }

            if (reqBulletPoints) {
                const int bulletPointsCount = getBulletPointsCount(rulesJSON);
                if (containsBulletPoints(commitMsg, bulletPointsCount)) {
                    printTypos(getBulletPoints(commitMsg), "bullet points");
                }
            }
        }

        if (requiresSummaryCapital(rulesJSON) && !isFirstLetterCapitalized(commitMsg)) {
            if (!hasErrorOrWarning) hasErrorOrWarning = true;
            std::cout << "  \U0000274C Error: First letter of summary must be capitalized." << "\n";
        }

        if (reqNitFormat && !containsCorrectNitFormat(commitMsg)) {
            if (!hasErrorOrWarning) hasErrorOrWarning = true;
            std::cout << "  \U0000274C Error: \"Nit:\" commits must have the correct format." << "\n";
        }

        if (reqWIPFormat && !containsCorrectWIPFormat(commitMsg)) {
            if (!hasErrorOrWarning) hasErrorOrWarning = true;
            std::cout << "  \U0000274C Error: \"WIP:\" commits must have the correct format." << "\n";
        }

        if (reqDocFormat && !containsCorrectDocFormat(commitMsg)) {
            if (!hasErrorOrWarning) hasErrorOrWarning = true;
            std::cout << "  \U0000274C Error: \"Documentation:\" commits must have the correct format." << "\n";
        }

        if (isSummaryMinLength(commitMsg, summaryMinLength)) {
            if (!hasErrorOrWarning) hasErrorOrWarning = true;
            std::cout << "  \U0000274C Error: Summary must be above " << summaryMinLength << " characters.\n";
        }

        if (isSummaryMaxLength(commitMsg, summaryMaxLength)) {
            if (!hasErrorOrWarning) hasErrorOrWarning = true;
            std::cout << "  \U0000274C Error: Summary must not exceed " << summaryMaxLength << " characters.\n";
        }

        if (reqDescription) {
            if (description.compare("") != 0) {
                const int descMinLength = getDescriptionMinLength(rulesJSON);
                const int descMaxLength = getDescriptionMaxLength(rulesJSON);

                if (isDescriptionMinLength(commitMsg, descMinLength)) {
                    if (!hasErrorOrWarning) hasErrorOrWarning = true;
                    std::cout << "  \U0000274C Error: Description must be above " << descMinLength << " characters.\n";
                }

                if (isDescriptionMaxLength(commitMsg, descMaxLength)) {
                    if (!hasErrorOrWarning) hasErrorOrWarning = true;
                    std::cout << "  \U0000274C Error: Description must not exceed " << descMaxLength << " characters.\n";
                }
            } else {
                if (!hasErrorOrWarning) hasErrorOrWarning = true;
                std::cout << "  \U0000274C Error: Description is required. \n";
            }
        }

        if (reqBulletPoints) {
            const int bulletPointsCount = getBulletPointsCount(rulesJSON);

            if (containsBulletPoints(commitMsg, bulletPointsCount)) {
                const int bpMinLength = getBulletPointsMinLength(rulesJSON);
                const int bpMaxLength = getBulletPointsMaxLength(rulesJSON);

                if (isBulletPointsMinLength(commitMsg, bpMinLength)) {
                    if (!hasErrorOrWarning) hasErrorOrWarning = true;
                    std::cout << "  \U0000274C Error: Bullet points must be above " << bpMinLength << " characters.\n";
                }

                if (isBulletPointsMaxLength(commitMsg, bpMaxLength)) {
                    if (!hasErrorOrWarning) hasErrorOrWarning = true;
                    std::cout << "  \U0000274C Error: Bullet points must not exceed " << bpMaxLength << " characters.\n";
                }
            } else {
                if (!hasErrorOrWarning) hasErrorOrWarning = true;
                std::cout << "  \U0000274C Error: " << bulletPointsCount << " bullet points are required. \n";
            }
        }

        if (!hasErrorOrWarning) {
            std::cout << "  \U0001F3C6 No warnings or errors found! \n";
        }
    }
}
