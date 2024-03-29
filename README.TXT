##############################################################################
#                                                                            #
#   RFPM_3D.cpp - code for energy minimization and approximate ground states
                   for the random-field Potts model (RFPM) via graph cuts    #
#                                                                            #
#    By Manoj Kumar and Martin Weigel                                        #
#                                                                            #
#    Copyright 2022      Manoj Kumar  <manojkmr8788@gmail.com>               #
#                        Martin Weigel <martin.weigel@gmail.com>             #
#                                                                            #
##############################################################################

  IMPORTANT:
  To use this code, you need to download the gco-v3.0 package by Olga Veksler 
  and Andrew Delong for optimizing the multi-label energies. The package is 
  available at Olga Veksler webpage https://www.csd.uwo.ca/~oveksler/.
  The package also provides libraries by Y. Boykov and V. Kolmogorov, namely 
  maxflow.cpp, graph.cpp, graph.h, block.h, and energy.h.
  
  Usage:

  Unpack the package gco-v3.0 and compile the code using the makefile.  The code is
  designed to minimize the energy for a three-state RFPM on a cubic lattice of linear
  size L = 16 with periodic boundary conditions in all directions.  The random field
  variables are drawn from a Gaussian distribution of standard deviation 1.8.  For a
  given sample of this strength, the code will optimize the RFPM energy function for
  10000 initial spin labelings and output the magnetization and bond-energy per spin
  from the minimum energy configuration among 10000 runs as well as the total
  optimize value of the minimum energy function. For the example configuration the
  code should finish a few minutes.
  
  Please see our publications as given below for details on RFPM energy function, 
  approximate ground states via graph cuts, its performance, and the role of RFs. 
  
  [1] Approximate ground states of the random-field Potts model from graph cuts.
      M. Kumar et al., Phys. Rev. E 97, 053307 (2018).
      
  [2] On the comparison of optimization algorithms for the random-field Potts model.
      M. Kumar and M. Weigel, J. Phys.: Conf. Series 2241 , 012003 (2022).
      
  [3] Quasi-exact ground-state algorithm for the random-field Potts model.
      M. Kumar and M. Weigel, Preprint arXiv:2204.11745. 
      
  [4] Critical behavior of the three-state random-field Potts model in three dimensions.     
      M. Kumar et al., Phys. Rev. Res. 4, L042041 (2022).
