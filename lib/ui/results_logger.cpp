#include <ctype.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rules/rule_retriever.hpp>
#include <lib/rules/rule_auditor.hpp>
#include <lib/rules/typo_handler.hpp>
#include <jamspell/spell_corrector.hpp>

using json = nlohmann::json;

void displayAuditResults(json rulesJSON, const std::string commitMsg) {
    getTypos(getSummary(commitMsg));

    std::cout << "************   \U00002699 Commit message audit...   ************\n\n";

    if (verifyIfRuleErrorExists(rulesJSON)) {
        std::cout << std::endl << "    Please fix your rules configuration file for" << std::endl
                  << "    correct attributes and value types." << std::endl << std::endl
                  << "    See https://github.com/williamgrosset/chapter/README.md" << std::endl;
    } else {
        int summaryMinLength = getSummaryMinLength(rulesJSON);
        int summaryMaxLength = getSummaryMaxLength(rulesJSON);
        bool reqNitFormat = requiresNitFormat(rulesJSON);
        bool reqWIPFormat = requiresWIPFormat(rulesJSON);
        bool reqDocFormat = requiresDocFormat(rulesJSON);
        bool hasErrorOrWarning = false;

        if (reqNitFormat && reqWIPFormat && reqDocFormat) {
            if (requiresSummaryCapital(rulesJSON) && !isFirstLetterCapitalized(commitMsg)) {
                if (!hasErrorOrWarning) hasErrorOrWarning = true;
                std::cout << "  \U0000274C Error: First letter of summary must be capitalized." << "\n";
            }
        }

        if (requiresNitFormat(rulesJSON) && !containsCorrectNitFormat(commitMsg)) {
            if (!hasErrorOrWarning) hasErrorOrWarning = true;
            std::cout << "  \U0000274C Error: \"Nit:\" commits must have the correct format." << "\n";
        }

        if (requiresWIPFormat(rulesJSON) && !containsCorrectWIPFormat(commitMsg)) {
            if (!hasErrorOrWarning) hasErrorOrWarning = true;
            std::cout << "  \U0000274C Error: \"WIP:\" commits must have the correct format." << "\n";
        }

        if (requiresDocFormat(rulesJSON) && !containsCorrectDocFormat(commitMsg)) {
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

        if (requiresDescription(rulesJSON)) {
            if (containsDescription(commitMsg)) {
                int descMinLength = getDescriptionMinLength(rulesJSON);
                int descMaxLength = getDescriptionMaxLength(rulesJSON);

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

        if (requiresBulletPoints(rulesJSON)) {
            int bulletPointsCount = getBulletPointsCount(rulesJSON);

            if (containsBulletPoints(commitMsg, bulletPointsCount)) {
                int bpMinLength = getBulletPointsMinLength(rulesJSON);
                int bpMaxLength = getBulletPointsMaxLength(rulesJSON);

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
            std::cout << "  \U0001F3C6 No errors or warnings found! \n";
        }
    }

    std::cout << "\n************        \U00002699 End of audit.        ************\n";
}
