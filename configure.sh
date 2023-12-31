#! /bin/bash

if test -d ! out/build/; then
	mkdir -p out/build
fi

cmake -S . -B out/build/ \
	-DGLFW_BUILD_TESTS=OFF \
	-DGLFW_BUILD_DOCS=OFF && cp out/build/compile_commands.json .
