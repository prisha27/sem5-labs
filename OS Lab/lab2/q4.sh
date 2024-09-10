echo "enter n value"
read n
count=1
p=1
while [ $count -le $n ]; do
	p=$((p*count))
        count=$((count+1))
done

echo factorial is $p

