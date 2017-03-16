
1. 7-series-chipset-pch-datasheet.pdf  from 

http://www.intel.com/content/dam/www/public/us/en/documents/datasheets/7-series-chipset-pch-datasheet.pdf

2.[usage]: gpio [option] {p , l , i , o , n ,} 
	p: parse  p <gpio_pin> [gpio_base] ie:./gpio r 36 
	l: list   l [gpio_base=default 500]  ie:./gpio l 
	i: input  i <gpi_pin> [gpio_base] ie:./gpio i 36 
	o: ouput  o <gpo_pin> <1:high,0:low> [gpio_base] ie:./gpio  o 36 1 
	n: native n <gpio_pin> [gpio_base] ie:./gpio  n 36
				
