#pragma once

#include <bitset>
#include <vector>


const unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature; // keeps track of which components the respective entity contains


struct IComponent {
    protected:
        static int nextId;
};

// Used to assign a unique id to a component type
template <typename TComponent>
class Component: IComponent {
    // Returns the unique id of Component<T>
    static int GetId() {
        static auto id = nextId++;
        return id;
    }

};


class Entity {

    private:
        int id;

    public:
        Entity(int id): id(id) {}; // c++ allows to initialize member variables in a initializer list directly
        Entity(const Entity &entity) = default;
        int GetId() const;

        // operator overloads
        Entity& operator = (const Entity &other) = default;
        bool operator == (const Entity &other) const { return id == other.id; }
        bool operator != (const Entity &other) const { return id != other.id; }
        bool operator > (const Entity &other) const { return id > other.id; }
        bool operator < (const Entity &other) const { return id < other.id; }

};


class System {
// The System class  processes entitiies that contain specific component signatures
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        const Signature& GetComponentSignature() const;

        // Defines component type that entities must have to be considered by
        // the System
        template <typename T> void RequireComponent();
};


class Registry {

};




template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);

}
