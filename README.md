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

## Vector and matrices functions

Header: "vector.h" <br />
Folder: vector

* Структура с координатами t_vector, определящая вектор  $(x, y, z)$, тип данных каждой координаты - float

* Создание переменной t_vector по трем переданным числам типа float <br />
`void	new_vector(t_coord *result, float x, float y, float z)` <br />

* Определение вектора $\overrightarrow{AB}$ по двум точкам $A(x_1, y_1, z_1)$ и $B(x_2, y_2, z_2$) <br />
$\overrightarrow{AB}= (x_2-x_1, y_2-y_1, z_2=z_1)$ <br />
`void	new_vector_by_two_points(t_coord *result, t_coord *a, t_coord *b)` <br />

* Определение длины вектора $\overrightarrow{AB}=(x, y, z)$ <br />
$|\overrightarrow{AB}|=\sqrt{x^2+y^2+z^2}$ <br />
`float	vector_length(t_coord *vector)`  <br />
По двум точкам: <br />
$|\overrightarrow{AB}|=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2+(z_2-z_1)^2}$  <br />

* Скалярное произведение вектора на число <br />
$\lambda\overrightarrow{a}=(\lambda a_x, \lambda a_y, \lambda _z )$ <br />
`void	scalar_multiplication(t_coord *vector, float lambda)` <br />

* Сумма/разность двух векторов <br />
$\overrightarrow{a}\pm\overrightarrow{b}=(a_x\pm b_x, a_y \pm b_y, a_z \pm b_z)$ <br />
`void	vector_addition(t_coord *result, t_coord *a, t_coord *b)` <br />
`void	vector_subtraction(t_coord *result, t_coord *a, t_coord *b)`

* Нахождение орта (вектора единичной длины)  <br />
$\overrightarrow{e}_{\overrightarrow{a}}=\frac{\overrightarrow{a}}{|\overrightarrow{a}|}$  <br />
`void	normalizing_vector(t_coord *result, t_coord *vector)`

* Скалярное умножение векторов
$\overrightarrow{a}\overrightarrow{b}=a_x b_x + a_y b_y + a_z b_z$

* Вычисление угла между векторами
$\cos{\phi}=\frac{\overrightarrow{a}\overrightarrow{b}}{|\overrightarrow{a}||\overrightarrow{b}| }$

Дополнительные функции для визуалиции:
- [X] Вывод на stdout вектора vector, опционально с именем вектора name <br />
`void	print_vector(char *name, t_coord *vector);`

## Формулы пересечения луча с объектами

### Пересечение луча и плоскости
$\begin{equation*}
 \begin{cases}
   x=a+td \quad \text{луч}
   \\
   (x,n)=r \quad \text{плоскость}
 \end{cases}
\end{equation*}$

где
* $a$ - точка нахождения камеры
* $d$ - вектор луча
* $n$ - вектор нормали к плоскости
* $r$ - точка плоскости

Отсюда, решение уравнения:
$t=\frac{((r - a), n)}{(d,n)}$

Условия:
* если $(d,n)=0$ луча параллелен плоскости,то есть не пересекает ее
* если $(t>0)$ луч пересекает плоскость в сторону проецирования

Нормаль, которая будет использоваться при дальнейшем вычислении отраженного луча, должна составлять тупой угол с направляющим вектором d.

## Useful source
* https://www.youtube.com/playlist?list=PLUJCSGGiox1Tm3X9ayvMi09K_-RALHJM5 - tutorial from lessie
* https://www.youtube.com/watch?v=e1xrz9wNpB8&feature=youtu.be - edu_events_mow miniRT by dcelsa
* https://habr.com/ru/post/342510/ - Трёхмерная графика с нуля. Часть 1: трассировка лучей
* https://habr.com/ru/post/436790/ - 256 строчек голого C++: пишем трассировщик лучей с нуля за несколько часов
* https://www.youtube.com/watch?v=UTz7ytMJ2yk - Пересечение луча и цилиндра

https://stackoverflow.com/questions/73866852/ray-cylinder-intersection-formula
https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm

https://docs.google.com/document/d/1UwsGC-uncR2P_btMNHE64VN8pahZCZhuCGPQeTWCqBg/edit?usp=sharing