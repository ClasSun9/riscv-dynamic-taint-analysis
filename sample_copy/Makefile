riscv = ../riscv

cc  = $(riscv)/bin/riscv64-unknown-linux-gnu-as
ccf = -march=rv64imfd -mabi=lp64d
ld  = $(riscv)/bin/riscv64-unknown-linux-gnu-ld

target = sample_copy

$(target) : sample_copy.o
	@$(ld) sample_copy.o -o $(target)

sample_copy.o :
	@$(cc) sample_copy.asm -o sample_copy.o $(ccf)

clean :
	@rm *.o
	@rm $(target)

release :
	scp -P 52010 $(target) ubuntu@localhost:~/$(target)
