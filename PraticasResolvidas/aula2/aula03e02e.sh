#!/bin/bash
# Bloco condicional if

if [[ $1 -eq $2 ]]; then # -eq: equal
  echo "O $1 é igual ao $2"
elif [[ $1 -lt $2 ]]; then # -lt: less than
  echo "O $1 é menor que o $2"
else
  echo "O $1 é maior que o $2" 
fi

