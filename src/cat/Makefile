CF=-Wall -Werror -Wextra

all: clean s21_cat
	
s21_cat:
	gcc $(CF) expofcat.c -o s21_cat


clean:
	rm -rf *.o s21_cat
test:
	sh tests.sh
