#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include <QObject>

class NavigationManager : public QObject
{

    Q_OBJECT
    Q_PROPERTY(Page currentPage READ getCurrentPage WRITE setCurrentPage NOTIFY currentPageChanged FINAL)

public:
    explicit NavigationManager(QObject* pParent = nullptr);

    enum Page
    {
        Login       = 0,
        Home        = 1,
        Nutrition   = 2,
        Profile     = 3,
        Settings    = 4,
        Sleep       = 5,
        Sport       = 6,
        Statistics  = 7
    };
    Q_ENUM(Page)

    Page getCurrentPage() const;
    void setCurrentPage(Page pPage);

    Q_INVOKABLE void navigateTo(Page pPage);
    Q_INVOKABLE void navigateToNutrition();
    Q_INVOKABLE void navigateToHome();

signals:
    void currentPageChanged();

private:
    Page mCurrentPage
    {
        Page::Login
    };

};

#endif // NAVIGATIONMANAGER_H
