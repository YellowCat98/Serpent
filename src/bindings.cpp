#include "Serpent.hpp"

namespace py = pybind11;
using namespace geode::prelude;

void Serpent::bindings::_geode::bind(pybind11::module m) {
	py::class_<Notification>(m, "Notification")
		.def_static("create", py::overload_cast<std::string const&, NotificationIcon, float>(&Notification::create), py::arg("text"), py::arg("icon") = NotificationIcon::None, py::arg("time") = geode::NOTIFICATION_DEFAULT_TIME, py::return_value_policy::reference)
		.def("show", &Notification::show)
		.def("cancel", &Notification::cancel)
		.def("hide", &Notification::hide);
	
	m.def("createQuickPopup", [=](const char* title, std::string const& content, const char* btn1, const char* btn2, std::function<void(FLAlertLayer*, bool)>&& selected){
		return geode::createQuickPopup(title, content, btn1, btn2, selected);
	}, py::return_value_policy::reference);

	py::class_<BaseSeedValue>(m, "BaseSeedValue")
		.def(py::init<>());
	
	py::class_<SeedValueRSV, BaseSeedValue>(m, "SeedValueRSV")
		.def("value", py::overload_cast<>(&SeedValueRSV::value));
}

void Serpent::bindings::_geode::enums(pybind11::module m) {
	py::enum_<NotificationIcon>(m, "NotificationIcon")
		.value("None", NotificationIcon::None)
		.value("Loading", NotificationIcon::Loading)
		.value("Success", NotificationIcon::Success)
		.value("Warning", NotificationIcon::Warning)
		.value("Error", NotificationIcon::Error)
		.value("Info", NotificationIcon::Info);
}

// cocos

