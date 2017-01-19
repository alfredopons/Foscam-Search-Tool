#!/bin/bash

# Alfredo Pons - 2017 - Indent with my preferences
# alfredo.pons@gmail.com


FILES="src/*.cpp src/*.hpp"
FILES_TO_DELETE="src/*.orig"

astyle -c -v -s2 --style=gnu --mode=c --lineend=linux --convert-tabs --delete-empty-lines --pad-paren-out --unpad-paren --indent-namespaces --pad-header --break-blocks --pad-oper --indent-preprocessor --indent-labels --indent-cases  --indent-switches --indent-namespaces --indent-classes --indent-col1-comments --delete-empty-lines $FILES 
	
rm -f $FILES_TO_DELETE
