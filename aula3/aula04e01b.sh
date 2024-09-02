#!/bin/bash

function imprime_msg()
{
    echo "A minha primeira funcao"
    return 0
}

function dateID()
{
    Data=$(date | cut -d " " -f 1-3)
    PC=$(hostname)
    Utilizador=$USER;
    echo "Data: $Data    PC: $PC    Utilizador: $Utilizador"
    return 0
}