echo "enter n value"
read n
count=0
odd=1
while [ $count -lt $n ]; do
	echo $odd
	odd=$((odd+2))
	count=$((count+1))
done
