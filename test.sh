#!/usr/bin/env bash
# Build the program, run the sample session, diff against expected output.
set -euo pipefail
cd "$(dirname "$0")"
CXX="${CXX:-g++}"
bin="$(mktemp -u).rbt"
"$CXX" -std=c++17 -O2 -o "$bin" main.cpp main_helpers.cpp race.cpp red_black_tree.cpp
"$bin" < sample-input.txt > "$bin.out" 2>&1 || true
rm -f "$bin"
if diff <(tr -d '\r' < "$bin.out") <(tr -d '\r' < expected-output.txt) >/dev/null; then
    rm -f "$bin.out"; echo "PASS: output matches expected-output.txt"; exit 0
else
    echo "FAIL: output differs"; diff <(tr -d '\r' < "$bin.out") <(tr -d '\r' < expected-output.txt) | head -20
    rm -f "$bin.out"; exit 1
fi
