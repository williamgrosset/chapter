## TODO
### Before Open Source
+ Integrate with an open source proof-reading tool (e.g https://github.com/bakwc/JamSpell)
+ Complete logic for all rules
+ Improve error handling for different cases and messages
+ Clean-up `console_printer` and all nits
+ Execute audit program on a `post-commit` hook 
+ Add terminal UI for progress and success/errors
+ Setup test suite
+ Update `README.md`: demo
+ Add other GitHub badges (e.g code coverage, build status)

### Badges
+ build passing
+ coverage
+ code size
+ license (MIT)
+ last commit
+ tweet

### Long Term
+ Add ability to toggle server-side Git hook to require commit message changes
+ Ruling support for different size of changes (per commit)
+ Ruling support for excluded strings when identifying typos (allow regex patterns)

### Rules
+ Require issue number
+ Exclude requirement of description/bullet points if `nit` commit
+ 72-line break for description
