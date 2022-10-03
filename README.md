# miniRT
render simple Computer-Generated-Images 

## External functions

| Functions | #include |Prototype | Description |
| ------ | ------ | ------ | ------ |
| open | <fcntl.h> | int open(const char *path, int oflag, ...)| open or create a file for reading or writing |
| close | <unistd.h> |int close(int fildes); | delete a descriptor from the per-process object reference table |
| read | <sys/types.h> <br /> <sys/uio.h> <br /> <unistd.h> | ssize_t read(int fildes, void *buf, size_t nbyte); | attempts to read nbyte bytes of data <br /> from the object referenced by the descriptor fildes <br /> into the buffer pointed to by buf |
| write | <unistd.h> | ssize_t write(int fildes, const void *buf, size_t nbyte); | attempts to write nbyte of data <br /> to the object referenced by the descriptor fildes <br /> from the buffer pointed to by buf |
| printf | <stdio.h> |  int printf(const char * restrict format, ...); | produces output |
| malloc | <stdlib.h> | void *malloc(size_t size); | allocate memory |
| free | <stdlib.h> | void free(void *ptr); |  deallocates the memory allocation pointed to by ptr |
| perror | <stdio.h> | void perror(const char *s); |  finds the error message corresponding to the current value <br /> of the global variable errno <br /> and writes it |
| strerror | <stdio.h> | char * strerror(int errnum);| accepts an error number argument errnum <br /> and returns a pointer to the corresponding message string |
| exit | <stdlib.h> | void exit(int status); | terminate a process |

Also:

* Use [libft functions](https://github.com/MariaKorshunova/libft) - a set of some functions.

* All functions of the math library

```sh
man 3 math
```

* All functions of the MinilibX
Useful source: https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

```sh
man /usr/share/man/man3/mlx.1
```

## Tasks
- [X] Makefile
- [ ] Mlx management (window, etc)
- [ ] Validation arguments
- [ ] Parser
- [ ] math functions (matrices, vectors etc)
- [ ] object structure
- [ ] scene structure
- [ ] camera


## Math functions

Header: "vector.h" <br />
Folder: vector

- [X] Структура с координатами t_vector, определящая вектор  $(x, y, z)$, тип данных каждой координаты - float
- [X] Создание переменной t_vector по трем переданным числам типа float <br />
`t_coord   *new_vector(float x, float y, float z);`
- [X] Определение вектора $\overrightarrow{AB}$ по двум точкам $A(x_1, y_1, z_1)$ и $B(x_2, y_2, z_2$) <br />
$\overrightarrow{AB}= (x_2-x_1, y_2-y_1, z_2=z_1)$ <br />
`t_coord	*new_vector_by_two_points(t_coord *a, t_coord *b)`
- [X] Определение длины вектора $\overrightarrow{AB}=(x, y, z)$ <br />
$|\overrightarrow{AB}|=\sqrt{x^2+y^2+z^2}$ <br />
`float	vector_length(t_coord *vector)`  <br />
По двум точкам: <br />
$|\overrightarrow{AB}|=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2+(z_2-z_1)^2}$ 
- [X] Скалярное произведение вектора на число <br />
$\lambda\overrightarrow{a}=(\lambda a_x, \lambda a_y, \lambda _z )$ <br />
`void	scalar_multiplication(t_coord *vector, float lambda)`
- [ ] 

Дополнительные функции для визуалиции:
- [X] Вывод на stdout вектора vector, опционально с именем вектора name <br />
`void	print_vector(char *name, t_coord *vector);`



## Useful source
* https://www.youtube.com/playlist?list=PLUJCSGGiox1Tm3X9ayvMi09K_-RALHJM5 - tutorial from lessie
* https://www.youtube.com/watch?v=e1xrz9wNpB8&feature=youtu.be - edu_events_mow miniRT by dcelsa
* https://habr.com/ru/post/342510/ - Трёхмерная графика с нуля. Часть 1: трассировка лучей
* https://habr.com/ru/post/436790/ - 256 строчек голого C++: пишем трассировщик лучей с нуля за несколько часов
