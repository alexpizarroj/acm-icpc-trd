#!/bin/bash

set -e

rm -f *.aux *.log *.toc *.pdf

rubber -d trd.tex

rm -f *.aux *.log *.toc
