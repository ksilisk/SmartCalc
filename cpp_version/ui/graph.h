#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <iostream>

#include "../backend/base.hpp"
#include "../backend/calculator.hpp"
#include "../backend/parser.hpp"

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  void scailing();
  void rescale();
  void plot(char *expr);
  void graph_proccessing();

 private slots:
  void replot();

 private:
  Ui::Graph *ui;
  double xBegin = -1000000, xEnd = 1000000;
  double step;
  std::pair<std::vector<double>, std::vector<double>> points;
};

#endif  // GRAPH_H
