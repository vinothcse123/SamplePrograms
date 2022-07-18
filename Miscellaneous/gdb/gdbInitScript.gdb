
printf  "== GDB Init file loaded ==\n"

define sb
        save breakpoints v6SavedBreakpoints.txt
end


define bload
    source /RMS/nrsp/vinoth/etc/gdbBreakpoints.txt
end

bload

######## print settings
catch throw
set print address off
set print repeats 0
set print pretty on
#set print thread-events off


##########Logging Info
#set logging on #By default writes to gdb.txt
#set logging file myFile.log

