@v_char_array=(a,b,c);
print " Character Array 1st element $v_array[0]\n";

@v_mixed_array=(1,"abc",3.22);
print "v_mixed_array 2nd element $v_mixed_array[1]\n";

#Array can be assigned individually
$v_mixed_array[3]="I am 4th element. OMG there is no 3rd element.";
print "assigned individually = $v_mixed_array[4]\n";


#use of qw operator
@v_qw_array=qw/This is vinoth/; #This will form array with white space as delimiter
print "v_qw_array[2] = $v_qw_array[2] ";

#using negative sign to access array
print "\Gn v_qw_array[-1] = $v_qw_array[-1]";

#seaquential number array declration
@v_seq_array=(1..21);
print "\nv_seq_array[20] = $v_seq_array[20]";


#printing entire array content
print "\nEntire Array: @v_char_array";

#finding physical size of the array,
print "\nphysical Size of the array :", scalar @v_mixed_array, "\n";

#finding actual size of the array
$v_array_size=@v_mixed_array;
print "\nArray size: $v_array_size";

#finding the maximum index in the array
@v_max_array=(1,2,3);
$v_max_array[100]=2; # Size of array increased to 100
print "\nMaximum index of the array: $#v_max_array"; #CAUTION: It is the maximum index, not the size of the array size is 
maximum index +1


