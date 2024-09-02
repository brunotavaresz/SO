#!/bin/bash
declare -A assArray # Associative array
assArray[Aveiro]=10 # Add a value to the array
assArray[Porto]=NA # Add a value to the array
assArray+=([Lisboa]=5) # Add a value to the array
echo vals ${assArray[@]} # Print all values of the array
echo count ${#assArray[@]} # Print the number of elements of the array
echo index ${!assArray[@]} # Print the indexes of the array
echo val Lisboa ${assArray[Lisboa]} # Print the value of the element with index Lisboa