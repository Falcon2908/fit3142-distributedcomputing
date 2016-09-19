#
# $Id: Amdahl-MM1-Plot.plt,v 1.2 2015/10/05 10:11:22 carlo Exp carlo $
#
# Amdahl's Law
#
# Permission granted to distribute freely for non-commercial purposes only
#
# Copyright (c) 1996 Carlo Kopp carlo@cs.monash.edu.au


set title "S/N: MyStudentNumber  Plot of Amdahl's Law in Grid"
set xlabel "Number of CPUs [-]"
set ylabel "Speedup [-]"
set xtics
set ytics
set sample 10000
set style data lines
set autoscale x
set grid
set key left

#
# Sample Plotfile for Amdahl's Law - Modify for tutorial
#
###############################################################################
# Expressions for network load model
###############################################################################

# Sc serial component of computation
delayfactor=0.01
meanqueue(util)=util/(1-util)
delay(util)=meanqueue(util)*delayfactor
amdahl(sc,util,x)=1/(delay(util) + sc + (1 - delay(util) - sc)/x)

set terminal x11

plot [0:128] \
1/(0 + 1/x) title "Linear (Ideal) Speedup",\
amdahl(0.001,1.0,x) title "Util=0.9 Sc=0.001"

pause -1 "Hit return to continue"

set terminal postscript color  solid
set output "MyStudentNumber-Task-1.ps"

replot

# Use psd2pdf MyStudentNumber-Plot-1.ps to make a PDF file which can view with Acrobat and submit for assessment
