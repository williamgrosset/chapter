...**chapter** logo...

## TODO
+ Support location for appropriate `.git` directory location for project
+ Check last committed that is not on remote (current branch)
+ Integrate with an open source proof-reading tool (e.g https://github.com/bakwc/JamSpell)
+ Execute audit program on a `post-commit` hook 
+ Add a config file for supporting rules (default includes all rules)
+ Option to ignore and push regardless of errors
+ Add terminal UI for progress and success/errors
+ Setup test suite
+ Update `README.md`: ToC, project name, overview, and add logo
+ Add GitHub badge to be downloaded (similar to Prettier)

## Overview
..

## Installation
+ Move executable in `$HOME/bin` (?)
+ Update bash script for `post-commit`
+ Ensure permissions are set `chmod +x .git/hooks/post-commit`
+ Add ability to install via `brew`
+ ...

### JSON helper
+ `brew tap nlohmann/json` && `brew install nlohmann_json`

## Usage
+ How to run script manually
+ Run option `--verbose` for more details on commands
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
+ Positive integers only
+ ...

### Description required
...

### Description length
...

### Bullet points required
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

## Future
See [TODO.md](https://github.com/williamgrosset/chapter/blob/master/TODO.md).

## Contributing 
See [CONTRIBUTING.md](https://github.com/williamgrosset/chapter/blob/master/CONTRIBUTING.md).

## Internal Integration 
Chapter is integrated into this repository at commit message [#154](https://github.com/williamgrosset/chapter.git).

## License
[MIT](https://github.com/williamgrosset/chapter/blob/master/LICENSE)
