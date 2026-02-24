#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include <QObject>

class NavigationManager : public QObject
{

    Q_OBJECT
    Q_PROPERTY(Page currentPage READ getCurrentPage WRITE setCurrentPage NOTIFY currentPageChanged FINAL)

public:
    explicit NavigationManager(QObject* pParent = nullptr);

    enum class Page
    {
        Login,
        Home,
        Nutrition,
        Profile,
        Settings,
        Sleep,
        Sport,
        Statistics
    };
    Q_ENUM(Page)

    Page getCurrentPage() const;
    void setCurrentPage(Page pPage);

    Q_INVOKABLE void navigateTo(Page pPage);
    Q_INVOKABLE void navigateToNutrition();
    Q_INVOKABLE void navigateToHome();

signals:
    void currentPageChanged(NavigationManager::Page pPage);

private:
    Page mCurrentPage
    {
        Page::Login
    };

};

#endif // NAVIGATIONMANAGER_H
