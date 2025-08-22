#include "Games.hpp"
#include <iostream>
#include <cmath>


Games::Games() : invisibleMan(std::make_shared<InvisibleMan>(this->mapGames)),
                dracula(std::make_shared<Dracula>(this->mapGames)),
                archaeologist(std::make_shared<Archaeologist>(this->mapGames, this->perckCardGames)),
                scientist(std::make_shared<Scientist>(this->mapGames, this->perckCardGames)),
                mayor(std::make_shared<Mayor>(this->mapGames, this->perckCardGames)),
                courier(std::make_shared<Courier>(this->mapGames, this->perckCardGames)),
                player1(this->mapGames, perckCardGames, mayor, archaeologist),
                player2(this->mapGames,this->perckCardGames, courier, scientist) 
                 {
    this->arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    this->handCursor.loadFromSystem(sf::Cursor::Hand);
    this->windowSize = this->window.getSize();
    setFont();
    // this->itemGames{(this->mapGames)};
    // Heroes hero(4, NameHeroes::ARCHAEOLOGIST, this->mapGames);
}

void Games::setFont() {
    if(!font.loadFromFile("../font/Creepster-Regular.ttf")) {
        throw std::invalid_argument("not found font");
    }
}

bool Games::isMouseOver(const sf::RectangleShape& button, const sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}

bool Games::isMouseOver(const sf::CircleShape& button, const sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}



void Games::centerTextInButton(sf::Text& text, const sf::RectangleShape& button) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    text.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);
}

void Games::setImageInDesktop(const sf::Texture& backgroundTexture, sf::Sprite& backgroundSprite) {
    sf::Vector2u textureSize = backgroundTexture.getSize();

    backgroundSprite.setScale(
        float(this->windowSize.x) / (textureSize.x),
        float(this->windowSize.y) / (textureSize.y)
    );
}

void Games::setButtonAndTextMenu(sf::RectangleShape& button1, sf::RectangleShape& button2, sf::RectangleShape& button3, sf::Text& text1, sf::Text& text2, sf::Text& text3) {
    button1.setFillColor(sf::Color(25,80,120,210));
    button1.setPosition(this->windowSize.x / 2 - 600.f, this->windowSize.y / 2 + 450.f);
    
    button2.setFillColor(sf::Color(25,80,120,210));
    button2.setPosition(this->windowSize.x / 2 - 150.f, this->windowSize.y / 2 + 450.f);

    button3.setFillColor(sf::Color(150,80,120,140));
    button3.setPosition(this->windowSize.x / 2 + 300.f, this->windowSize.y / 2 + 450.f);

    text1.setFillColor(sf::Color(180,40,40,250));
    text1.setOutlineColor(sf::Color::Black);
    text1.setOutlineThickness(4.f);
    this->centerTextInButton(text1, button1);

    text2.setFillColor(sf::Color(180,40,40,250));
    text2.setOutlineColor(sf::Color::Black);
    text2.setOutlineThickness(4.f);
    this->centerTextInButton(text2, button2);

    text3.setFillColor(sf::Color::Black);
    text3.setOutlineColor(sf::Color(180,40,40,250));
    text3.setOutlineThickness(4.f);
    this->centerTextInButton(text3, button3);
}


