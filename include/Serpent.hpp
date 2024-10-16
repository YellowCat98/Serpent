#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <Geode/Geode.hpp>


#define CREATE_HOOK_FOR(pyclass, fn, pyfn, wrapperName, address, convention, returnName, body)                 \
if (pybind11::hasattr(pyclass, pyfn)) {                                                                        \
	auto func = pyclass.attr(pyfn);                                                                            \
	if (pybind11::isinstance<pybind11::function>(func)) {                                                      \
		auto returnName = Mod::get()->hook(                                                                    \
    		reinterpret_cast<void*>(address),                                                                  \
    	    &wrapperName,                                                                                      \
    	    fn,                                                                                                \
    	    tulip::hook::TulipConvention::convention                                                           \
    	);                                                                                                     \
		body                                                                                                   \
	}                                                                                                          \
}                                                                                                              \


#define CREATE_HOOK_WITH_CHECK_FOR(pyclass, function, pyfn, wrapperName, address, convention, returnName)  \
CREATE_HOOK_FOR(pyclass, function, pyfn, wrapperName, address, convention, returnName,                     \
	if (returnName.isErr()) {                                                                              \
		log::error("Error enabling {} hook.", function);                                                   \
	}                                                                                                      \
)                                                                                                          \

#define GET_PY_FN(pyclass, fn, type, ...) pyclass.attr(fn)(__VA_ARGS__).cast<type>()

#define CREATE_WRAPPER_FOR(pyclass, fn, type, args, ...) \
type script::wrapper::fn(__VA_ARGS__) { \
	return GET_PY_FN(pyclass, #fn, type, args); \
} \

#define ARGS(...) __VA_ARGS__

namespace Serpent {

	extern pybind11::module m;
	extern std::unordered_map<std::string, intptr_t> methods;


	void initModule();

	namespace bindings {
		struct _geode { // prefixed with _ so compiler/YOU doesnt/dont get confused between Serpent::geode and geode ns
			static void bind();
			static void enums();
		};

		struct cocos {
			static void bind();
			static void enums();
		};

		struct robtop {
			static void bind();
			static void enums();
		};

		// mod-specific bindings
		struct serpent {
			static void bind();
		};
	}

	// reserved for showing the scripts in ScriptsLayer
	struct visualScripts {
		std::string name;
		std::string developer;
		std::string script;
		std::string id;
		visualScripts(std::string n, std::string d, std::string s, std::string i) : name(n), developer(d), script(s), id(i) {}

	};
	extern std::vector<visualScripts*> scripts;

	class script {
	private:
		struct wrapper {
			static script* instance;
			static void setParent(script* parent) {
				instance = parent;
			}
			static bool MenuLayer_init(MenuLayer* self);
			static void MenuLayer_onMoreGames(MenuLayer* self, cocos2d::CCObject* p0);
		};
	
	public:
		std::string ID;
		std::string name;
		std::string developer;
		std::string scriptjson;
		std::string serpentVer;
		pybind11::object mainClass;
		script(const std::string& scriptID, pybind11::object obj) : ID(scriptID), mainClass(obj) {
			wrapper::setParent(this);
			if (loadMetadata(getScriptJson())) {
				geode::log::info("Loaded metadata for script {}!", ID);
			} else {
				geode::log::error("Failed to load metadata for script {}.", ID);
			}
		}
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
}