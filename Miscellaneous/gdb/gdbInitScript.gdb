define sb
        save breakpoints v6SavedBreakpoints.txt
end

source v6SavedBreakpoints.txt

######## print settings
set print address off
set print repeats 0
set print pretty on
#set print thread-events off


##########Logging Info
#set logging on #By default writes to gdb.txt
#set logging file myFile.log

