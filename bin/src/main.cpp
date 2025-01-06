#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include "../cpp/discord.h"

struct DiscordState {
  std::unique_ptr<discord::Core> core;
};

namespace {
  volatile bool interrupted{ false };
}

int main() {
  DiscordState state{};
  discord::Core* core{};
  auto response = discord::Core::Create(1325672105496285228, DiscordCreateFlags_Default, &core);
  state.core.reset(core);

  if (!state.core) {
    std::cerr << "Failed to instantiate Discord!";
    std::exit(-1);
  }

  state.core->SetLogHook(
    discord::LogLevel::Debug, [](discord::LogLevel level, const char* message) {
        std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << message << "\n";
    }
  );

  discord::Activity activity{};
  activity.SetDetails("neovim");
  activity.SetState("editing");
  activity.SetType(discord::ActivityType::Playing);
  state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
    std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
      << " updating activity!\n";
  });

  std::signal(SIGINT, [](int) {
    interrupted = true;
  });
  do {
    state.core->RunCallbacks();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  } while (!interrupted);
}
