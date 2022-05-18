
#$1 out put log
#$? diff return 0:pass 1:fail

#where
echo $PWD/$0

#log
log_file="pci.log"
if [ -n "$1" ];then
  log_file=$1
fi


#check ini
if [ ! -f "lspci.ini" ] ; then
 lspci >lspci.ini
 echo lspci.ini is create!
else
 echo lspci.ini is exist!
fi

#cmp

lspci >lspci.log
diff lspci.ini lspci.log

#output 
if test $? -eq 0 ; then
  echo PASS:PCI device exist test pass!
  echo PASS:PCI device exist test pass! >>$log_file
else
  echo FAIL:PCI device exist test fail!
  echo FAIL:PCI device exist test fail! >>$log_file
fi
