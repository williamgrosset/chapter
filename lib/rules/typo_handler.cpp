#include <ctype.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rules/rule_retriever.hpp>
#include <lib/rules/rule_auditor.hpp>
#include <jamspell/spell_corrector.hpp>

void displayTypos(const std::string commitMsg) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model.bin");
    std::string msg = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commitMsg)));
    printf("%s\n\n\n", msg.c_str());
}
