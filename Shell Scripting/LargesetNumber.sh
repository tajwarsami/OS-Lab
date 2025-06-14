#!/bin/bash

read -p "Enter first number: " a
read -p "Enter second number: " b
read -p "Enter third number: " c

if (( a >= b && a >= c )); then
    echo "$a is the largest"
elif (( b >= a && b >= c )); then
    echo "$b is the largest"
else
    echo "$c is the largest"
fi
