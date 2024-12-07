#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include "Serpent.hpp"


namespace py = pybind11;
using namespace geode::prelude;
using namespace Serpent;

bool Serpent::safeMode = false;

void unzipAndExecute(std::filesystem::path scripts) {
	log::info("Unzipping and executing...");
	auto unzippedDirRes = geode::utils::file::createDirectory(Mod::get()->getConfigDir() / "unzipped");
	if (unzippedDirRes.isErr()) {
		log::error("There was an error creating the `unzipped` directory: {}", unzippedDirRes.err());
		return;
	}

	static bool shouldExec = true;
	Serpent::safeMode = std::filesystem::exists(Mod::get()->getConfigDir() / "safemode");
	if (Serpent::safeMode) {
		log::debug("Safe Mode is on, the enabled script will not be executed.");
	}

	auto unzipped = Mod::get()->getConfigDir() / "unzipped";

	for (const auto& script : std::filesystem::directory_iterator(scripts)) {
		auto name = script.path().filename().stem().string();
		if (script.is_directory()) {
			log::warn("{} is a folder. will be ignored.", name);
			continue;
		}
		if (script.path().extension() == ".zip") {
			auto scriptDir = unzipped / name;
			log::info("Unzipping {}...", name);
			auto zip = geode::utils::file::Unzip::create(script.path());
			if (zip) {
				if (zip.unwrap().extractAllTo(scriptDir)) {
					log::info("Unzipped {}!", name);
					auto scriptString = geode::utils::file::readString(scriptDir / "script.json");
					if (scriptString.isErr()) {
						log::error("Failed to read script.json for {}, file may be corrupted or does not exist.", name);
						return;
					}
					auto scriptjson = matjson::parse(scriptString.unwrap());

					Serpent::tempScripts.push_back(scriptjson.unwrap());

					if (Mod::get()->getSavedValue<std::string>("enabled-script") == name && shouldExec && !Serpent::safeMode) {
						log::info("Executing {}...", name);
						try {
							auto scriptSource = geode::utils::file::readString(scriptDir / std::filesystem::path(name + ".py"));
							if (scriptSource.isErr()) {
								log::error("Failed to execute {}, file may be corrupted or does not exist.", name);
								return;
							}
							shouldExec = false;
							py::exec(scriptSource.unwrap());
						} catch (py::error_already_set& e) {
							log::error("{}", e.what());
						}
					}
				} else {
					log::error("There was an error Unzipping {},\n{}", name, zip.err());
				}
			}
		} else {
			log::warn("a file that doesn't have a .zip extension was found in {}", scripts.string());
		}
	}
}


$on_mod(Loaded) {
	log::debug("Serpent loaded!");
	if (!Py_IsInitialized()) {
		py::initialize_interpreter();
	}
	py::module m = py::module::import("__main__");
	bindings::_geode::enums(m);
	bindings::_geode::bind(m);
	bindings::cocos::enums(m);
	bindings::cocos::bind(m);
	bindings::robtop::bind(m);
	bindings::serpent::bind(m);

	auto ScriptsDirectoryResult = geode::utils::file::createDirectory(Mod::get()->getConfigDir() / "scripts");
	if (ScriptsDirectoryResult.isErr()) {
		log::error("There was an error creating the scripts directory: {}", ScriptsDirectoryResult.err());
		return;
	}

	auto scripts = Mod::get()->getConfigDir() / "scripts";

	unzipAndExecute(scripts);
}

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(CCMenuItemExt::createSpriteExtra(geode::CircleButtonSprite::createWithSprite("PyBtn.png"_spr, 1.0f, CircleBaseColor::Green, CircleBaseSize::MediumAlt), [=](CCObject* sender) {
			ui::ScriptsLayer::create()->show();
		}));
		if (!Loader::get()->isModLoaded("alphalaneous.pages_api") || !Loader::get()->isModLoaded("alphalaneous.vanilla_pages")) {
			menu->updateLayout();
		}
		return true;
	}
};