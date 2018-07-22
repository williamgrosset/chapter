<p align="center">
  <br />
  <img src="https://fontmeme.com/permalink/180705/a447e6adbbc9c3f3c5f967c39ed0f7a1.png" alt="old-english-fonts" border="0">
  <br /><br />
  <img src="https://img.shields.io/github/license/williamgrosset/chapter.svg" />
  <img src="https://img.shields.io/github/last-commit/williamgrosset/chapter.svg" />
  <img src="https://img.shields.io/badge/commit%20style-chapter-red.svg" />
</p>

## Table of Contents
- [Demo](#demo)
- [Overview](#overview)
- [Usage](#usage)
- [Rules](#rules)
  * [Typos](#typos)
  * [Summary Capitalization](#summary-capitalization)
  * [Summary Length](#summary-length)
  * [Documentation Format](#documentation-format)
  * [Nit Format](#nit-format)
  * [WIP Format](#wip-format)
  * [Description](#description)
  * [Bullet Points](#bullet-points)
- [Articles](#articles)
- [Future](#future)
- [Contributing](#contributing)
- [Internal Integration](#internal-integration)
- [Disclaimer](#disclaimer)
- [License](#license)

## Demo
![Chapter](https://github.com/williamgrosset/chapter/blob/master/demo.gif "Demo")

## Overview
**SEE [DISCLAIMER](#disclaimer)**. Chapter is an open-source, C++ tool that provides conventions for Git commit messages. After every `git commit`, an audit script will display warnings and errors in your terminal regarding your commit message. Choose your message preferences through a set of custom rules defined in a `.json` file. Adding this tool to your project can help ensure that commit messages become standardized and informative.

## Usage
1. Clone repository, compile, and move files into your `$HOME/` directory:
```bash
$ git clone https://williamgrosset/chapter.git && cd chapter/
$ make fresh
$ mv chapter.o en.bin $HOME/
```
2. Update the `post-commit` hook in your project directory (`project/.git/hooks/post-commit`):
```bash
#!/bin/bash
$HOME/chapter.o
```
3. Create the `COMMIT_MSG_RULES.json` file in your project directory. See [Rules](#rules) below.

### Badge
Show the world that you use Chapter: [![commit style: chapter](https://img.shields.io/badge/commit%20style-chapter-red.svg)](https://github.com/williamgrosset/chapter)
```md
[![commit style: chapter](https://img.shields.io/badge/commit%20style-chapter-red.svg)](https://github.com/williamgrosset/chapter)
```

## Rules
Rules are defined in the `COMMIT_MSG_RULES.json` file that will be in your project's top-level directory. Rules determine the structure and behaviour of commit messages. Rules can be turned-off and have their values modified to preference. The entire list of rules defined in the JSON file can be seen below:
```json
{
    "sum_max_len": 50,
    "sum_min_len": 18,
    "desc": {
        "max_len": 110,
        "min_len": 40
    },
    "bullet_points": {
        "count": 3,
        "max_len": 70,
        "min_len": 24
    },
    "doc_format": true,
    "identify_typos": true,
    "nit_format": true,
    "sum_capital": true,
    "wip_format": true
}
```

### Typos
Identify typos via a trained neural net from [JamSpell](https://github.com/bakwc/JamSpell). Rule must be a **boolean**:
```json
"identify_typos": true
```

### Summary Capitalization
Require summary to be capitalized. Rule must be a **boolean**:
```json
"sum_capital": true
```

### Summary Length
Define maximum and minimum length of summary. Both rules are **required** and must be a positive **integer**:
```json
"sum_max_len": 50,
"sum_min_len": 18
```

### Documentation Format
Require formatting for messages related to documentation. Rule must be a **boolean**:
```json
"doc_format": true
```

#### Format
```md
Docs: Insert summary text here 
```

### Nit Format
Require formatting for messages related to nits. Rule must be a **boolean**:
```json
"nit_format": true
```

#### Format
```md
Nit: Insert summary text here 
```

### WIP Format
Require formatting for messages related to work in progress. Rule must be a **boolean**:
```json
"wip_format": true
```

#### Format
```md
WIP: Insert summary text here 
```

### Description
Define maximum and minimum length of description. Rule must not exist (description not required) or be an **object** with `max_length` and `min_length`, both as positive **integers**:
```json
"desc": {
    "max_len": 72,
    "min_len": 40 
}
```

#### Format
```md
Insert summary text here

Insert description here regarding more details about the commit changes.
Identifying typos works best when there are full sentences.
```

### Bullet Points
Define count, maximum and minimum length of bullet points. Rule must not exist (bullet points not required) or be an **object** with `count`, `max_length`, and `min_length`, all as positive **integers**:
```json
"bullet_points": {
    "count": 3,
    "max_len": 80,
    "min_len": 12
}
```

#### Format
Bullet points are on their own line starting with one of the characters: `+`, `*`, `-`.
```md
Insert summary text here

Insert description here regarding more details about the commit changes.
Identifying typos works best when there are full sentences.

+ Key points regarding feature.
+ Shorter than summary.
+ Any other details.
```

## Articles
See [ARTICLES.md](https://github.com/williamgrosset/chapter/blob/master/ARTICLES.md).

## Future
See [TODO.md](https://github.com/williamgrosset/chapter/blob/master/TODO.md).

## Contributing 
See [CONTRIBUTING.md](https://github.com/williamgrosset/chapter/blob/master/CONTRIBUTING.md).

## Internal Integration 
Chapter was integrated into this repository at commit message [#XXX](https://github.com/williamgrosset/chapter.git).

## Disclaimer
Chapter is in early stages of development (**writing tests**) — use with caution.

## License
[MIT](https://github.com/williamgrosset/chapter/blob/master/LICENSE)
