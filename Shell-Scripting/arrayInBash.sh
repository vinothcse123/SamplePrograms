myArray=(1 2 "StringValue" 9.876)

for x in ${myArray[@]}
do
    echo $x
done

ARRAY=()
ARRAY+=('foo')
ARRAY+=('bar')
