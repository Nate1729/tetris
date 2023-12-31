#! /bin/bash

cmake -S . -B out/build/ \
	-DGLFW_BUILD_TESTS=OFF \
	-DGLFW_BUILD_DOCS=OFF && cp out/build/compile_commands.json .
