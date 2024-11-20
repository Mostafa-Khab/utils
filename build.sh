for file in src/*.cpp
do
  filename=$(basename "$file" .cpp)
  g++ $file -o "build/$filename" # -I/path/to/stb
done
