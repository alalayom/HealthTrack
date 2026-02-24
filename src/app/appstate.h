#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QDate>

class AppState : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate selectedDate READ getSelectedDate WRITE setSelectedDate NOTIFY selectedDateChanged FINAL)

public:
    explicit AppState(QObject* pParent = nullptr);

    QDate getSelectedDate() const;
    void setSelectedDate(const QDate& pSelectedDate);

signals:
    void selectedDateChanged(const QDate& pDate);

private:
    QDate mSelectedDate;
};

#endif // APPSTATE_H
