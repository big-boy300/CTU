#!/usr/bin/env bash 
 
while getopts "hz" opt; do
    case $opt in
    h) echo "This script defines if the entered path is a file, directory or a symlink. It can also archive a file with the help of -z flag."
    exit 0
    ;;
    z) TARVAR=1
    ;;
    \?) exit 2
    ;;
    esac
done   
 
FILES_TO_BE_ARCH=()
while read -r INPUT
do
    if [ "${INPUT:0:5}" = "PATH " ]; then
        PATH_TO_FILE=${INPUT#*PATH }
        if [[ -L "${PATH_TO_FILE}" ]]; then
            PATH_IN_SYMLINK=$(readlink "$PATH_TO_FILE")
            echo "LINK '${PATH_TO_FILE}' '${PATH_IN_SYMLINK}'"
        elif [[ -f "${PATH_TO_FILE}" ]]; then
            if [[ ! -r "${PATH_TO_FILE}" ]]; then
                exit 2
            fi 
            LINES_NUM=$(wc -l < "$PATH_TO_FILE")
            FIRST_LINE=$(awk 'NR==1 {print; exit}' "$PATH_TO_FILE")
            FILES_TO_BE_ARCH+=("${PATH_TO_FILE}")
            if [[ "${LINES_NUM}" -ne 0 ]]; then
                echo "FILE '${PATH_TO_FILE}' ${LINES_NUM} '${FIRST_LINE}'"
            else   
                echo "FILE '${PATH_TO_FILE}' ${LINES_NUM}"
            fi
        elif [[ -d "${PATH_TO_FILE}" ]]; then
                echo "DIR '${PATH_TO_FILE}'"
            else
            echo "ERROR '${PATH_TO_FILE}'" >&2
            exit 1  
        fi
    fi
done
 
if [[ "${TARVAR}" -eq 1 ]]; then
    tar czf output.tgz "${FILES_TO_BE_ARCH[@]}"
    RETVALUE=$?
    if [[ "${RETVALUE}" -ne 0 ]]; then
        exit 2
    fi
fi
