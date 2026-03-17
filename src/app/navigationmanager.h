#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include <QObject>
#include <QString>

class NavigationManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Page currentPage READ getCurrentPage WRITE setCurrentPage NOTIFY currentPageChanged FINAL)

    Q_PROPERTY(int selectedMealIndex READ getSelectedMealIndex WRITE setSelectedMealIndex NOTIFY selectedMealIndexChanged FINAL)
    Q_PROPERTY(QString selectedMealName READ getSelectedMealName WRITE setSelectedMealName NOTIFY selectedMealNameChanged FINAL)

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
        Statistics  = 7,
        MealDetails = 8,
        AddFood     = 9
    };
    Q_ENUM(Page)

    Page getCurrentPage() const;
    void setCurrentPage(Page pPage);

    int getSelectedMealIndex() const;
    void setSelectedMealIndex(int pSelectedMealIndex);

    QString getSelectedMealName() const;
    void setSelectedMealName(const QString& pSelectedMealName);

    Q_INVOKABLE void navigateTo(Page pPage);
    Q_INVOKABLE void navigateToNutrition();
    Q_INVOKABLE void navigateToHome();

    Q_INVOKABLE void openMealDetails(int pMealIndex, const QString& pMealName);
    Q_INVOKABLE void openAddFoodPage();
    Q_INVOKABLE void goBackToMealDetails();


signals:
    void currentPageChanged();
    void selectedMealIndexChanged();
    void selectedMealNameChanged();

private:
    Page mCurrentPage { Page::Login };
    int m_selectedMealIndex { -1 };
    QString m_selectedMealName;
};

#endif // NAVIGATIONMANAGER_H
