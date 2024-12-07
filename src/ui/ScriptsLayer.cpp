#include "Serpent.hpp"

using namespace geode::prelude;
using namespace Serpent::ui;

bool ScriptsLayer::setup() {
    scroll = ScrollLayer::create(CCSize(winSize.width - 125.0f, 230));
    this->setTitle("Serpent", "bigFont.fnt");

    scroll->setPosition(winSize / 2);
    scroll->m_contentLayer->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(250.0f)
            ->setGap(5.0f)
    );

    border = Border::create(scroll, {100, 45, 0, 255}, {winSize.width - 125.0f, 230});

    border->setPosition(
        {
            (m_bgSprite->getPositionX() - (m_bgSprite->getContentWidth() * m_bgSprite->getAnchorPoint().x)) + 10,
            m_bgSprite->getPositionY() - 130
        }
    );

    m_mainLayer->addChild(border);

    for (auto& script : Serpent::tempScripts) {
        scroll->m_contentLayer->addChild(ScriptItem::create(script, [&](CCObject* sender) {
            if (static_cast<CCMenuItemToggler*>(sender)->isToggled()) {
                Mod::get()->setSavedValue<std::string>("enabled-script", script["id"].asString().unwrap());
            }
        }, CCSize(scroll->getContentSize().width, 30)));
    }

    auto menu = CCMenu::create();

    auto restartBtn = CCMenuItemExt::createSpriteExtraWithFrameName("GJ_updateBtn_001.png", 0.78f, [](CCObject* sender){
        game::restart();
    });
    menu->addChild(restartBtn);
    auto plusSpr = CircleButtonSprite::createWithSprite("plus_sign.png"_spr);
    plusSpr->setScale(0.78f);
    auto addBtn = CCMenuItemSpriteExtra::create(plusSpr, this, menu_selector(ScriptsLayer::onAdd));
    menu->addChild(addBtn);

    menu->setLayout(RowLayout::create()
        ->setAxis(Axis::Row)
        ->setAxisAlignment(AxisAlignment::Center)
        ->setAutoScale(true)
        ->setGap(5.0f)
        ->setCrossAxisAlignment(AxisAlignment::Center)
    );
    menu->setPosition({70.0f, 258.0f});

    m_buttonMenu->addChild(menu);
    scroll->m_contentLayer->updateLayout();
    scroll->updateLayout();
    scroll->scrollToTop();
    return true;
}

void ScriptsLayer::onAdd(CCObject* sender) {
    // https://github.com/ShineUA/Geometrize2GD/blob/main/src/layers/ImportPopup.cpp
    file::FilePickOptions::Filter filter = {};
    file::FilePickOptions options = {
        std::nullopt,
        {filter}
    };

    m_pickListener.bind([this](Task<Result<std::filesystem::path>>::Event* event) {
        if (event->isCancelled()) {
            Notification::create("Failed to open file, task cancelled.", NotificationIcon::Error)->show();
            return;
        }

        if (auto result = event->getValue()) {
            if (result->isErr()) {
                Notification::create(fmt::format("Error opening file: {}", result->err()), NotificationIcon::Error)->show();
                return;
            }
            auto path = result->unwrap();
            if (path.extension() != ".zip") {
                Notification::create("Must have a .zip extension.", NotificationIcon::Error)->show();
                return;
            }
            if (std::filesystem::exists(Mod::get()->getConfigDir() / "scripts" / path.filename().stem())) {
                geode::createQuickPopup(
                    "File already exists.",
                    fmt::format("File {} already exists at {}, overwrite?", path.filename(), path),
                    "Yes", "No",
                    [=](auto, bool btn2) {
                        if (!btn2) {
                            std::filesystem::copy(path, Mod::get()->getConfigDir() / "scripts", std::filesystem::copy_options::overwrite_existing);
                        }
                    }
                );
            } else {
                std::filesystem::copy(path, Mod::get()->getConfigDir() / "scripts", std::filesystem::copy_options::overwrite_existing); // we made sure it doesnt exist yet, the last argument is useless
            }
        }
    });
    m_pickListener.setFilter(file::pick(file::PickMode::OpenFile, options));
}

bool ScriptsLayer::initAnchored() {
    winSize = CCDirector::get()->getWinSize();
    return Popup::initAnchored(winSize.width - 100.0f, 280.0f);
}

ScriptsLayer* ScriptsLayer::create() {
    auto ret = new ScriptsLayer();
    if (ret->initAnchored()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}