void Games::menu(bool chek) {

    sf::Texture backgroundTextTureMenu;
    if(!backgroundTextTureMenu.loadFromFile("../Horrified_Assets/Menus.png")) {
        throw std::invalid_argument("not found image");
    }
    sf::Sprite backgroundSpritMenu(backgroundTextTureMenu);
    this->setImageInDesktop(backgroundTextTureMenu, backgroundSpritMenu);
    
    sf::RectangleShape button1(sf::Vector2f(300.f, 90.f));
    sf::RectangleShape button2(sf::Vector2f(300.f, 90.f));
    sf::RectangleShape button3(sf::Vector2f(300.f, 90.f));

    sf::Text text1("Start Game", font, 45);
    sf::Text text2("Load Game", font, 45);
    sf::Text text3("Exit", font, 50);

    this->setButtonAndTextMenu(button1, button2, button3, text1, text2, text3);

    while (this->window.isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionf(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        
        if(button1.getGlobalBounds().contains(mousePositionf) || 
        button2.getGlobalBounds().contains(mousePositionf) ||
        button3.getGlobalBounds().contains(mousePositionf)) {
            this->window.setMouseCursor(this->handCursor);
        }
        else {
            this->window.setMouseCursor(this->arrowCursor);
        }

        while (this->window.pollEvent(this->event)) {
            if(this->event.type == sf::Event::MouseButtonPressed && this->event.mouseButton.button == sf::Mouse::Left) {
                if(this->isMouseOver(button1, this->window)) {
                    if(chek) {
                        std::vector<std::string> s1 = this->startPlay("1");
                        std::vector<std::string> s2 = this->startPlay("2");
                        if(s1[1] >= s2[1]) {
                            player1.namePlayer = s2[0];
                            player1.player = Player::PLAYER_1;
                            
                            player2.namePlayer = s1[0];
                            player2.player = Player::PLAYER_2;
                            this->startGame();
                        }
                        else {
                            player1.namePlayer = s1[0];
                            player1.player = Player::PLAYER_1;

                            player2.namePlayer = s2[0];
                            player2.player = Player::PLAYER_2;
                            this->startGame();

                        }
                    }
                    else {
                        return;
                    }
                }
                else if(this->isMouseOver(button2, this->window)) {
                    return;
                }
                else if(this->isMouseOver(button3, this->window)) {
                    this->window.close();
                }
            }
        }

        this->window.clear();

        this->window.draw(backgroundSpritMenu);

        this->window.draw(button1);
        this->window.draw(button2);
        this->window.draw(button3);

        this->window.draw(text1);
        this->window.draw(text2);
        this->window.draw(text3);

        this->window.display();        
    }
}

void Games::setButtonAndTextStartGame(sf::RectangleShape& inputBox1, sf::RectangleShape& inputBox2, sf::RectangleShape& button3, sf::Text& text1, sf::Text& text2, sf::Text& text3, sf::Text& textInput1, sf::Text& textInput2) {
    sf::FloatRect textRect = textInput1.getLocalBounds();
    textInput1.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    textInput1.setFillColor(sf::Color(180,40,40,250));
    textInput1.setOutlineColor(sf::Color::White);
    textInput1.setOutlineThickness(2.f);
    textInput1.setPosition(this->windowSize.x / 2, this->windowSize.y / 2);

    inputBox1.setFillColor(sf::Color::Black);
    inputBox1.setOutlineColor(sf::Color(25,80,120,210));
    inputBox1.setOutlineThickness(2.f);
    inputBox1.setPosition(this->windowSize.x / 2 - 250, this->windowSize.y / 2 + 75);
    
    textRect = textInput2.getLocalBounds();
    textInput2.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    textInput2.setFillColor(sf::Color(180,40,40,250));
    textInput2.setOutlineColor(sf::Color::White);
    textInput2.setOutlineThickness(2.f);
    textInput2.setPosition(this->windowSize.x / 2, this->windowSize.y / 2 + 225);


    inputBox2.setFillColor(sf::Color::Black);
    inputBox2.setOutlineColor(sf::Color(25,80,120,210));
    inputBox2.setOutlineThickness(2.f);
    inputBox2.setPosition(this->windowSize.x / 2 - 250, this->windowSize.y / 2 + 300);

    button3.setFillColor(sf::Color::Black);
    button3.setOutlineColor(sf::Color(25,80,120,210));
    button3.setOutlineThickness(2.f);
    button3.setPosition(this->windowSize.x / 2 - 150, this->windowSize.y / 2 + 425);
    
    sf::FloatRect textBounds = text3.getLocalBounds();

    text1.setFillColor(sf::Color(180,40,40,250));
    text1.setOutlineColor(sf::Color::Black);
    text1.setOutlineThickness(4.f);
    text1.setOrigin(textBounds.width / 2, textBounds.height / 2);
    text1.setPosition(
        inputBox1.getPosition().x + inputBox1.getSize().x / 2 - 150,
        inputBox1.getPosition().y + inputBox1.getSize().y / 2 - 5
    );


    text2.setFillColor(sf::Color(180,40,40,250));
    text2.setOutlineColor(sf::Color::Black);
    text2.setOutlineThickness(4.f);
    text2.setOrigin(textBounds.width / 2, textBounds.height / 2);
    text2.setPosition(
        inputBox2.getPosition().x + inputBox2.getSize().x / 2 - 150,
        inputBox2.getPosition().y + inputBox2.getSize().y / 2 - 5
    );


    text3.setFillColor(sf::Color::White);
    text3.setOutlineColor(sf::Color(180,40,40,250));
    text3.setOutlineThickness(2.f);
    this->centerTextInButton(text3, button3);
}



std::vector<std::string> Games::startPlay(const std::string& numberPlayer) {

    sf::Texture backgroundTextTureStartPlay;
    if(!backgroundTextTureStartPlay.loadFromFile("../Horrified_Assets/StartPlayer.png")) {
        throw std::invalid_argument("not found image");
    }
    sf::Sprite backgroundSpritStartPlay(backgroundTextTureStartPlay);
    this->setImageInDesktop(backgroundTextTureStartPlay, backgroundSpritStartPlay);

    sf::Text textInputBox1("PLAYER NAME " + numberPlayer + ":", this->font, 60);
    sf::RectangleShape inputBox1(sf::Vector2f(500.f, 80.f)); 
    std::string inputString1 = "";
    sf::Text text1("", this->font, 45);
    bool selected1 = false;
    bool chekInput1 = false;

    sf::Text textInputBox2("LAST TIME YOU ATE GARLIC:", this->font, 60);
    sf::RectangleShape inputBox2(sf::Vector2f(500.f, 80.f));
    std::string inputString2 = "";
    sf::Text text2("", this->font, 45);
    bool selected2 = false;
    bool chekInput2 = false;
    
    sf::RectangleShape submit(sf::Vector2f(300.f, 80.f));
    sf::Text text3("SUBMIT", this->font, 55);

    this->setButtonAndTextStartGame(inputBox1, inputBox2, submit, text1, text2, text3, textInputBox1, textInputBox2);


    while (this->window.isOpen()) {
        
        while (this->window.pollEvent(this->event)) {
            if(this->event.key.code == sf::Keyboard::Escape) {
                this->menu(false);
            }
            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if(inputBox1.getGlobalBounds().contains(mouse) || 
            inputBox2.getGlobalBounds().contains(mouse) ||
            submit.getGlobalBounds().contains(mouse)) {
                this->window.setMouseCursor(this->handCursor);
            }
            else {
                this->window.setMouseCursor(this->arrowCursor);
            }

            if(this->event.type == sf::Event::MouseButtonPressed) {
                selected1 = this->isMouseOver(inputBox1, this->window);
                selected2 = this->isMouseOver(inputBox2, this->window);
            }
                
            if((this->isMouseOver(submit, this->window)&& this->event.type == sf::Event::MouseButtonPressed && this->event.mouseButton.button == sf::Mouse::Left) || this->event.key.code == sf::Keyboard::Enter) {
                if(chekInput1 == true && chekInput2 == true) {
                    return{inputString1, inputString2};
                }
            }

            if(this->event.type == sf::Event::TextEntered) {
                if(selected1) {
                    if(this->event.text.unicode == 8 && !inputString1.empty())
                        inputString1.pop_back();
                    else if(this->event.text.unicode < 128 && inputString1.size() < 20) {
                        inputString1 += static_cast<char>(this->event.text.unicode);
                        chekInput1 = true;
                    }
                }
                if(selected2) {
                    if(this->event.text.unicode == 8 && !inputString2.empty())
                        inputString2.pop_back();
                    else if(this->event.text.unicode >= '0' && this->event.text.unicode <= '9' && inputString2.size() < 20) {
                        inputString2 += static_cast<char>(this->event.text.unicode);
                        chekInput2 = true;
                    }
                }
            }
            
            
        }
        text1.setString(inputString1);
        text2.setString(inputString2);


        this->window.clear();

        this->window.draw(backgroundSpritStartPlay);

        this->window.draw(textInputBox1);
        this->window.draw(inputBox1);
        this->window.draw(text1);

        this->window.draw(textInputBox2);
        this->window.draw(inputBox2);
        this->window.draw(text2);



        this->window.draw(submit);
        this->window.draw(text3);

        this->window.display();
    }
    return{inputString1, inputString2};
    
}

void Games::addLocations() {

    float scaleX = float(windowSize.x - 400) / 1663.f;
    float scaleY = float(windowSize.y) / 1653.f;
    
    
    auto addLocation = [&](const NameLocation& nameLocation, sf::FloatRect rect, float radius) {
        float centerX = (rect.left +rect.width / 2.f) * scaleX;
        float centerY = (rect.top + rect.height / 2.f) * scaleY;
        sf::CircleShape shape(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(centerX, centerY);
        shape.setFillColor(sf::Color::Transparent);

        this->locations.emplace_back(nameLocation, shape);
    };



    addLocation(NameLocation::CAVE,{46, 308, 165, 165}, 60);
    addLocation(NameLocation::CAMP,      {273, 238, 220, 220}, 100);
    addLocation(NameLocation::PRECINCT,  {548, 185, 230, 230}, 90);
    addLocation(NameLocation::INN, {827, 134, 230, 230}, 90);
    addLocation(NameLocation::BARN, {1140, 170, 230, 230}, 90);
    addLocation(NameLocation::DUNGEON, {1429, 197, 203, 203}, 80);
    addLocation(NameLocation::TOWER, {1280, 462, 230, 230}, 90);
    addLocation(NameLocation::DOCKS, {1375, 755, 230, 230}, 90);
    addLocation(NameLocation::THEATRE, {945, 492, 230, 230}, 90);
    addLocation(NameLocation::MANSION, {344, 738, 230, 230}, 100);
    addLocation(NameLocation::ABBEY, {50, 852, 230, 230}, 90);
    addLocation(NameLocation::CRYPT, {27, 1171, 200, 200}, 80);
    addLocation(NameLocation::MUSEUM, {253, 1112, 244, 244}, 100);
    addLocation(NameLocation::SHOP, {805, 921, 230, 230}, 90);
    addLocation(NameLocation::CHURCH, {639, 1190, 230, 230}, 85);
    addLocation(NameLocation::HOSPITAL, {535, 1421, 189, 189}, 70);
    addLocation(NameLocation::GRAVEYARD, {876, 1368, 230, 230}, 90);
    addLocation(NameLocation::LABORATORY, {1028, 1121, 240, 240}, 90);
    addLocation(NameLocation::INSTITUTE, {1220, 1366, 240, 240}, 90);
}


void Games::startGame() {
    this->itemGames.addItemInGame();

    this->addLocations();   
    sf::Texture backgroundTextureMap;
    if(!backgroundTextureMap.loadFromFile("../Horrified_Assets/map.png")) {
        throw std::invalid_argument("not found image");
    }

    sf::Sprite backgroundSpriteMap(backgroundTextureMap);
    backgroundSpriteMap.setScale(
        float(this->windowSize.x-400) / (backgroundTextureMap.getSize().x),
        float(this->windowSize.y) / (backgroundTextureMap.getSize().y)
    );
    while (this->window.isOpen()) {
        this->window.clear();
        this->window.draw(backgroundSpriteMap);
        
        if(player1.hero1->canTakeAction() || player1.hero2->canTakeAction() || player1.turn == Turn::MONSTER) {
        this->run(player1);
        } 
        else if(player2.hero1->canTakeAction() || player2.hero2->canTakeAction() || player2.turn == Turn::MONSTER) {
            this->run(player2);
        }
        else {

            this->player1.hero1->resetActions();
            this->player1.hero2->resetActions();
            this->player2.hero1->resetActions();
            this->player2.hero2->resetActions();
        }
        this->window.display();
    }
}

void Games::run(Players& player) {

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f mousePositionf(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    bool cursorOnLocation = false;

    sf::Texture textureAction[8];
    sf::Sprite spriteAction[8];
    sf::RectangleShape recAction[8];
    
    if(player.turn == Turn::HERO) {
        
        this->setButtonAndImageAction(recAction[0],textureAction[0],spriteAction[0],"move.png",1,0);
        this->setButtonAndImageAction(recAction[1],textureAction[1],spriteAction[1],"guide.png",1,1);
        this->setButtonAndImageAction(recAction[2],textureAction[2],spriteAction[2],"advance.png",1,2);
        this->setButtonAndImageAction(recAction[3],textureAction[3],spriteAction[3],"defeat.png",2,1);
        this->setButtonAndImageAction(recAction[4],textureAction[4],spriteAction[4],"pickup.png",2,0);
        this->setButtonAndImageAction(recAction[5],textureAction[5],spriteAction[5],"specialAction.png",2,2);

        this->setImageMonsterCard(textureAction[6],spriteAction[6],recAction[6], this->getNameImage(player.hero1->getNameHero()));
        this->setImageMonsterCard(textureAction[7],spriteAction[7],recAction[7], this->getNameImage(player.hero2->getNameHero()),300);

        bool skip = false;

        sf::Texture TextureMVHI[2];
        sf::Sprite SpriteMVHI[2];
        this->setImageMVHI(TextureMVHI[0], SpriteMVHI[0], "item.png", 1);
        
        for(size_t i = 0; i < 8; ++i) {
            this->window.draw(spriteAction[i]);
            this->window.draw(recAction[i]);
        }

        
        for(size_t i = 0; i < 8; ++i) {
            
            if(this->isMouseOver(recAction[i], this->window)) {
                cursorOnLocation = true;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    switch (i)
                    {
                        case 0:
                            this->moveGames(player);
                            break;
                        case 1:
                            this->guideGames(player);
                            break;
                        case 2:
                            this->advanceGames(player);
                            break;
                        case 3:
                            this->defeatGames(player);
                            break;
                        case 4:
                            try
                            {
                                this->clickedLocation(player.hero1->getLocationHero(), player, *player.hero1, NameAction::PICKUP);
                            }
                            catch(const std::bad_alloc& e)
                            {
                                try
                                {
                                    /* code */
                                    this->clickedLocation(player.hero2->getLocationHero(), player, *player.hero2, NameAction::PICKUP);
                                    return;
                                }
                                catch(const std::exception& e)
                                {
                                    this->cout("There are no items at your location");
                                    return;
                                }
                                

                                std::cerr << e.what() << '\n';
                            }
                        case 6:{


                            sf::Texture TextureMVHI[2];
                            sf::Sprite SpriteMVHI[2];
                            this->setImageMVHI(TextureMVHI[0], SpriteMVHI[0], "item.png", 1);

                            sf::Texture textureBackground;
                            if(!textureBackground.loadFromFile("../Horrified_Assets/backgroundClick.png")) {
                                throw std::invalid_argument("not found background click");
                            }
                            sf::Sprite spriteBackground(textureBackground);
                            spriteBackground.setPosition(270, 0);
                            spriteBackground.setScale(
                                float(((this->windowSize.x)) / (textureBackground.getSize().x)),
                                float(this->windowSize.y / textureBackground.getSize().y)
                            );

                            std::vector<std::pair<NameItem,sf::RectangleShape>> itemShape;
                            std::vector<sf::Sprite> itemSprit;
                            std::vector<sf::Texture> itemTexture;
                            std::vector<NameItem> nameItem;
                            TypeOwnership type;
                            switch (player.hero1->getNameHero())
                            {
                            case NameHeroes::ARCHAEOLOGIST:
                                type = TypeOwnership::ARCHAEOLOGIST;
                                break;
                            
                            case NameHeroes::COURIER:
                                type = TypeOwnership::COURIER;
                                break;
                            
                            case NameHeroes::MAYOR:
                                type = TypeOwnership::MAYOR;
                                break;
                            
                            case NameHeroes::SCIENTIST:
                                type = TypeOwnership::SCIENTIST;
                                break;
                            default:
                                break;
                            }
                            for(const auto& item : itemGames.getItemsInGame()) {
                                if(type == item.second.getTypeOwnsership()) {
                                    nameItem.emplace_back(item.first);
                                }
                            }
                            this->cout("");
                            std::vector<std::pair<PerkCardType,sf::RectangleShape>> perkShape;
                            std::vector<sf::Sprite> perkSprit;
                            std::vector<sf::Texture> perkTexture;
                            std::vector<PerkCardType> nameperk;
                            for(const auto& perk : player.hero2->getPerkCards()) {
                                nameperk.emplace_back(perk.getPerkType());
                            }
                            this->setButtonClickedLocation(itemShape,nameItem, itemSprit,itemTexture,-100, 1);
                            this->setButtonClickedLocation(perkShape,nameperk, perkSprit,perkTexture,50, -1);
                                while (this->event.key.code != sf::Keyboard::Escape) 
                                {
                                    while (window.pollEvent(this->event)) { 
                                        
                                    }
                                        window.clear();
                                        window.draw(spriteBackground);
                                        for(const auto& i : itemSprit) {
                                            window.draw(i);
                                        }
                                        for(const auto& i : perkSprit) {
                                            window.draw(i);
                                        }
                                        for(const auto& i : SpriteMVHI) {
                                            window.draw(i);
                                        }
                                        window.display();
                                }


                        }
                        case 7:{
                        sf::Texture TextureMVHI[2];
                            sf::Sprite SpriteMVHI[2];
                            this->setImageMVHI(TextureMVHI[0], SpriteMVHI[0], "item.png", 1);

                            sf::Texture textureBackground;
                            if(!textureBackground.loadFromFile("../Horrified_Assets/backgroundClick.png")) {
                                throw std::invalid_argument("not found background click");
                            }
                            sf::Sprite spriteBackground(textureBackground);
                            spriteBackground.setPosition(270, 0);
                            spriteBackground.setScale(
                                float(((this->windowSize.x)) / (textureBackground.getSize().x)),
                                float(this->windowSize.y / textureBackground.getSize().y)
                            );

                            std::vector<std::pair<NameItem,sf::RectangleShape>> itemShape;
                            std::vector<sf::Sprite> itemSprit;
                            std::vector<sf::Texture> itemTexture;
                            std::vector<NameItem> nameItem;
                            TypeOwnership type;
                            switch (player.hero1->getNameHero())
                            {
                            case NameHeroes::ARCHAEOLOGIST:
                                type = TypeOwnership::ARCHAEOLOGIST;
                                break;
                            
                            case NameHeroes::COURIER:
                                type = TypeOwnership::COURIER;
                                break;
                            
                            case NameHeroes::MAYOR:
                                type = TypeOwnership::MAYOR;
                                break;
                            
                            case NameHeroes::SCIENTIST:
                                type = TypeOwnership::SCIENTIST;
                                break;
                            default:
                                break;
                            }
                            for(const auto& item : itemGames.getItemsInGame()) {
                                if(type == item.second.getTypeOwnsership()) {
                                    nameItem.emplace_back(item.first);
                                }
                            }
                            std::vector<std::pair<PerkCardType,sf::RectangleShape>> perkShape;
                            std::vector<sf::Sprite> perkSprit;
                            std::vector<sf::Texture> perkTexture;
                            std::vector<PerkCardType> nameperk;
                            for(const auto& perk : player.hero2->getPerkCards()) {
                                nameperk.emplace_back(perk.getPerkType());
                            }
                            this->setButtonClickedLocation(itemShape,nameItem, itemSprit,itemTexture,-100, 1);
                            this->setButtonClickedLocation(perkShape,nameperk, perkSprit,perkTexture,50, -1);
                                while (this->event.key.code != sf::Keyboard::Escape) 
                                {
                                    while (window.pollEvent(this->event)) { 
                                        
                                    }
                                        window.clear();
                                        window.draw(spriteBackground);
                                        for(const auto& i : itemSprit) {
                                            window.draw(i);
                                        }
                                        for(const auto& i : perkSprit) {
                                            window.draw(i);
                                        }
                                        for(const auto& i : SpriteMVHI) {
                                            window.draw(i);
                                        }
                                        window.display();
                                }


                        }
                            break;
                        default:
                        break;
                    }
                }
            }
        }
        if(!skip) {
            if(!player.hero1->canTakeAction() && !player.hero2->canTakeAction()) {
                player.turn = Turn::MONSTER; // نوبت مانستر
                return; // برگرد به حلقه اصلی
            }
        }

    }
    else if(player.turn == Turn::MONSTER) {
        this->monsterCardInGames.drawCard(this->itemGames, this->villagerGames, *player1.hero1, *player1.hero2, *player2.hero1, *player2.hero2, dynamic_cast<Dracula&>(*dracula),
    dynamic_cast<InvisibleMan&>(*invisibleMan), this);
        this->drawMonsterCard( this->monsterCardInGames.drawCard(this->itemGames, this->villagerGames, *player1.hero1, *player1.hero2, *player2.hero1, *player2.hero2, dynamic_cast<Dracula&>(*dracula),
    dynamic_cast<InvisibleMan&>(*invisibleMan), this).getTypeItem());

        player.turn = Turn::HERO;
    }
    
    

    for(const auto& [name, shape] : this->locations) {
        if (this->isMouseOver(shape, this->window)) {
            cursorOnLocation = true;
            break;
        }
    }
    this->window.setMouseCursor(cursorOnLocation ? this->handCursor : this->arrowCursor);
    
    while (this->window.pollEvent(this->event)) {
            if(this->event.key.code == sf::Keyboard::Escape) {
            this->menu(false);
        }
        for(const auto& [name, shape] : this->locations) {
            if(this->isMouseOver(shape, this->window)) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    this->clickedLocation(name, player, *player.hero1);
                    break;
                }
            }
        }
    }
}

