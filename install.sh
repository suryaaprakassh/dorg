#!/bin/bash
set -xe
gcc -c src/parse.c -o src/parse.o
gcc -o dorg src/parse.o src/main.c
sudo mv dorg /usr/bin/
echo "Installation Successful!"
