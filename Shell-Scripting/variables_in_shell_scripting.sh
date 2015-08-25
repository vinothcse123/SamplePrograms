
# variables in shell scripting


# $# gives the list of arguments passed
if [ $# = 0 ]; then
   echo "No Arguments passed!"
   exit 1
fi

echo "Your current process number is "$$


# $@ and $* takes the entire arguments as single list difference is $* takes entire arguments as single list separated by spaces. where as the $@ also takes the entire argumengts but each arguments can be spliited
echo "Argument passed "$@
echo "Argument passed "$*

echo "Demo of \$@.."
for V_TOKEN in $@
do
   echo $V_TOKEN
done

echo "Demo of \$*"

for V_TOKEN in $*
do
   echo $*
done

# $? will say about the exit status of the program

true
echo "Last Exit status is "$?

false
echo "Last Exit status is "$?

# Array varaibles

V_MYARRAY=(apple orange guava)
echo " First index in array is "${V_MYARRAY[0]}
echo " All content in array is "${V_MYARRAY[*]}
