#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QCheckBox;
class QHBoxLayout;
class QGridLayout;
class QVBoxLayout;
class QLabel;

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
    QComboBox *y, *fonts;
    QCheckBox *au;
    QSpinBox *nc;
    QLineEdit *name, *email, *repo, *type, *pass;
    QPushButton *preview, *invert, *doit;
    QGridLayout *l;
    QHBoxLayout *h, *h2, *h3;
    QVBoxLayout *v;
    QLabel *lbl, *al;
};
#endif // MAINWINDOW_H
