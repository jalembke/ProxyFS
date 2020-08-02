# Set formatting
set output out_file         # Set the output path

# Set the font to something pleasing
set term svg fname "Times,19" size 225, 225
unset key                   # No key
set grid                    # Turn the grid on

#set title gtitle offset 0,-0.7
set style fill pattern border
set boxwidth 0.40

# Create the plot
set format y "%.2f"
set ylabel "Write Speed (MB/sec)" offset 3.5
set yrange [0:*]
set xrange [-0.5:2.5]
set ytics 0.25, 0.25 offset graph 0.07
set xtics rotate by 25 right font ",15" offset 0,graph 0.05
set xtic scale 0

set lmargin at screen 0.25
set rmargin at screen 0.98
set tmargin at screen 0.97
set bmargin at screen 0.23

set style line 1 lt 6
set style line 2 lt 1
set style line 3 lt 3

plot  dat_file every ::0::0 using 1:3:xtic(2) with boxes ls 1 fs pattern 6, \
      dat_file every ::1::1 using 1:3:xtic(2) with boxes ls 2 fs pattern 1, \
	  dat_file every ::2::2 using 1:3:xtic(2) with boxes ls 3 fs pattern 4;
