#!/bin/bash

CONFIG_FILE="$HOME/.dorg.conf"

TEMPLATE_DIR="./src/templates/template.conf"
gcc -c src/parse.c -o src/parse.o
gcc -o dorg src/parse.o src/main.c
sudo mv dorg /usr/bin/
echo "Installation Successful!"

#default config

read -p "Do you want to create config file in your home directory? (y/n): " choice

echo "Nah gonna do it anyways!"

if [ ! -f "$CONFIG_FILE" ]; then 
  cp "$CONFIG_TEMPLATE_PATH" "$CONFIG_FILE"
  echo "Default Config Created in Home Directory!"
else
  echo "Config File Already Exists!"
fi

