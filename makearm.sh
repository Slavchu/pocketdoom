#!/bin/sh
cmake --debug-output -DCMAKE_BUILD_TYPE=Release -DTARGET_TYPE=ARM
make

