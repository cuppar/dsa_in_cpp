#!/bin/env bash

if [[ $# -lt 1 ]]
then
	echo "need a arg(ex number)"
	exit 1
fi

exDir="ex$1"
mkdir "$exDir"
cd "$exDir"
cp ~/project/dsa_in_cpp/templates/main.cpp .
cp ~/project/dsa_in_cpp/templates/CMakeLists.txt .
