#ifndef ROLLDICE_H
#define ROLLDICE_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QVBoxLayout>
#include <QMovie>


namespace Ui {
class rollDice;
}

class rollDice : public QDialog
{
    Q_OBJECT

public:
    explicit rollDice(QWidget *parent = 0);
    ~rollDice();
    int getFirst();

private:
    Ui::rollDice *ui;
    bool rollingFlag;
    QString bgfile;
    QMovie *bgMovie;
    QPushButton *rollButton;
    QPushButton *beginButton;
    QLabel *diceLabel;
    QLabel *resultLabel;
    QVBoxLayout *layout;
    int k;
    int firstPlayer;
private slots:
    void roll();
};

#endif // ROLLDICE_H
