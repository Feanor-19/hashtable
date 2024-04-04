CC=g++

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
			-Wstack-usage=8192 -pie -fPIE -Werror=vla 
			
SAN = -fsanitize=alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
sanitize_banned = leak, address

OBJ = obj
SRC = src
BIN = bin
OUT = $(BIN)/mandelbrot
LST = lst

SOURCES 		= $(wildcard $(SRC)/*.cpp)
OBJFILES 		= $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.cpp=.o))

OPTIMIZE		= -O3
BASE_LINK		= $(CC) -o $@ $(OPTIMIZE) $(CFLAGS) $^
BASE_CMPL		= $(CC) -c $(OPTIMIZE) $(CFLAGS) -march=native -o $@ $<

$(OUT) : $(OBJFILES)
	$(BASE_LINK)

$(OBJ)/%.o : $(SRC)/%.cpp $(SRC)/%.h
	@$(BASE_CMPL)

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)

.PHONY: run
run:
	$(OUT)