#!/usr/bin/env bash
set -e

EXE="./build/undo.exe"
mkdir -p tests/out
PASS=0
FAIL=0

run_case () {
  local name="$1"
  echo "==> $name"

  "$EXE" < <(printf "run tests/input/$name.txt\nexit\n") > "tests/out/$name.out"

  if diff -u "tests/expected/$name.out" "tests/out/$name.out" >/dev/null; then
    echo "PASS $name"
    PASS=$((PASS+1))
  else
    echo "FAIL $name"
    FAIL=$((FAIL+1))
  fi
}

run_case "case01_basic"
run_case "case02_undo"
run_case "case03_redo_clear"
run_case "case04_save_load"
run_case "case05_search"
run_case "case06_report"

echo "--------------------"
echo "PASS=$PASS FAIL=$FAIL"
exit $FAIL
