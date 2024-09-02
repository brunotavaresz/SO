#!/bin/bash
# Calculate the sum and average of a series of numbers.
SCORE="0"
SUM="0"
COUNT="0"

while true; do
    echo -n "Enter your score [0-10] ('q' to quit, 'r' to reset): " # imprime a mensagem
    read SCORE # lê a variável SCORE
    if [[ "$SCORE" == "q" ]]; then # se SCORE for igual a q então sai do loop
        if [ "$COUNT" -eq 0 ]; then # se COUNT for igual a 0 então imprime a mensagem
            echo "No scores entered. Exiting."
        else
            AVERAGE=$(bc -l <<< "scale=2; $SUM / $COUNT") # AVERAGE = SUM / COUNT
            echo "Sum: $SUM" # imprime a soma
            echo "Average: $AVERAGE" # imprime a média
        fi
        break
    elif [[ "$SCORE" == "r" ]]; then # se SCORE for igual a r então zera a soma e o contador
        SUM="0" 
        COUNT="0"
        echo "Count and sum reset." # imprime a mensagem
    elif ((SCORE < 0)) || ((SCORE > 10)); then # se SCORE for menor que 0 ou maior que 10 então imprime a mensagem
        echo "Try again: " 
    else
        SUM=$((SUM + SCORE)) # SUM = SUM + SCORE
        COUNT=$((COUNT + 1)) # COUNT = COUNT + 1
    fi
done

echo "Exiting." # imprime a mensagem de saída
