#include <QPainter>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include "window.h"
//параметры по умолчанию
#define A -10
#define B 10
#define N 20
#define FUNC_ID 1
//задаем функции и их производные
static
double f_0 (double x)
{
  return pow(x, 0);
}

static
double f_1 (double x)
{
  return x;
}

static
double f_2 (double x)
{
  return x * x;
}

static
double f_3 (double x)
{
  return x * x * x;
}

static
double f_4 (double x)
{
  return x * x * x * x;
}

static
double f_5 (double x)
{
  return exp(x);
}

static
double f_6 (double x)
{
  return 1 / (25 * x * x + 1);
}

static
double f_0_d (double x)
{
  return 0 * x;
}

static
double f_1_d (double x)
{
  return pow(x, 0);
}

static
double f_2_d (double x)
{
  return 2 * x;
}

static
double f_3_d (double x)
{
  return 3 * x * x;
}

static
double f_4_d (double x)
{
  return 4 * x * x * x;
}

static
double f_5_d (double x)
{
  return exp(x);
}

static
double f_6_d (double x)
{
  return (-50 * x) / ((25 * x * x + 1) * (25 * x * x + 1));
}



//функция подсчета разделенной разности
double razn (double *f, double *x, int i, int j)
{
    if (j < i)
        std::swap(j, i);
    return (f[j] - f[i]) / (x[j] - x[i]);
}

//дополнительная функция для подсчета коэффицентов в методе Акимы
double w (double *f, double* x, int j)
{
    double q = razn(f, x, j + 1, j);
    q = q - razn(f, x, j, j - 1);
    return fabs(q);
}





//подсчет коэффицентов для кубического многочлена методом акимы
void Window::c_26(double* f, double* x, double* d, double* c)
{
    for (int i = 2; i < n - 3; i++)
    {
        c[4 * i] = f[i];
        c[4 * i + 1] = d[i];
        c[4 * i + 2] = (3 * razn(f, x, i, i + 1) - 2 * d[i] - d[i + 1])/(x[i + 1] - x[i]);
        c[4 * i + 3] = (d[i] + d[i + 1] - 2 * razn(f, x, i, i + 1))/ ((x[i + 1] - x[i])*(x[i + 1] - x[i]));
    }
    //коэффиценты в приграничных многочленах по методу отсутствия узла
    c[4*1]=f[0];
    c[4*1+1] = razn(f, x, 0, 1);
    c[4*1+2] =(f[2]-c[4*1]-(c[4*1+1])*(x[2]-x[0]))/((x[2]-x[1])*(x[2]-x[0]));
    c[4*1+3] = (d[2]-c[4*1+1]-(c[4*1+2])*((2)*(x[2])-x[1]-x[0]))/((x[0])*(x[1]-x[2])-(x[1])*(x[2])+(x[2])*(x[2]));

    c[0] = c[4 * 1];
    c[1] = c[4 * 1 + 1];
    c[2] = c[4 * 1 + 2];
    c[3] = c[4 * 1 + 3];

    c[4*(n-3)]=f[n-3];
    c[4*(n-3)+1] = razn(f, x, n-3, n-2);
    c[4*(n-3)+2] =(f[n-1]-c[4*(n-3)]-c[4*(n-3)+1]*(x[n-1]-x[n-3]))/((x[n-1]-x[n-2])*(x[n-1]-x[n-3]));
    c[4*(n-3)+3] = (d[n-3]-c[4*(n-3)+1]-c[4*(n-3)+2]*(x[n-3]-x[n-2]))/((x[n-3]-x[n-2])*(x[n-3]-x[n-1]));

    c[4 * (n-2)] = c[4 * (n-3)];
    c[4 * (n-2) + 1] = c[4 * (n-3) + 1];
    c[4 * (n-2) + 2] = c[4 * (n-3) + 2];
    c[4 * (n-2) + 3] = c[4 * (n-3) + 3];    
}
//подсчет коэффицентов для кубического многочлена в методе 15(с дополнительным узлом)
void Window::c_15(double* f, double* x, double* d, double* c)
{
    for (int i = 0; i < n; i++)
    {
        c[4 * i] = f[i];
        c[4 * i + 1] = d[i];
        c[4 * i + 2] = (3 * razn(f, x, i, i + 1) - 2 * d[i] - d[i + 1])/(x[i + 1] - x[i]);
        c[4 * i + 3] = (d[i] + d[i + 1] - 2 * razn(f, x, i, i + 1))/ ((x[i + 1] - x[i])*(x[i + 1] - x[i]));
    }
}


