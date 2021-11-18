
#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QtWidgets>

class Window : public QWidget
{
  Q_OBJECT

private:
  bool r;
  bool r_15;
  bool r_26;
  bool re_15;
  bool re_26;
  const char *f_name;
  int func_id;
  int composition_graphs;
  int n;
  int s;
  int p;
  double a;
  double b;

public:
  Window (QWidget *parent);

  QSize minimumSizeHint () const;
  QSize sizeHint () const;

  int command_line (int argc, char *argv[]);
  double value (double t, double* x, int n, double* c);
  double value_26 (double t, double* x, int n, double* c);
  void c_26(double* f, double* x, double* d, double* c);
  void c_15(double* f, double* x, double* d, double* c);
  void m_15(int n, double* x, double* f, double* c);
  void m_26(int n, double* x, double* f, double* c);
  double (*f) (double);
  double (*f_derivative) (double);
  double (*f_second_derivative) (double);

public slots:
  void q1 ();
  void q2 ();
  void q3 ();
  void q4 ();
  void q5 ();
  void q6 ();
  void q7();
  void q8();


protected:
  void paintEvent (QPaintEvent *event);
};

#endif
