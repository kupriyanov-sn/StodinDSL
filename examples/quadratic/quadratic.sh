#!/bin/bash
REAL_PATH=$(realpath "quadratic.stdn")
../../stodin-compiler/compile ${REAL_PATH} -run
