#!/bin/bash

cd ~/Documenti/progetto

while true; do
  inotifywait -e modify,create,delete,move -r . > /dev/null 2>&1

  if ! git diff --quiet || ! git diff --cached --quiet; then
    git add .
    git commit -m "Backup automatico LIVE - $(date '+%Y-%m-%d %H:%M:%S')"
    git push
    notify-send "Backup Git" "Backup effettuato subito dopo una modifica ✅"
  fi
done

