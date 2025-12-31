#!/usr/bin/env bash
set -e

mv_glob () {
  local pattern="$1"
  local dest="$2"
  shopt -s nullglob
  local files=( $pattern )
  if ((${#files[@]})); then
    mkdir -p "$dest"
    git mv "${files[@]}" "$dest"
  fi
  shopt -u nullglob
}

mkdir -p include/core include/ds include/algo include/app \
         src/core src/ds src/algo src/app

# HEADERS: baogom -> include  (pattern PHẢI QUOTE)
mv_glob "baogom/core/*.h"    "include/core"
mv_glob "baogom/core/*.hpp"  "include/core"
mv_glob "baogom/ds/*.h"      "include/ds"
mv_glob "baogom/ds/*.hpp"    "include/ds"
mv_glob "baogom/algo/*.h"    "include/algo"
mv_glob "baogom/algo/*.hpp"  "include/algo"
mv_glob "baogom/app/*.h"     "include/app"
mv_glob "baogom/app/*.hpp"   "include/app"
mv_glob "baogom/*.h"         "include/core"
mv_glob "baogom/*.hpp"       "include/core"

# SOURCES: nguon -> src
[ -f nguon/main.cpp ] && git mv nguon/main.cpp src/ || true
[ -f nguon/main.c ]   && git mv nguon/main.c   src/ || true

mv_glob "nguon/core/*.c"     "src/core"
mv_glob "nguon/core/*.cpp"   "src/core"
mv_glob "nguon/ds/*.c"       "src/ds"
mv_glob "nguon/ds/*.cpp"     "src/ds"
mv_glob "nguon/algo/*.c"     "src/algo"
mv_glob "nguon/algo/*.cpp"   "src/algo"
mv_glob "nguon/app/*.c"      "src/app"
mv_glob "nguon/app/*.cpp"    "src/app"
mv_glob "nguon/*.c"          "src/app"
mv_glob "nguon/*.cpp"        "src/app"

echo "== DONE MOVE =="
git status
