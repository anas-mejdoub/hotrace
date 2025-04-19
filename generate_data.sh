#!/bin/bash

# Function to generate a random string of a specified length
generate_random_string() {
    local length=$1
    tr -dc 'a-z0-9' </dev/urandom | head -c "$length"
}

# File name for the test file
filename="test_file.txt"

# Number of insertions (key-value pairs)
num_insertions=10000

# Create a new test file (overwrite if exists)
> "$filename"

# Arrays to store keys and values
declare -a keys
declare -a values

# Generate insertions (key-value pairs) and store in arrays
for ((i = 0; i < num_insertions; i++)); do
    key=$(generate_random_string $((RANDOM % 8 + 3)))  # Random key length between 3 and 10
    value=$(generate_random_string $((RANDOM % 8 + 3)))  # Random value length between 3 and 10
    keys+=("$key")
    values+=("$value")
    
    # Write the key and value consecutively
    echo "$key" >> "$filename"
    echo "$value" >> "$filename"
done

# After the key-value pairs, leave two empty lines
echo "" >> "$filename"
echo "" >> "$filename"

# After insertions, write the keys only for lookup simulation
for key in "${keys[@]}"; do
    echo "$key" >> "$filename"
done

# Add a few non-existent keys to simulate a not-found case
echo "keydoesn'texist" >> "$filename"

echo "Test file '$filename' generated."
