(begin 

 (write "%test%")

 (write '\\\%test%)

 (write 
  (scm-symbol->chars 'xx))
 (write 
  (inc-c 4))

 (write '%xest%)

 (write :av)

 (write :%test%)


 (write '(5 plus 7 is #.(+ 5 7)) )
)


