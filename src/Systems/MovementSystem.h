#pragma once


class MovementSystem: public System {
    public:
        MovementSystem() {
            //TODO: RequireConponent<TransformComponent>();
            // ...
        }

        void Update() {
            for (auto entity : GetEntities()) {
                //TODO: Update entity position based on it velocity
            }

        }
};
