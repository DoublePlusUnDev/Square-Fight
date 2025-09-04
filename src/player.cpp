<<<<<<< HEAD
#ifndef CPORTA
#include "player.h"

#include "gamemanager.h"
#include "inputhandler.h"

#include <vector>
#include <algorithm>

Player::Player(const Color& color, const InputScheme& inputScheme)
: PhysicsObject(Transform(), {}), 
  Updatable(UpdatePriority::GAME_LOGIC), 
  renderer(this, color, UpdatePriority::PLAYER_RENDERER), 
  collider(Transform(this), ColliderType::INTERACTIVE, 0, {ColliderTag::PLAYER}), 
  groundCheck(Transform(this, {0, -0.6}, {0.99, 0.04}), ColliderType::PASSIVE), 
  headCheck(Transform(this, {0, 0.6}, {0.99, 0.04}), ColliderType::PASSIVE),
  inputScheme(inputScheme), 
  hasDied(false)
{
    setGravity({0, 2* -9.81});
}

void Player::controlPlayer()
{
    Vector2 newAcceleration = getAcceleration();
    Vector2 newVelocity = getVelocity();

    setMaxYVelocity({-maxFallSpeed, maxFallSpeed});
    setMaxXVelocity({-maxSpeed, maxSpeed});

    //dash down
    if (InputHandler::isKeyPressed(inputScheme.getDashKey()))
    {
        newVelocity.y = std::min(-dashSpeed, newVelocity.y);
    }
    //jump
    else if (InputHandler::isKeyPressed(inputScheme.getJumpKey()) && isGrounded())
    {
        newVelocity.y = std::max(jumpSpeed, newVelocity.y);
    }

    //adjust gravity;
    if (InputHandler::isKeyPressed(inputScheme.getJumpKey()) && newVelocity.y > 0)
        setGravity({0, -floatGravity});
    else
        setGravity({0, -fallGravity});

    //move left
    if (InputHandler::isKeyPressed(inputScheme.getLeftKey()))
    {
        if (newVelocity.x <= 0)
            newAcceleration.x = -moveAcceleration;
        else
            newAcceleration.x = -turnAcceleration;
    }
    //move right
    else if (InputHandler::isKeyPressed(inputScheme.getRightKey()))
    {
        if (newVelocity.x >= 0)
            newAcceleration.x = moveAcceleration;
        else
            newAcceleration.x = turnAcceleration;
    }

    //apply drag if on ground
    else if (isGrounded())
    {
        if (newVelocity.x > 0)
        {
            newAcceleration.x = -groundDrag;
            setMaxXVelocity({0, maxSpeed});
        }
        else
        {
            newAcceleration.x = groundDrag;
            setMaxXVelocity({-maxSpeed, 0});
        }
    }
    //apply drag in air
    else
    {
        if (newVelocity.x > 0)
        {
            newAcceleration.x = -airDrag;
            setMaxXVelocity({0, maxSpeed});
        }
        else
        {
            newAcceleration.x = airDrag;
            setMaxXVelocity({-maxSpeed, 0});
        }
    }

    setVelocity(newVelocity);
    setAcceleration(newAcceleration);
}

void Player::boundsCheck()
{
    if (getPosition().y < -GameManager::getInstance().getMapHeight() - getScale().y / 2)
        tryTeleport({getPosition().x, GameManager::getInstance().getMapHeight() + getScale().y});

    if (getPosition().x < -GameManager::getInstance().getMapWidth() - getScale().x / 2)
        tryTeleport({getPosition().x + 2 * GameManager::getInstance().getMapWidth() + getScale().x, getPosition().y});

    if (getPosition().x > GameManager::getInstance().getMapWidth() + getScale().x / 2)
        tryTeleport({getPosition().x - 2 * GameManager::getInstance().getMapWidth() - getScale().x, getPosition().y});
}

bool Player::checkDeath() const
{
    //check if headcheck collider intersects with any players
    std::vector<Collider*> headCheckResult = headCheck.checkIntersection();
    
    for (Collider* collider : headCheckResult)
    {       
        //kill if collider is a player
        if (collider->hasTag(ColliderTag::PLAYER))
            return true;
    }

    //deadly collider check
    if (checkTag(ColliderTag::DEADLY))
    {
        return true;
    }

    return false;
}

bool Player::isGrounded() const
{
    std::vector<Collider*> ground = groundCheck.checkIntersection();

    //check if there is any non deadly collider under the player
    for (Collider* collider : ground)
    {       
        //ignore deadly colliders
        if (!collider->hasTag(ColliderTag::DEADLY))
            return true;
    }

    return false;
}

void Player::update()
{
    boundsCheck();

    if (!hasDied)
        controlPlayer();

    if (checkDeath())
    {
        hasDied = true;
        setVelocity({0, 0});
        setAcceleration({0, 0});
    }
}

void Player::reset(const Vector2& resetPosition)
{
    hasDied = false;
    setPosition(resetPosition);
    clearTags();
}

