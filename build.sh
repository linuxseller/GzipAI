#!/bin/bash

set -xe

clang main.c -o work -Wall -Wextra -Werror -pedantic
./work
