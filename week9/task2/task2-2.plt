#
# $Id: Amdahl-MM1-Plot.plt,v 1.2 2015/10/05 10:11:22 carlo Exp carlo $
#
# Amdahl's Law
#
# Permission granted to distribute freely for non-commercial purposes only
#
# Copyright (c) 1996 Carlo Kopp carlo@cs.monash.edu.au


set title "S/N: 24282588  Plot of Amdahl's Law in Grid"
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
amdahl(0.001,0.1,x) title "Util=0.1 Sc=0.001",\
amdahl(0.001,0.2,x) title "Util=0.2 Sc=0.001",\
amdahl(0.001,0.3,x) title "Util=0.3 Sc=0.001",\
amdahl(0.001,0.4,x) title "Util=0.4 Sc=0.001",\
amdahl(0.001,0.5,x) title "Util=0.5 Sc=0.001",\
amdahl(0.001,0.6,x) title "Util=0.6 Sc=0.001",\
amdahl(0.001,0.7,x) title "Util=0.7 Sc=0.001",\
amdahl(0.001,0.8,x) title "Util=0.8 Sc=0.001",\
amdahl(0.001,0.9,x) title "Util=0.9 Sc=0.001"

set terminal postscript color  solid
set output "task2-2.ps"

replot

# Use psd2pdf MyStudentNumber-Plot-1.ps to make a PDF file which can view with Acrobat and submit for assessment
