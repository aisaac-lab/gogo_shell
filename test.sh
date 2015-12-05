a=`echo "ls | grep s | grep r | grep c" | ./mysh`

if [ "$a" = "src
$ " ]; then
    echo "OK"
else
    echo "NG"
fi;

b=`echo "cat < test.txt" | ./mysh`
if [ "$b" = "abcdefg
$ " ]; then
    echo "OK"
else
    echo "NG"
fi;
