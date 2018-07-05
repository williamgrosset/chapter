<p align="center">
  <br />
  <img src="https://fontmeme.com/permalink/180705/a447e6adbbc9c3f3c5f967c39ed0f7a1.png" alt="old-english-fonts" border="0">
  <br /><br />
  <img src="https://img.shields.io/badge/commit%20style-chapter-red.svg" />
</p>

## Table of Contents
- [Overview](#overview)
- [Usage](#usage)
- [Rules](#rules)
  * [Typos](#typos)
  * [No Emoji](#no-emoji)
  * [Summary Capitalization](#summary-capitalization)
  * [Summary Length](#summary-length)
  * [Documentation Format](#documentation-format)
  * [Nit Format](#nit-format)
  * [WIP Format](#wip-format)
  * [Description Length](#description-length)
  * [Bullet Points Count](#bullet-points-count)
  * [Bullet Points Length](#bullet-points-length)
- [Articles](#articles)
- [Future](#future)
- [Contributing](#contributing)
- [Internal Integration](#internal-integration)
- [Disclaimer](#disclaimer)
- [License](#license)

## Overview
Chapter is a open-source, C++ tool that provides conventions for writing Git commit messages amongst other developers. You determine your own conventions and structure of messages through custom rules defined below. Adding this tool to your project can help ensure that commit messages become concise, standardized, and informative.

## Usage
0. JSON helper: `brew tap nlohmann/json` && `brew install nlohmann_json`
1. Compile and and move executable (`chapter.o`) into your `$HOME/` directory:
```bash
make
mv ./chapter.o $HOME/
2. Update the `post-commit` hook:
```bash
#!/bin/bash
$HOME/chapter.o
```
3. Create the `COMMIT_MSG_RULES.json` file in your project directory.

## Rules
Rules are defined in the `COMMIT_MSG_RULES.json` file that will be in your current project's top-level directory. Rules determine the structure and behaviour of commit messages. Rules can be turned-off and have their values modified to preference. The entire list of rules defined in the JSON file can be seen below:
```json
{
    "bullet_points": {
        "count": 3,
        "max_len": 50,
        "min_len": 12
    },
    "desc": {
        "max_len": 72,
        "min_len": 40
    },
    "doc_format": false,
    "identify_typos": true,
    "nit_format": true,
    "sum_capital": true,
    "sum_max_len": 50,
    "sum_min_len": 18,
    "wip_format": true
}
```

### Typos
...

### No Emoji
...

### Summary Capitalization
...

### Summary Length
...

### Documentation Format
...

### Nit Format
...

### WIP Format
...

### Description Length
...

### Bullet Points Count
...

### Bullet Points Length
...

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
