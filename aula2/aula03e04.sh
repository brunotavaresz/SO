#!/bin/bash
# This script performs a very simple test to check disk space.
space=$(df -h | awk '{print $5}' | grep % | grep -v Use | sort -n | tail -1 | cut -d "%" -f1 -)
echo "Largest occupied space = $space%"

case $space in
  [0-6]* ) # space < 70% [0, 69]
    Message="All OK."
    ;;
  [7-8]* ) # 70% <= space < 90% [70, 89]
    Message="Cleaning out. One partition is $space % full."
    ;;
  99 ) # space = 99%
    Message="I'm drowning here! There's a partition at $space %!"
    ;;
  * )
    Message="I seem to be running with a non-existent disk..."
    ;;
esac

echo $Message
