#!/bin/bash

CXXFLAGS="-std=c++17 -O3 -pipe -static"
WARNFLAGS="-W -Wall -Wextra"
HSFLAGS="-O"

function print_help() {
  echo "Usage: $0 <args>"
  echo "Available <args>:"
  echo " - [compile|c]          - compile the source code"
  echo " - [benchmark|b|run|r]  - run the benchmark"
  echo " - [clean]              - clean the directory"
}

function check_deps() {
  ldconfig --help 1>/dev/null 2>&1
  if [ $? -ne 0 ]; then
    echo "- Please install 'ldconfig'."
    exit 1
  fi

  ldconfig -p | grep -q "libboost_system.so"
  if [ $? -ne 0 ]; then
    echo "- Please install 'boost'."
    exit 1
  fi
}

function clean() {
  rm -rf ./{build,result}
}

function compile() {
  check_deps

  g++ ${CFLAGS} ${WARNFLAGS} ./c++17/*.cpp -o ./build/exe-c++
  ghc ${HSFLAGS} ./haskell/*.hs -o ./build/exe-hs && rm -f ./haskell/*{.hi,.o}
}

function benchmark() {
  mkdir -p ./result

  for exe in ./build/*; do
    name=$(basename ${exe})

    hyperfine --shell=none --style none -i --warmup 1 -r 10 \
      --export-json "./result/${name}.json" \
      --output "./result/${name}.output" \
      "${exe}"
  done
}

if [ ! -d "./c++17" ]; then
  echo "- ERROR Please cd the root directory first."
  exit 1
fi

if [ $# -eq 0 ]; then
  print_help
  exit
fi

mkdir -p ./build

case "${1}" in
"clean")
  clean
  ;;
"compile") ;&
"c")
  compile
  ;;
"benchmark") ;&
"b") ;&
"run") ;&
"r")
  compile
  benchmark
  ;;
*)
  echo "- Invalid args: ${0} ${1}"
  print_help
  ;;
esac
