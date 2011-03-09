#ifndef TRAMPROPERTIESWIDGET_H
#define TRAMPROPERTIESWIDGET_H

#include <QWidget>
#include <QTimer>
class Tram;
namespace Ui {
    class TramPropertiesWidget;
}

class TramPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TramPropertiesWidget(Tram* t, QWidget *parent = 0);
    ~TramPropertiesWidget();
private slots:
    void updateTramInformation();
private:
    Ui::TramPropertiesWidget *ui;
    QTimer *m_timer;
    Tram *m_tram;
};

#endif // TRAMPROPERTIESWIDGET_H
