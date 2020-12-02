#pragma once
/*it's a homemade c string lbrary*/
#ifndef _HMCSL
	#define _HMCSL
	#include<stdio.h>
	#include<stdlib.h>
	int strlen(const char* str) {/*1)определение длины строки*/
		int it = 0;
		while (str[it] != '\0')it++;/*идём до конца строки*/
		return it;
	}
	char* revstr(char* str) {/*11)инвертирование строки*/
		int sz = strlen(str), it1, it2, tmp;
		for (it1 = 0, it2 = sz - 1; it1 < it2; it1++, it2--) {
			tmp = str[it1];
			str[it1] = str[it2];
			str[it2] = tmp;
		}
		return str;
	}
	char* deleteSpaces(char* str) {/*6)удаление лишних пробелов
	вариант с выделением памяти, работает за O(n)*/
		int sz = strlen(str), it1, it2 = 0;
		char* newstr = (char*)malloc(sizeof(char) * (sz + 1));/*sz+1 чтобы хватило места для \0, когда пробелов нет*/
		if (!newstr) {
			return NULL;
		}
		for (it1 = 0; it1 < sz; it1++)
			if (str[it1] != ' ')
				newstr[it2++] = str[it1];/*сохраняем всё кроме пробелов*/
		newstr[it2] = '\0';
		for (it1 = 0; it1 <= it2; it1++)
			str[it1] = newstr[it1];
		free(newstr);/*освобождаем память*/
		return str;
	}
	char* deleteSpaceslong(char* str) {/*6)удаление лишних пробелов
	вариант сдвигом символов, O(n^2)*/
		int sz = strlen(str), it1, it2, it3;
		for (it1 = 0; str[it1] != '\0';) {
			if (str[it1] == ' ') {
				it2 = 0;
				while (str[it1 + it2] != '\0') {
					str[it1 + it2] = str[it1 + it2 + 1];
					it2++;
				}
				continue;
			}
			it1++;
		}
		return str;
	}
	char* downreg(char* str) {/*10)понижение регистра*/
		int it = 0;
		for (it = 0; str[it] != '\0'; it++)
			if (str[it] >= 'A' && str[it] <= 'Z') /*меняем только большие буквы*/
				str[it] = str[it] - 'A' + 'a';
		return str;
	}
	char* upreg(char* str) {/*9)повышение регистра*/
		int it = 0;
		for (it = 0; str[it] != '\0'; it++)
			if (str[it] >= 'a' && str[it] <= 'z') /*меняем только маленькие буквы*/
				str[it] = str[it] - 'a' + 'A';
		return str;
	}
	long converToI(const char* str) {/*7)перевод строки цифр в число
		игнорирует пробелы в начале, далее определяет знак и генерирует число пока не лойдёт до конца строки или */
		long a = 0;
		int it = 0, sign = 1;
		while (str[it] == ' ')it++;/*пропускает пробелы в начале*/
		if (str[it] == '-') {/*учесть знак*/
			sign = -1;
			it++;
		}
		if (str[it] == '+')it++;/*пропустить знак +*/
		for (it; str[it] != '\0'; it++)
			if (str[it] >= '0' && str[it] <= '9')
				a = a * 10 + (str[it] - '0') * sign;/*запоминаем очередную цифру*/
			else
				return a;/*число закончилось*/
		return a;/*строка с числом закончилась*/
	}
	char* convertToS(long number) {/*8)перевод числа в строку*/
		long copy = number, digits = 0, it;
		char* str;
		while (copy) {
			digits++;
			copy /= 10;
		}
		digits = (digits + 1 + (number < 0));/*number<0 чтобы выделить место под - если число отрицательное*/
		str = (char*)malloc(sizeof(char) * digits);
		if (!str)return str;/*если память не вделилась*/
		if (number < 0) {/*записать - в на первое место*/
			str[0] = '-';
			number = -number;
		}
		str[digits - 1] = '\0';
		it = digits - 2;
		while (number) {
			str[it--] = number % 10 + '0';
			number /= 10;
		}
		return str;
	}
	int strcmp(const char* str1, const char* str2) {/*2)сравнение строк лексикографически
		-1 str1<str2
		0 str1=str2
		1 str1>str2*/
		int it = 0;
		while (str1[it] == str2[it] && str1[it] != '\0' && str2[it] != '\0')
			it++;/*идём пока не дойдём до конца одной из строк или пока не встретим различные символы*/
		if (str1[it] == '\0' || str2[it] == '\0') {/*если хотябы одна из строк подошла к концу*/
			if (str1[it] == '\0' && str2[it] == '\0')
				return 0;/*строки равны*/
			if (str1[it] == '\0')
				return -1;/*первая строка короче*/
			if (str2[it] == '\0')
				return 1;/*вторая строка короче*/
		}
		if (str1[it] < str2[it])
			return -1;/*первая строка меньше*/
		return 1;/*вторая строка меньше*/
	}
	int strncmp(const char* str1, const char* str2, int n) {/*сравнение строк лексикографически сравнивая не более n символов
		-1 str1<str2
		0 str1=str2
		1 str1>str2*/
		int it = 0;
		while (str1[it] == str2[it] && str1[it] != '\0' && str2[it] != '\0' && n != it)
			it++;/*идём пока не дойдём до конца одной из строк или пока не встретим различные символы или пока не сравним n символов*/
		if (n == it)return 0;/*если обработали требуемые n символов*/
		if (str1[it] == '\0' || str2[it] == '\0') {/*если хотябы одна из строк подошла к концу*/
			if (str1[it] == '\0' && str2[it] == '\0')
				return 0;/*строки равны*/
			if (str1[it] == '\0')
				return -1;/*первая строка короче*/
			if (str2[it] == '\0')
				return 1;/*вторая строка короче*/
		}
		if (str1[it] < str2[it])
			return -1;/*первая строка меньше*/
		return 1;/*вторая строка меньше*/
	}
	int strcmplen(const char* str1, const char* str2) {/*3)сравнение строк по длине
		-1 str1<str2
		0 str1=str2
		1 str1>str2*/
		int sz1 = strlen(str1), sz2 = strlen(str2);
		if (sz1 < sz2)return -1;
		if (sz1 == sz2)return 0;
		return 1;
	}
	char* strstr(const char* str1, const char* str2) {/*5)поиск подстроки в строке*/
		int sz1 = strlen(str1), sz2 = strlen(str2);
		if (sz2 > sz1)return NULL;/*подстрока длиннее строки*/
		for (int i = 0; i < sz1 - sz2; i++) {
			if (!strncmp(str1 + i, str2, sz2)) {/*ф-ция strncmp сравнивает первые sz2 символов строки str2 с str+i
				фактически она вернёт 0 если str2 является префиком строки str+i, а значит и подстрокий str*/
				return str1 + i;
			}
		}
		return NULL;
	}
	char* strcpy(const char* from, char* place) {/*4)копирование строки. корирует пока не доёдёт до конца from.*/
		int it = 0;
		while (from[it] != '\0') {
			place[it] = from[it];
			it++;
		}
		place[it] = '\0';
		return place;
	}
	char* strncpy(const char* from, char* place, int n) {/*4)копирование строки.
		корирует пока не доёдёт до конца from или не более n символов. т.е. place должно иметь n+1 место*/
		int it = 0;
		while (from[it] != '\0' && it != n) {
			place[it] = from[it];
			it++;
		}
		place[it] = '\0';
		return place;
	}
#endif // !_HMCSL
