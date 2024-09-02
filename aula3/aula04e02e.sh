#!/bin/bash
function compare()
{
    read -p "Digite o primeiro número: " n1
    read -p "Digite o segundo número: " n2
    if [ $n1 -eq $n2 ]; then
        echo "São iguais"
    else
        if [ $n1 -gt $n2 ]; then
            echo "$n1 é maior que $n2"
        else
            echo "$n2 é maior que $n1"
        fi
    fi
    return 0
}

compare 