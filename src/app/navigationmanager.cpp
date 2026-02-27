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
