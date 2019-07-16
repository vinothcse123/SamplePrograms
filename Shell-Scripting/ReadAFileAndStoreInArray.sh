fileName="MyInput.txt"
declare -a myArray
myArray=(`cat "$fileName"`)


for i in "${myArray[@]}"
do
        echo $i
done
