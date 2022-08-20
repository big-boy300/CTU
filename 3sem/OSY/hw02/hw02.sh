#!/usr/bin/env bash
 
while getopts "habcd:" opt; do
    case $opt in
    h) echo "This script performs a number of functions: 
    -a outputs all pdf files in current directory;
    -b outputs all lines from text that begin with number;
    -c outputs all sentences from text on separate lines;
    -d <pattern>: inserts pattern before filename in all #include directives."
    exit 0
    ;;
    a) grep -E -o '.+\.[Pp][Dd][Ff]$' <<< "$(ls -a)"
    exit 0
    ;;
    b) cat - | grep -E -o "^[+\-]?[0-9]+.+" | sed -E 's/^([+-])?[0-9]+//'
    exit 0
    ;;
    c) cat - | tr '\n' ' '  | grep -E -o "[[:alpha:]][^\.!?]*[\.!?]"
    exit 0
    ;;
    d)
    TMPFILE=$(mktemp)
    cat > "${TMPFILE}"
    INCLUDE_FOUND="false"
    if grep -E -q ".*include.*" < "$TMPFILE"; then
        INCLUDE_FOUND="true"
    fi
    if [[ ${INCLUDE_FOUND} = "false" ]]; then
        cat "$TMPFILE"
        rm "$TMPFILE"
        exit 0;
    fi
    if grep -E -q "#include[[:space:]]*\".+>|#include[[:space:]]*<.+\"" < "$TMPFILE"; then
        cat "$TMPFILE"
        rm "$TMPFILE"
        exit 0;
    fi
    FINAL_ARG=$(tr -d '/' <<< "${OPTARG}")
    (sed -E 's/</<'"$FINAL_ARG"'\//' < "$TMPFILE" |  sed -E 's/"/"'"$FINAL_ARG"'\//') || sed -E 's/"#include[[:space:]]*</"#include <'"$FINAL_ARG"'\//' < "$TMPFILE"
    rm "$TMPFILE"
    exit 0  
    ;;
    \?) echo "This script performs a number of functions: 
    -a: outputs all pdf files in current directory;
    -b: outputs all lines from text that begin with number;
    -c: outputs all sentences from text on separate lines;
    -d <pattern>: inserts pattern before filename in all #include directives."
    exit 1
    ;;
    esac
done
