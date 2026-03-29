def validate(seq):   
  for i in range(len(seq)):     
    for j in range(i+1,len(seq)):      
      if seq[i]==seq[j]:        
        print("New Language Error")        
        return False   
  return True       
seq=input() 
string=input()  
if validate(seq)!=False:   
  s_t=""    
  for i in list(string.split(" ")):    
    tmp=["`"]*len(seq)    
    for j in i:      
      if j in tmp:        
        tmp.insert(tmp.index(j),j)   
      if j.upper() in seq:     
        tmp[seq.index(j.upper())]=j.upper()    
      elif j.lower() in seq:   
        tmp[seq.index(j.lower())]=j.lower()   
    s_t+="".join(tmp)+" "  
    s_t=s_t.replace("`","",s_t.count("`"))  
  print(s_t)