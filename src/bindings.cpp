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
	
	py::class_<cocos2d::CCTexture2D, cocos2d::CCObject>(m, "CCTexture2D")
		.def(py::init<>())
		.def("PVRImagesHavePremultipliedAlpha", py::overload_cast<bool>(&cocos2d::CCTexture2D::PVRImagesHavePremultipliedAlpha), py::arg("value"))
		.def("initWithData", py::overload_cast<const void*, cocos2d::CCTexture2DPixelFormat, unsigned int, unsigned int, const cocos2d::CCSize&>(&cocos2d::CCTexture2D::initWithData), py::arg("data"), py::arg("pixelFormat"), py::arg("width"), py::arg("height"), py::arg("contentSize"))
		.def("initWithETCFile", py::overload_cast<const char*>(&cocos2d::CCTexture2D::initWithETCFile), py::arg("filePath"))
		.def("initWithImage", py::overload_cast<cocos2d::CCImage*>(&cocos2d::CCTexture2D::initWithImage), py::arg("image"))
		.def("initWithPVRFile", py::overload_cast<const char*>(&cocos2d::CCTexture2D::initWithPVRFile), py::arg("filePath"))
		.def("initWithString", py::overload_cast<const char*, const char*, float>(&cocos2d::CCTexture2D::initWithString), py::arg("text"), py::arg("fontName"), py::arg("fontSize"))
		.def("setAliasTexParameters", py::overload_cast<>(&cocos2d::CCTexture2D::setAliasTexParameters))
		.def("setTexParameters", py::overload_cast<cocos2d::_ccTexParams*>(&cocos2d::CCTexture2D::setTexParameters), py::arg("texParams"))
		.def("releaseGLTexture", py::overload_cast<>(&cocos2d::CCTexture2D::releaseGLTexture))
		.def("generateMipmap", py::overload_cast<>(&cocos2d::CCTexture2D::generateMipmap))
		.def("getPixelFormat", py::overload_cast<>(&cocos2d::CCTexture2D::getPixelFormat))
		.def("getPixelsWide", py::overload_cast<>(&cocos2d::CCTexture2D::getPixelsWide))
		.def("getPixelsHigh", py::overload_cast<>(&cocos2d::CCTexture2D::getPixelsHigh))
		.def("getName", py::overload_cast<>(&cocos2d::CCTexture2D::getName))
		.def("getMaxS", py::overload_cast<>(&cocos2d::CCTexture2D::getMaxS))
		.def("setMaxS", py::overload_cast<float>(&cocos2d::CCTexture2D::setMaxS), py::arg("maxS"))
		.def("getMaxT", py::overload_cast<>(&cocos2d::CCTexture2D::getMaxT))
		.def("setMaxT", py::overload_cast<float>(&cocos2d::CCTexture2D::setMaxT), py::arg("maxT"))
		.def("getContentSize", py::overload_cast<>(&cocos2d::CCTexture2D::getContentSize));
	
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
		.def("isIconUnlocked", py::overload_cast<int, IconType>(&GameManager::isIconUnlocked), py::arg("p0"), py::arg("p1"))
		.def_readwrite("m_unkAnimationDict", &GameManager::m_unkAnimationDict)
		.def_readwrite("m_unkAnimationDict2", &GameManager::m_unkAnimationDict2)
		.def_readwrite("m_frameTimeForAnimation", &GameManager::m_frameTimeForAnimation)
		.def_readwrite("m_framesForAnimation", &GameManager::m_framesForAnimation)
		.def_readwrite("m_defaultFrames", &GameManager::m_defaultFrames)
		.def_readwrite("m_switchModes", &GameManager::m_switchModes)
		.def_readwrite("m_toFullscreen", &GameManager::m_toFullscreen)
		.def_readwrite("m_reloading", &GameManager::m_reloading)
		.def_readwrite("m_fix", &GameManager::m_fix)
		.def_readwrite("m_unkBool1", &GameManager::m_unkBool1)
		.def_readwrite("m_unkBool2", &GameManager::m_unkBool2)
		.def_readwrite("m_vsyncEnabled", &GameManager::m_vsyncEnabled)
		.def_readwrite("m_valueKeeper", &GameManager::m_valueKeeper)
		.def_readwrite("m_unlockValueKeeper", &GameManager::m_unlockValueKeeper)
		.def_readwrite("m_customObjectDict", &GameManager::m_customObjectDict)
		.def_readwrite("m_adTimer", &GameManager::m_adTimer)
		.def_readwrite("m_adCache", &GameManager::m_adCache)
		.def_readwrite("m_unkBool3", &GameManager::m_unkBool3)
		.def_readwrite("m_unkSize4_1", &GameManager::m_unkSize4_1)
		.def_readwrite("m_unkDouble2", &GameManager::m_unkDouble2)
		.def_readwrite("m_unkSize4_2", &GameManager::m_unkSize4_2)
		.def_readwrite("m_unkSize4_3", &GameManager::m_unkSize4_3)
		.def_readwrite("m_loaded", &GameManager::m_loaded)
		.def_readwrite("m_googlePlaySignedIn", &GameManager::m_googlePlaySignedIn)
		.def_readwrite("m_editorClipboard", &GameManager::m_editorClipboard)
		.def_readwrite("m_unkSize4_4", &GameManager::m_unkSize4_4)
		.def_readwrite("m_playLayer", &GameManager::m_playLayer)
		.def_readwrite("m_levelEditorLayer", &GameManager::m_levelEditorLayer)
		.def_readwrite("m_gameLayer", &GameManager::m_gameLayer)
		.def_readwrite("m_unkPtr", &GameManager::m_unkPtr)
		.def_readwrite("m_menuLayer", &GameManager::m_menuLayer)
		.def_readwrite("m_inMenuLayer", &GameManager::m_inMenuLayer)
		.def_readwrite("m_unknownVariable", &GameManager::m_unknownVariable)
		.def_readwrite("m_unknownBool3", &GameManager::m_unknownBool3)
		.def_readwrite("m_unknownPlayLayerBool", &GameManager::m_unknownPlayLayerBool)
		.def_readwrite("m_unknownBool4", &GameManager::m_unknownBool4)
		.def_readwrite("m_unknownBool5", &GameManager::m_unknownBool5)
		.def_readwrite("m_playerUDID", &GameManager::m_playerUDID)
		.def_readwrite("m_playerName", &GameManager::m_playerName)
		.def_readwrite("m_commentsEnabled", &GameManager::m_commentsEnabled)
		.def_readwrite("m_playerUserID", &GameManager::m_playerUserID)
		.def_readwrite("m_bgVolume", &GameManager::m_bgVolume)
		.def_readwrite("m_sfxVolume", &GameManager::m_sfxVolume)
		.def_readwrite("m_timeOffset", &GameManager::m_timeOffset)
		.def_readwrite("m_ratedGame", &GameManager::m_ratedGame)
		.def_readwrite("m_clickedFacebook", &GameManager::m_clickedFacebook)
		.def_readwrite("m_clickedTwitter", &GameManager::m_clickedTwitter)
		.def_readwrite("m_clickedYouTube", &GameManager::m_clickedYouTube)
		.def_readwrite("m_clickedTwitch", &GameManager::m_clickedTwitch)
		.def_readwrite("m_clickedDiscord_", &GameManager::m_clickedDiscord_)
		.def_readwrite("m_clickedReddit", &GameManager::m_clickedReddit)
		.def_readwrite("m_socialsDuration", &GameManager::m_socialsDuration)
		.def_readwrite("m_showedAd", &GameManager::m_showedAd)
		.def_readwrite("m_unknownBool", &GameManager::m_unknownBool)
		.def_readwrite("m_editorEnabled", &GameManager::m_editorEnabled)
		.def_readwrite("m_sceneEnum", &GameManager::m_sceneEnum)
		.def_readwrite("m_searchObjectBool", &GameManager::m_searchObjectBool)
		.def_readwrite("m_playerFrame", &GameManager::m_playerFrame)
		.def_readwrite("m_playerShip", &GameManager::m_playerShip)
		.def_readwrite("m_playerBall", &GameManager::m_playerBall)
		.def_readwrite("m_playerBird", &GameManager::m_playerBird)
		.def_readwrite("m_playerDart", &GameManager::m_playerDart)
		.def_readwrite("m_playerRobot", &GameManager::m_playerRobot)
		.def_readwrite("m_playerSpider", &GameManager::m_playerSpider)
		.def_readwrite("m_playerSwing", &GameManager::m_playerSwing)
		.def_readwrite("m_playerColor", &GameManager::m_playerColor)
		.def_readwrite("m_playerColor2", &GameManager::m_playerColor2)
		.def_readwrite("m_playerGlowColor", &GameManager::m_playerGlowColor)
		.def_readwrite("m_playerStreak", &GameManager::m_playerStreak)
		.def_readwrite("m_playerShipFire", &GameManager::m_playerShipFire)
		.def_readwrite("m_playerDeathEffect", &GameManager::m_playerDeathEffect)
		.def_readwrite("m_playerJetpack", &GameManager::m_playerJetpack)
		.def_readwrite("m_chk", &GameManager::m_chk)
		.def_readwrite("m_secretNumber", &GameManager::m_secretNumber)
		.def_readwrite("m_playerGlow", &GameManager::m_playerGlow)
		.def_readwrite("m_playerIconType", &GameManager::m_playerIconType)
		.def_readwrite("m_everyPlaySetup", &GameManager::m_everyPlaySetup)
		.def_readwrite("m_showSongMarkers", &GameManager::m_showSongMarkers)
		.def_readwrite("m_showBPMMarkers", &GameManager::m_showBPMMarkers)
		.def_readwrite("m_recordGameplay", &GameManager::m_recordGameplay)
		.def_readwrite("m_showProgressBar", &GameManager::m_showProgressBar)
		.def_readwrite("m_performanceMode", &GameManager::m_performanceMode)
		.def_readwrite("m_unkBool4", &GameManager::m_unkBool4)
		.def_readwrite("m_clickedGarage", &GameManager::m_clickedGarage)
		.def_readwrite("m_clickedEditor", &GameManager::m_clickedEditor)
		.def_readwrite("m_clickedName", &GameManager::m_clickedName)
		.def_readwrite("m_clickedPractice", &GameManager::m_clickedPractice)
		.def_readwrite("m_showedEditorGuide", &GameManager::m_showedEditorGuide)
		.def_readwrite("m_showedRateDiffDialog", &GameManager::m_showedRateDiffDialog)
		.def_readwrite("m_showedRateStarDialog", &GameManager::m_showedRateStarDialog)
		.def_readwrite("m_showedLowDetailDialog", &GameManager::m_showedLowDetailDialog)
		.def_readwrite("m_unkPtr2", &GameManager::m_unkPtr2)
		.def_readwrite("m_unkPtr3", &GameManager::m_unkPtr3)
		.def_readwrite("m_unkSize4_5", &GameManager::m_unkSize4_5)
		.def_readwrite("m_unkSize4_6", &GameManager::m_unkSize4_6)
		.def_readwrite("m_unkSize4_7", &GameManager::m_unkSize4_7)
		.def_readwrite("m_unkSize4_8", &GameManager::m_unkSize4_8)
		.def_readwrite("m_loadedBgID", &GameManager::m_loadedBgID)
		.def_readwrite("m_loadedGroundID", &GameManager::m_loadedGroundID)
		.def_readwrite("m_loadedMG", &GameManager::m_loadedMG)
		.def_readwrite("m_loadedFont", &GameManager::m_loadedFont)
		.def_readwrite("m_loadedDeathEffect", &GameManager::m_loadedDeathEffect)
		.def_readwrite("m_loadingBG", &GameManager::m_loadingBG)
		.def_readwrite("m_loadingG", &GameManager::m_loadingG)
		.def_readwrite("m_loadingG1", &GameManager::m_loadingG1)
		.def_readwrite("m_finishedLoadingG1", &GameManager::m_finishedLoadingG1)
		.def_readwrite("m_shouldLoadG1", &GameManager::m_shouldLoadG1)
		.def_readwrite("m_finishedLoadingMG1", &GameManager::m_finishedLoadingMG1)
		.def_readwrite("m_finishedLoadingMG2", &GameManager::m_finishedLoadingMG2)
		.def_readwrite("m_unkBool5", &GameManager::m_unkBool5)
		.def_readwrite("m_unkSize4_9", &GameManager::m_unkSize4_9)
		.def_readwrite("m_unkSize4_10", &GameManager::m_unkSize4_10)
		.def_readwrite("m_unkSize4_11", &GameManager::m_unkSize4_11)
		.def_readwrite("m_bootups", &GameManager::m_bootups)
		.def_readwrite("m_hasRatedGame", &GameManager::m_hasRatedGame)
		.def_readwrite("m_unkBool6", &GameManager::m_unkBool6)
		.def_readwrite("m_shouldLoadUnlockValueKeeper", &GameManager::m_shouldLoadUnlockValueKeeper)
		.def_readwrite("m_unkBool7", &GameManager::m_unkBool7)
		.def_readwrite("m_unkBool8", &GameManager::m_unkBool8)
		.def_readwrite("m_hasRP", &GameManager::m_hasRP)
		.def_readwrite("m_canGetLevelSaveData", &GameManager::m_canGetLevelSaveData)
		.def_readwrite("m_resolution", &GameManager::m_resolution)
		.def_readwrite("m_texQuality", &GameManager::m_texQuality)
		.def_readwrite("m_somethingInMenuLayer", &GameManager::m_somethingInMenuLayer)
		.def_readwrite("m_unkPtr4", &GameManager::m_unkPtr4)
		.def_readwrite("m_ropeGarageEnter", &GameManager::m_ropeGarageEnter)
		.def_readwrite("m_unkSize4_12", &GameManager::m_unkSize4_12)
		.def_readwrite("m_unkSize4_13", &GameManager::m_unkSize4_13)
		.def_readwrite("m_unkBool10", &GameManager::m_unkBool10)
		.def_readwrite("m_unkSize4_14", &GameManager::m_unkSize4_14)
		.def_readwrite("m_disableThumbstick", &GameManager::m_disableThumbstick)
		.def_readwrite("m_customFPSTarget", &GameManager::m_customFPSTarget)
		.def_readwrite("m_unkBool11", &GameManager::m_unkBool11)
		.def_readwrite("m_customMenuSongID", &GameManager::m_customMenuSongID)
		.def_readwrite("m_customPracticeSongID", &GameManager::m_customPracticeSongID)
		.def_readwrite("m_loadIcon", &GameManager::m_loadIcon)
		.def_readwrite("m_loadIcon2", &GameManager::m_loadIcon2)
		.def_readwrite("m_isIconBeingLoaded", &GameManager::m_isIconBeingLoaded)
		.def_readwrite("m_keyStartForIcon", &GameManager::m_keyStartForIcon)
		.def_readwrite("m_iconDelegates", &GameManager::m_iconDelegates)
		.def_readwrite("m_iconRequestID", &GameManager::m_iconRequestID)
		.def_readwrite("m_unkArray", &GameManager::m_unkArray)
		.def_readwrite("m_someAdPointer", &GameManager::m_someAdPointer)
		.def_readwrite("m_unkSize4_15", &GameManager::m_unkSize4_15)
		.def_readwrite("m_unkSize4_16", &GameManager::m_unkSize4_16)
		.def_readwrite("m_unkSize4_17", &GameManager::m_unkSize4_17)
		.def_readwrite("m_dpad1", &GameManager::m_dpad1)
		.def_readwrite("m_dpad2", &GameManager::m_dpad2)
		.def_readwrite("m_dpad3", &GameManager::m_dpad3)
		.def_readwrite("m_dpad4", &GameManager::m_dpad4)
		.def_readwrite("m_dpad5", &GameManager::m_dpad5)
		.def_readwrite("m_dpadLayout1", &GameManager::m_dpadLayout1)
		.def_readwrite("m_dpadLayout2", &GameManager::m_dpadLayout2)
		.def_readwrite("m_dpadLayout3", &GameManager::m_dpadLayout3)
		.def_readwrite("m_dpadLayoutDual1", &GameManager::m_dpadLayoutDual1)
		.def_readwrite("m_dpadLayoutDual2", &GameManager::m_dpadLayoutDual2)
		.def_readwrite("m_dpadLayoutDual3", &GameManager::m_dpadLayoutDual3)
		.def_readwrite("m_unkSize4_18", &GameManager::m_unkSize4_18)
		.def_readwrite("m_unkSize4_19", &GameManager::m_unkSize4_19)
		.def_readwrite("m_unkSize4_20", &GameManager::m_unkSize4_20)
		.def_readwrite("m_shouldResetShader", &GameManager::m_shouldResetShader)
		.def_readwrite("m_practicePosX", &GameManager::m_practicePosX)
		.def_readwrite("m_practicePosY", &GameManager::m_practicePosY)
		.def_readwrite("m_practiceOpacity", &GameManager::m_practiceOpacity);
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