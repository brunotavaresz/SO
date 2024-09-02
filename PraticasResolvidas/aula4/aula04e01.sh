#!/bin/bash

# Função para imprimir uma mensagem
function imprime_msg() {
  echo "A minha primeira função"
  return 0
}

# Função para mostrar a data atual, o nome do computador e o nome do usuário
function info_sistema() {
  echo "Data atual: $(date)"
  echo "Nome do PC: $(hostname)"
  echo "Nome do usuário: $USER"
}

# Chamando a primeira função
imprime_msg

# Chamando a segunda função
info_sistema
