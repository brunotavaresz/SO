#!/bin/bash

function compare_numbers() {
  if [ $1 -eq $2 ]; then
    return 0  # Números iguais
  elif [ $1 -gt $2 ]; then
    return 1  # O primeiro número é maior
  else
    return 2  # O segundo número é maior
  fi
}

if [ $# -ne 2 ]; then # $# é o número de argumentos passados para o script (neste caso, 2) e -ne é o operador de comparação "não igual"
  echo "Informe dois números como argumentos."
  exit 1
fi

compare_numbers $1 $2
result=$?

if [ $result -eq 0 ]; then
  echo "Os números são iguais."
elif [ $result -eq 1 ]; then
  echo "O primeiro número é maior."
else
  echo "O segundo número é maior."
fi
