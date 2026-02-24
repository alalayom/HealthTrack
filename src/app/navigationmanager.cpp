#include "navigationmanager.h"

NavigationManager::NavigationManager(QObject *pParent)
    : QObject(pParent)
    , mCurrentPage(Page::Login)
{

}

NavigationManager::Page NavigationManager::getCurrentPage() const
{
    return mCurrentPage;
}

void NavigationManager::setCurrentPage(Page pPage)
{
    if(mCurrentPage == pPage)
    {
        return;
    }

    mCurrentPage = pPage;
    emit currentPageChanged(mCurrentPage);
}

void NavigationManager::navigateTo(Page pPage)
{
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
