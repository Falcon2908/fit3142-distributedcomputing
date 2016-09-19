#
# $Id: Amdahl-Sample-Plot.plt,v 1.2 2015/10/05 10:11:22 carlo Exp carlo $
#
# Amdahl's Law
#
# Permission granted to distribute freely for non-commercial purposes only
#
# Copyright (c) 1996 Carlo Kopp carlo@cs.monash.edu.au


set title "S/N: 24282588  Plot of Amdahl's Law"
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


set terminal x11

plot [0:128] \
1/(0 + 1/x) title "Linear (Ideal) Speedup",\
1/(0.001 + 0.999/x) title "0.1% Serial Fraction",\
1/(0.005 + 0.995/x) title "0.5% Serial Fraction"
1/(0.01 + 0.99/x) title "1% Serial Fraction"
1/(0.02 + 0.98/x) title "2% Serial Fraction"
1/(0.03 + 0.97/x) title "3% Serial Fraction"
1/(0.04 + 0.96/x) title "4% Serial Fraction"
1/(0.05 + 0.95/x) title "5% Serial Fraction"

pause -1 "Hit return to continue"

set terminal postscript color  solid
set output "24282588-Task-1.ps"

replot

# Use psd2pdf MyStudentNumber-Plot-1.ps to make a PDF file which can view with Acrobat and submit for assessment
