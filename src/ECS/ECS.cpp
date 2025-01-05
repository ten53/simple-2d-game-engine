#include "ECS.h"


int Entity::GetId() const {
    return id;
}


void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}


void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity item) {
                // see operator overloads
                return entity == item;
    }));
}


std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}


const Signature& System::GetComponentSignature() const {
    return componentSignature;
}


