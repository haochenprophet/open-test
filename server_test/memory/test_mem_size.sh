
#$1 out put log
#$? diff return 0:pass 1:fail

#where
echo $PWD/$0

#log
log_file="memory.log"
if [ -n "$1" ];then
  log_file=$1
fi


#check ini
if [ ! -f "mem_size.ini" ] ; then
 grep "MemTotal:" /proc/meminfo >mem_size.ini
 echo mem_size.ini is create!
else
 echo mem_size.ini is exist!
fi

#cmp

grep "MemTotal:" /proc/meminfo >mem_size.log
diff mem_size.ini mem_size.log

#output 
if test $? -eq 0 ; then
  echo PASS:Memory size test pass!
  echo PASS:Memory size test pass! >>$log_file
else
  echo FAIL:Memory size test fail!
  echo FAIL:Memory size test fail! >>$log_file
  cat mem_size.log
fi