//интерполяция кубическими многочленами Эрмита
void Window::m_15 (int n, double* x, double* f, double* c)
{
    double *d = new double[n+1];
    for (int i = 0; i < n; i++){
        d[i] = f_derivative(x[i]);
    }
    c_15(f, x, d, c);



    delete[] d;
}



//интерполяция кубическими многочленами методом Акимы
void Window::m_26 (int n, double* x, double* f, double* c)
{
    double *d = new double[n];
    double w_l, w_r;

    for (int i = 2; i < n - 2; i++)
    {
        w_l = w(f, x, i - 1);
        w_r = w(f, x, i + 1);
        if (fabs(w_l) < 1e-10 && fabs(w_r) < 1e-10)
        {
            d[i] = (((x[i + 1] - x[i]) * razn(f, x, i - 1, i))+((x[i] - x[i - 1]) * razn(f, x, i, i + 1)))/ (x[i + 1] - x[i - 1]);


        }
        else
        {
            d[i] = (w_r * razn(f, x, i - 1, i)+w_l * razn(f, x, i, i + 1)) / (w_r + w_l);


        }
    }

    c_26(f, x, d, c);

    delete[] d;
}




//подсчет значения кубического многочлена для метода 15
double Window::value (double t, double* x, int n, double* c)
{
  int i;
  for (i = 0; i < n - 1; i++)
  {
      if (fabs(t - x[i]) < 1e-10 || fabs(t - x[i + 1]) < 1e-10)
          break;
      else if (t > x[i] && t < x[i + 1])
          break;
  }

  return c[4 * i] +
         c[4 * i + 1] * (t - x[i]) +
         c[4 * i + 2] * (t - x[i]) * (t - x[i]) +
         c[4 * i + 3] * (t - x[i]) * (t - x[i]) * (t - x[i]);
}

//подсчет значения кубического многочлена для метода 26
double Window::value_26 (double t, double* x, int n, double* c)
{
  int i;
  for (i = 0; i < n - 1; i++)
  {
      if (fabs(t - x[i]) < 1e-10 || fabs(t - x[i + 1]) < 1e-10)
          break;
      else if (t > x[i] && t < x[i + 1])
          break;
  }
  if(fabs(t - x[n-1]) < 1e-10){
      return c[4 * i] +
             c[4 * i + 1] * (t - x[n-3]) +
             c[4 * i + 2] * (t - x[n-3]) * (t - x[n-2]) +
             c[4 * i + 3] * (t - x[n-3]) * (t - x[n-2]) * (t - x[n-1]);
  }
  if(i>1 && i<n-3){
      return c[4 * i] +
             c[4 * i + 1] * (t - x[i]) +
             c[4 * i + 2] * (t - x[i]) * (t - x[i]) +
             c[4 * i + 3] * (t - x[i]) * (t - x[i]) * (t - x[i]);
  }
  if(i == 1 || i == 0){
      return c[4 * i] +
             c[4 * i + 1] * (t - x[0]) +
             c[4 * i + 2] * (t - x[0]) * (t - x[1]) +
             c[4 * i + 3] * (t - x[0]) * (t - x[1]) * (t - x[2]);
  }

  if(i == n-2 || i == n-3 ){
      return c[4 * i] +
             c[4 * i + 1] * (t - x[n-3]) +
             c[4 * i + 2] * (t - x[n-3]) * (t - x[n-2]) +
             c[4 * i + 3] * (t - x[n-3]) * (t - x[n-2]) * (t - x[n-1]);
  }


}


Window::Window (QWidget *parent)
  : QWidget (parent)
{
  a = A;
  b = B;
  n = N;
  func_id = FUNC_ID;
  s = 0;
  p = 0;
  composition_graphs = -1;
  q1();
  q2();
}

QSize Window::minimumSizeHint () const
{
  return QSize (100, 100);
}

QSize Window::sizeHint () const
{
  return QSize (1000, 1000);
}

int Window::command_line (int argc, char *argv[])
{
  if (argc == 1)
    return 0;

  if (argc >= 1 && argc <= 4)
    return -1;

  if (   sscanf (argv[1], "%lf", &a) != 1
      || sscanf (argv[2], "%lf", &b) != 1
      || b - a < 1.e-6
      || (argc > 3 && sscanf (argv[3], "%d", &n) != 1)
      || n <= 2
      || (argc > 4 && sscanf (argv[4], "%d", &func_id) != 1)
      || (func_id < 0 || func_id > 6) )
    return -2;

  return 0;
}

