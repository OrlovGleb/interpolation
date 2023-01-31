# interpolation
Программа интерполяции функции одной переменной с помощью QtCreator. Используется 2 метода: Метод интерполяции кубическими многочленами с дополнительным узлом(1) и интерполячция кубическими многочленами методом Акимы(2).

1. Программа имеет 4 обязательных аргумента:
2. 
(1) a – левый конец отрезка (тип double),

(2) b – правый конец отрезка (тип double),

(3) n – начальное значение для числа точек интерполяции (тип int),

(4) k – начальное значение номера приближаемой функции (тип int).


2. В программе должны быть реализованы подпрограммы для задания следующих приближаемых
функций f(x) по аналитически заданной формуле в зависимости от параметра k:

(1) для k = 0 f(x) = 1

(2) для k = 1 f(x) = x

(3) для k = 2 f(x) = x^2

(4) для k = 3 f(x) = x^3

(5) для k = 4 f(x) = x^4

(6) для k = 5 f(x) = e^x

(7) для k = 6 f(x) = 1/(25x^2 + 1)

3. Программа содержит подпрограмму графического представления заданной функции в
окне приложения, разработанного с помощью библиотеки Qt5. Особенности графического интерфейса:

(1) Автоматическое масштабирование графика и вывод на экран максимального по модулю значения на участке интерполяции,

(2) По нажатию клавиши "0" циклически меняется номер k приближаемой функции и перерисовывается новый график,

(3) По нажатию клавиши "1" циклически меняется состав отображаемых графиков и перерисовывается новый график:

  i. показывается график функции и график ее приближения по методу (1);
  
  ii. показывается график функции и график ее приближения по методу (2);
  
  iii. показывается график функции и графики ее приближения по методам (1) и (2);
  
  iv. показывается графики погрешностей методов (1) и (2);
  
(4) По нажатию клавиши "2" увеличивается, а по нажатию клавиши "3" уменьшается масштаб текущего графика, осуществляя двукратное растяжение/сжатие оси Х относительно середины отрезка [a, b] и перерисовку графика в новом масштабе,

(5) По нажатию клавиши "4" увеличивается, а по нажатию клавиши "5" уменьшается в 2 раза
число точек приближения n и перерисовываются графики для нового числа точек приближения,

(6) По нажатию клавиши "6" прибавляется, а по нажатию клавиши "7" вычитается к/от вычисленного значения функции одна десятая максимума функции f на отрезке
[a, b], и перерисовывается новый график. 
