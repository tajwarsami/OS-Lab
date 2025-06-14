#!/bin/bash

read -p "Enter first number: " a
read -p "Enter second number: " b

echo "Before swap: a=$a, b=$b"
temp=$a
a=$b
b=$temp
echo "After swap: a=$a, b=$b"
