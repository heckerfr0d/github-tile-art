#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QComboBox;
class QSpinBox;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void doIT();
    void inv();
    void translate();
private:
    QComboBox *y;
    QSpinBox *nc;
    QComboBox *fonts;
    QLineEdit *name;
    QLineEdit *email;
    QLineEdit *repo;
    QLineEdit *type;
    QLineEdit *pass;
    QPushButton *preview;
    QPushButton *invert;
    QPushButton *doit;
};
#endif // MAINWINDOW_H
