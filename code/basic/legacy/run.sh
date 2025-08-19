clear
echo File Location: $1
echo File Name: $2
extension="${2##*.}"
basename="${2%%.*}"

if [ ! -f "$1/input" ]; then
    echo "Input not exists, create an empty one."
    echo "" >> $1/input
fi

echo ============================================
if [[ $extension == "cpp" || $extension == "c" || $extension == "ts" ]]; then
    echo Start compiling \"$2\"...
    echo --------------------------------------------
    echo
    if [ $extension == "cpp" ]; then
        g++ $1/$2 -I ~/Desktop/cpp/include -std=c++23 -g -fsanitize=address,undefined -Ofast -Wall -Wextra -o$1/a.out
    fi
    if [ $extension == "c" ]; then 
        gcc $1/$2 -std=c17 -g -fsanitize=address,undefined -Ofast -Wall -Wextra -o$1/a.out
    fi
    if [ $extension == "ts" ]; then
        if [ ! -f "$1/tsconfig.json" ]; then
            npx tsc -p $1 --init
        fi
        npx tsc -p $1
    fi
    if [ "$?" -ne 0 ]; then
        exit 1
    fi
fi

echo Start executing \"$2\"...
echo ============================================
echo Input file:
echo --------------------------------------------
cat $1/input
echo ============================================
declare startTime=`date +%s%N`
if [[ $extension == "cpp" || $extension == "c" ]]; then
    $1/a.out < $1/input > $1/output
fi
if [ $extension == "py" ]; then
    python $1/$2 < $1/input > $1/output
fi
if [[ $extension == "js" || $extension == "ts" ]]; then
    if [ ! -f "$1/package.json" ]; then
        echo "Remember to npm init"
    fi
    node $1/${basename}.js < $1/input > $1/output
fi
declare endTime=`date +%s%N`
delta=`expr $endTime - $startTime`
delta=`expr $delta / 1000000`
if [ "$?" -ne 0 ]; then
    exit 1
fi
echo "Program ended in $delta ms with the return value $?"
cat $1/output

