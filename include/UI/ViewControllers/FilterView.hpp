#pragma once

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/ClickableText.hpp"
#include "bsml/shared/BSML/Components/Settings/DropdownListSetting.hpp"
#include "bsml/shared/BSML/Components/Settings/ListSetting.hpp"
#include "bsml/shared/BSML/Components/Settings/SliderSetting.hpp"
#include "bsml/shared/BSML/Components/Settings/StringSetting.hpp"
#include "bsml/shared/BSML/ViewControllers/HotReloadViewController.hpp"
#include "bsml/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UI/Modals/GenrePicker.hpp"
#include "UI/Modals/Presets.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "Util/RatelimitCoroutine.hpp"

#ifdef HotReload
DECLARE_CLASS_CUSTOM(BetterSongSearch::UI::ViewControllers, FilterViewController, BSML::HotReloadViewController) {
#else
DECLARE_CLASS_CODEGEN(BetterSongSearch::UI::ViewControllers, FilterViewController, HMUI::ViewController) {
#endif
    DECLARE_CTOR(ctor);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);

    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling);

    // Modals
    DECLARE_INSTANCE_FIELD(UnityW<Modals::Presets>, presetsModal);
    DECLARE_INSTANCE_FIELD(UnityW<Modals::GenrePicker>, genrePickerModal);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::ModalView>, sponsorModal);

    DECLARE_INSTANCE_METHOD(void, PostParse);

    // Modal related things
    DECLARE_INSTANCE_METHOD(void, OpenSponsorsModal);
    DECLARE_INSTANCE_METHOD(void, CloseSponsorModal);
    DECLARE_INSTANCE_METHOD(void, OpenSponsorsLink);
    DECLARE_INSTANCE_METHOD(void, TryToDownloadDataset);
    DECLARE_INSTANCE_METHOD(void, ShowGenrePicker);

    // @brief Update the global state from the filter settings withouth updating the UI
    DECLARE_INSTANCE_METHOD(void, UpdateLocalState);

    DECLARE_INSTANCE_METHOD(void, ForceRefreshUI);

    DECLARE_INSTANCE_METHOD(void, ForceFormatValues);

    // Header buttons
    DECLARE_INSTANCE_METHOD(void, ClearFilters);
    DECLARE_INSTANCE_METHOD(void, ShowPresets);

    // Options for dropdowns
    BSML_OPTIONS_LIST_OBJECT(downloadedFilterOptions, "전체", "다운로드만", "다운로드 제외");
    BSML_OPTIONS_LIST_OBJECT(scoreFilterOptions, "전체", "통과곡 제외", "통과곡만");
    BSML_OPTIONS_LIST_OBJECT(rankedFilterOptions, "전체", "스코어세이버 랭크", "비트리더 랭크", "스코어세이버 예선", "비트리더 예선");
    BSML_OPTIONS_LIST_OBJECT(characteristics, "전체", "커스텀", "표준", "한손 세이버", "화살표 없음", "90도", "360도", "라이트쇼", "무규칙");
    BSML_OPTIONS_LIST_OBJECT(difficulties, "전체", "쉬움", "보통", "어려움", "전문가", "전문가+");
    BSML_OPTIONS_LIST_OBJECT(modOptions, "전체", "Noodle Extensions", "Mapping Extensions", "Chroma", "Cinema", "없음");
    BSML_OPTIONS_LIST_OBJECT(mapStyles, "전체", "정확도", "균형", "도전", "댄스", "운동", "스피드", "테크");

    // Values for dropdowns
    DECLARE_INSTANCE_FIELD(StringW, existingSongs);
    DECLARE_INSTANCE_FIELD(StringW, existingScore);
    DECLARE_INSTANCE_FIELD(StringW, rankedState);
    DECLARE_INSTANCE_FIELD(StringW, characteristic);
    DECLARE_INSTANCE_FIELD(StringW, difficulty);
    DECLARE_INSTANCE_FIELD(StringW, mods);
    DECLARE_INSTANCE_FIELD(StringW, mapStyleString);

    // Values for sliders
    DECLARE_INSTANCE_FIELD(float, minimumSongLength);
    DECLARE_INSTANCE_FIELD(float, maximumSongLength);
    DECLARE_INSTANCE_FIELD(float, minimumNjs);
    DECLARE_INSTANCE_FIELD(float, maximumNjs);
    DECLARE_INSTANCE_FIELD(float, minimumNps);
    DECLARE_INSTANCE_FIELD(float, maximumNps);
    DECLARE_INSTANCE_FIELD(float, minimumStars);
    DECLARE_INSTANCE_FIELD(float, maximumStars);
    DECLARE_INSTANCE_FIELD(float, minimumRating);

    // Values for toggles
    DECLARE_INSTANCE_FIELD(bool, onlyCuratedMaps);
    DECLARE_INSTANCE_FIELD(bool, onlyVerifiedMappers);
    DECLARE_INSTANCE_FIELD(bool, onlyV3Maps);

    // These are float because there is some bug in
    DECLARE_INSTANCE_FIELD(float, minimumVotes);
    DECLARE_INSTANCE_FIELD(float, hideOlderThan);

    DECLARE_INSTANCE_METHOD(void, UpdateFilterSettings);

    // Used to refresh the filter text
    DECLARE_INSTANCE_METHOD(void, UpdateGenreFilterText);

    // BG layout stuff
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::HorizontalLayoutGroup*, filterbarContainer);

    // Sliders that need to be formatted
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, hideOlderThanSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, minimumRatingSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, minStarsSetting);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, maxStarsSetting);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, minimumNjsSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, maximumNjsSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, minimumNpsSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, maximumNpsSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, minimumSongLengthSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, maximumSongLengthSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::SliderSetting>, minimumVotesSlider);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::StringSetting>, uploadersStringControl);

    // Values for string fields
    DECLARE_INSTANCE_FIELD(StringW, uploadersString);

    // Dropdowns and settings
    DECLARE_INSTANCE_FIELD(UnityW<BSML::ListSetting>, existingSongsSetting);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::ListSetting>, existingScoreSetting);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::DropdownListSetting>, rankedStateSetting);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::DropdownListSetting>, characteristicDropdown);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::DropdownListSetting>, difficultyDropdown);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::DropdownListSetting>, modsRequirementDropdown);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::DropdownListSetting>, mapStyleDropdown);

    DECLARE_INSTANCE_FIELD(UnityW<UnityEngine::UI::Button>, genrePickButton);

    DECLARE_INSTANCE_FIELD(UnityW<BSML::ClickableText>, datasetInfoLabel);
    DECLARE_INSTANCE_FIELD(UnityW<TMPro::TextMeshProUGUI>, versionLabel);

    // Toggles that need to be refreshed
    DECLARE_INSTANCE_FIELD(UnityW<BSML::ToggleSetting>, onlyCuratedMapsToggle);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::ToggleSetting>, onlyVerifiedMappersToggle);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::ToggleSetting>, onlyV3MapsToggle);

    // DECLARE_INSTANCE_METHOD(StringW, minRatingSliderFormatFunction, float value);
    // DECLARE_INSTANCE_METHOD(StringW, minUploadDateSliderFormatFunciton, float monthsSinceFirstUpload);
   public:
    custom_types::Helpers::Coroutine _UpdateFilterSettings();
    void OnLoaded();
    void OnFailed(std::string error);
    void OnSearchComplete();
    BetterSongSearch::Util::RatelimitCoroutine* limitedUpdateFilterSettings = nullptr;
};