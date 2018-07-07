#include <ctype.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rules/rule_retriever.hpp>
#include <lib/rules/rule_auditor.hpp>
#include <jamspell/spell_corrector.hpp>

/*
 * TODO:
 * Must be lowercase for best identification
 * check summary typos and return typo
 * check description typos and return typo 
 * check bullet point typos and return typo 
 */

void displayTypos(const std::string commitMsg) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model.bin");
    std::string msg = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commitMsg)));
    printf("%s\n\n\n", msg.c_str());
}

std::vector<std::wstring> getTypos(const std::string commitMsg) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model.bin");
    std::vector<std::wstring> typos;
    typos = corrector.GetCandidates({L"fixes", L"strange", L"bug"}, 0);

    for (std::wstring& str : typos) {
        std::wcout << str << std::endl;
    }

    return typos;
}
