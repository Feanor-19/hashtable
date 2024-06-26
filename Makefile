CC=g++

SAN = -fsanitize=alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr,leak,address
CFLAGS  =	-D _DEBUG -ggdb3 -std=c++17 -Wall -Wextra -Weffc++ 									\
			-Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations 				\
			-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported 				\
			-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal 						\
			-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 				\
			-Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual 		\
			-Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow 					\
			-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 			\
			-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types 			\
			-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef 				\
			-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix 	\
			-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs 	\
			-Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector 				\
			-fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer					\
			-Wstack-usage=8192 -pie -fPIE -Werror=vla $(SAN)
			

OBJ = obj
SRC = src
BIN = bin
OUT = $(BIN)/prog
LST = lst

DEDLIST_SRC = dedlist_src
DEDLIST_OBJ = dedlist_obj

SOURCES 		= $(wildcard $(SRC)/*.cpp)
OBJFILES 		= $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.cpp=.o))

SOURCES_DEDLIST  = $(wildcard $(DEDLIST_SRC)/*.cpp)
OBJFILES_DEDLIST = $(patsubst $(DEDLIST_SRC)/%,$(DEDLIST_OBJ)/%,$(SOURCES_DEDLIST:.cpp=.o))

OPTIMIZE		= -O3
BASE_LINK		= $(CC) -o $@ $(OPTIMIZE) $(CFLAGS) $^
BASE_CMPL		= $(CC) -c $(OPTIMIZE) $(CFLAGS) -masm=intel -march=native -o $@ $<

$(OUT) : $(OBJFILES) $(OBJFILES_DEDLIST)
	$(BASE_LINK)

$(OBJ)/%.o : $(SRC)/%.cpp
	@$(BASE_CMPL)

$(DEDLIST_OBJ)/%.o : $(DEDLIST_SRC)/%.cpp
	@$(BASE_CMPL)

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)

.PHONY: clean_out
clean_out:
	rm -f out/*

.PHONY: run
run:
	$(OUT) $(ARGS)



.PHONY: gen_hash_funcs_lst
gen_hash_funcs_lst:
	g++ $(OPTIMIZE) -I $(DEDLIST_SRC) -S -masm=intel -o lst/hashfuncs.asm src/hashfuncs.cpp



.PHONY: make_asm
make_asm:
	$(CC) -S -march=native -masm=intel -I $(DEDLIST_SRC) $(OPTIMIZE) $(FILE)


.PHONY: for_prof
for_prof:
	$(CC) $(OPTIMIZE) -g -march=native -masm=intel -o $(OUT) $(SOURCES)

.PHONY: perf_record
perf_record: for_prof
	cpufreq-info | grep "current policy"
	sudo perf record $(OUT) -t

.PHONY: perf_report
perf_report:
	sudo perf report -n -f

.PHONY: show_freq_policy
show_freq_policy:
	cpufreq-info | grep "current policy"

MAX_FREQ = 1.6
.PHONY: set_max_freq
set_max_freq:
	cpupower frequency-set -u $(MAX_FREQ)GHz