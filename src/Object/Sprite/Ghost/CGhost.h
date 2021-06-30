#pragma once
#include "../CMovingObject.h"
#include "../../../Game/CGameMode.h"

/**
* @brief Ghosts logic
*/
class CGhost : public CMovingObject{
public:
    /**
     * @brief Constructor for ghost
     * @param prisoned Parameter that shows if ghost is detained or not
     */
    explicit CGhost(bool prisoned) : CMovingObject(), prisoned(prisoned), inGates(false) {}
    /**
     * @brief Changing ghost's direction
     * @param map Game map
     * @return Returning new direction
     */
    Direction changeDirection(CMap &map);
    /**
     * @brief Moving a ghost
     * @param renderer App's renderer
     * @param map Game map
     */
    void move(SDL_Renderer *renderer, CMap &map) override;
    /**
     * @brief Checking if ghost is at intersection
     * @param map Game map
     * @return If ghost is at intersection - return true, else - false
     */
    bool intersectionCheck(CMap &map) const;
    /**
     * @brief Finding hypotenuse to calculate closest way
     * @param current Current tile
     * @param dest Destination tile
     * @return Returning distance between ghost and it's destination
     */
    static int calculateHypotenuse(CTilePos current, CTilePos dest);
    /**
     * @brief Setting ghost's model depending on game mode and timers
     * @param tmp Ghost's rectangle
     */
    void setModelToDraw(SDL_Rect &tmp) override;
    /**
     * @brief Resetting ghost's speed, position and destination
     * @param target New ghost's target
     */
    virtual void reset(CTilePos target);
    /**
     * @brief Calculating destination
     * @param pacmanPos Pacman position
     * @param pacmanDir Pacman direction
     * @return Calculating ghost's target
     */
    virtual CTilePos calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) = 0;
    /**
     * @brief Setting new destination
     * @param pos Target
     */
    void setDestination(CTilePos pos) { destination = pos; }
    /**
     * @brief Setting game mode
     * @param mode Game mode
     */
    void setGameMode(GameMode *mode) { gameMode = mode; }
    /**
     * @brief Setting prisoned status
     * @param p Prisoned
     */
    void setPrisoned(bool p) { prisoned = p; }
    /**
     * @brief Setting prisoned timer
     * @param pTimer Prisoned timer
     */
    void setPrisonedTimer(int pTimer) { prisonedTimer = pTimer; }
    /**
     * @brief Setting frightened timer
     * @param fTimer Frightened timer
     */
    void setFrightenedTimer(int fTimer) { frightenedTimer = fTimer; }
    /**
     * @brief Setting ghost and gates status
     * @param gates Boolean that shows is ghost in gates or not
     */
    void setInGates(bool gates) { inGates = gates; }
    /**
     * @brief Setting starting position
     * @param s Starting position
     */
    void setStartingPos(const CTilePos &s) { startingPos = s; }
    /**
     * @brief Setting direction
     * @param direction New direction
     * @param map Game map
     */
    void setDirection(Direction direction, CMap &map) override { currentDirection = direction; }
    /**
     * @brief Is ghost prisoned or not
     * @return Boolean variable representing prisoned status
     */
    bool isPrisoned() const { return prisoned; }
    /**
     * @brief Getting prisoned timer
     * @return Prisoned timer
     */
    int getPrisonedTimer() const { return prisonedTimer; }
    /**
     * @brief Ghost and gates status
     * @return Boolean that shows if ghost is in gates or not
     */
    bool isInGates() const { return inGates; }
    /**
     * @brief Getting starting position
     * @return Starting position
     */
    const CTilePos &getStartingPos() const { return startingPos; }
protected:
    CTilePos destination, newPosition;
    GameMode *gameMode{};
    int frightenedTimer = 0, prisonedTimer = 0;
    bool prisoned, inGates;
    CTilePos startingPos;
};
