#!/bin/bash
if [ "$1" -gt 5 ] && [ "$1" -lt 10 ]; then # -gt: greater than; -lt: less than
  echo "Número maior do que 5 e menor do que 10"
else
  echo "Número não está na faixa desejada"
fi

