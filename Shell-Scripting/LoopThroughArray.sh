declare -a myArray=("Vinoth" "Kiruba")

for i in "${myArray[@]}"
do
        echo "$i"
done


end=5
for ((i=1;i<=end;i++)); do
echo "Welcome $i times"
done
