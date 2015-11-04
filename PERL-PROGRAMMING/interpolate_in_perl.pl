$var='How are you';

print '\nVinoth, $var';
print "\nVinoth, $var";

$var2=<<"MY_END";

Multi-Line text.  $var

MY_END

print  $var2;

$var3=<<'MY_END';

Multi-Line text.  $var

MY_END

print  $var3;