void Serpent::bindings::cocos::bind(pybind11::module m) {
	py::class_<CCObject>(m, "CCObject")
		.def("release", &CCObject::release)
		.def("retain", &CCObject::retain)
		.def("copy", &CCObject::copy, py::return_value_policy::reference)
		.def("autorelease", &CCObject::autorelease, py::return_value_policy::reference)
		.def("getTag", &CCObject::getTag)
		.def("setTag", &CCObject::setTag, py::arg("nTag"))
		.def("setObjType", &CCObject::setObjType, py::arg("type"))
		.def("isEqual", &CCObject::isEqual, py::arg("pObject"));
	
	py::class_<CCPoint>(m, "CCPoint")
		.def(py::init<float, float>())
		.def_readwrite("x", &CCPoint::x)
		.def_readwrite("y", &CCPoint::y);
	
	py::class_<CCSize>(m, "CCSize")
		.def(py::init<float, float>())
		.def_readwrite("height", &CCSize::height)
		.def_readwrite("width", &CCSize::width);
	
	py::class_<CCRect>(m, "CCRect")
		.def_readwrite("origin", &CCRect::origin)
		.def_readwrite("size", &CCRect::size)
		.def("intersectsRect", py::overload_cast<CCRect const&>(&CCRect::intersectsRect, py::const_));
	
	py::class_<ccColor3B>(m, "ccColor3B")
		.def(py::init<>())
		.def_readwrite("r", &ccColor3B::r)
		.def_readwrite("g", &ccColor3B::g)
		.def_readwrite("g", &ccColor3B::b);

	py::class_<ccColor4B>(m, "ccColor4B")
		.def(py::init<>())
		.def_readwrite("r", &ccColor4B::r)
		.def_readwrite("g", &ccColor4B::g)
		.def_readwrite("g", &ccColor4B::b)
		.def_readwrite("a", &ccColor4B::a);

	py::class_<CCDirector>(m, "CCDirector")
		.def_static("get", py::overload_cast<>(&CCDirector::get), py::return_value_policy::reference)
		.def("getWinSize", py::overload_cast<>(&CCDirector::getWinSize))
		.def("replaceScene", py::overload_cast<CCScene*>(&CCDirector::replaceScene), py::arg("pScene"))
		.def("pushScene", py::overload_cast<CCScene*>(&CCDirector::pushScene), py::arg("pScene"))
		.def("popScene", py::overload_cast<>(&CCDirector::popScene));

	py::class_<CCNode, CCObject>(m, "CCNode")
		.def_static("create", &CCNode::create, py::return_value_policy::reference)
		.def("init", &CCNode::init)
		.def("description", &CCNode::description)
		.def("setZOrder", &CCNode::setZOrder, py::arg("zOrder"))
		.def("getZOrder", &CCNode::getZOrder)
		.def("setVertexZ", &CCNode::setVertexZ, py::arg("vertexZ"))
		.def("getVertexZ", &CCNode::getVertexZ)
		.def("setScaleX", &CCNode::setScaleX)
		.def("getScaleY", &CCNode::getScaleY)
		.def("setScale", py::overload_cast<float, float>(&CCNode::setScale), py::arg("scaleX"), py::arg("scaleY"))
		.def("setPosition", py::overload_cast<CCPoint const&>(&CCNode::setPosition), py::arg("position"))
		.def("getPosition", py::overload_cast<>(&CCNode::getPosition))
		.def("setPositionX", py::overload_cast<float>(&CCNode::setPositionX), py::arg("x"))
		.def("getPositionX", py::overload_cast<>(&CCNode::getPositionX))
		.def("setPositionY", py::overload_cast<float>(&CCNode::setPositionY), py::arg("y"))
		.def("getPositionY", py::overload_cast<>(&CCNode::getPositionY))
		.def("setSkewX", py::overload_cast<float>(&CCNode::setSkewX), py::arg("fSkewX"))
		.def("getSkewX", py::overload_cast<>(&CCNode::getSkewX))
		.def("setSkewY", py::overload_cast<float>(&CCNode::setSkewY), py::arg("fSkewY"))
		.def("getSkewY", py::overload_cast<>(&CCNode::getSkewY))
		.def("setAnchorPoint", py::overload_cast<CCPoint const&>(&CCNode::setAnchorPoint), py::arg("anchorPoint"))
		.def("getAnchorPoint", py::overload_cast<>(&CCNode::getAnchorPoint))
		.def("getAnchorPointInPoint", py::overload_cast<>(&CCNode::getAnchorPointInPoints))
		.def("setContentSize", py::overload_cast<const CCSize&>(&CCNode::setContentSize), py::arg("contentSize"))
		.def("getContentSize", py::overload_cast<>(&CCNode::getContentSize, py::const_), py::return_value_policy::reference)
		.def("getScaledContentSize", py::overload_cast<>(&CCNode::getScaledContentSize))
		.def("setVisible", py::overload_cast<bool>(&CCNode::setVisible))
		.def("isVisible", py::overload_cast<>(&CCNode::isVisible))
		.def("setRotation", py::overload_cast<float>(&CCNode::setRotation), py::arg("fRotation"))
		.def("getRotation", py::overload_cast<>(&CCNode::getRotation))
		.def("setRotationX", py::overload_cast<float>(&CCNode::setRotationX), py::arg("fRotaionX")) // the arg name was misspelt in the docs, i wanted to use the same arg names as the ones in the docs so uhh have fun with rotaion
		.def("getRotationX", py::overload_cast<>(&CCNode::getRotationX))
		.def("setRotationY", py::overload_cast<float>(&CCNode::setRotationY), py::arg("fRotationY"))
		.def("getRotationY", py::overload_cast<>(&CCNode::getRotationY))
		.def("addChild", py::overload_cast<CCNode*>(&CCNode::addChild), py::arg("child"))
		.def("addChild", py::overload_cast<CCNode*, int>(&CCNode::addChild), py::arg("child"), py::arg("zOrder"))
		.def("addChild", py::overload_cast<CCNode*, int, int>(&CCNode::addChild), py::arg("child"), py::arg("zOrder"), py::arg("tag"))
		.def("getChildByTag", py::overload_cast<int>(&CCNode::getChildByTag), py::arg("tag"), py::return_value_policy::reference)
		.def("getParent", py::overload_cast<>(&CCNode::getParent))
		.def("removeFromParent", py::overload_cast<>(&CCNode::removeFromParent))
		.def("removeFromParentAndCleanup", py::overload_cast<bool>(&CCNode::removeFromParentAndCleanup), py::arg("cleanup"))
		.def("removeChild", py::overload_cast<CCNode*, bool>(&CCNode::removeChild), py::arg("child"), py::arg("cleanup"))
		.def("removeChildByTag", py::overload_cast<int, bool>(&CCNode::removeChildByTag), py::arg("tag"), py::arg("cleanup"))
		.def("removeAllChildren", py::overload_cast<>(&CCNode::removeAllChildren))
		.def("removeAllChildrenAndCleanup", py::overload_cast<bool>(&CCNode::removeAllChildrenWithCleanup), py::arg("cleanup")) // binded as 2 separate functions (wanted to bind removeAllChildrenWithCleanup only, but didnt want to cause confusion)
		.def("getID", py::overload_cast<>(&CCNode::getID))
		.def("setID", py::overload_cast<std::string const&>(&CCNode::setID), py::arg("id"))
		.def("getChildByID", py::overload_cast<std::string_view>(&CCNode::getChildByID), py::arg("id"), py::return_value_policy::reference)
		.def("getChildByIDRecursive", py::overload_cast<std::string_view>(&CCNode::getChildByIDRecursive), py::arg("id"), py::return_value_policy::reference)
		.def("removeChildByID", py::overload_cast<std::string_view>(&CCNode::removeChildByID), py::arg("id"));
	

	py::class_<CCScene, CCNode>(m, "CCScene")
		.def_static("create", py::overload_cast<>(&CCScene::create), py::return_value_policy::reference);

	py::class_<CCRGBAProtocol>(m, "CCRGBAProtocol")
		.def("setColor", py::overload_cast<ccColor3B const&>(&CCRGBAProtocol::setColor), py::arg("color"))
		.def("getColor", py::overload_cast<>(&CCRGBAProtocol::getColor))
		.def("getDisplayedColor", py::overload_cast<>(&CCRGBAProtocol::getDisplayedColor))
		.def("setOpacity", py::overload_cast<GLubyte>(&CCRGBAProtocol::setOpacity), py::arg("opacity"))
		.def("getOpacity", py::overload_cast<>(&CCRGBAProtocol::getOpacity));
	
	py::class_<CCLayer, CCNode>(m, "CCLayer")
		.def(py::init<>())
		.def_static("create", py::overload_cast<>(&CCLayer::create), py::return_value_policy::reference);
	
	py::class_<CCLayerRGBA, CCLayer, CCRGBAProtocol>(m, "CCLayerRGBA")
		.def_static("create", py::overload_cast<>(&CCLayerRGBA::create), py::return_value_policy::reference);

	py::class_<CCNodeRGBA, CCNode, CCRGBAProtocol>(m, "CCNodeRGBA")
		.def_static("create", py::overload_cast<>(&CCNodeRGBA::create), py::return_value_policy::reference);
	
	py::class_<CCTexture2D, CCObject>(m, "CCTexture2D")
		.def(py::init<>());
	
	py::class_<CCTextureProtocol>(m, "CCTextureProtocol")
		.def("getTexture", &CCTextureProtocol::getTexture)
		.def("setTexture", &CCTextureProtocol::setTexture);
	
	py::class_<CCSprite, CCNodeRGBA, CCTextureProtocol>(m, "CCSprite")
		.def_static("create", py::overload_cast<const char*>(&CCSprite::create), py::arg("pszFileName"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<>(&CCSprite::create), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<const char*, CCRect const&>(&CCSprite::create), py::arg("pszFileName"), py::arg("rect"), py::return_value_policy::reference)
		.def_static("createWithSpriteFrameName", py::overload_cast<const char*>(&CCSprite::createWithSpriteFrameName), py::arg("pszSpriteFrameName"), py::return_value_policy::reference);
	
	py::class_<CCSpriteBatchNode, CCNode, CCTextureProtocol>(m, "CCSpriteBatchNode")
		.def_static("create", py::overload_cast<char const*>(&CCSpriteBatchNode::create), py::arg("fileImage"), py::return_value_policy::reference);
	
	py::class_<CCLabelProtocol>(m, "CCLabelProtocol")
		.def("setString", py::overload_cast<char const*>(&CCLabelProtocol::setString), py::arg("label"))
		.def("getString", py::overload_cast<>(&CCLabelProtocol::getString));

	py::class_<CCLabelBMFont, CCSpriteBatchNode, CCLabelProtocol, CCRGBAProtocol>(m, "CCLabelBMFont")
		.def_static("create", py::overload_cast<char const*, char const*>(&CCLabelBMFont::create), py::arg("str"), py::arg("fntFile"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<>(&CCLabelBMFont::create), py::return_value_policy::reference);
	
	py::class_<CCMenu, CCLayerRGBA>(m, "CCMenu")
		.def_static("create", py::overload_cast<>(&CCMenu::create));
	
	py::class_<CCMenuItem, CCNodeRGBA>(m, "CCMenuItem")
		.def_static("create", py::overload_cast<>(&CCMenuItem::create))
		.def_static("create", py::overload_cast<CCObject*, SEL_MenuHandler>(&CCMenuItem::create), py::arg("rec"), py::arg("selector"));
	
	py::class_<CCMenuItemSprite, CCMenuItem>(m, "CCMenuItemSprite")
		.def_static("create", py::overload_cast<CCNode*, CCNode*, CCNode*>(&CCMenuItemSprite::create), py::arg("normalSprite"), py::arg("selectedSprite"), py::arg("disabledSprite"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<CCNode*, CCNode*, CCNode*, CCObject*, SEL_MenuHandler>(&CCMenuItemSprite::create), py::arg("normalSprite"), py::arg("selectedSprite"), py::arg("disabledSprite"), py::arg("target"), py::arg("selector"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<CCNode*, CCNode*, CCObject*, SEL_MenuHandler>(&CCMenuItemSprite::create), py::arg("normalSprite"), py::arg("selectedSprite"), py::arg("target"), py::arg("selector")), py::return_value_policy::reference;
	
	py::class_<CCMenuItemSpriteExtra, CCMenuItemSprite>(m, "CCMenuItemSpriteExtra")
		.def_static("create", py::overload_cast<CCNode*, CCNode*, CCObject*, SEL_MenuHandler>(&CCMenuItemSpriteExtra::create), py::arg("sprite"), py::arg("disabledSprite"), py::arg("target"), py::arg("callback"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<CCNode*, CCObject*, SEL_MenuHandler>(&CCMenuItemSpriteExtra::create), py::arg("sprite"), py::arg("target"), py::arg("callback"));
	
	py::class_<CCMenuItemExt>(m, "CCMenuItemExt")
		.def_static("createSpriteExtra", [](CCNode* sprite, std::function<void(CCMenuItemSpriteExtra* sender)>&& callback) {
			return CCMenuItemExt::createSpriteExtra(sprite, callback);
		}, py::return_value_policy::reference);
	
	py::class_<CCLayerColor, CCLayerRGBA>(m, "CCLayerColor")
		.def_static("create", py::overload_cast<>(&CCLayerColor::create), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<ccColor4B const&>(&CCLayerColor::create), py::arg("color"), py::return_value_policy::reference);
}


void Serpent::bindings::cocos::enums(pybind11::module m) {
	py::enum_<CCObjectType>(m, "CCObjectType") // i actualy dont know why this exists but ill just bind it for the 2 people that want it!
		.value("PlayLayer", CCObjectType::PlayLayer)
		.value("LevelEditorLayer", CCObjectType::LevelEditorLayer)
		.value("GameObject", CCObjectType::GameObject)
		.value("MenuLayer", CCObjectType::MenuLayer);
}

void Serpent::bindings::robtop::bind(pybind11::module m) {
	py::class_<GooglePlayDelegate>(m, "GooglePlayDelegate")	
		.def("googlePlaySignedIn", py::overload_cast<>(&GooglePlayDelegate::googlePlaySignedIn));

	py::class_<MenuLayer, CCLayer, GooglePlayDelegate>(m, "MenuLayer")
		.def_static("scene", py::overload_cast<bool>(&MenuLayer::scene))
		.def("init", py::overload_cast<>(&MenuLayer::init))
		.def("onMoreGames", py::overload_cast<CCObject*>(&MenuLayer::onMoreGames))
		.def("endGame", py::overload_cast<>(&MenuLayer::endGame))
		.def("firstNetworkTest", py::overload_cast<>(&MenuLayer::firstNetworkTest))
		.def("onAchievements", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onAchievements), py::arg("sender"))
		.def("onCreator", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onCreator), py::arg("sender"))
		.def("onDaily", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onDaily), py::arg("sender"))
		.def("onGarage", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onGarage), py::arg("sender"))
		.def("onMyProfile", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onMyProfile), py::arg("sender"))
		.def("onOptions", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onOptions), py::arg("sender"))
		.def("onOptionsInstant", py::overload_cast<>(&MenuLayer::onOptionsInstant))
		.def("onPlay", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onPlay), py::arg("sender"))
		.def("onQuit", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onQuit), py::arg("sender"))
		.def("onRobTop", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onRobTop), py::arg("sender"))
		.def("onStats", py::overload_cast<cocos2d::CCObject*>(&MenuLayer::onStats), py::arg("sender"))
		.def("openOptions", py::overload_cast<bool>(&MenuLayer::openOptions), py::arg("videoOptions"))
		.def("showTOS", py::overload_cast<>(&MenuLayer::showTOS))
		.def("updateUserProfileButton", py::overload_cast<>(&MenuLayer::updateUserProfileButton))
		.def("willClose", py::overload_cast<>(&MenuLayer::willClose));

	py::class_<LoadingLayer, CCLayer>(m, "LoadingLayer")
		.def("getLoadingString", py::overload_cast<>(&LoadingLayer::getLoadingString), py::return_value_policy::reference)
		.def("init", py::overload_cast<bool>(&LoadingLayer::init), py::arg("p0"))
		.def("loadAssets", py::overload_cast<>(&LoadingLayer::loadAssets))
		.def_static("scene", py::overload_cast<bool>(&LoadingLayer::scene), py::arg("p0"), py::return_value_policy::reference)
		.def("updateProgress", py::overload_cast<int>(&LoadingLayer::updateProgress))
		.def_readwrite("unknown", &LoadingLayer::m_unknown)
		.def_readwrite("unknown2", &LoadingLayer::m_unknown2)
		.def_readwrite("loadStep", &LoadingLayer::m_loadStep)
		.def_readwrite("caption", &LoadingLayer::m_caption)
		.def_readwrite("textArea", &LoadingLayer::m_textArea)
		.def_readwrite("sliderBar", &LoadingLayer::m_sliderBar)
		.def_readwrite("sliderGrooveXPos", &LoadingLayer::m_sliderGrooveXPos)
		.def_readwrite("sliderGrooveHeight", &LoadingLayer::m_sliderGrooveHeight)
		.def_readwrite("fromRefresh", &LoadingLayer::m_fromRefresh);

	py::class_<FLAlertLayerProtocol>(m, "FLAlertLayerProtocol")
		.def("FLAlert_Clicked", py::overload_cast<FLAlertLayer*, bool>(&FLAlertLayerProtocol::FLAlert_Clicked));

	py::class_<FLAlertLayer, CCLayerColor>(m, "FLAlertLayer")
		.def_static("create", py::overload_cast<FLAlertLayerProtocol*, char const*, std::string, char const*, char const*, float, bool, float, float>(&FLAlertLayer::create), py::arg("delegate"), py::arg("title"), py::arg("desc"), py::arg("btn1"), py::arg("btn2"), py::arg("width"), py::arg("scroll"), py::arg("height"), py::arg("textScale"), py::return_value_policy::reference) // why.
		.def_static("create", py::overload_cast<FLAlertLayerProtocol*, char const*, std::string, char const*, char const*, float>(&FLAlertLayer::create), py::arg("delegate"), py::arg("title"), py::arg("desc"), py::arg("btn1"), py::arg("btn2"), py::arg("width"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<FLAlertLayerProtocol*, char const*, std::string, char const*, char const*>(&FLAlertLayer::create), py::arg("delegate"), py::arg("title"), py::arg("desc"), py::arg("btn1"), py::arg("btn2"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<char const*, std::string const&, char const*>(&FLAlertLayer::create), py::arg("title"), py::arg("desc"), py::arg("btn"), py::return_value_policy::reference)
		.def("show", py::overload_cast<>(&FLAlertLayer::show));
	

	// adding this so im consistent with inheritance!
	py::class_<GManager, CCNode>(m, "GManager")
		.def("setup", py::overload_cast<>(&GManager::setup))
		.def("loadDataFromFile", py::overload_cast<const std::string&>(&GManager::loadDataFromFile), py::arg("p0"))
		.def("save", py::overload_cast<>(&GManager::save));
	

	py::class_<GameManager, GManager>(m, "GameManager")
		.def_static("get", py::overload_cast<>(&GameManager::get), py::return_value_policy::reference)
		.def("setPlayerBall", py::overload_cast<int>(&GameManager::setPlayerBall), py::arg("id"))
		.def("setPlayerBird", py::overload_cast<int>(&GameManager::setPlayerBird), py::arg("id"))
		.def("setPlayerColor", py::overload_cast<int>(&GameManager::setPlayerColor), py::arg("id"))
		.def("setPlayerColor2", py::overload_cast<int>(&GameManager::setPlayerColor2), py::arg("id"))
		.def("setPlayerColor3", py::overload_cast<int>(&GameManager::setPlayerColor3), py::arg("id"))
		.def("setPlayerDart", py::overload_cast<int>(&GameManager::setPlayerDart), py::arg("id"))
		.def("setPlayerDeathEffect", py::overload_cast<int>(&GameManager::setPlayerDeathEffect), py::arg("id"))
		.def("setPlayerFrame", py::overload_cast<int>(&GameManager::setPlayerFrame), py::arg("id"))
		.def("setPlayerGlow", py::overload_cast<bool>(&GameManager::setPlayerGlow), py::arg("v"))
		.def("setPlayerJetpack", py::overload_cast<int>(&GameManager::setPlayerJetpack), py::arg("id"))
		.def("setPlayerRobot", py::overload_cast<int>(&GameManager::setPlayerRobot), py::arg("id"))
		.def("setPlayerShip", py::overload_cast<int>(&GameManager::setPlayerShip), py::arg("id"))
		.def("setPlayerShipStreak", py::overload_cast<int>(&GameManager::setPlayerShipStreak), py::arg("id"))
		.def("setPlayerSpider", py::overload_cast<int>(&GameManager::setPlayerSpider), py::arg("id"))
		.def("setPlayerStreak", py::overload_cast<int>(&GameManager::setPlayerStreak), py::arg("id"))
		.def("setPlayerSwing", py::overload_cast<int>(&GameManager::setPlayerSwing), py::arg("id"))
		.def("isColorUnlocked", py::overload_cast<int, UnlockType>(&GameManager::isColorUnlocked), py::arg("p0"), py::arg("p1"))
		.def("isIconUnlocked", py::overload_cast<int, IconType>(&GameManager::isIconUnlocked), py::arg("p0"), py::arg("p1"));
}

void Serpent::bindings::robtop::enums(pybind11::module m) {
	py::enum_<IconType>(m, "IconType")
		.value("Cube", IconType::Cube)
		.value("Ship", IconType::Ship)
		.value("Ball", IconType::Ball)
		.value("Ufo", IconType::Ufo)
		.value("Wave", IconType::Wave)
		.value("Robot", IconType::Robot)
		.value("Spider", IconType::Spider)
		.value("Swing", IconType::Swing)
		.value("Jetpack", IconType::Jetpack)
		.value("DeathEffect", IconType::DeathEffect)
		.value("Special", IconType::Special)
		.value("Item", IconType::Item)
		.value("ShipFire", IconType::ShipFire);
	
	py::enum_<UnlockType>(m, "UnlockType")
		.value("Cube", UnlockType::Cube)
		.value("Col1", UnlockType::Col1)
		.value("Col2", UnlockType::Col2)
		.value("Ship", UnlockType::Ship)
		.value("Ball", UnlockType::Ball)
		.value("Bird", UnlockType::Bird)
		.value("Dart", UnlockType::Dart)
		.value("Robot", UnlockType::Robot)
		.value("Spider", UnlockType::Spider)
		.value("Streak", UnlockType::Streak)
		.value("Death", UnlockType::Death)
		.value("GJItem", UnlockType::GJItem)
		.value("Swing", UnlockType::Swing)
		.value("Jetpack", UnlockType::Jetpack)
		.value("ShipFire", UnlockType::ShipFire);
}

void Serpent::bindings::serpent::bind(pybind11::module m) {
	py::class_<script>(m, "script")
		.def(py::init<const std::string&, py::object>(), py::return_value_policy::reference)
		.def_readwrite("ID", &script::ID)
		.def_readwrite("name", &script::name)
		.def_readwrite("developer", &script::developer)
		.def_readwrite("serpentVer", &script::serpentVer)
		.def("initAllHooks", py::overload_cast<>(&script::initAllHooks)) // enables all Hooks!
		.def("info", py::overload_cast<std::string const&>(&script::info))
		.def("warn", py::overload_cast<std::string const&>(&script::warn))
		.def("debug", py::overload_cast<std::string const&>(&script::debug))
		.def("error", py::overload_cast<std::string const&>(&script::error))
		.def("loadMetadata", py::overload_cast<std::string const&>(&script::loadMetadata))
		.def("getScriptJson", py::overload_cast<>(&script::getScriptJson));
}