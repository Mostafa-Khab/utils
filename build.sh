mkdir build

for file in *.cpp
do
  filename=$(basename "$file" .cpp)
  g++ $file -o "build/$filename"
done