bool Player::isDead() const { return hasDied; }
=======
#ifndef CPORTA
#include "player.h"

#include "gamemanager.h"
#include "inputhandler.h"

#include <vector>
#include <algorithm>

Player::Player(const Color& color, const InputScheme& inputScheme)
: PhysicsObject(Transform(), {}), 
  Updatable(UpdatePriority::GAME_LOGIC), 
  renderer(this, color, UpdatePriority::PLAYER_RENDERER), 
  collider(Transform(this), ColliderType::INTERACTIVE, 0, {ColliderTag::PLAYER}), 
  groundCheck(Transform(this, {0, -0.6}, {0.99, 0.04}), ColliderType::PASSIVE), 
  headCheck(Transform(this, {0, 0.6}, {0.99, 0.04}), ColliderType::PASSIVE),
  inputScheme(inputScheme), 
  hasDied(false)
{
    setGravity({0, 2* -9.81});
}

void Player::controlPlayer()
{
    Vector2 newAcceleration = getAcceleration();
    Vector2 newVelocity = getVelocity();

    setMaxYVelocity({-maxFallSpeed, maxFallSpeed});
    setMaxXVelocity({-maxSpeed, maxSpeed});

    //dash down
    if (InputHandler::isKeyPressed(inputScheme.getDashKey()))
    {
        newVelocity.y = std::min(-dashSpeed, newVelocity.y);
    }
    //jump
    else if (InputHandler::isKeyPressed(inputScheme.getJumpKey()) && isGrounded())
    {
        newVelocity.y = std::max(jumpSpeed, newVelocity.y);
    }

    //adjust gravity;
    if (InputHandler::isKeyPressed(inputScheme.getJumpKey()) && newVelocity.y > 0)
        setGravity({0, -floatGravity});
    else
        setGravity({0, -fallGravity});

    //move left
    if (InputHandler::isKeyPressed(inputScheme.getLeftKey()))
    {
        if (newVelocity.x <= 0)
            newAcceleration.x = -moveAcceleration;
        else
            newAcceleration.x = -turnAcceleration;
    }
    //move right
    else if (InputHandler::isKeyPressed(inputScheme.getRightKey()))
    {
        if (newVelocity.x >= 0)
            newAcceleration.x = moveAcceleration;
        else
            newAcceleration.x = turnAcceleration;
    }

    //apply drag if on ground
    else if (isGrounded())
    {
        if (newVelocity.x > 0)
        {
            newAcceleration.x = -groundDrag;
            setMaxXVelocity({0, maxSpeed});
        }
        else
        {
            newAcceleration.x = groundDrag;
            setMaxXVelocity({-maxSpeed, 0});
        }
    }
    //apply drag in air
    else
    {
        if (newVelocity.x > 0)
        {
            newAcceleration.x = -airDrag;
            setMaxXVelocity({0, maxSpeed});
        }
        else
        {
            newAcceleration.x = airDrag;
            setMaxXVelocity({-maxSpeed, 0});
        }
    }

    setVelocity(newVelocity);
    setAcceleration(newAcceleration);
}

void Player::boundsCheck()
{
    if (getPosition().y < -GameManager::getInstance().getMapHeight() - getScale().y / 2)
        tryTeleport({getPosition().x, GameManager::getInstance().getMapHeight() + getScale().y});

    if (getPosition().x < -GameManager::getInstance().getMapWidth() - getScale().x / 2)
        tryTeleport({getPosition().x + 2 * GameManager::getInstance().getMapWidth() + getScale().x, getPosition().y});

    if (getPosition().x > GameManager::getInstance().getMapWidth() + getScale().x / 2)
        tryTeleport({getPosition().x - 2 * GameManager::getInstance().getMapWidth() - getScale().x, getPosition().y});
}

bool Player::checkDeath() const
{
    //check if headcheck collider intersects with any players
    std::vector<Collider*> headCheckResult = headCheck.checkIntersection();
    
    for (Collider* collider : headCheckResult)
    {       
        //kill if collider is a player
        if (collider->hasTag(ColliderTag::PLAYER))
            return true;
    }

    //deadly collider check
    if (checkTag(ColliderTag::DEADLY))
    {
        return true;
    }

    return false;
}

bool Player::isGrounded() const
{
    std::vector<Collider*> ground = groundCheck.checkIntersection();

    //check if there is any non deadly collider under the player
    for (Collider* collider : ground)
    {       
        //ignore deadly colliders
        if (!collider->hasTag(ColliderTag::DEADLY))
            return true;
    }

    return false;
}

void Player::update()
{
    boundsCheck();

    if (!hasDied)
        controlPlayer();

    if (checkDeath())
    {
        hasDied = true;
        setVelocity({0, 0});
        setAcceleration({0, 0});
    }
}

void Player::reset(const Vector2& resetPosition)
{
    hasDied = false;
    setPosition(resetPosition);
    clearTags();
}

bool Player::isDead() const { return hasDied; }
>>>>>>> a04c523 (Idk :3)
#endif