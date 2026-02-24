#include "appstate.h"

AppState::AppState(QObject* pParent)
    : QObject(pParent),
    mSelectedDate(QDate::currentDate())
{

}

QDate AppState::getSelectedDate() const
{
    return mSelectedDate;
}

void AppState::setSelectedDate(const QDate& pSelectedDate)
{
    if (mSelectedDate == pSelectedDate)
    {
        return;
    }

    mSelectedDate = pSelectedDate;
    emit selectedDateChanged(mSelectedDate);
}
