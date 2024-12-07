#pragma once
#include <Python.h>
#include <frameobject.h>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <Geode/Geode.hpp>

#define CREATE_HOOK_FOR(pyclass, fn, pyfn, wrapperName, address, convention, returnName, body) \
if (std::find(wrapper::enabledHooks.begin(), wrapper::enabledHooks.end(), pyfn) == wrapper::enabledHooks.end()) { \
	if (pybind11::hasattr(pyclass, pyfn)) { \
		auto func = pyclass.attr(pyfn); \
		if (pybind11::isinstance<pybind11::function>(func)) { \
			auto returnName = Mod::get()->hook( \
				reinterpret_cast<void*>(address), \
				&wrapperName, \
				fmt::format("{} for {}", fn, std::string(pybind11::str(pyclass.attr("__class__").attr("__name__")))), \
				tulip::hook::TulipConvention::convention \
			); \
			body \
		} \
	} \
	wrapper::enabledHooks.push_back(pyfn); \
} \


#define CREATE_HOOK_WITH_CHECK_FOR(pyclass, function, pyfn, wrapperName, address, convention, returnName)  \
CREATE_HOOK_FOR(pyclass, function, pyfn, wrapperName, address, convention, returnName,                     \
	if (returnName.isErr()) {                                                                              \
		log::error("Error enabling {} hook.", function);                                                   \
	}                                                                                                      \
)                                                                                                          \

#define GET_PY_FN(pyclass, fn, type, ...) pyclass.attr(fn)(__VA_ARGS__).cast<type>()

#define CREATE_WRAPPER_FOR(pyclass, fn, type, args, ...) \
type wrapper::fn(__VA_ARGS__) { \
	return GET_PY_FN(pyclass, #fn, type, args); \
} \

#define ARGS(...) __VA_ARGS__

namespace Serpent {
	namespace bindings {
		struct _geode { // prefixed with _ so compiler/YOU doesnt/dont get confused between Serpent::geode and geode ns
			static void bind(pybind11::module m);
			static void enums(pybind11::module m);
		};

		struct cocos {
			static void bind(pybind11::module m);
			static void enums(pybind11::module m);
		};

		struct robtop {
			static void bind(pybind11::module m);
			static void enums(pybind11::module m);
		};

		// mod-specific bindings
		struct serpent {
			static void bind(pybind11::module m);
		};
	}

	extern bool safeMode;

	class script;

	class script {
	public:
		std::string ID;
		std::string name;
		std::string developer;
		std::string scriptjson;
		std::string serpentVer;
		pybind11::object mainClass;
		script(const std::string& scriptID, pybind11::object obj);
		void initAllHooks();
		void info(const std::string& str) {
			geode::log::info("[{}]: {}", name, str);
		}
		void warn(const std::string& str) {
			geode::log::warn("[{}]: {}", name, str);
		}
		void debug(const std::string& str) {
			geode::log::debug("[{}]: {}", name, str);
		}
		void error(const std::string& str) {
			geode::log::error("[{}]: {}", name, str);
		}
		bool loadMetadata(const std::string& json);
		bool CheckMetadata(matjson::Value json);
		std::string getScriptJson();
	};

	

	namespace ui {
		class ScriptItem : public cocos2d::CCNode {
		private:
			cocos2d::extension::CCScale9Sprite* bg;
			cocos2d::CCNode* title;
			cocos2d::CCNode* mainContainer;
			cocos2d::CCLabelBMFont* titleLabel;
			cocos2d::CCMenu* devContainer;
			cocos2d::CCLabelBMFont* dev;
			cocos2d::CCMenu* viewMenu;
			matjson::Value json;
			bool init(matjson::Value theJson, std::function<void(cocos2d::CCObject*)> onButton, const cocos2d::CCSize& size);
			void listener(float dt);
		public:
			static ScriptItem* create(matjson::Value, std::function<void(cocos2d::CCObject*)> onButton, const cocos2d::CCSize& size);
			CCMenuItemToggler* viewBtn; // pretty much need to access it within ScriptsLayer!
		};

		class ScriptsLayer : public geode::Popup<> {
		public:
			static ScriptsLayer* create();
		private:
			bool setup() override;
			bool initAnchored();
			void onAdd(CCObject* sender);
			geode::ScrollLayer* scroll;
			geode::Border* border;
			cocos2d::CCSize winSize;
			geode::EventListener<geode::Task<geode::Result<std::filesystem::path>>> m_pickListener;
		};
	}

	extern std::vector<ui::ScriptItem*> scripts;
	extern std::vector<matjson::Value> tempScripts;
}