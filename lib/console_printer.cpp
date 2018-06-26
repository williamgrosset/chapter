#include <ctype.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rule_retriever.hpp>
#include <lib/rule_auditor.hpp>
#include <jamspell/spell_corrector.hpp>

/*
 * TODO:
 * + Remove success statements (add trophy statement)
 */

void displayAuditResults(nlohmann::json rulesJSON, const std::string commit_msg) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model.bin");

    printf("************   \U00002699 Commit message audit...   ************\n");

    // TODO:
    // std::string commit_msg_mod = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commit_msg)));
    // printf("Testing spell check...\n");
    // printf("%s\n", commit_msg_mod.c_str());

    if (requiresSummaryCapital(rulesJSON) && isFirstLetterCapitalized(commit_msg)) {
        std::cout << "\U00002705 Success: First letter of summary must be capitalized." << "\n";
    } else {
        std::cout << "\U0000274C Error: First letter of summary must be capitalized." << "\n";
    }

    if (requiresNitFormat(rulesJSON) && !containsCorrectNitFormat(commit_msg)) {
        std::cout << "\U0000274C Error: \"Nit:\" commits must have the correct format." << "\n";
    }

    if (requiresWIPFormat(rulesJSON) && !containsCorrectWIPFormat(commit_msg)) {
        std::cout << "\U0000274C Error: \"WIP:\" commits must have the correct format." << "\n";
    }

    int summaryMinLength = getSummaryMinLength(rulesJSON);
    if (isSummaryMinLength(commit_msg, summaryMinLength)) {
        std::cout << "\U0000274C Error: Summary must be above " << summaryMinLength << " characters.\n";
    } else {
        std::cout << "\U00002705 Success: Summary must be above " << summaryMinLength << " characters.\n";
    }

    int summaryMaxLength = getSummaryMaxLength(rulesJSON);
    if (isSummaryMaxLength(commit_msg, summaryMaxLength)) {
        std::cout << "\U0000274C Error: Summary must not exceed " << summaryMaxLength << " characters.\n";
    } else {
        std::cout << "\U00002705 Success: Summary must not exceed " << summaryMaxLength << " characters.\n";
    }

    if (requiresDescription(rulesJSON) && containsDescription(commit_msg)) {
        printf("\U00002705 Success: Description is required. \n");
        int descMinLength = getDescriptionMinLength(rulesJSON);
        int descMaxLength = getDescriptionMaxLength(rulesJSON);

        if (isDescriptionMinLength(commit_msg, descMinLength)) {
            std::cout << "\U0000274C Error: Description must be above " << descMinLength << " characters.\n";
        } else {
            std::cout << "\U00002705 Success: Description must be above " << descMinLength << " characters.\n";
        }

        if (isDescriptionMaxLength(commit_msg, descMaxLength)) {
            std::cout << "\U0000274C Error: Description must not exceed " << descMaxLength << " characters.\n";
        } else {
            std::cout << "\U00002705 Success: Description must not exceed " << descMaxLength << " characters.\n";
        }
    } else {
        printf("\U0000274C Error: Description is required. \n");
    }

    int bulletPointsVal = getBulletPoints(rulesJSON);
    if (containsBulletPoints(commit_msg, bulletPointsVal)) {
        std::cout << "\U00002705 Success: " << bulletPointsVal << " bullet points are required. \n";
    } else {
        std::cout << "\U0000274C Error: " << bulletPointsVal << " bullet points are required. \n";
    }

    printf("************        \U00002699 End of audit.        ************\n");
}
