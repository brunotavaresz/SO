#!/bin/bash
echo "O meu editor por omissão BASH $BASH \$BASH"
echo 'O meu editor por omissão BASH $BASH \$BASH'
echo $(( 5 + 5 ))
(( 5 > 0 )) && echo "cinco é maior do que zero"
today=$(date); echo $today


#Aqui estão os comandos que permitem listar os arquivos e diretórios no diretório /etc de acordo com os critérios especificados:
#i. Todos os arquivos e diretórios em /etc:
#ls /etc

#ii. Todos os arquivos e diretórios em /etc cujo nome começa com 'a':
#ls /etc/a*

#iii. Todos os arquivos e diretórios em /etc cujo nome começa com 'a' e tem mais de 3 caracteres:
#ls /etc/a??*

#iv. Todos os arquivos e diretórios em /etc que têm 'conf' no nome:
#ls /etc/*conf*
