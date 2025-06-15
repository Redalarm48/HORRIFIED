#if !defined(HERO_H)
#define HERO_H
#include "PerkCard.hpp"
#include "Villagers.hpp"
#include "Map.hpp"
#include <string>
// #include "Villagers.hpp"
enum class Status{
    Alive,
    Dade
};

class Heroes {
private:
    std::string nameHero;
    Status statusHero;
    PerkDeck perkCard;
    Map& locationHero;
    int numberActionTaken;
    int maxActions;

public:
    Heroes(int,const std::string, Map&);
    virtual ~Heroes() = default;

    std::string getName() const;
    Status getStatus() const;
    void setStatus(Status);

    Location* getLocationHeroPtr() const;
    std::string getLocationHero() const;
    bool canTakeAction() const;
    void resetActions();

    void move();
    void guide();
    void pickUp();
    void Advance();
    void defeat();
    // virtual void specialAction() = 0;

protected:
    void incrementAction();
};

class Archaeologist : public Heroes {
public:
    // Archaeologist(Map&);
    // void specialAction() override;
};

class Mayor : public Heroes {
public:
    // Mayor(Map&);
    // void specialAction() override;
};

#endif // HERO_H
