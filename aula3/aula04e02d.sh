#!/bin/bash
function compare()
{
    if [ $1 -eq $2 ]; then
        echo "$1 são iguais $2"
    else
        if [ $1 -gt $2 ]; then
            echo "$1 é maior que $2"
        else
            echo "$2 é maior que $1"
        fi
    fi
    return 0
}

compare $1 $2