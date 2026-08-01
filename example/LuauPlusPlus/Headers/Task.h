
#pragma once
#ifndef LUAU_TASK_H
#define LUAU_TASK_H

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <variant>
#include <utility>

//--------------------------//
//     Task functions       //
//--------------------------//

namespace Luau {
    struct SpawnActions {
        std::thread Function;
        SpawnActions() = default;
        SpawnActions(std::thread thread) : Function(std::move(thread)) {}
        inline void WaitThread() {if(Function.joinable()) {Function.join();}}
        inline void DetachThread() {if(Function.joinable()) {Function.detach();}}
    };
    namespace Task {
        inline SpawnActions Spawn(const std::function<void()> funct) {
            try {return SpawnActions(std::thread(funct));} catch (...) {return {};};
        }
        inline void Wait(double seconds) noexcept {
            if (seconds <= 0.0) return;
            using namespace std::chrono;
            auto dur = duration<double>(seconds);
            std::this_thread::sleep_for(duration_cast<milliseconds>(dur));
        }
    }
}

#endif