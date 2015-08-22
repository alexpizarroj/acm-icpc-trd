#!/bin/bash

set -e

rm -f *.aux *.log *.toc *.pdf

python build-contents.py > contents.tex

rubber -d trd.tex

rm -f *.aux *.log *.toc contents.tex
