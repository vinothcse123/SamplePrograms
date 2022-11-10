
#Style 1
function myFunctionInBash()
{
    echo "myFunctionInBash"
}


#Style 2
functionWithoutFunctionKeyWord()
{
    echo "functionWithoutFunctionKeyWord"
}


functionWithArgs()
{
    echo "$1 $2"
}

returnValueAsRef=()

functionWithReturnValue()
{
    returnValueAsRef=("VINOTH","KIRUBA")
}

myFunctionInBash
functionWithoutFunctionKeyWord
functionWithArgs "Hello" 19.88
functionWithReturnValue 
echo $returnValueAsRef
