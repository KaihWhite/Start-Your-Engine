// By Chonglin Guan

#pragma once
#include "box2d/box2d.h"
#include "Player.h"  // Include Player header if Player-specific methods are used

class ContactListener : public b2ContactListener {
public:
    void ContactListener::BeginContact(b2Contact* contact) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        // Ensure at least one of the fixtures is dynamic (the player)
        if (fixtureA->GetBody()->GetType() != b2_dynamicBody && fixtureB->GetBody()->GetType() != b2_dynamicBody) {
            return; // Neither fixture is a player
        }

        // Assuming the player's user data is set to the player object
        b2Body* playerBody = fixtureA->GetBody()->GetType() == b2_dynamicBody ? fixtureA->GetBody() : fixtureB->GetBody();
        Player* player = reinterpret_cast<Player*>(playerBody->GetUserData().pointer);

        if (player) {
            player->onPlatform = true;
        }
    }
    void ContactListener::EndContact(b2Contact* contact) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        // Similar logic as BeginContact to identify the player
        if (fixtureA->GetBody()->GetType() != b2_dynamicBody && fixtureB->GetBody()->GetType() != b2_dynamicBody) {
            return; // Neither fixture is a player
        }

        b2Body* playerBody = fixtureA->GetBody()->GetType() == b2_dynamicBody ? fixtureA->GetBody() : fixtureB->GetBody();
        Player* player = reinterpret_cast<Player*>(playerBody->GetUserData().pointer);

        if (player) {
            player->onPlatform = false;
        }
    }
};
