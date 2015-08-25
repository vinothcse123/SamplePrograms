/*  Passing array to function.sh  */

V_ARR=(A B C)
V_ARR_2=(VINO HAI)

function callme(){
   echo "Called the function.."$1
   V_PARAM_1=("${!1}")
   V_PARAM_2=("${!2}")


  echo ${V_PARAM_1[1]}
  echo ${V_PARAM_2[0]}

}

callme V_ARR[@] V_ARR_2[@]

