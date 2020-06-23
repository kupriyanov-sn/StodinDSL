#!/bin/bash
REAL_PATH=$(realpath "guesser.stdn")
../../stodin-compiler/compile ${REAL_PATH} -run
