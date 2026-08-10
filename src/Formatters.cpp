#include "Formatters.hpp"

#include "logging.hpp"

namespace BetterSongSearch::Formatters {
    StringW FormatMapStyle(StringW value) {
        DEBUG("Formatting map style");
        std::string raw = (std::string) value;

        if (raw == "Any") return "전체";
        if (raw == "accuracy") return "정확도";
        if (raw == "balanced") return "균형";
        if (raw == "challenge") return "도전";
        if (raw == "dance") return "댄스";
        if (raw == "fitness") return "운동";
        if (raw == "speed") return "스피드";
        if (raw == "tech") return "테크";

        // Fallback for unknown/new styles: preserve the original behavior.
        if (raw.empty()) {
            return raw;
        }
        raw[0] = std::toupper(raw[0]);
        DEBUG("Formatted map style: {}", raw);
        return raw;
    }

    std::string FormatSongGenre(StringW value) {
        return (std::string) value;
    }
}  // namespace BetterSongSearch::Formatters
