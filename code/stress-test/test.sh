g++ -std=c++20 -o buggy $1
g++ -std=c++20 -o ac ac.cpp
for i in {1..100}; do
  echo "TEST $i"
  python3 gen.py > in
  ./ac < in > oa
  ./buggy < in > ob
  if ! diff -q oa ob; then
    cat in <(echo "=== AC") oa <(echo "=== WA") ob
    break
  fi
done
