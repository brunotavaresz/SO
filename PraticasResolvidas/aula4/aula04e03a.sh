#!/bin/bash
lista=( {1..10} )
for i in "${lista[@]}"; do # O @ é necessário para que o for percorra todos os elementos do array e não apenas o primeiro
echo "$i"
done