#include "Games.hpp"
#include <iostream>
#include <cmath>


Games::Games() {
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
                        this->startGame();
                        std::vector<std::string> s1 = this->startPlay("1");
                        std::vector<std::string> s2 = this->startPlay("2");
                        if(s1[1] >= s2[1]) {
                            player1.namePlayer = s2[0];
                            player1.player = Player::PLAYER_1;

                            player2.namePlayer = s1[0];
                            player2.player = Player::PLAYER_2;
                        }
                        else {
                            player1.namePlayer = s1[0];
                            player1.player = Player::PLAYER_1;

                            player2.namePlayer = s2[0];
                            player2.player = Player::PLAYER_2;
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

void Games::run(Players& player) {

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f mousePositionf(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    bool cursorOnLocation = false;

    sf::Texture textureAction[6];
    sf::Sprite spriteAction[6];
    sf::RectangleShape recAction[6];
    
    if(player.turn == Turn::HERO) {
        
        this->setButtonAndImageAction(recAction[0],textureAction[0],spriteAction[0],"move.png",1,0);
        this->setButtonAndImageAction(recAction[1],textureAction[1],spriteAction[1],"guide.png",1,1);
        this->setButtonAndImageAction(recAction[2],textureAction[2],spriteAction[2],"advance.png",1,2);
        this->setButtonAndImageAction(recAction[3],textureAction[3],spriteAction[3],"defeat.png",2,1);
        this->setButtonAndImageAction(recAction[4],textureAction[4],spriteAction[4],"pickup.png",2,0);
        this->setButtonAndImageAction(recAction[5],textureAction[5],spriteAction[5],"specialAction.png",2,2);
        
        for(size_t i = 0; i < 6; ++i) {
            this->window.draw(spriteAction[i]);
            this->window.draw(recAction[i]);
        }

        
        for(size_t i = 0; i < 6; ++i) {
            
            if(this->isMouseOver(recAction[i], this->window)) {
                cursorOnLocation = true;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    switch (i)
                    {
                        case 0:
                            this->moveGames(player);
                            break;
                        case 1:
                            this->guideGames();
                            break;
                        case 2:
                            this->advanceGames(player);
                            break;
                        case 3:
                            this->defeatGames(player);
                            break;
                        case 4:
                            this->clickedLocation(NameLocation::CAMP, NameAction::PICKUP);
                            break;
                        default:
                        break;
                    }
                }
            }
        }
        if(!player.hero1->canTakeAction() && !player.hero2->canTakeAction()) {
            player.turn = Turn::MONSTER; // نوبت مانستر
            return; // برگرد به حلقه اصلی
        }

    }
    else if(player.turn == Turn::MONSTER) {
        this->drawMonsterCard(MonsterCardType::FormOfTheBat);
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
                    this->clickedLocation(name);
                    break;
                }
            }
        }
    }


  
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
