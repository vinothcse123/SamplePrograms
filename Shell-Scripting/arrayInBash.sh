myArray=(1 2 "StringValue" 9.876)

for x in ${myArray[@]}
do
    echo $x
done

firstPos=${myArray[0]}
secondPos=${myArray[1]}


ARRAY=()
ARRAY+=('foo')
ARRAY+=('bar')

#Array of Array


array=("Vinoth Kiruba" "PavanKarthi DevaSastika")

for list in "${array[@]}"
do
    for item in $list
    do
        echo $item
    done
done
