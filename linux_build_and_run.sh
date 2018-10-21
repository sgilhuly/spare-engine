#!/bin/bash

function run_command() {
  tput bold
  tput setaf 6
  echo "\$ $1"
  tput sgr0
  $1 || exit 1
}

run_command "cmake -H. -Bbuild"
run_command "cmake --build build -- -j3"
run_command "build/spare-engine"
