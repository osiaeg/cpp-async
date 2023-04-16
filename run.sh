#!/bin/bash
cmake -B build -DBUILD_TESTING=OFF
cmake --build build -j 8

