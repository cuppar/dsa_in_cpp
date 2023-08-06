#!/bin/env bash

if [[ $# -lt 1 ]]
then
	echo "need a arg(class number)"
	exit 1
fi

classDir="class$1"
mkdir "$classDir"
cd "$classDir"
cp ~/project/dsa_in_cpp/templates/main.cpp .
cp ~/project/dsa_in_cpp/templates/CMakeLists.txt .
