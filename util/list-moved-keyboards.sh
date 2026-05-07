#!/usr/bin/env bash

echo "This might take a while... let it sit." >&2

git cherry upstream/master upstream/develop | awk '{print $2}' | while read sha1; do
    git diff --name-status -M25 ${sha1}^..${sha1} | grep 'keyboards/' | grep '^R' | grep -E '(info|keyboard).json'
done | sed -e 's@keyboards/@@g' -e 's@/info.json@@g' -e 's@/keyboard.json@@g' | sort -k+2 | while IFS=$'\n' read line; do
    if [[ $(echo $line | awk '{print $2}') != $(echo $line | awk '{print $3}') ]]; then
        echo $line
    fi
done | sort -k+2 | awk '{printf "| %s | %s |\n", $2, $3}' | column -t | sort
