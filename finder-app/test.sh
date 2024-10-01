#!/bin/bash

export CROSS_COMPILE=aarch64-none-linux-gnu-

echo $PATH
which ${CROSS_COMPILE}-gcc
make clean
make "CROSS_COMPILE="${CROSS_COMPILE}
