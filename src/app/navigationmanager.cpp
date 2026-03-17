#include "navigationmanager.h"

//Test function, delete before release
#include <android/log.h>

static inline void ALOG(const char* msg)
{
    __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "%s", msg);
}

NavigationManager::NavigationManager(QObject *pParent)
    : QObject(pParent)
    , mCurrentPage(Page::Login)
    , m_selectedMealIndex(-1)
    , m_selectedMealName("")
{

}

NavigationManager::Page NavigationManager::getCurrentPage() const
{
    return mCurrentPage;
}

void NavigationManager::setCurrentPage(Page pPage)
{
    ALOG("setCurrentPage ENTER");

    if(mCurrentPage == pPage)
    {
        ALOG("setCurrentPage SAME -> return");
        return;
    }

    mCurrentPage = pPage;
    ALOG("EMIT currentPageChanged");
    emit currentPageChanged();
}

void NavigationManager::navigateTo(Page pPage)
{
    ALOG("navigateTo called");
    setCurrentPage(pPage);
}

void NavigationManager::navigateToNutrition()
{
    setCurrentPage(Page::Nutrition);
}

void NavigationManager::navigateToHome()
{
    setCurrentPage(Page::Home);
}

int NavigationManager::getSelectedMealIndex() const
{
    return m_selectedMealIndex;
}

void NavigationManager::setSelectedMealIndex(int newSelectedMealIndex)
{
    if (m_selectedMealIndex == newSelectedMealIndex)
    {
        return;
    }

    m_selectedMealIndex = newSelectedMealIndex;
    emit selectedMealIndexChanged();
}

QString NavigationManager::getSelectedMealName() const
{
    return m_selectedMealName;
}

void NavigationManager::setSelectedMealName(const QString &newSelectedMealName)
{
    if (m_selectedMealName == newSelectedMealName)
    {
        return;
    }

    m_selectedMealName = newSelectedMealName;
    emit selectedMealNameChanged();
}

void NavigationManager::openMealDetails(int pMealIndex, const QString &pMealName)
{
    setSelectedMealIndex(pMealIndex);
    setSelectedMealName(pMealName);
    setCurrentPage(Page::MealDetails);
}

void NavigationManager::openAddFoodPage()
{
    setCurrentPage(Page::AddFood);
}

void NavigationManager::goBackToMealDetails()
{
    setCurrentPage(Page::MealDetails);
}
