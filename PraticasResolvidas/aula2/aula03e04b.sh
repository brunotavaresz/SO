#!/bin/bash
# Este script faz um teste muito simples para verificar o espaço em disco.

# Validação dos argumentos
if [[ ! $1 =~ ^[0-9]{1,2}$ ]]; then
    echo "O primeiro argumento deve ser um número entre 0 e 99."
    exit 1
fi

if [[ ! $2 =~ ^sec.* ]]; then
    echo "O segundo argumento deve começar por 'sec'."
    exit 1
fi

# Inicializa max_space como -1 para garantir a primeira porcentagem será maior
max_space=-1 
max_partition="" # Inicializa a partição com maior espaço ocupado

while read -r line; do # -r: raw input (não interpreta \ como escape) 
    if [[ $line == Filesystem* ]]; then # Pula a linha de cabeçalho
        continue 
    fi

    current_space=$(echo "$line" | awk '{print $5}' | sed 's/%//') # Remove o % do final
    current_partition=$(echo "$line" | awk '{print $1}') # Pega o nome da partição

    if ((current_space > max_space)); then # Se a percentagem atual for maior que a maior percentagem
        max_space="$current_space" # Atualiza a maior percentagem
        max_partition="$current_partition" # Atualiza a partição com maior espaço ocupado
    fi
done <<< "$(df -h)" # Redireciona a saída do comando df -h para o loop while

echo "Partição com maior espaço ocupado: $max_partition"  # Imprime a partição com maior espaço ocupado
echo "Espaço ocupado na partição: $max_space%"  # Imprime a porcentagem de espaço ocupado na partição

case $max_space in
    [0-6]* ) # espaço < 70%
        Message="All OK."
        ;;
    [7-8]* ) # 70% <= espaço < 90%
        Message="Better buy a new disk. One partition is $space % full."
        ;;
    99 ) # espaço = 99%
        Message="I'm drowning here! There's a partition at $space %!"
        ;;
    * )
        Message="I seem to be running with a non-existent disk..."
        ;;
esac

echo $Message

