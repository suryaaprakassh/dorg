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

### 3.usage

- create a .dorg.conf file in your home directory

- copy the example conf file

## Example .dorg.conf

```
Videos=(mp4|avi)
Photos=(mp3|wav)
Installers=(deb|exe)
```

> **PROTIP**: don't leave any white space character in your config file or a empty line
> if so, you will get a good old segfault good luck fixing it.

## Help

`dorg -h`
