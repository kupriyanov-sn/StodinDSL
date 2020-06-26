#!/bin/bash
REAL_PATH=$(realpath "prime_sieves.stdn")
../../stodin-compiler/compile ${REAL_PATH} -run
