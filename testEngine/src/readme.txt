1.build in windows should use cmd option : -D WINDOWS_OS

2.test ini file format :{errorlevel,cmd,desc}
  errorlevel:0:error if(cmd!=0) report error; 1:warning : 2:ignore test
 {1, ping 127.0.0.1 , self ping test.}

3.[usage]:
   testEngine test_engine_items.ini