#!/bin/bash
set -e

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Paths
test_dir="test_cases"
correct_dir="Correct"
incorrect_dir="InCorrect"

validator="validator_exec"
checker="checker_exec"
temp_out="temp_output.txt"

# Compile validator and checker
echo "Compiling validator.cpp..."
g++ validator.cpp -o "$validator" || { echo -e "${RED}Validator compilation failed!${NC}"; exit 1; }

echo "Compiling checker.cpp..."
g++ checker.cpp -o "$checker" || { echo -e "${RED}Checker compilation failed!${NC}"; exit 1; }

# 1. Validate all test cases
echo
echo "=== Validating test cases ==="
for input in "$test_dir"/*.in; do
    ./"$validator" < "$input" > /dev/null || {
        echo -e "${RED}Invalid input file: $(basename "$input")${NC}"
        exit 1
    }
done
echo -e "${GREEN}All input files are valid.${NC}"

# 2. Run solution and use checker
run_solution() {
    cpp_file=$1
    tag=$2
    exe="solution_exec"

    echo
    echo "Compiling $cpp_file..."
    g++ -O2 "$cpp_file" -o "$exe" || { echo -e "${RED}Compilation failed: $cpp_file${NC}"; return; }

    pass=0
    fail=0

    for input in "$test_dir"/*.in; do
        base=$(basename "$input" .in)
        expected="$test_dir/$base.out"

        ./"$exe" < "$input" > "$temp_out" 2>/dev/null

        # Run checker and explicitly capture exit code
        ./"$checker" "$input" "$expected" "$temp_out" > /dev/null 2>&1
        checker_exit=$?

        # Evaluate the result
        if [ $checker_exit -eq 0 ]; then
            ((pass++))
        else
            echo -e "${RED}[$tag] Failed on $base.in: $cpp_file${NC}"
            ((fail++))
        fi
    done

    echo -e "[$tag] $cpp_file: ${GREEN}$pass passed${NC}, ${RED}$fail failed${NC}"
    rm -f "$exe"
}
# 3. Test correct solutions
echo
echo "=== Testing Correct Solutions ==="
for file in "$correct_dir"/*.cpp; do
    run_solution "$file" "Correct"
done

# 4. Test incorrect solutions
echo
echo "=== Testing InCorrect Solutions ==="
for file in "$incorrect_dir"/*.cpp; do
    run_solution "$file" "InCorrect"
done

rm -f "$temp_out" "$validator" "$checker"
