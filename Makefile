bstart : cpos.o report.o menu.o common.o prog.o bill.o order.o 
	@-cc -o pstart cpos.o report.o menu.o common.o prog.o bill.o order.o -lncurses
	@echo link-finish

cash.o : cpos.c cash.h key.h mpos.c
	@-cc -c cpos.c -Wno-cpp -Wno-format -Wno-format-security
	@echo compiling

report.o : report.c creport.c key.h mpos.c
	@-cc -c report.c -Wno-cpp -Wno-format -Wno-format-security
	@echo compiling

menu.o : menu.c menu.h key.h clean.h
	@-cc -c menu.c -Wno-cpp -Wno-format -Wno-format-security
	@echo compiling

common.o : common.c common.h key.h  clean.h
	@-cc -c common.c -Wno-cpp -Wno-format -Wno-format-security
	@echo compiling
	
prog.o : prog.c prog.h cprog.c key.h clean.h 
	@-cc -c prog.c -Wno-cpp -Wno-format -Wno-format-security
	@echo compiling

bill.o : bill.c bill.h cbill.c key.h clean.h 
	@-cc -c bill.c -Wno-cpp -Wno-format -Wno-format-security
	@echo compiling

order.o : morder.c order.c cbill.c bill.h key.h clean.h 
	@-cc -c order.c -Wno-cpp -Wno-format -Wno-format-security
	@echo compiling

clean :
	rm -rf *.o
	rm -rf pstart

