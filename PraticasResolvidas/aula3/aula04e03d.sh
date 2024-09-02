function selecao() {
    arr=( $(cat $1) )
    retval=1

    while (( $retval == 1 )); do
        retval=0

        for i in ${!arr[@]}; do
            current_index=$i
            next_index=$(($i+1))
            current_value=${arr[current_index]}
            next_value=${arr[next_index]}

            if [[ $next_value -ne "" ]]; then
                if [[ $current_value -gt $next_value ]]; then
                    arr[current_index]=$next_value
                    arr[next_index]=$current_value
                    retval=1
                fi
            fi
        done
    done

    echo $(cat $1)
    echo ${arr[@]}
}

selecao $1
