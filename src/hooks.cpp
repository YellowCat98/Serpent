#include "Serpent.hpp"
#include "wrapper.hpp"

using namespace geode::prelude;
using namespace Serpent;

void script::initAllHooks() {
    log::info("Enabling hooks for {}", ID);
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::init", "MenuLayer_init", wrapper::MenuLayer_init, geode::base::get() + 0x31ebd0, Default, MenuLayer_initHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onMoreGames", "MenuLayer_onMoreGames", wrapper::MenuLayer_onMoreGames, geode::base::get() + 0x320880, Default, MenuLayer_onMoreGamesHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::endGame", "MenuLayer_endGame", wrapper::MenuLayer_endGame, geode::base::get() + 0x321510, Default, MenuLayer_endGameHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::firstNetworkTest", "MenuLayer_firstNetworkTest", wrapper::MenuLayer_firstNetworkTest, geode::base::get() + 0x320430, Default, MenuLayer_firstNetworkTestHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onAchievements", "MenuLayer_onAchievements", wrapper::MenuLayer_onAchievements, geode::base::get() + 0x320960, Default, MenuLayer_onAchievementsHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onCreator", "MenuLayer_onCreator", wrapper::MenuLayer_onCreator, geode::base::get() + 0x320e70, Default, MenuLayer_onCreatorHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onDaily", "MenuLayer_onDaily", wrapper::MenuLayer_onDaily, geode::base::get() + 0x3201e0, Default, MenuLayer_onDailyHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onGarage", "MenuLayer_onGarage", wrapper::MenuLayer_onGarage, geode::base::get() + 0x320f00, Default, MenuLayer_onGarageHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onMoreGames", "MenuLayer_onMoreGames", wrapper::MenuLayer_onMoreGames, geode::base::get() + 0x320880, Default, MenuLayer_onMoreGamesHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onMyProfile", "MenuLayer_onMyProfile", wrapper::MenuLayer_onMyProfile, geode::base::get() + 0x320720, Default, MenuLayer_onMyProfileHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onOptions", "MenuLayer_onOptions", wrapper::MenuLayer_onOptions, geode::base::get() + 0x320bb0, Default, MenuLayer_onOptionsHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onOptionsInstant", "MenuLayer_onOptionsInstant", wrapper::MenuLayer_onOptionsInstant, geode::base::get() + 0x320bc0, Default, MenuLayer_onOptionsInstantHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onPlay", "MenuLayer_onPlay", wrapper::MenuLayer_onPlay, geode::base::get() + 0x320b10, Default, MenuLayer_onPlayHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onQuit", "MenuLayer_onQuit", wrapper::MenuLayer_onQuit, geode::base::get() + 0x3210c0, Default, MenuLayer_onQuitHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onRobTop", "MenuLayer_onRobTop", wrapper::MenuLayer_onRobTop, geode::base::get() + 0x3207c0, Default, MenuLayer_onRobTopHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onStats", "MenuLayer_onStats", wrapper::MenuLayer_onStats, geode::base::get() + 0x320d50, Default, MenuLayer_onStatsHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::openOptions", "MenuLayer_openOptions", wrapper::MenuLayer_openOptions, geode::base::get() + 0x320bd0, Default, MenuLayer_openOptionsHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::showTOS", "MenuLayer_showTOS", wrapper::MenuLayer_showTOS, geode::base::get() + 0x320600, Default, MenuLayer_showTOSHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::updateUserProfileButton", "MenuLayer_updateUserProfileButton", wrapper::MenuLayer_updateUserProfileButton, geode::base::get() + 0x320330, Default, MenuLayer_updateUserProfileButtonHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::willClose", "MenuLayer_willClose", wrapper::MenuLayer_willClose, geode::base::get() + 0x3211f0, Default, MenuLayer_willCloseHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::init", "MenuLayer_init", wrapper::MenuLayer_init, geode::base::get() + 0x31ebd0, Default, MenuLayer_initHook)

    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "LoadingLayer::scene", "LoadingLayer_scene", wrapper::LoadingLayer_scene, geode::base::get() + 0x3194f0, Default, LoadingLayer_sceneHook)
    // CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "LoadingLayer::getLoadingString", "LoadingLayer_getLoadingString", wrapper::LoadingLayer_getLoadingString, geode::base::get() + 0x31a930, Default, LoadingLayer_getLoadingStringHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "LoadingLayer::init", "LoadingLayer_init", wrapper::LoadingLayer_init, geode::base::get() + 0x319600, Default, LoadingLayer_initHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "LoadingLayer::loadAssets", "LoadingLayer_loadAssets", wrapper::LoadingLayer_loadAssets, geode::base::get() + 0x319ea0, Default, LoadingLayer_loadAssetsHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "LoadingLayer::updateProgress", "LoadingLayer_updateProgress", wrapper::LoadingLayer_updateProgress, geode::base::get() + 0x319e20, Default, LoadingLayer_updateProgressHook)
}