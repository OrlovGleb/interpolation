#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>

#include "window.h"

int main (int argc, char *argv[])
{
  QApplication app (argc, argv);

  QMainWindow *window = new QMainWindow;
  QMenuBar *tool_bar = new QMenuBar (window);
  Window *graph_area = new Window (window);
  QAction *action;

  if (graph_area->command_line (argc, argv))
    {
      return -1;
    }

  action = tool_bar->addAction ("&Изменить функцию", graph_area, SLOT (q1 ()));
  action->setShortcut (QString ("0"));

  action = tool_bar->addAction ("&Изменить графики", graph_area, SLOT (q2 ()));
  action->setShortcut (QString ("1"));

  action = tool_bar->addAction ("&Уменьшение масштаба", graph_area, SLOT (q3 ()));
  action->setShortcut (QString ("2"));

  action = tool_bar->addAction ("&Увеличение масштаба", graph_area, SLOT (q4 ()));
  action->setShortcut (QString ("3"));

  action = tool_bar->addAction ("&Увеличить n", graph_area, SLOT (q5 ()));
  action->setShortcut (QString ("4"));

  action = tool_bar->addAction ("&Уменьшить n", graph_area, SLOT (q6 ()));
  action->setShortcut (QString ("5"));

  action = tool_bar->addAction ("&+ максимум", graph_area, SLOT (q7 ()));
  action->setShortcut (QString ("6"));

  action = tool_bar->addAction ("&- максимум", graph_area, SLOT (q8 ()));
  action->setShortcut (QString ("7"));

  action = tool_bar->addAction ("&Выход", window, SLOT (close ()));
  action->setShortcut (QString ("0"));

  tool_bar->setMaximumHeight (30);

  window->setMenuBar (tool_bar);
  window->setCentralWidget (graph_area);
  window->setWindowTitle ("Graph");

  window->show ();
  app.exec ();
  delete window;
  return 0;
}
