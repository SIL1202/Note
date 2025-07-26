#!/bin/bash

echo "Total number of arguments: $#"
echo "File name: $0"
echo "First argument: $1"
echo "Second argument: $2"

echo "Combine arguments into array: $@"  # Each argument is preserved as a separate string
echo "Combine arguments into string: $*" # All arguments are combined into a single string separated by spaces

# Loop over each individual argument
for var in "$@"; do
  echo "$var"
done

# Loop only once because "$*" is a single string
for var in "$*"; do
  echo "$var"
done

# Words are split by spaces (word splitting happens here)
for var in $*; do
  echo "$var"
done
