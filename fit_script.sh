# FILE:  fit_script.sh
# USAGE: bash fit_script.sh
# TASK:  Gnuplot script to jointly fit the data for magnetization "m" and bond energy per spin "e_J" as a function of number of initial conditions "n". It will produce their extrapolated values in the 	  limit of infinite n.
# INSTRUCTIONS: create a data file say 'inputFile.dat' containing three columns, where first column lists the different n values, second is the m or e_J and third is the corresponding errors 

gnuplot -persist << EOF


f(x,y)=value(sprintf("a%d",y))*x**-b*(1+value(sprintf("c%d",y))*x**-d)+value(sprintf("e%d",y))  ## Joint fit function f(x,y), where exponents b and d have a common value. The parameters e0 and e1 are 												    ## the extrapolate estimates for m and e_J, respectively.  

fit f(x,y) 'inputFile.dat' u 1:-1:2:3 via a0,a1,b,c0,c1,d,e0,e1
set print "outputFile.dat" append    								    ##create an output file
print b,b_err/FIT_STDFIT,d,d_err/FIT_STDFIT,e0,e0_err/FIT_STDFIT,e1,e1_err/FIT_STDFIT,FIT_P     ##store the power-law exponents and extrapolated results alongwith fit quality FIT_P in the output file 

EOF
