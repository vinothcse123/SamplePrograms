


def basicStringFunctionality():
    mystring="Hai Hello"
    mystringAsNumbers="0123456789"
    MyConcatString = "Hai " + "Hello"
    makeMyString3Times = "Vinoth" * 3
    lengthOfString=len(mystring)
    indexOfI=mystring.index('i')
    countOfH=mystring.count('H')
    newStringWithRange=mystringAsNumbers[1:3]
    RangewithStep=mystringAsNumbers[1:9:2] #steps positions while extracting range. Instead of 123456 it fetches 1357
    makeStringUpper=mystring.upper()
    isStartsWith=mystring.startswith("Hai")
    isEndsWith=mystring.endswith("Hai")
    convertToList=mystring.split(" ")


    print(MyConcatString)
    print(makeMyString3Times)
    print(lengthOfString)
    print(indexOfI)
    print(countOfH)
    print(newStringWithRange)
    print(RangewithStep)
    print(isStartsWith)
    print(isEndsWith)
    print(convertToList)


def substringAndParsing():

    myVar="HELLO.HAI120"

    substrPositition=myVar.find(".")

    if substrPositition != -1:
        print(substrPositition)
        print(myVar[substrPositition+1:substrPositition+4])
    else:
        print("Unable to find substring....")

if __name__ == "__main__":
    # basicStringFunctionality()
    substringAndParsing()
