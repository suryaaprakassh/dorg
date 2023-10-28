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

- A default config file will be created in home directory
- make your changes there

### 4.Rules(could not find a better word)

- write the extensions within paranthesis() and seperated by |
- write the regex within //
- moving priority depends upon the order in the config file, so the topmost line
  in the config have highest priority
- by default a folder named Others will be created
- any file that doesnt match the config will be moved to Others

## Example .dorg.conf

```
Videos=(mp4|avi)
Photos=(mp3|wav)
Installers=(deb|exe)
notes=/notes.*/
```

> **PROTIP**: If you find a bug fix it!

## Help

`dorg -h`
