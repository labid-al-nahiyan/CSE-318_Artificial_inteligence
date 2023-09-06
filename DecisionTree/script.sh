#!/bin/bash

accuracy_arr=()
total_accuracy=0.0
iterations=20
g++ decisionTree.cpp -o 1905110

for ((i = 1; i <= $iterations; i++)); do
    accuracy=$(./1905110)
    echo $accuracy
    accuracy_arr+=($accuracy)
    total_accuracy=$(echo "$total_accuracy + $accuracy" | bc -l)
done

mean=$(echo "scale=6;$total_accuracy / $iterations" | bc -l)
echo "Mean Accuracy: $mean%"

squared_diff_sum=0
for num in "${accuracy_arr[@]}"; do
    diff=$(echo "$num - $mean" | bc -l)
    squared_diff=$(echo "scale=6; $diff * $diff" | bc -l)
    squared_diff_sum=$(echo "scale=6; $squared_diff_sum + $squared_diff" | bc -l)
done
variance=$(echo "scale=6; $squared_diff_sum / $iterations" | bc)
std_deviation=$(echo "sqrt($variance)" | bc)
echo "Standard deviation : $std_deviation%"

