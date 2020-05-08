
#if statement
myVar=2
myName="Vinoth"
if myVar == 2 and myVar != 3 and myName in ["Vinoth","Kiruba"] :
    print("True")
elif myVar == 29:
    print("This is else if")
else:
    print("False")

#for Loop
myList=[1,2,3,5]

for currVariable in myList:
    print(currVariable,end = '')
print("\n")

#Range in for loop

for currVariable in range(1,5): 
    print(currVariable,end = '') 
print("\n")

for currVariable in range(1,10,2): #print odd numbers 
    print(currVariable,end = '') 
print("\n")


#while loop

myCount=0
while myCount < 5:
    print(myCount,end = '') 
    if myCount == 3:
        break
    myCount+=1;


#Else for Loops
myCount=0
while myCount < 5:
    print(myCount,end = '') 
    myCount+=1;
else:
    print("My While is finished")
print("\n")
