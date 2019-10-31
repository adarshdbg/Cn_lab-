set terminal png
set output "cwnd.png"
set title "TCP congestion window"
set title "Congestion Window Plot"
set xlabel "Time (in seconds)"
set ylabel "cwnd (in Bytes)"
plot "TcpVariantsComparison-cwnd.data" using 1:2 with lines title "TCP congestion window" lw 2
