#!/bin/sh

pandoc --filter pandoc-citeproc --bibliography=refs.bib --number-sections -s -o ex2.pdf ex2.md
pandoc -o ex2_pres.pdf -t beamer ex2.md