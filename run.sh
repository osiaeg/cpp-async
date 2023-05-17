#!/bin/bash
cmake -B cmake-build-debug -DBUILD_TESTING=OFF
cmake --build cmake-build-debug -j 16
./cmake-build-debug/async_server &
./cmake-build-debug/async_client 10 10 &
fg %1

