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

    std::string commit_msg_mod = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commit_msg)));

    printf("Testing spell check...\n");
    printf("%s\n", commit_msg_mod.c_str());

    if (requiresSummaryCapital(rulesJSON) && isFirstLetterCapitalized(commit_msg)) {
        printf("\U00002705 Success: First letter of summary must be capitalized. \n");
    } else {
        printf("\U0000274C Error: First letter of summary must be capitalized. \n");
    }

    if (requiresNitFormat(rulesJSON) && !containsCorrectNitFormat(commit_msg)) {
        printf("\U0000274C Error: \"Nit:\" commits must have the correct format. \n");
    }

    if (requiresWIPFormat(rulesJSON) && !containsCorrectWIPFormat(commit_msg)) {
        printf("\U0000274C Error: \"WIP:\" commits must have the correct format. \n");
    }

    if (isSummaryMinLength(commit_msg, getSummaryMinLength(rulesJSON))) {
        printf("\U0000274C Error: Summary must be above 18 characters. \n");
    } else {
        printf("\U00002705 Success: Summary must be above 18 characters. \n");
    }

    if (isSummaryMaxLength(commit_msg, getSummaryMaxLength(rulesJSON))) {
        printf("\U0000274C Error: Summary must not exceed 50 characters. \n");
    } else {
        printf("\U00002705 Success: Summary must not exceed 50 characters. \n");
    }

    if (requiresDescription(rulesJSON) && containsDescription(commit_msg)) {
        printf("\U00002705 Success: Description is required. \n");

        if (isDescriptionMinLength(commit_msg, getDescriptionMinLength(rulesJSON))) {
            printf("\U0000274C Error: Description must be above 40 characters. \n");
        } else {
            printf("\U00002705 Success: Description must be above 40 characters. \n");
        }

        if (isDescriptionMaxLength(commit_msg, getDescriptionMaxLength(rulesJSON))) {
            printf("\U0000274C Error: Description must not exceed 72 characters. \n");
        } else {
            printf("\U00002705 Success: Description must not exceed 72 characters. \n");
        }
    } else {
        printf("\U0000274C Error: Description is required. \n");
    }

    if (containsBulletPoints(commit_msg, getBulletPoints(rulesJSON))) {
        printf("\U00002705 Success: 3 bullet points are required. \n");
    } else {
        printf("\U0000274C Error: 3 bullet points are required. \n");
    }

    printf("************        \U00002699 End of audit.        ************\n");
}
