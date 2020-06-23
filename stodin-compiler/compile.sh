#!/bin/bash
make -f MakefileLin all
rm *.o
cp ../compile/config_lin.cfg config.cfg
