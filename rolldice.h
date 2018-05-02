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
    int firstPlayer;
    //int getFirst();
    void setType(int type);
    int getType();

private:
    Ui::rollDice *ui;
    bool rollingFlag;
    int type;
    QString bgfile;
    QMovie *bgMovie;
    QPushButton *rollButton;
    QPushButton *beginButton;
    QLabel *diceLabel;
    QLabel *resultLabel;
    QVBoxLayout *layout;
    int k;

private slots:
    void roll();
};

#endif // ROLLDICE_H
