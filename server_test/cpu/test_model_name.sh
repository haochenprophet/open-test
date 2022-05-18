
#$1 out put log
#$? diff return 0:pass 1:fail

#where
echo $PWD/$0

#log
log_file="cpu.log"
if [ -n "$1" ];then
  log_file=$1
fi


#check ini
if [ ! -f "model_name.ini" ] ; then
 grep 'model name' /proc/cpuinfo >model_name.ini
 echo model_name.ini is create!
else
 echo model_name.ini is exist!
fi

#cmp

grep 'model name' /proc/cpuinfo >model_name.log
diff model_name.ini model_name.log

#output 
if test $? -eq 0 ; then
  echo PASS:CPU model name test pass!
  echo PASS:CPU model name test pass! >>$log_file
else
  echo FAIL:CPU model name test fail!
  echo FAIL:CPU model name test fail! >>$log_file
  cat model_name.log
fi
