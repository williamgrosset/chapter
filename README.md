...**chapter** logo...

## TODO
+ Integrate with an open source proof-reading tool (e.g https://github.com/bakwc/JamSpell)
+ Complete logic for all rules
+ Improve error handling for different cases and messages
+ Clean-up `console_printer` and all nits
+ Execute audit program on a `post-commit` hook 
+ Add terminal UI for progress and success/errors
+ Setup test suite
+ Update `README.md`: ToC, content, overview, and add logo
+ Add GitHub badge to be downloaded (similar to Prettier)
+ Add other GitHub badges (e.g code coverage, build status)

## Overview
..

## Installation
+ Move executable in `$HOME/bin`
+ Update bash script for `post-commit`
+ Ensure permissions are set `chmod +x .git/hooks/post-commit`
+ Ability to install directly via `brew` or shell script
+ ...

### JSON helper
+ `brew tap nlohmann/json` && `brew install nlohmann_json`

## Usage
+ How to run script manually (?)
+ Run option `--verbose` for more details on commands (?)
+ ...

## Rules
+ Show example of warning/error
+ Rule in `COMMIT_MSG_RULES.json`
+ ...

### Typos
...

### Summary capitalization
...

### Summary length
...

### Description required
...

### Description length
...

### Bullet points 
...

### Documentation format
...

### Nit format
...

### WIP format
...

### Rules TODO
+ JSON file (or alike for C++ projects)
+ No-typos
+ Max-character length
+ Capitalization of each sentence
+ Require summary (character length)
+ Require X bullet points (hyphen, astericks, plus)
+ Explicit rule for `Nit: ...` and `WIP:...` (format, character length)
+ Require UTF-8 characters
+ No Emoji
+ Include JIRA ticket number

## Articles
See [ARTICLES.md](https://github.com/williamgrosset/chapter/blob/master/ARTICLES.md).

## Future
See [TODO.md](https://github.com/williamgrosset/chapter/blob/master/TODO.md).

## Contributing 
See [CONTRIBUTING.md](https://github.com/williamgrosset/chapter/blob/master/CONTRIBUTING.md).

## Internal Integration 
Chapter was integrated into this repository at commit message [#XXX](https://github.com/williamgrosset/chapter.git).

## Disclaimer
Chapter is in early stages of development — use with caution.

## License
[MIT](https://github.com/williamgrosset/chapter/blob/master/LICENSE)
