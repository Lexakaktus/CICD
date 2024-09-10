CF=-Wall -Werror -Wextra -std=c11 

all: clean s21_grep
	
s21_grep:
	gcc $(CF) s21_grep.c -o s21_grep


clean:
	rm -rf *.o s21_grep
test:
	 sh test_grep.sh