void Games::setImageMonsterCard(sf::Texture& texture, sf::Sprite& sprite, sf::RectangleShape& rect, const std::string& nameImage, int i) {
    if(!texture.loadFromFile(nameImage)) {
        throw std::invalid_argument("not found image");
    }
    sprite.setTexture(texture);
    sprite.setPosition(this->windowSize.x - 400, this->windowSize.y / 2 - i);
    sprite.setScale(400.f / texture.getSize().x ,300.f / texture.getSize().y);

    rect.setSize(sf::Vector2f(400, 300));
    rect.setPosition(sprite.getPosition());
    rect.setFillColor(sf::Color(100,0,0,100));

}

void Games::setImageMVHI(sf::Texture& texture, sf::Sprite& sprite, const std::string& nameImage, const int loc) {
    if(!texture.loadFromFile("../Horrified_Assets/Action/" + nameImage)) {
        throw std::invalid_argument("not found image");
    }
    sprite.setTexture(texture);
    sprite.setPosition(0, this->windowSize.y / 2 + (loc * 300));
    sprite.setScale(
        float(270) / (texture.getSize().x),
        float(this->windowSize.y / 4) / (texture.getSize().y)
    );
}

void Games::setButtonAndImageAction(sf::RectangleShape& rect, sf::Texture& texture, sf::Sprite& sprit, const std::string& nameImage, const int i, const int j) {

    if(!texture.loadFromFile("../Horrified_Assets/Action/" + nameImage)) {
        throw std::invalid_argument("not found image action");
    }

    sprit.setTexture(texture);
    sprit.setPosition(this->windowSize.x-(200*i), this->windowSize.y / 2+(200*j));

    sprit.setScale(
        float(200.f / texture.getSize().x), 
        float((200.f )/(texture.getSize().y))
    );



        rect.setSize(sf::Vector2f(200, 200));
        rect.setPosition(this->windowSize.x - (200*i), this->windowSize.y / 2+(200*j));
        rect.setFillColor(sf::Color(100,0,0,100));

}

