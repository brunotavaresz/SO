#!/bin/bash
lista=( $(seq 2 3 15) ) # Cria um array com os números de 2 a 15, pulando de 3 em 3
echo vals ${lista[@]} # Imprime todos os valores do array
echo count ${#lista[@]} # Imprime a quantidade de elementos do array
echo index ${!lista[@]} # Imprime os índices do array
for ((i = 0; i < ${#lista[@]}; i++)); do # Percorre o array e imprime os valores e os índices
lista[i]=$((${lista[i]}+1)) # Soma 1 ao valor do elemento atual
echo "$i: ${lista[i]}" # Imprime o índice e o valor do elemento atual
done
unset lista[1] # Remove o elemento de índice 1
unset lista[3] # Remove o elemento de índice 3
echo count ${#lista[@]} # Imprime a quantidade de elementos do array
for i in ${!lista[@]}; do # Percorre o array e imprime os valores e os índices
echo "$i: ${lista[i]}" 
done