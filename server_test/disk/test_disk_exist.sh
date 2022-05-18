
#$1 out put log
#$? diff return 0:pass 1:fail

#where
echo $PWD/$0

#log
log_file="disk.log"
if [ -n "$1" ];then
  log_file=$1
fi


#check ini
if [ ! -f "fdisk.ini" ] ; then
 sudo fdisk -l | grep "Disk /dev/sd" >fdisk.ini
 echo fdisk.ini is create!
else
 echo fdisk.ini is exist!
fi

#cmp

sudo fdisk -l | grep "Disk /dev/sd" >fdisk.log
diff fdisk.ini fdisk.log

#output 
if test $? -eq 0 ; then
  echo PASS:DISK device exist test pass!
  echo PASS:DISK device exist test pass! >>$log_file
else
  echo FAIL:DISK device exist test fail!
  echo FAIL:DISK device exist test fail! >>$log_file
  cat fdisk.log
fi