void Games::clickedLocation(const NameLocation& nameLocation, Players& player, Heroes& hero, const NameAction& nameAction) {
    auto chek = std::find_if(mapGames.map.begin(), mapGames.map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });
    if(chek == mapGames.map.end()) {
        throw std::invalid_argument("not fount location map");
    }

    
    auto getItem = chek->second.getNameItems();
    auto getvillager = chek->second.getNameVillagers();
    auto getmonster = chek->second.getNameMonsters();
    auto getHero = chek->second.getNameHeroes();
        
    
    sf::Texture TextureMVHI[4];
    sf::Sprite SpriteMVHI[4];
    this->setImageMVHI(TextureMVHI[0], SpriteMVHI[0], "item.png", 1);
    this->setImageMVHI(TextureMVHI[1], SpriteMVHI[1], "villager.png", 0);
    this->setImageMVHI(TextureMVHI[2], SpriteMVHI[2], "monster.png", -1);
    this->setImageMVHI(TextureMVHI[3], SpriteMVHI[3], "hero.png", -2);
    
    
    sf::Texture textureBackground;
    if(!textureBackground.loadFromFile("../Horrified_Assets/backgroundClick.png")) {
        throw std::invalid_argument("not found background click");
    }
    sf::Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition(270, 0);
    spriteBackground.setScale(
        float(((this->windowSize.x)) / (textureBackground.getSize().x)),
        float(this->windowSize.y / textureBackground.getSize().y)
    );
    
    std::vector<std::pair<NameItem,sf::RectangleShape>> itemShape;
    std::vector<sf::Sprite> itemSprit;
    std::vector<sf::Texture> itemTexture;
    
    
    std::vector<std::pair<NameVillagers,sf::RectangleShape>> villagerShape;
    std::vector<sf::Sprite> villagerSprit;
    std::vector<sf::Texture> villagerTexture;
    
    std::vector<std::pair<NameMonster,sf::RectangleShape>> monsterShape;
    std::vector<sf::Sprite> monsterSprit;
    std::vector<sf::Texture> monsterTexture;
    
    std::vector<std::pair<NameHeroes,sf::RectangleShape>> heroShape;
    std::vector<sf::Sprite> heroSprit;
    std::vector<sf::Texture> heroTexture;
    
    this->setButtonClickedLocation(itemShape, getItem, itemSprit,itemTexture,-100, 1);
    
    this->setButtonClickedLocation(villagerShape, getvillager, villagerSprit,villagerTexture,150);
    
    this->setButtonClickedLocation(monsterShape, getmonster, monsterSprit,monsterTexture,-50, -1);
    
    this->setButtonClickedLocation(heroShape, getHero, heroSprit, heroTexture,0, -2);

    std::vector<NameItem> nameItems;
        
    while (this->event.key.code != sf::Keyboard::Escape) 
    {
        while (window.pollEvent(this->event)) { 
            if(nameAction == NameAction::GUIDE) {
                if(this->event.type == sf::Event::MouseButtonPressed && this->event.mouseButton.button == sf::Mouse::Left) {
                    for(const auto& [name, shape] : villagerShape) {
                        if(this->isMouseOver(shape, this->window)) {
                            this->guideGames(nameLocation,villagerShape,player1);
                            return;
                        }
                    }
                    this->cout("Please select only one villager.");
                }
            }
            if(nameAction == NameAction::PICKUP) {
                if(itemShape.empty()) {
                    throw std::bad_alloc();
                    return;
                }
                
                if(this->event.type == sf::Event::MouseButtonPressed && this->event.mouseButton.button == sf::Mouse::Left) {
                    for(const auto& [name, shape] : itemShape) {
                        if(this->isMouseOver(shape, this->window)) {
                            bool select = true;
                            for(const auto& i : nameItems) {
                                if(i == name) {
                                    this->cout("This item is already selected.");
                                    select = false;
                                    break;
                                }
                            }
                            if(select) {
                                this->cout(this->itemGames.chengNameItemTheString(name) + " was selected");
                                nameItems.emplace_back(name);
                            }
                        }
                    }
                }
                else if(this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Delete) {
                    if(!nameItems.empty()) {
                        auto del = nameItems.back();
                        this->cout(this->itemGames.chengNameItemTheString(del) + " Removed from the selected list.");
                        nameItems.pop_back();
                    }
                }

                else if(this->event.key.code == sf::Keyboard::Enter) {
                    try
                    {
                        this->pickUpGames(nameItems, hero);
                        this->clickedLocation(nameLocation, player, hero);
                    }
                    catch(const std::exception& e)
                    {
                        this->cout("Select at least one item.");
                        std::cerr << e.what() << '\n';
                        break;
                    }
                    
                    return;
                }

            }
        }
        window.clear();
        window.draw(spriteBackground);

        for(size_t i = 0; i < 4; i++) {
            this->window.draw(SpriteMVHI[i]);
        }

        for(const auto& i : itemSprit) {
            window.draw(i);
        }
        for(const auto& [name, shape] : itemShape) {
            window.draw(shape);
        }
        for(const auto& i : villagerSprit) {
            window.draw(i);
        }
        for(const auto& [name, shape] : villagerShape) {
            window.draw(shape);
        }
        for(const auto& i : monsterSprit) {
            window.draw(i);
        }
        for(const auto& [name, shape] : monsterShape) {
            window.draw(shape);
        }
        for(const auto& i : heroSprit) {
            window.draw(i);
        }
        for(const auto& [name, shape] : heroShape) {
            window.draw(shape);
        }
        this->window.display();
    }
}
template<typename T>
void Games::setButtonClickedLocation(std::vector<std::pair<T, sf::RectangleShape>>& part, const std::vector<T>& name, std::vector<sf::Sprite>& sprit, std::vector<sf::Texture>& texture,const int sizeimage, const int sizeHeight) {
    float x = 270 ;
    float y = this->windowSize.y / 2 + (sizeHeight * 300);
    float width = this->windowSize.x - 270.f;
    float height = this->windowSize.y / 4.f  ;
    float partWidth = width / name.size();
    int i = 0;

    sprit.clear();
    texture.clear();
    texture.reserve(name.size());

    
    for(const auto& vec : name) {
        sf::Texture tex;
        if (!tex.loadFromFile(this->getNameImage(vec))) {
            throw std::invalid_argument("not found image: ");
        }
        
        texture.emplace_back(tex);

        sf::Texture& finalTexture = texture.back();

        sf::Sprite sprite(finalTexture);
        sprite.setPosition(x + (i) * partWidth - (sizeimage / 2), y - (sizeimage/2));
        
        sprite.setScale(
            float(300 + sizeimage) / finalTexture.getSize().x,
            float(height + sizeimage) / finalTexture.getSize().y
        );
        sprit.emplace_back(sprite);



        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(partWidth, height));
        rect.setPosition(x + (i) * partWidth, y);
        rect.setFillColor(sf::Color(0,0,0,50));

  
        part.emplace_back(vec, rect);
        ++i;
    }
}
void Games::guideGames(Players& player) {

    for(const auto& neghbor : this->mapGames.getNeighborLocation(player.hero1->getLocationHero())) {
        if(neghbor->getNameVillagers().empty()) {
            this->cout("There are no villagers in your neighborhood.");
            return;
        }
    }
    for(const auto& neghbor : this->mapGames.getNeighborLocation(player.hero2->getLocationHero())) {
        if(neghbor->getNameVillagers().empty()) {
            this->cout("There are no villagers in your neighborhood.");
            return;
        }
    }


    sf::Clock clock;
    
    while (true) {
        while (this->window.pollEvent(this->event)) {
            if(clock.getElapsedTime().asSeconds() < 1.0f) {
                this->cout("Choose a villager from the neighborhood of the locations ." + this->mapGames.chengNameLocationTheString(this->player1.hero1->getLocationHero()) + ", " + this->mapGames.chengNameLocationTheString(this->player1.hero2->getLocationHero()));
            }
            if(true) {
                if(event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                    for(const auto& [name, shape] : this->locations) {
                        if(this->isMouseOver(shape, this->window)) {
                            for(const auto& neghbor : this->mapGames.getNeighborLocation(player.hero1->getLocationHero())) {
                                if(name == neghbor->getNameLocation() && !neghbor->getNameVillagers().empty()) {
                                    this->clickedLocation(name,player, *player.hero1, NameAction::GUIDE);
                                    return;
                                }
                            }

                            for(const auto& neghbor : this->mapGames.getNeighborLocation(player.hero2->getLocationHero())) {
                                if(name == neghbor->getNameLocation() && !neghbor->getNameVillagers().empty()) {
                                    this->clickedLocation(name, player, *player.hero2, NameAction::GUIDE);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    

}
void Games::guideGames(const NameLocation& nameLocation, const std::vector<std::pair<NameVillagers,sf::RectangleShape>>& villagerShape, Players& player) {
    int numberHero1 = mapGames.findShortestPath<int>(player.hero1->getLocationHero(), nameLocation);
    int numberHero2 = mapGames.findShortestPath<int>(player.hero2->getLocationHero(), nameLocation);

    if(numberHero1 == 1) {
        for(const auto& [name, shape] : villagerShape) {
            if (this->isMouseOver(shape, this->window)) {
                player.hero1->guide(this->villagerGames, name);
                this->cout ("villager " + villagerGames.chengNameVillagerTheString(name) + " move the location hero " + player.hero1->getName());
                this->clickedLocation(nameLocation, player, *player.hero1);
                return;
            }
        }
    }
    else if(numberHero2 == 1) {
        for(const auto& [name, shape] : villagerShape) {
            if (this->isMouseOver(shape, this->window)) {
                player.hero2->guide(this->villagerGames, name);                
                this->cout ("villager " + villagerGames.chengNameVillagerTheString(name) + " move the location hero " + player.hero2->getName());
                this->clickedLocation(nameLocation, player, *player.hero2);
                return;
            }
        }
    }
    else {
        throw std::invalid_argument("can not move the villager in location");
    }
}

void Games::moveGames(Players& player) {
    sf::RectangleShape rect[3];
    sf::Texture texture[2];
    sf::Sprite sprit[2];

    if(!texture[0].loadFromFile(this->getNameImage(player.hero1->getNameHero())) || !texture[1].loadFromFile(this->getNameImage(player.hero2->getNameHero()))) {
        throw std::invalid_argument("not found image hero");
    }

    sprit[0].setTexture(texture[0]);
    sprit[0].setPosition(this->windowSize.x - (400), this->windowSize.y / 2 - 600);
    sprit[0].setScale(
        float(400.f / texture[0].getSize().x),
        float(600.f / texture[0].getSize().y)
    );

    sprit[1].setTexture(texture[1]);
    sprit[1].setPosition(this->windowSize.x - (400), this->windowSize.y / 2);
    sprit[1].setScale(
        float(400.f / texture[1].getSize().x),
        float(600.f / texture[1].getSize().y)
    );


    rect[0].setFillColor(sf::Color::Black);
    rect[0].setOutlineColor(sf::Color::Red);
    rect[0].setOutlineThickness(-5.f);
    rect[0].setSize(sf::Vector2f(400,600));
    rect[0].setPosition(this->windowSize.x - 400, this->windowSize.y / 2 - 600);

    rect[1].setFillColor(sf::Color::Black);
    rect[1].setSize(sf::Vector2f(400,600));
    rect[1].setPosition(this->windowSize.x - 400, this->windowSize.y / 2);
    rect[1].setOutlineColor(sf::Color::Red);
    rect[1].setOutlineThickness(-5.f);



    sf::Texture screen;
    screen.create(this->window.getSize().x, this->window.getSize().y);
    screen.update(this->window);
    sf::Sprite background(screen);


    bool moveVillager = false;
    bool chek[2] = {false,false};
    
    while (true)
    {           
        while (window.pollEvent(event)) {
            if(!chek[0] && !chek[1]) {
                if(event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Right) {

                    if(this->isMouseOver(rect[0], this->window)) {
                        if(player.hero1->canTakeAction()) {
                            chek[0] = true;
                        }
                        else {
                            this->cout("This hero's actions are over.");
                        }
                    }
                    if(this->isMouseOver(rect[1], this->window)) {
                        if(player.hero2->canTakeAction()) {
                            rect[1].setPosition(rect[0].getPosition());
                            sprit[1].setPosition(sprit[0].getPosition());
                            chek[1] = true;
                        }
                        else {
                            this->cout("This hero's actions are over.");
                        }
                    }
                    
                }
            }

            if(chek[0] == true || chek[1] == true) {
                for(const auto& [name, shape] : this->locations) {
                    if(this->isMouseOver(shape, this->window)) {
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            if(chek[0] == true) {
                                try
                                {
                                    for(const auto& [nameLocaiton, locaiton] : this->mapGames.map) {
                                        if(nameLocaiton == player.hero1->getLocationHero()) {
                                            if(!locaiton.getNameVillagers().empty()) {
                                                this->cout("aa");
                                                moveVillager = this->yesOrNo();
                                                player.hero1->move(this->villagerGames, name, moveVillager, locaiton.getNameVillagers());
                                            }
                                            else {
                                                player.hero1->move(this->villagerGames, name, moveVillager, {});
                                            }
                                        }
                                    }

                                    this->cout(player.hero1->getName() + " move the location ");
                                    return;
                                }
                                catch(const std::exception& e)
                                {
                                    this->cout("no location move");
                                    std::cerr << e.what() << '\n';
                                    break;
                                }
                                
                            }
                            else if(chek[1] == true) {
                                try
                                {
                                    for(const auto& [nameLocaiton, locaiton] : this->mapGames.map) {
                                        if(nameLocaiton == player.hero2->getLocationHero()) {
                                            if(!locaiton.getNameVillagers().empty()) {
                                                this->cout("aa");
                                                moveVillager = this->yesOrNo();
                                                player.hero2->move(this->villagerGames, name, moveVillager, locaiton.getNameVillagers());
                                            }
                                            else {
                                                player.hero2->move(this->villagerGames, name, moveVillager, {});
                                            }
                                        }
                                    }
                                    this->cout(player.hero2->getName() + " move the location ");
                                    return;
                                }
                                catch(const std::exception& e)
                                {
                                    std::cerr << e.what() << '\n';
                                    this->cout("no location move");
                                    break;
                                }
                                
                            }
                        }
                            
                    }
                }
            }        
        }
    
        window.draw(background);
        if(!chek[1]) {
            window.draw(rect[0]);
            window.draw(sprit[0]);
        }
        if(!chek[0]) {
            window.draw(rect[1]);
            window.draw(sprit[1]);
        }
        window.display();            
    }

}
bool Games::yesOrNo() {
    sf::RectangleShape rect[2];
    sf::Text text[2];

    rect[0].setSize(sf::Vector2f(200, 100));
    rect[0].setFillColor(sf::Color(100,100,100));
    rect[0].setPosition(this->windowSize.x / 2, this->windowSize.y / 2);
    text[0].setFont(this->font);
    text[0].setCharacterSize(30);
    text[0].setString("Yes");
    this->centerTextInButton(text[0], rect[0]);

    rect[1].setSize(sf::Vector2f(200, 100));
    rect[1].setFillColor(sf::Color(100,100,100));
    rect[1].setPosition(this->windowSize.x / 2 - 250, this->windowSize.y / 2);
    text[1].setFont(this->font);
    text[1].setCharacterSize(30);
    text[1].setString("No");
    this->centerTextInButton(text[1], rect[1]);

     sf::Texture screen;
    screen.create(this->window.getSize().x, this->window.getSize().y);
    screen.update(this->window);
    sf::Sprite background(screen);


    bool selectedYes = false;
    bool selectedNo  = false;
    NameLocation nameLocation;

    
    
    while (this->window.isOpen()) {
        while (this->window.pollEvent(this->event)) {
            if(this->event.type == sf::Event::Closed) this->window.close();
            
            if(this->event.type == sf::Event::MouseButtonPressed &&
                this->event.mouseButton.button == sf::Mouse::Left)
                {
                    if(this->isMouseOver(rect[0], this->window)) {
                        return true;
                    }
                    else if(this->isMouseOver(rect[1], this->window)) {
                        return false;
                    }
                    
                }
        }
        window.draw(background);

        this->window.draw(rect[1]);
        this->window.draw(text[1]);
        this->window.draw(rect[0]);
        this->window.draw(text[0]);
        this->window.display();
    }
}

void Games::pickUpGames(const std::vector<NameItem>& item ,Heroes& hero) {
    if(item.empty()) {
        throw std::invalid_argument("null item");
    }
    hero.pickUp(this->itemGames, item);
}

void Games::advanceGames(Players& player) {
    NameLocation nameLocationHero;
    NameHeroes nameHero;
    if(player.hero1->getLocationHero() == NameLocation::CAVE || 
        player.hero1->getLocationHero() == NameLocation::CRYPT || 
        player.hero1->getLocationHero() == NameLocation::DUNGEON || 
        player.hero1->getLocationHero() == NameLocation::GRAVEYARD) {
            nameHero = player.hero1->getNameHero();
            nameLocationHero = player.hero1->getLocationHero();
        }
    else if(player.hero2->getLocationHero() == NameLocation::CAVE || 
        player.hero2->getLocationHero() == NameLocation::CRYPT || 
        player.hero2->getLocationHero() == NameLocation::DUNGEON || 
        player.hero2->getLocationHero() == NameLocation::GRAVEYARD) {
            nameLocationHero = player.hero2->getLocationHero();
            nameHero = player.hero2->getNameHero();
    }
    else if(player.hero1->getLocationHero() == NameLocation::PRECINCT && !player.hero1->getNameItemPickUpInvisibleMan().empty()) {
            
            for(auto& [name,map] : this->mapGames.map) {
                if(map.getInvisibleItemCollecte()) {
                    this->cout("The invisibleman badge was found at this location.");
                    return;
                }
                for(const auto& [nameItem, nameMap] : player.hero1->getNameItemPickUpInvisibleMan()) {
                    if(nameMap == name) {
                        this->itemGames.removeItemInGame(nameItem);
                        map.setInvivsibleItemCollecte();
                        this->cout("One of the invisibleman signs was found.");
                        return;
                    }
                }
            }
            throw std::invalid_argument("not found item the location invisble man");
    }

    else if(player.hero2->getLocationHero() == NameLocation::PRECINCT && !player.hero2->getNameItemPickUpInvisibleMan().empty()) { 
            for(auto& [name,map] : this->mapGames.map) {
                if(map.getInvisibleItemCollecte()) {
                    this->cout("The invisibleman badge was found at this location.");
                    return;
                }
                for(const auto& [nameItem, nameMap] : player.hero2->getNameItemPickUpInvisibleMan()) {
                    if(nameMap == name) {
                        map.setInvivsibleItemCollecte();
                        this->cout("One of the invisibleman signs was found.");
                        return;
                    }
                }
            }
            throw std::invalid_argument("not found item the location invisble man");
    }

    
    else {
        this->cout("You are not in the right place.");
        return;
    }

    for(const auto& [name, map] : this->mapGames.map) {
        if(name == nameLocationHero) {
            if(map.getCoffindestroyed()) {
                this->cout("The grave of this place has been broken.");
                return;
            }
        }
    }

    auto items = this->itemGames.getItemsInGame();
    TypeOwnership typeOnserShip;
    switch (nameHero)
    {
    case NameHeroes::ARCHAEOLOGIST:
        typeOnserShip = TypeOwnership::ARCHAEOLOGIST;
        break;
    case NameHeroes::MAYOR:
        typeOnserShip = TypeOwnership::MAYOR;
        break;
    
    default:
        throw std::invalid_argument(" ");
        break;
    }

    int chekNumberItem = 0;
    std::vector<Item> advanceItem;

    for(auto& [name,item] : items) {
        if(chekNumberItem >= 6) {
            break;
        }
        if(item.getTypeOwnsership() == typeOnserShip) {
            if(item.getTypeItem() == TypeItem::RED) {
                chekNumberItem += item.getPower();
                advanceItem.emplace_back(item);
            }
        }
    }

    if(chekNumberItem < 6) {
        this->cout("You do not have enough items to use this section.");
        return;
    }

    for(auto& item : advanceItem) {
        this->itemGames.removeItemInGame(item.getNameItem());
    }

    for(auto& [name, map] : this->mapGames.map ) {
        if(name == nameLocationHero) {
            map.setCoffinDestroyed();
            this->drawCard("../Horrified_Assets/Items/Coffins/SmashedCoffin.png", 2.f);
            // player
            return;
        }
    }
}

void Games::defeatGames(Players& player) {
    if(this->mapGames.getcoffinDestroyed()) {
        if(player.hero1->getLocationHero() == dracula->getNameLocationMonster()) {
            player.hero1->defieat(*dracula, this->itemGames);
            
        }
        else if(player.hero2->getLocationHero() == dracula->getNameLocationMonster()) {
            player.hero2->defieat(*dracula, this->itemGames);

        }
    }
    else if (this->mapGames.getInvisibleItemCollecte()) {
        if(player.hero1->getLocationHero() == invisibleMan->getNameLocationMonster()) {
            player.hero1->defieat(*invisibleMan, this->itemGames);
        }
        else if(player.hero2->getLocationHero() == invisibleMan->getNameLocationMonster()) {
            player.hero2->defieat(*invisibleMan, this->itemGames);
            
        }
    }
    else {
        this->cout("can not efect");
        return;
    }
}

        
void Games::drawPrekCard(const PerkCardType& prekCardType) {
    std::string nameImagePerkCard = "../Horrified_Assets/Perk_Cards/";
    switch (prekCardType)
    {
    case PerkCardType::BreakOfDawn: 
        nameImagePerkCard += "BreakOfDawn.png";
        break;
    case PerkCardType::Hurry: 
        nameImagePerkCard += "Hurry.png";
        break;
    case PerkCardType::LateIntoTheNight: 
        nameImagePerkCard += "LateIntoTheNight.png";
        break;
    case PerkCardType::Overstock: 
        nameImagePerkCard += "Overstock.png";
        break;
    case PerkCardType::Repel: 
        nameImagePerkCard += "Repel.png";
        break;
    case PerkCardType::VisitFromDetective: 
        nameImagePerkCard += "VisitFromTheDetective.png";
        break;
    
    default:
        throw std::invalid_argument("not found prek card type");
        break;
    }

    this->drawCard(nameImagePerkCard, 3.f);

}

std::string Games::drawMonsterCard(const MonsterCardType& monsterCardType) {
    std::string nameImageMonsterCard = "../Horrified_Assets/Monster_Cards/";
    switch (monsterCardType)
    {
    case MonsterCardType::EgyptianExpert:
        nameImageMonsterCard += "EgyptianExpert.png";
        break;
    case MonsterCardType::FormerEmployer:
        nameImageMonsterCard += "FomerEmployer.png";
        break;
    case MonsterCardType::FormOfTheBat:
        nameImageMonsterCard += "FormOfTheBat.png";
        break;
    case MonsterCardType::FortuneTeller:
        nameImageMonsterCard += "FortuneTeller.png";
        break;
    case MonsterCardType::HurriedAssistant:
        nameImageMonsterCard += "HurriedAssistant.png";
        break;
    case MonsterCardType::HypnoticGaze:
        nameImageMonsterCard += "HypnoticGaze.png";
        break;
    case MonsterCardType::OnTHeMove:
        nameImageMonsterCard += "OnTheMove.png";
        break;
    case MonsterCardType::Sunrise:
        nameImageMonsterCard += "Sunrise.png";
        break;
    case MonsterCardType::TheDelivery:
        nameImageMonsterCard += "TheDelivery.png";
        break;
    case MonsterCardType::TheIchthyologist:
        nameImageMonsterCard += "TheIchtyologist.png";
        break;
    case MonsterCardType::TheInnocent:
        nameImageMonsterCard += "TheInnocent.png";
        break;
    case MonsterCardType::Thief:
        nameImageMonsterCard += "Thief.png";
        break;
    
    default:
        throw std::invalid_argument("not found image Monster card");
    }

    return this->drawCard(nameImageMonsterCard, 2.5f);

}

std::string Games::drawCard(const std::string& nameImageCard, const int size) {
    sf::Texture cardTexture;
    if(!cardTexture.loadFromFile(nameImageCard)) {
        throw std::invalid_argument("not found image");
    }
    sf::Texture screen;
    screen.create(this->window.getSize().x, this->window.getSize().y);
    screen.update(this->window);
    sf::Sprite background(screen);

    sf::RectangleShape darkOverlay;
    darkOverlay.setSize(sf::Vector2f(this->window.getSize()));
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 150));

    sf::Sprite card(cardTexture);
    card.setOrigin(card.getLocalBounds().width / 2, card.getLocalBounds().height / 2);
    card.setPosition(this->window.getSize().x / 2, this->window.getSize().y / 2);
    
    sf::Clock clock;
    while (this->window.isOpen()) {
        while (this->window.pollEvent(this->event)) {
            if (this->event.key.code == sf::Keyboard::Enter) {
                return nameImageCard;
            }
        }

        this->window.clear();
        if(clock.getElapsedTime().asSeconds() < 2.0f) {
            float t = clock.getElapsedTime().asSeconds();
            float scaleX = std::abs(std::cos(t * 3)); // شبیه چرخش
            card.setScale(scaleX / size, 
            float(this->windowSize.y / 2) / (cardTexture.getSize().y));       
        }
        
        this->window.draw(background);
        this->window.draw(darkOverlay);
        this->window.draw(card);
        this->window.display();
    }
}



std::string Games::getNameImage(const PerkCardType& prekCardType) {
    std::string nameImagePerkCard = "../Horrified_Assets/Perk_Cards/";
    switch (prekCardType)
    {
    case PerkCardType::BreakOfDawn: 
        return nameImagePerkCard + "BreakOfDawn.png";
        
    case PerkCardType::Hurry: 
        return nameImagePerkCard + "Hurry.png";
        
    case PerkCardType::LateIntoTheNight: 
        return nameImagePerkCard + "LateIntoTheNight.png";
        
    case PerkCardType::Overstock: 
        return nameImagePerkCard + "Overstock.png";
        
    case PerkCardType::Repel: 
        return nameImagePerkCard + "Repel.png";
        
    case PerkCardType::VisitFromDetective: 
        return nameImagePerkCard + "VisitFromTheDetective.png";
    
    default:
        throw std::invalid_argument("not found prek card type");
        break;
    }
}



std::string Games::getNameImage(const NameItem& nameItem) {
    std::string nameItemImage = "../Horrified_Assets/Items/";
    switch (nameItem) {
        case NameItem::ANALYSIS:
        return nameItemImage + "Blue/Analysis.png";
        case NameItem::ANATOMY_TEXT:
        return nameItemImage + "Blue/AnatomyText.png";
        case NameItem::CENTRIFUGE:
        return nameItemImage + "Blue/Centrifuge.png";
        case NameItem::COSMIC_RAY_DIFFUSER:
        return nameItemImage + "Blue/CosmicRayDiffuser.png";
        case NameItem::EXPERIMENT:
        return nameItemImage + "Blue/Experiments.png";
        case NameItem::FOSSIL:
        return nameItemImage + "Blue/Fossil.png";
        case NameItem::KITE:
        return nameItemImage + "Blue/Kite.png";
        case NameItem::MONOCANE_MIXTURE:
        return nameItemImage + "Blue/MonocaneMixture.png";
        case NameItem::NEBULARLUM:
        return nameItemImage + "Blue/Nebularium.png";
        case NameItem::RESARCH:
        return nameItemImage + "Blue/Research.png";
        case NameItem::ROTENONE:
        return nameItemImage + "Blue/Rotenone.png";
        case NameItem::SEARCHLIGHT:
        return nameItemImage + "Blue/Searchlight.png";
        case NameItem::TELESCOPE:
        return nameItemImage + "Blue/Telescope.png";
        case NameItem::BEAR_TRAP:
        return nameItemImage + "Red/BearTrap.png";
        case NameItem::DART:
        return nameItemImage + "Red/Dart.png";
        case NameItem::FIRE_POKER:
        return nameItemImage + "Red/FirePoker.png";
        case NameItem::KNIFE:
        return nameItemImage + "Red/Knife.png";
        case NameItem::PISTOL:
        return nameItemImage + "Red/Pistol.png";
        case NameItem::PITCHFORK:
        return nameItemImage + "Red/Pitchfork.png";
        case NameItem::RAPIER:
        return nameItemImage + "Red/Rapier.png";
        case NameItem::RIFLE:
        return nameItemImage + "Red/Rifle.png";
        case NameItem::SHOVEL:
        return nameItemImage + "Red/Shovel.png";
        case NameItem::SILVER_CANE:
        return nameItemImage + "Red/SilverCane.png";
        case NameItem::SPEARGUN:
        return nameItemImage + "Red/Speargun.png";
        case NameItem::TORCH:
        return nameItemImage + "Red/Torch.png";
        case NameItem::CHARM:
        return nameItemImage + "Yellow/Charm.png";
        case NameItem::FLOWER:
        return nameItemImage + "Yellow/Flower.png";
        case NameItem::GARLIC:
        return nameItemImage + "Yellow/Garlic.png";
        case NameItem::MIRRORED_BOX:
        return nameItemImage + "Yellow/Mirrored_Box.png";
        case NameItem::SCROLL_OF_THOTH:
        return nameItemImage + "Yellow/Scroll.png";
        case NameItem::STAKE:
        return nameItemImage + "Yellow/Stake.png";
        case NameItem::TABLET:
        return nameItemImage + "Yellow/Tablet.png";
        case NameItem::TAROT_DECK:
        return nameItemImage + "Yellow/Tarot.png";
        case NameItem::VIOLIN:
        return nameItemImage + "Yellow/Violin.png";
        case NameItem::WOLFSBANE:
        return nameItemImage + "Yellow/Wolfsbane.png";
        default:
            throw std::invalid_argument("not found image item");
    }
    throw std::invalid_argument("not found image item");

}
    
std::string Games::getNameImage(const NameVillagers& nameVillager) {
    std::string nameImageVillager = "../Horrified_Assets/Villager/";
    switch (nameVillager)
    {
    case NameVillagers::Dr_crunly:
    return nameImageVillager + "DrCranly.png";
    case NameVillagers::Dr_read:
    return nameImageVillager + "DrReed.png";
    case NameVillagers::Fritz:
    return nameImageVillager + "Fritz.png";
    case NameVillagers::Maleva:
    return nameImageVillager + "Maleva.png";
    case NameVillagers::Maria:
    return nameImageVillager + "Maria.png";
    case NameVillagers::Prof_pearson:
    return nameImageVillager + "ProfPearson.png";
    case NameVillagers::WilnureAndChick:
    return nameImageVillager + "WilburAndChick.png";

    default:
        throw std::invalid_argument("not found image villager");
    }
}

std::string Games::getNameImage(const NameHeroes& nameHero) {
    std::string nameImageHeroes = "../Horrified_Assets/Heros/";
    switch (nameHero)
    {
    case NameHeroes::ARCHAEOLOGIST:
        return nameImageHeroes + "Archaeologist.png";
    case NameHeroes::MAYOR:
        return nameImageHeroes + "Mayor.png";    
    case NameHeroes::SCIENTIST:
        return nameImageHeroes + "Scientist.png";
    case NameHeroes::COURIER:
        return nameImageHeroes + "Courier.png";
        
    default:
        throw std::invalid_argument("not found Name Heroes or Defualt");
    }

}
std::string Games::getNameImage(const NameMonster& nameMonster) {
    std::string nameImageMonster = "../Horrified_Assets/Monsters/";
    switch (nameMonster)
    {
    case NameMonster::DRACULA:
        return nameImageMonster + "Dracula.png";
    case NameMonster::INVISIBLE_MAN:
        return nameImageMonster + "InvisibleMan.png";        
    default:
        throw std::invalid_argument("not found Name Monster or Default");
    }
}
std::string Games::getNameImage(const bool bol) {
    if(bol)
        return "../Horrified_Assets/Items/Coffins/SmashedCoffin.png";
    else
        return "../Horrified_Assets/Items/Coffins/Coffin.png";
}

void Games::cout(const std::string& message) {
    sf::RectangleShape box;
    box.setPosition(0,0);
    box.setSize(sf::Vector2f(this->windowSize.x , 300));
    box.setFillColor(sf::Color(180,40,40,200)); 
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(3);


    sf::Texture screen;
    screen.create(this->window.getSize().x, this->window.getSize().y);
    screen.update(this->window);
    sf::Sprite background(screen);

    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        box.getPosition().x + (box.getSize().x - textBounds.width) / 2.f,
        box.getPosition().y + (box.getSize().y - textBounds.height) / 2.f - 10
    );

    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 2.0f) {

        while (this->window.pollEvent(this->event)) 
        {            
            if(this->event.type == sf::Event::MouseButtonPressed && this->event.mouseButton.button == sf::Mouse::Left) {
                return;
            }
        }
        window.clear();
        window.draw(background);
        window.draw(box);
        window.draw(text);
        window.display();

    }
    return;
}