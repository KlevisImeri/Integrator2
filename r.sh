#!/bin/bash
# Compile all the .cpp files in src directory


# Append each filename to a string variable
for file in src/*.cpp; do
  source_files="$source_files $file"
done

# Compile the source files into an executable
echo g++ $source_files -I./include -g
g++ $source_files -I./include -g
# Run the program
#./a.out < input.txt

# Memory leakage
#valgrind --leak-check=full --show-leak-kinds=all ./a.out

# # Create build directory if it doesn't exist
# mkdir -p build

# # Compile each source file using g++
# for file in src/*.cpp
# do
#   # Extract the filename without extension
#   filename=$(basename "$file" .cpp)

#   # Compile the file using g++
#   g++ -c "$file" -o "build/$filename.o" -Iinclude
# done

# # Link the object files to create the executable
# g++ build/*.o -o a