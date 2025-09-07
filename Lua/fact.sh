#!/bin/bash

fact() {
  local n="$1"
  if ((n < 2)); then
    echo 1
  else
    local prev
    prev="$(fact $((n - 1)))"
    echo $((n * prev))
  fi
}

result=$(fact 5)
echo "$result"
