#!/bin/bash
# select structure to create menus
PS3="Escolha uma opção: " # Redefinindo a variável PS3 para alterar a mensagem do usuário
options=("$@") # Criando um array com os argumentos passados para o script
options+=("Sair") # Adicionando uma opção para sair

select arg in "${options[@]}"; do # Criando um menu com as opções do array
    case $arg in # Verificando qual opção foi escolhida
        "Sair")
            echo "Você escolheu sair. Adeus, aquele abraço!" 
            break
            ;;
        *)
            if [ -n "$arg" ]; then # Se o argumento não for nulo
                echo "Você escolheu $arg ($REPLY)." # Imprime a opção escolhida
            else
                echo "Opção inválida." # Imprime a mensagem de erro
            fi
            ;;
    esac
done
