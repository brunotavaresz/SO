#!/bin/bash
# Calculate the sum of a series of numbers.
SCORE="0" 
SUM="0"
while true; 
echo -n "Enter your score [0-10] ('q' to quit): "  
read SCORE; # lê a variável SCORE
if (("$SCORE" < "0")) || (("$SCORE" > "10")); then  # if [ "$SCORE" -lt "0" ] || [ "$SCORE" -gt "10" ]
echo "Try again: "
elif [[ "$SCORE" == "q" ]]; then # se SCORE for igual a q então sai do loop
echo "Sum: $SUM." # imprime a soma
break 
else
SUM=$((SUM + SCORE)) # SUM = SUM + SCORE
fi
done 
echo "Exiting." # imprime a mensagem de saída