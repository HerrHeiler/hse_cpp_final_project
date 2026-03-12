#pragma once
#include "IStudent.hpp"

class RoomActionBase {
public:
    virtual ~RoomActionBase() = default;
    virtual void Apply(IStudent& IStudent, float dt) = 0;
};

class LectureAction : public RoomActionBase {
public:
    void Apply(IStudent& s, float dt) override {
        s.ModifyStats(-1.f * dt, +5.f * dt, 0.f * dt);
        s.AddTime(dt * 60.f);
    }
};

class HomeRestAction : public RoomActionBase {
public:
    void Apply(IStudent& s, float dt) override {
        s.ModifyStats(+2.f * dt, 0.f, +0.5f * dt);
        s.AddTime(dt * 60.f);
    }
};

class SeminarAction : public RoomActionBase {
public:
    void Apply(IStudent& s, float dt) override {
        s.ModifyStats(-2.f * dt, +4.f * dt, -7.f * dt);
        s.AddTime(dt * 60.f);
    }
};

class CafeteriaAction : public RoomActionBase {
public:
    void Apply(IStudent& s, float dt) override {
        s.ModifyStats(+3.f * dt, 0.f, -0.1f * dt);
        s.AddTime(dt * 60.f);
    }
};