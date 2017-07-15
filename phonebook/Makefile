
# compiler
CC ?= gcc
# CC = clang

# compiler common options
CFLAGS_common = -Wall -std=gnu99

# compiler optimization options
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

# common source code
SRCS_common = main.c

# targets want to execute
# EXEC = phonebook_orig phonebook_small_struct  phonebook_list2bst phonebook_hash
EXEC = phonebook_hash

debug: CFLAGS_common += -g
debug: $(EXEC)

.PHONY: all
all: $(EXEC)


phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) $(CFLAGS_compiler) \
		-DIMPL="\"$@.h\"" -D_ORIG_STRUCT -o $@ \
		$(SRCS_common) $@.c

phonebook_small_struct: $(SRCS_common) phonebook_small_struct.c phonebook_small_struct.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(CFLAGS_compiler) \
		-DIMPL="\"$@.h\"" -D_SMALL_STRUCT -o $@ \
		$(SRCS_common) $@.c

phonebook_bst: $(SRCS_common) phonebook_bst.c phonebook_bst.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(CFLAGS_compiler) \
		-DIMPL="\"$@.h\"" -D_BST -o $@ \
		$(SRCS_common) $@.c

phonebook_list2bst: $(SRCS_common) phonebook_list2bst.c phonebook_list2bst.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(CFLAGS_compiler) \
		-DIMPL="\"$@.h\"" -D_LIST2BST -o $@ \
		$(SRCS_common) $@.c

phonebook_hash: $(SRCS_common) phonebook_hash.c phonebook_hash.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(CFLAGS_compiler) \
		-DIMPL="\"$@.h\"" -D_HASH -o $@ \
		$(SRCS_common) $@.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_small_struct
	# perf stat --repeat 100 \
	# 	-e cache-misses,cache-references,instructions,cycles \
	# 	./phonebook_bst
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_list2bst
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_hash
		
output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png
