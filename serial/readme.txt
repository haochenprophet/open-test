1.build in windows should use cmd option : -D WINDOWS_OS

2.[usage]: serial [option] {r, w ; k,R; t,v;} 
	r: r <filename>  [COM[n]] [bps] ie:./serial r read.txt  2 
	w: w <filename>  [COM[n]] [bps] ie:./serial  w write.txt 1 
	k: k  [COM[n]] [bps] ie:./serial  k 1
	R: R  [COM[n]] [bps] ie:./serial  R 1
	t: t  [COM[n]] [bps] [count] ie:./serial t 1 9600 512
	v: v  [COM[n]] [bps] ie:./serial  v 1 9600
   