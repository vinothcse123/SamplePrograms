def find_n_th_element(input,searchstring,occNumber,curpos=0):
  res =  input.find(searchstring,curpos)
  if res == -1 or occNumber == 1:
     return res
  else:
     return find_n_th_element(input,searchstring,occNumber-1,res+len(searchstring))


print find_n_th_element("a,b,c,",",",2)