//смена функции
void Window::q1()
{
  func_id = (func_id + 1) % 7;

  switch (func_id)
    {
      case 0:
        f_name = "f (x) = 1";
        f = f_0;
        f_derivative = f_0_d;
        break;
      case 1:
        f_name = "f (x) = x";
        f = f_1;
        f_derivative = f_1_d;
        break;
      case 2:
        f_name = "f (x) = x^2";
        f = f_2;
        f_derivative = f_2_d;
        break;
      case 3:
        f_name = "f (x) = x^3";
        f = f_3;
        f_derivative = f_3_d;
        break;
      case 4:
        f_name = "f (x) = x^4";
        f = f_4;
        f_derivative = f_4_d;
        break;
      case 5:
        f_name = "f (x) = e^x";
        f = f_5;
        f_derivative = f_5_d;
        break;
      case 6:
        f_name = "f (x) = 1/(25*x^2 + 1)";
        f = f_6;
        f_derivative = f_6_d;
        break;
    }
  update ();
}
//смена состава отображаемых графиков
void Window::q2 ()
{
    composition_graphs = (composition_graphs + 1) % 4;

    r = false;
    r_15 = false;
    r_26 = false;
    re_15 = false;
    re_26 = false;

    switch (composition_graphs)
      {
        case 0:
          r = true;
          r_15 = true;
          break;
        case 1:
          r = true;
          r_26 = true;
          break;
        case 2:
          r = true;
          r_15 = true;
          r_26 = true;
          break;
        case 3:
          re_15 = true;
          re_26 = true;
          break;
      }

    update();
}

//уменьшение масштаба по x в 2 раза
void Window::q3 ()
{
    a /= 2;
    b /= 2;
    s++;
    update();
}

//увеличение масштаба по x в 2 раза
void Window::q4 ()
{
    a *= 2;
    b *= 2;
    s--;
    update();
}

//увеличение n
void Window::q5 ()
{
    n *= 2;
    update();
}

//уменьшение n
void Window::q6 ()
{
    if (n < 10) //при n <10 уменьшение n не работает, так как для метода 26 необходимо хотя бы 5 точек
        return;

    n /= 2;
    update();
}

//добавление максимума
void Window::q7()
{
    p++;
    update();
}

//вычитание максимума
void Window::q8()
{
    p--;
    update();
}


