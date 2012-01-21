#!/bin/sh

./clean.sh
./runswig.sh

python setup.py build
