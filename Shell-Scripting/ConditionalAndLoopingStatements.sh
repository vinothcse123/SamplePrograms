/********************************************* IF STATEMENT ********************************************/

printf "\n1 - vinothdb"
printf "\n2 - vinothdbTEST"
V_DB_ID=5

printf "\nEnter the choice: "
read choice

if [ $choice = 1 ]; then
    V_DB_ID=1;
else
    V_DB_ID=2;
fi;

echo $V_DB_ID

if [ $agdTprId -ge $startWeek ] && [ $agdTprId -le $endWeek ]; then
echo "$file"
fi



# Comparing string

x=vinoth

if [ "$x" = "vinoth" ]; then
  echo "It is vinoth"
fi


#check environment variable is set or not

if [ -z "$MYENV" ]; then echo "MYENV is not set" ;

if [ ! -z ${MYENV} ]; then 
        echo "MYENV is set"
fi


# OR Condition

if [ ! -z ${DEBUG} ] || [ ! -z ${MYENV} ]; then
        echo "DEBUG or MYENV is set"
fi


#cascading If statement

if [ ! -z ${DEBUG} ] || [ ! -z ${MYENV} ]; then
	if [ ! -z ${MYANOTHERVARIABLE} ]; then
    	MYANOTHERVARIABLE1=$MYANOTHERVARIABLE
	else	
		exit 1
	fi	
else
	DEBUG1=$DEBUG
fi



#checking variable value

if [ X"$MYENV" = X"1" ]; then


/********************************************* FOR LOOP ********************************************/

declare -a myArray=("Vinoth" "Kiruba")

for i in "${myArray[@]}"
do
        echo "$i"
done

for i in `ls core*`; do echo $i; done


end=5
for ((i=1;i<=end;i++)); do
echo "Welcome $i times"
done

for fileName in `find ./ -iname "*.json" `;
do
    echo $fileName
done


for tableName in {"VINOTH","KIRUBA"}
do
    echo $tableName
done


for tableName in "VINOTH KUMAR" "KIRUBA SUBRAMANI"
do
    echo $tableName
done
