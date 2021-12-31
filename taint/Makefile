bin  = ./bin
obj  = ./obj
src  = ./src
riscv = ../riscv

ld  = $(riscv)/bin/riscv64-unknown-linux-gnu-ld
cc  = $(riscv)/bin/riscv64-unknown-linux-gnu-g++
ccf = -c -std=c++17 -I $(src) -march=rv64imafdc

obj_files = $(shell find $(obj) -name *.o)
cpp_files = $(shell find $(src) -name *.cpp)

target = taint

$(target) : cpp_objs
	@$(cc) $(obj_files) -o $(bin)/$(target)

cpp_objs : $(cpp_files)
	@$(foreach file, \
		$^, \
		$(cc) $(file) -o $(patsubst %.cpp, $(obj)/%.o, $(notdir $(file))) $(ccf);)

clean :
	@rm $(obj)/* 2>/dev/null
	@rm $(bin)/* 2>/dev/null

release :
	scp -P 52010 $(bin)/$(target) ubuntu@localhost:~/capstone/$(target)
