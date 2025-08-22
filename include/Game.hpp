// #ifndef GAME_HPP
// #define GAME_HPP

// #include <vector>
// #include <memory>
// #include <unordered_map>
// #include "Hero.hpp"
// #include "Map.hpp"
// #include "Monster.hpp"
// #include "Dracula.hpp"
// #include "InvisibleMan.hpp"
// #include "Item.hpp"
// #include "Villagers.hpp"
// #include "PerkCard.hpp"
// #include "MonsterCard.hpp"
// #include <unordered_set>

// class Game {
// private:
//     // نقشهٔ بازی
//     Map& gameMap;

//     // قهرمان‌ها
//     Mayor mayor;
//     Archaeologist archaeologist;
//     Heroes* currentHero;

//     // هیولاها
//     Dracula dracula;
//     InvisibleMan invisibleMan;

//     // هیولای Frenzied
//     Monster* frenziedMonster;

//     // سطح وحشت (۰ تا ۵)
//     int terrorLevel;


//     std::vector<Item*> itemBag;

//     std::vector<Item*> activeItems; // اشاره‌گر به آیتم‌های روی نقشه

//     // کارت‌ها
//     PerkDeck perkDeck;
//     MonsterDeck monsterDeck{ &dracula, &invisibleMan, &dracula };  // فرض کن فعلاً frenzy رو هم Dracula می‌گیریم

//     std::vector<std::string> draculaCoffinLocations = { "cave", "crypt", "dungeon", "graveyard" };


//     bool invisibleAdvanceDone = true;


//     // نوبت‌ها
//     bool isMayorTurn;

//     // مدیریت villager
//     Villager villagerManager;

//     // شمارشگر آیتم برای بازیابی آیتم‌های تمام‌شده
//     int itemIndex;

//     // کنترل پرک کارت‌هایی که در دست بازیکن‌ها هستند (در صورت نیاز به توسعه)
//     // std::unordered_map<std::string, std::vector<PerkCard>> playerPerks;
//     std::vector<Heroes*> heroes;

//     std::vector<std::pair<std::string ,std::string>> villagers;

//     std::string pekrcardName;


//     bool monsterPhaseTrue = true;
//     std::vector<Item*> allGameItems;



// public:
//     Game();

//     Map& gM();

//     void run();

//     // راه‌اندازی اولیه
//     void initializeGame();

//     // اجرای حلقه اصلی بازی
//     void startGameLoop();

//     // قرار دادن ۱۲ آیتم ابتدایی روی نقشه
//     void placeInitialItems();

//     // دریافت آیتم از بین ۶۰ آیتم (به صورت چرخشی)


//     // اجرای نوبت قهرمان
//     void heroTurn(Heroes& hero);

//     // منوی ترمینالی نوبت قهرمان
//     void displayHeroMenu(Heroes& hero);

//     // اجرای فاز هیولا
//     void monsterPhase();

//     // پیاده‌سازی رویداد کارت مانستر
//     void resolveMonsterCard(const MonsterCard& card);

//     // اجرای تاس و افکت آن (با توجه به ترتیب strike)
//     void rollDiceAndResolve(const std::vector<Monster*>& order, int diceCount);

//     // بررسی شرایط برد و باخت
//     bool checkWinCondition() const;
//     bool checkLoseCondition() const;

//     // افزایش سطح وحشت
//     void increaseTerrorLevel();

//     // اجرای کارت پرک
//     void usePerkCard(Heroes& hero, const PerkCard& card);

//     // جای‌گذاری یک Villager در مکان مشخص
//     void placeVillager(const std::string& name, const std::string& location, const std::string& safeZone);
//     Item& getNextItem();
//     std::string getRandomLocation() const;
//     void determineFirstPlayer();
//     void resolveMonsterEvent(const MonsterCard& card);
//     void rollDice(const MonsterCard& card);
//     void handleDraculaAttack();
//     void handleInvisibleManAttack();
//     void returnItemToBag(Item* item); 
//     void placeRandomItem(int count); 
//     void placeRandomItemAt(const std::string& location, int count);
//     std::string findLocationWithMostItems() const;

//     void handleDefeatDracula(Monster* monster, Heroes& hero);
//     void handleAdvanceInvisibleMan(Heroes& hero);

//     void setMonsterPhaseTrue(bool);
//     void setInvisibleAdvanceDone(bool);
// };

// #endif // GAME_HPP
