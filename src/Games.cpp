#include "../include/Games.hpp"
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
