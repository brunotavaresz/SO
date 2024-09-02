#!/bin/bash
function numeric_to_string()
{
case "$1" in
1)
echo "Um"
;;
2)
echo "Dois"
;;
3)
echo "Três"
;;
*)
echo "Outro numero"
esac
return 0
}
numeric_to_string $1


#!/bin/bash

function numeric_to_number() {
  return $1
}

numeric_to_number $1
echo "O valor de retorno da função é: $?"


