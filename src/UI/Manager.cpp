#include "UI/Manager.hpp"

#include <bsml/shared/Helpers/getters.hpp>

#include "DataHolder.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "HMUI/NoTransitionsButton.hpp"
#include "logging.hpp"
#include "sys/sysinfo.h"
#include "sys/types.h"
#include "System/GC.hpp"
#include "UnityEngine/Profiling/Profiler.hpp"
#include "UnityEngine/Resources.hpp"
#include "Util/Debug.hpp"

using namespace BetterSongSearch::UI;
using namespace BetterSongSearch::Util;
using namespace GlobalNamespace;

#define coro(coroutine) BSML::SharedCoroutineStarter::get_instance()->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(coroutine))

void BetterSongSearch::UI::Manager::Init() {
    // Register the menu button
    BSML::Register::RegisterMenuButton("향상된 곡 검색", "향상된 곡 검색", [this]() {
        DEBUG("MenuButtonClick");
        ShowFlow(false);
    });
}

custom_types::Helpers::Coroutine BetterSongSearch::UI::Manager::Debug() {
    static struct sysinfo memInfo;
    int iterations_count = 0;
    int64_t lastused = 0;
    int64_t initialmemusage = UnityEngine::Profiling::Profiler::GetMonoUsedSizeLong();
    // wait for the game to start
    co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForSeconds::New_ctor(3.0f));

    // Open the BSS
    ShowFlow(true);
    co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForSeconds::New_ctor(1.0f));

    // Wait for songs to load
    while (!dataHolder.loaded) {
        co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForSeconds::New_ctor(0.2f));
    }

    // co_return;

    while (true) {
        // Tests for the fcinstance
        if (fcInstance) {
            DEBUG("Iteration: {}", iterations_count);
            {
                auto songlist = fcInstance->SongListController;
                co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForSeconds::New_ctor(0.01f));
                songlist->SelectRandom();
                auto currentSong = songlist->GetCurrentSong();
                if (currentSong) {
                    ++iterations_count;
                } else {
                    WARNING("Current song is null, skipping");
                }
            }
        }
    }
    co_yield nullptr;
}

void BetterSongSearch::UI::Manager::DestroyFlow() {
    if (flow) {
        DEBUG("Destroying BSS flowController");
        auto flowGO = flow->get_gameObject();
        if (flowGO) {
            UnityEngine::Object::DestroyImmediate(flowGO);
        }
    } else {
        WARNING("Destroy flow called when the controller didn't exist");
    }
}

void BetterSongSearch::UI::Manager::ShowFlow(bool immediately) {
    if (!flow) {
        flow = BSML::Helpers::CreateFlowCoordinator<BetterSongSearch::UI::FlowCoordinators::BetterSongSearchFlowCoordinator*>();
    }
    parentFlow = BSML::Helpers::GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();
    parentFlow->PresentFlowCoordinator(flow.ptr(), nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
}

void BetterSongSearch::UI::Manager::GoToSongSelect() {
    SafePtrUnity<UnityEngine::GameObject> songSelectButton = UnityEngine::GameObject::Find("SoloButton").unsafePtr();
    if (!songSelectButton) {
        songSelectButton = UnityEngine::GameObject::Find("Wrapper/BeatmapWithModifiers/BeatmapSelection/EditButton");
    }
    if (!songSelectButton) {
        return;
    }
    songSelectButton->GetComponent<HMUI::NoTransitionsButton*>()->Press();
}

void BetterSongSearch::UI::Manager::Close(bool immediately, bool downloadAbortConfim) {
    if (flow) {
        flow->Close(immediately, downloadAbortConfim);
    }
};