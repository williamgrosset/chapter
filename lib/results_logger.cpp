#include <ctype.h>
#include <boost/regex.hpp>
#include <lib/audit_helper.hpp>
#include <jamspell/spell_corrector.hpp>

void displayAuditResults(const std::string commit_msg) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model.bin");

    printf("************   \U00002699 Commit message audit...   ************\n\n");

    std::string commit_msg_mod = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commit_msg)));

    printf("Testing spell check...\n");
    printf("%s\n", commit_msg_mod.c_str());

    if (isFirstLetterCapitalized(commit_msg)) {
        printf("\U00002705 Success: First letter of summary must be capitalized. \n");
    } else {
        printf("\U0000274C Error: First letter of summary must be capitalized. \n");
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

        if (isDescriptionMinLength(commit_msg, 40)) {
            printf("\U00002705 Success: Description must be above 40 characters. \n");
        } else {
            printf("\U0000274C Error: Description must be above 40 characters. \n");
        }

        if (isDescriptionMaxLength(commit_msg, 72)) {
            printf("\U0000274C Error: Description must not exceed 72 characters. \n");
        } else {
            printf("\U00002705 Success: Description must not exceed 72 characters. \n");
        }
    } else {
        printf("\U0000274C Error: Description is required. \n");
    }

    if (containsBulletPoints(commit_msg, 3)) {
        printf("\U00002705 Success: 3 bullet points are required. \n");
    } else {
        printf("\U0000274C Error: 3 bullet points are required. \n");
    }

    printf("\n************        \U00002699 End of audit.        ************\n");
}