//вывод изображения
void Window::paintEvent (QPaintEvent * /* event */)
{
  int i = 0;
  QPainter painter (this);
  double current_x;
  double *x, *f_x;
  double max_y = 0.0;
  double max_f = 0.0;
  double min_y = 0.0;
  double min_f = 0.0;
  double max;
  double l;
  double m;
  double v = (b - a) / (n-1);
  QPen pen_black(Qt::black, 0, Qt::SolidLine);
  QPen pen_blue(Qt::blue, 0, Qt::SolidLine);
  QPen pen_red(Qt::red, 0, Qt::SolidLine);
  QPen pen_green(Qt::green, 0, Qt::SolidLine);
  //задаем массивы со сзначениями x и f
  x = new double[n+1];
  f_x = new double[n+1];

  painter.setPen (pen_black);
  //заполняем массивы
  for (current_x = a; current_x < b; current_x += v, i++)
  {
      x[i] = current_x;
      f_x[i] = f(current_x);
  }
  x[n-1] = b;
  f_x[n-1] = f(b);
  x[n] = b+v; //значения для для дополнительного узла в методе 15
  f_x[n] = f(b+v);

  for (i = 0; i < n; i++) //нахождение максиммума и минимума финкции
  {
      if (f_x[i] > max_f)
          max_f = f_x[i];
      if (f_x[i] < min_f)
          min_f = f_x[i];
  }

  f_x[n / 2] = f_x[n / 2] + p * 0.1 * max_f;

  if (f_x[n / 2] > max_f)
      max_f = f_x[n / 2];
  if (f_x[n / 2] < min_f)
      min_f = f_x[n / 2];

  if (r)
  {
      max_y = max_f;
      min_y = min_f;
  }
  else
  {
      double *c = new double[4 * n];

      m_15(n, x, f_x, c);

      for (current_x = a; current_x < x[n - 1]; current_x += v / 2)
      {
          double current_value = fabs(value(current_x, x, n, c) - f(current_x));
          if (current_value > max_y)
              max_y = current_value;
          if (current_value < min_y)
              min_y = current_value;
      }

      m_26(n, x, f_x, c);

      for (current_x = a; current_x < x[n - 1]; current_x += v / 2)
      {
          double current_value = fabs(value_26(current_x, x, n, c) - f(current_x));
          if (current_value > max_y)
              max_y = current_value;
          if (current_value < min_y)
              min_y = current_value;
      }

      delete [] c;
  }

  painter.save ();
  painter.translate (0.5 * width (), 0.5 * height ());
  painter.scale (width () /(b - a), -height () / (max_y - min_y));
  painter.translate (-0.5 * (a + b), -0.5 * (min_y + max_y));

  //нарисовать график приближаемой функции
  if (r)
  {
      for (i = 0; i < n-1 ; i++)
          painter.drawLine (QPointF(x[i], f_x[i]), QPointF(x[i + 1], f_x[i + 1]));
  }
//нарисовать график функции по методу 15
  if (r_15)
  {
      double *c = new double[4 * n];
      m_15(n, x, f_x, c);

      painter.setPen (pen_green);

      for (current_x = a; current_x < x[n-1]; current_x += v / 2)
          painter.drawLine (QPointF(current_x, value(current_x, x, n, c)), QPointF(current_x + v / 2, value(current_x + v / 2, x, n, c)));

      delete[] c;
  }
//нарисовать график функции по методу 26
  if (r_26)
  {
      double *c = new double[4 * n];
      m_26(n, x, f_x, c);

      painter.setPen (pen_blue);

      for (current_x = a; current_x < x[n - 1]-v / 2; current_x += v / 2){
          painter.drawLine (QPointF(current_x, value_26(current_x, x, n, c)), QPointF(current_x + v / 2, value_26(current_x + v / 2, x, n, c)));
      }
      painter.drawLine (QPointF(b-v / 2, value_26(b-v / 2, x, n, c)), QPointF(b, f(b)));
      delete[] c;
  }
// вывод погрешности
  if (re_15)
  {
      double *c = new double[4 * n];
      m_15(n, x, f_x, c);

      painter.setPen (pen_green);

      for (current_x = a; current_x < x[n - 1]; current_x += v / 2){
          if(fabs(current_x-x[n/2])<1e-10){l = f_x[n / 2];} else {l = f(current_x);}
          if(fabs(current_x+v/2-x[n/2])<1e-10){m = f_x[n / 2];} else {m = f(current_x+v/2);}
          painter.drawLine (QPointF(current_x, fabs(value(current_x, x, n, c) - l)),
                            QPointF(current_x + v / 2, fabs(value(current_x + v / 2, x, n, c) - m)));

         // painter.drawLine (QPointF(current_x, fabs(value(current_x, x, n, c) - f(current_x))),
         //                   QPointF(current_x + v / 2, fabs(value(current_x + v / 2, x, n, c) - f(current_x + v / 2))));
      }
      delete[] c;
  }

  if (re_26)
  {
      double *c = new double[4 * n];
      m_26(n, x, f_x, c);

      painter.setPen (pen_blue);

      for (current_x = a; current_x < x[n - 1]; current_x += v / 2){
          if(fabs(current_x-x[n/2])<1e-10){l = f_x[n / 2];} else {l = f(current_x);}
          if(fabs(current_x+v/2-x[n/2])<1e-10){m = f_x[n / 2];} else {m = f(current_x+v/2);}
          painter.drawLine (QPointF(current_x, fabs(value_26(current_x, x, n, c) - l)),
                            QPointF(current_x + v / 2, fabs(value_26(current_x + v / 2, x, n, c) - m)));
      }
      delete[] c;
  }

  //оси
  painter.setPen(pen_red);
  painter.drawLine (a * pow(2, fabs(s)), 0, b * pow(2, fabs(s)), 0);
  painter.drawLine (0, 2 * (max_y) * pow(2, fabs(s)), 0, 2 * (min_y) * pow(2, fabs(s)));

  painter.restore ();

  max = fabs(max_y) > fabs(min_y) ? fabs(max_y) : fabs(min_y);
  painter.setPen (pen_black);
  painter.drawText (0, 10, (std::string("k = ") + std::to_string(func_id)).c_str());
  painter.drawText (0, 25, f_name);
  painter.drawText (0, 40, (std::string("max{|F_min|, |F_max|} = ") + std::to_string(max)).c_str());
  painter.drawText (0, 55, (std::string("n = ") + std::to_string(n)).c_str());
  painter.drawText (0, 70, (std::string("s = ") + std::to_string(s)).c_str());
  painter.drawText (0, 85, (std::string("p = ") + std::to_string(p)).c_str());


  std::cout << (std::string("max{|F_min|, |F_max|} = ") + std::to_string(max)).c_str() << "\n";

  delete[] x;
  delete[] f_x;
}
