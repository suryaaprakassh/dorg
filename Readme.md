# Dorg Docs

## PS:

    | ONLY SUPPORTED FOR LINUX

## Description

    + A useless file organiser written in c
    + Why I chose c as my language only god knows
    + Will it work without any bugs only god knows
    + Just run the executable to see

## Installation

### 1. Clone the Repository

```
git clone https://github.com/suryaaprakassh/dorg && cd dorg
```

### 2. Install

```bash
bash install.sh
```

or

```bash
./install.sh
```

### 3.Usage

- create a .dorg.conf file in your home directory

- copy the example conf file

### 4.Rules(could not find a better word)

- write the extensions within paranthesis() and seperated by |
- write the regex within //
- dont leave any white space between = (because there is no native trim function
  in c)
- dont leave any empty line in the config file
- moving priority depends upon the order in the config file, so the topmost line
  in the config have highest priority

## Example .dorg.conf

```
Videos=(mp4|avi)
Photos=(mp3|wav)
Installers=(deb|exe)
notes=/notes.*/
```

> **PROTIP**: don't leave any white space character in your config file or a
> empty line if so, you will get a good old segfault good luck fixing it.

## Help

`dorg -h`
