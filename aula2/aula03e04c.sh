#!/bin/bash

# Get the first argument
arg1=$1

# Check if the first argument is a number between 0 and 99
case $arg1 in
    [0-9]|[1-9][0-9]) # Valid range
        # Get the second argument
        arg2=$2

        # Check if the second argument starts with "sec"
        case $arg2 in
            sec*) # Starts with "sec"
                echo "Success: Arguments are valid."
                ;;
            *)
                echo "Error: Second argument must start with 'sec'."
                ;;
        esac
        ;;
    *)
        echo "Error: First argument must be a number between 0 and 99."
        ;;
esac

