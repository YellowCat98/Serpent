#pragma once
#include "Serpent.hpp"

namespace Serpent {
	struct wrapper {
		static script* instance;
		static void setParent(script* parent) {
			instance = parent;
		}
		static std::vector<std::string> enabledHooks;
		static bool MenuLayer_init(MenuLayer* self);
		static void MenuLayer_onMoreGames(MenuLayer* self, cocos2d::CCObject* p0);
		static void MenuLayer_endGame(MenuLayer* self);
		static void MenuLayer_firstNetworkTest(MenuLayer* self);
		static void MenuLayer_onAchievements(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onCreator(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onDaily(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onGarage(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onMyProfile(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onOptions(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onOptionsInstant(MenuLayer* self);
		static void MenuLayer_onPlay(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onQuit(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onRobTop(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_onStats(MenuLayer* self, cocos2d::CCObject* sender);
		static void MenuLayer_openOptions(MenuLayer* self, bool videoOptions);
		static void MenuLayer_showTOS(MenuLayer* self);
		static void MenuLayer_updateUserProfileButton(MenuLayer* self);
		static void MenuLayer_willClose(MenuLayer* self);

		// static const char* LoadingLayer_getLoadingString(LoadingLayer* self);
		static bool LoadingLayer_init(LoadingLayer* self, bool p0);
		static void LoadingLayer_loadAssets(LoadingLayer* self);
		static cocos2d::CCScene* LoadingLayer_scene(LoadingLayer* self, bool p0);
		static void LoadingLayer_updateProgress(LoadingLayer* self, int p0);

		static bool CCLayer_init(cocos2d::CCLayer* self);

		static bool CCScene_init(cocos2d::CCScene* self);
	};
}