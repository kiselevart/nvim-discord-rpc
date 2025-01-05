#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include "discord-files/discord.h"

struct DiscordState {
  std::unique_ptr<discord::Core> core;
};

namespace {
  volatile bool interrupted{ false };
}

int main() {
  DiscordState state{};
}
