a=`echo "ls | grep s | grep r | grep c" | ./gsh`

if [ "$a" = "src
$ " ]; then
    echo "OK"
else
    echo "NG"
fi;

b=`echo "cat < test.txt" | ./gsh`
if [ "$b" = "abcdefg
$ " ]; then
    echo "OK"
else
    echo "NG"
fi;
