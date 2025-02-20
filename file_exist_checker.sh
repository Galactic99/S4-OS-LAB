#!/bin/bash


echo "Enter the file name to check:"
read filename

if [ -f "$filename" ]; then
  echo "File exists."
else
  echo "File does not exist."
fi

