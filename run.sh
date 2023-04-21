#!/bin/bash
cmake -B build -DBUILD_TESTING=OFF
cmake --build build -j 8
./build/async_client 10 5

