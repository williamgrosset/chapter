#include <ctype.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rules/rule_retriever.hpp>
#include <lib/rules/rule_auditor.hpp>
#include <jamspell/spell_corrector.hpp>

/*
 * TODO:
 * + Check all rule types in config file before running audit (in main.cpp)
 * + Remove success statements (add (\U0001F3C6) trophy statement for no warnings/errors)
 */

void displayAuditResults(nlohmann::json rulesJSON, const std::string commitMsg) {
    std::cout << "************   \U00002699 Commit message audit...   ************\n\n";

    if (hasRuleErrorThrown(rulesJSON)) {
        std::cout << "\nPlease fix your rules configuration file for correct attributes and value types.\n";
    } else {
      int summaryMinLength = getSummaryMinLength(rulesJSON);
      int summaryMaxLength = getSummaryMaxLength(rulesJSON);
      int bulletPointsCount = getBulletPointsCount(rulesJSON);
      bool reqNitFormat = requiresNitFormat(rulesJSON);
      bool reqWIPFormat = requiresWIPFormat(rulesJSON);
      bool reqDocFormat = requiresDocFormat(rulesJSON);

      if (reqNitFormat && reqWIPFormat && reqDocFormat) {
          if (requiresSummaryCapital(rulesJSON) && !isFirstLetterCapitalized(commitMsg)) {
              std::cout << "\U0000274C Error: First letter of summary must be capitalized." << "\n";
          }
      }

      if (requiresNitFormat(rulesJSON) && !containsCorrectNitFormat(commitMsg)) {
          std::cout << "\U0000274C Error: \"Nit:\" commits must have the correct format." << "\n";
      }

      if (requiresWIPFormat(rulesJSON) && !containsCorrectWIPFormat(commitMsg)) {
          std::cout << "\U0000274C Error: \"WIP:\" commits must have the correct format." << "\n";
      }

      if (requiresDocFormat(rulesJSON) && !containsCorrectDocFormat(commitMsg)) {
          std::cout << "\U0000274C Error: \"Documentation:\" commits must have the correct format." << "\n";
      }

      if (isSummaryMinLength(commitMsg, summaryMinLength)) {
          std::cout << "\U0000274C Error: Summary must be above " << summaryMinLength << " characters.\n";
      }

      if (isSummaryMaxLength(commitMsg, summaryMaxLength)) {
          std::cout << "\U0000274C Error: Summary must not exceed " << summaryMaxLength << " characters.\n";
      }

      if (requiresDescription(rulesJSON)) {
          if (containsDescription(commitMsg)) {
              int descMinLength = getDescriptionMinLength(rulesJSON);
              int descMaxLength = getDescriptionMaxLength(rulesJSON);

              if (isDescriptionMinLength(commitMsg, descMinLength)) {
                  std::cout << "\U0000274C Error: Description must be above " << descMinLength << " characters.\n";
              }

              if (isDescriptionMaxLength(commitMsg, descMaxLength)) {
                  std::cout << "\U0000274C Error: Description must not exceed " << descMaxLength << " characters.\n";
              }
          } else {
              std::cout << "\U0000274C Error: Description is required. \n";
          }
      }

      if (requiresBulletPoints(rulesJSON)) {
          if (containsBulletPoints(commitMsg, bulletPointsCount)) {
              int bpMinLength = getBulletPointsMinLength(rulesJSON);
              int bpMaxLength = getBulletPointsMaxLength(rulesJSON);

              if (isBulletPointsMinLength(commitMsg, bpMinLength)) {
                  std::cout << "\U0000274C Error: Bullet points must be above " << bpMinLength << " characters.\n";
              }

              if (isBulletPointsMaxLength(commitMsg, bpMaxLength)) {
                  std::cout << "\U0000274C Error: Bullet points must not exceed " << bpMaxLength << " characters.\n";
              }
          } else {
              std::cout << "\U0000274C Error: " << bulletPointsCount << " bullet points are required. \n";
          }
      }
    }

    std::cout << "\n************        \U00002699 End of audit.        ************\n";
}
