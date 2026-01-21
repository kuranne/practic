i=1
while [ $i -le 99 ]; do
    echo $i
    i=$(expr $i + 2)
done