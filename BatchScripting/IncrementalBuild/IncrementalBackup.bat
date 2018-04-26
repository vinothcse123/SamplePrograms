::INPUTS
set sourcePath=C:\Users\xbbnkzm




@echo off
for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "YY=%dt:~2,2%" & set "YYYY=%dt:~0,4%" & set "MM=%dt:~4,2%" & set "DD=%dt:~6,2%"
set "HH=%dt:~8,2%" & set "Min=%dt:~10,2%" & set "Sec=%dt:~12,2%"



set "datestamp=%YYYY%%MM%%DD%" & set "timestamp=%HH%%Min%%Sec%"
set "fullstamp=%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%"

echo fullstamp: "%fullstamp%"


::get yesterday datestamp
:: yesterdays date
@echo off
set day=-1
echo >"%temp%\%~n0.vbs" s=DateAdd("d",%day%,now) : d=weekday(s)
echo>>"%temp%\%~n0.vbs" WScript.Echo year(s)^& right(100+month(s),2)^& right(100+day(s),2)
for /f %%a in ('cscript /nologo "%temp%\%~n0.vbs"') do set "result=%%a"
del "%temp%\%~n0.vbs"
set "YYYY=%result:~0,4%"
set "MM=%result:~4,2%"
set "DD=%result:~6,2%"
set "prevDate=%mm%-%dd%-%yyyy%"

echo Yesterday was "%prevDate%"

set "desdirName=V6_BACKUP_%fullstamp%"

set destinationPath=%desdirName%

mkdir %destinationPath%


echo source path is %sourcePath%
echo destinationPath path is %destinationPath%

xcopy /y /s %sourcePath% %destinationPath% /D:%prevDate% /exclude:excludeExtensionsList.txt




pause

