@echo off

del /F /Q *.aux *.log *.toc *.pdf
if %errorlevel% neq 0 goto build_end

python build-contents.py > contents.tex
if %errorlevel% neq 0 goto build_end

pdflatex trd.tex && pdflatex trd.tex
if %errorlevel% neq 0 goto build_end

del /F /Q *.aux *.log *.toc contents.tex
if %errorlevel% neq 0 goto build_end

:build_end
