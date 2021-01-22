#GH_PY_SAM_1

#List Data Structure

#Basics
myList = []
myList.append("Vinoth")
myList.append("Kiruba")


myListWithValues=["MyInitialValue1","MyInitialValue2","MyInitialValue1"] #Init list with value
addingTwoLists = myListWithValues + myList
multiplyMyList = [1,2,3]*5
LengthOfList=len(myListWithValues)
countofMyInitialValue1=myListWithValues.count("MyInitialValue1") #counts the number of values
ListOfList=[[1,2,5],[100,200]]
ListOfListTakesEachListAsRef = [multiplyMyList] * 5
ListIsNotHomogeneous=["String",10,9.44]


print(myList)
print(myList[0]) #Starts with zero
print(addingTwoLists)
print("multiplyMyList %s"%multiplyMyList)
print(LengthOfList)
print(countofMyInitialValue1)
print("List using argument specifier %s" % myList);

for x in myList:
    print(x)

