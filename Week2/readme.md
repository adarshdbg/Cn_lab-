## ● Plot a Line graph for TCP congestion window (cwnd) using gnuplot

do
```diff 
+ ./waf clean

+ ./waf --enable-examples --enable-tests configure
build 
+./waf

+./waf --run "tcp-variants-comparison --tracing=true"
```
    now gnuplot is a linux software already installed , incase if it isn't install it using 
    $ sudo apt get gnuplot
    now to enter gnuplot just type
    $ gnuplot
    Try 
    $ plot sin(x)
    a new window opens with graph of sin(x)

After doing the above commands we'll find **TcpVariantsComparison-cwnd.data** in the ns3 folder.   
Create a same file **mygnupolt.plt** in the same directory.  
Write this in the file 

    set terminal png
    set output "cwnd.png"
    set title "Congestion Window Plot"
    set xlabel "Time (in seconds)"
    set ylabel "cwnd (in Bytes)"
    plot "TcpVariantsComparison-cwnd.data" using 1:2 with lines
and a file is generated named cwnd.png , which is the required output file.

## ● Enable support of ASCII traces in first.cc and collect the statistics

[solution here](https://codein.withgoogle.com/archive/2018/organization/5152211763986432/task/5521019934605312])