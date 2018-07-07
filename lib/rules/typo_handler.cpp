#include <locale>
#include <codecvt>
#include <ctype.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rules/rule_retriever.hpp>
#include <lib/rules/rule_auditor.hpp>
#include <jamspell/spell_corrector.hpp>

/*
 * TODO:
 * Must be lowercase for best identification
 */

void displayTypos(const std::string commitMsg) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model_en.bin");
    std::string msg = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commitMsg)));
    printf("%s\n\n\n", msg.c_str());
}

/*
 * getTypos(getSummary(commitMsg))
 * getTypos(getDescription(commitMsg))
 * getTypos(getBulletPoints(commitMsg))
 */
std::vector<std::string> getTypos(const std::string msgPartial) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model_en.bin");

    // lowercase string and trim \n

    // convert string to wstring
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring msgWStr = converter.from_bytes(msgPartial);

    // split wstring on empty space
    std::wstring temp;
    std::vector<std::wstring> parts;
    std::wstringstream ws_stream(msgWStr);
    while (std::getline(ws_stream, temp, L' ')) {
        parts.push_back(temp);
    }

    std::vector<std::string> typos;
    for (size_t i = 0; i < parts.size(); i++) {
        std::vector<std::wstring> candidates = corrector.GetCandidates(parts, i);

        if (candidates.size() > 0) {
            // Compare with best-case candidate
            if (candidates[0].compare(parts[i]) != 0) {
                // convert wstring to string
                typos.push_back(converter.to_bytes(parts[i]));
            }
        }
    }

    for (std::string& str : typos) {
        std::cout << str << std::endl;
    }

    return typos;
}
