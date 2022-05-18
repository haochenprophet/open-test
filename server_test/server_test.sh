echo [CPU]:
cd cpu
sh test_model_name.sh
cd ..

echo [Memory]:
cd memory
sh test_mem_size.sh
cd ..

echo [Disk]:
cd disk
sh test_disk_exist.sh
cd ..

echo [PCI]:
cd pci
sh test_pci_exist.sh
cd ..
