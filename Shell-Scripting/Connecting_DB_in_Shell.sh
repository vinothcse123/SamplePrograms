/* Connecting DB in Shell.sh */

export V_DB_ID

if [ $V_DB_ID = 1 ]; then
   CONN_STRING="LYCARRBS/LYCARRBS123@LYCAPZ"
else

   CONN_STRING="LYCARRBS/LYCARRBS123@LYCAPZ"
fi;

sqlplus $CONN_STRING    << EOF47
   select sysdate from dual;
EOF47
