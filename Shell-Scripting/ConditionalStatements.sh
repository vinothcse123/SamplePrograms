/* if else statement.sh */

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
