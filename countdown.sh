#!/bin/bash


echo "Enter a number to start countdown:"
read countdown

while [ $countdown -gt 0 ]
do
  echo $countdown
  countdown=$((countdown - 1))
  sleep 1
done

echo "Time's up!"

