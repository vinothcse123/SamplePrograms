
#Types
myInteger=100
myFloat=19.89; 
myForcedFloat = float(9); #Forcing Integer to float
myString = 'This is my string'
myStringWithDoubleQuote = "This is my double quoted string"
myStringWhenToUseDoubleQuote = "When using apostrope' use double quotes"
ArgumentSpecifier="Argument Specifier"
nextOne = "Next One"
#Print
print("This is to print like function");
print(myInteger);
print(myStringWithDoubleQuote);
print(myStringWhenToUseDoubleQuote);
print(myInteger,myFloat);
print("This is %s !" % ArgumentSpecifier)
print("This is %s ! %s !" %(ArgumentSpecifier,nextOne))
print("%d %s %f %.20f" %(myInteger,"Hai",myFloat,myFloat))
print("Integer in hexadecimal (Both are same) %X %x" %(myInteger,myInteger))
print("Next Line will not be print ", end = '')
print("Same line ")


if __name__ == "__main__":
    test_SaveNode()
