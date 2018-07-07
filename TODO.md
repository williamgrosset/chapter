## TODO
### Before Open Source
+ Integrate with an open source proof-reading tool (e.g https://github.com/bakwc/JamSpell)
+ Test location for `model_en.bin.spell`
+ Allow for any rule to not exist in `COMMIT_MSG_RULES.json`
+ General run through for nits and regex logic
+ Setup test suite
+ Update `README.md`: demo
+ Simplify installation instructions
+ Complete other docs

### Long Term
+ Add ability to toggle server-side Git hook to require commit message changes
+ Ruling support for different size of changes (per commit)
+ Ruling support for excluded strings when identifying typos (allow regex patterns)

### Rules
+ Require issue number
+ 72-line break for description
+ No emoji
+ Exclude requirement of description/bullet points if `nit` commit

### `README.md` badges
+ Build status
+ Code coverage %
+ Code size
