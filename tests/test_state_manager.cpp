#include <gtest/gtest.h>
#include "StateManager.hpp"
#include "State.hpp"
#include <memory>


class FakeState : public State {
public:
    bool isUpdated = false;
    void HandleEvent(const sf::Event& event) override {}
    void Update(float dt) override { isUpdated = true; }
    void Render(sf::RenderWindow& window) override {}
};

TEST(StateManagerTest, PushAndVerifyUpdate) {
    StateManager sm;
    auto test = std::make_unique<FakeState>();
    FakeState* rawPtr = test.get(); 
    
    sm.Push(std::move(test));
    sm.Update(1.0f);
    EXPECT_TRUE(rawPtr->isUpdated);
}

TEST(StateManagerTest, PopDoesNotCrashOnEmpty) {
    StateManager sm;
    EXPECT_NO_THROW(sm.Pop());
}