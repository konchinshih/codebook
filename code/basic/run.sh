clear
echo File Location: $1
echo File Name: $2
echo ============================================
echo Start compiling \"$2\"...
echo
g++ $1/$2 -std=c++20 -Ofast -Wall -Wextra -g -fsanitize=address,undefined -o$1/a.out
if [ "$?" -ne 0 ]
then
        exit 1
fi
echo
echo Done compiling...
echo ============================================
echo Input file:
echo --------------------------------------------
cat $1/input
echo ============================================
declare startTime=`date +%s%N`
$1/a.out < $1/input > $1/output
declare endTime=`date +%s%N`
delta=`expr $endTime - $startTime`
delta=`expr $delta / 1000000`
echo "Program ended in $delta ms with the return value $?"
cat $1/output
