#include "Util/TextUtil.hpp"

#include <fmt/format.h>

#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>
#include <vector>

namespace BetterSongSearch::Util {
    // this hurts
    std::vector<std::string> split(std::string_view buffer, std::string_view const delimeter) {
        std::vector<std::string> ret{};
        std::decay_t<decltype(std::string::npos)> pos{};
        while ((pos = buffer.find(delimeter)) != std::string::npos) {
            auto const match = buffer.substr(0, pos);
            if (!match.empty()) {
                ret.emplace_back(match);
            }
            buffer = buffer.substr(pos + delimeter.size());
        }
        if (!buffer.empty()) {
            ret.emplace_back(buffer);
        }
        return ret;
    }

    std::string join(std::vector<std::string> strings, std::string_view const delimeter) {
        if (strings.empty()) {
            return "";
        }

        std::string ret;
        for (size_t i = 0; i < strings.size(); i++) {
            ret += strings[i];
            if (i != strings.size() - 1) {
                ret += delimeter;
            }
        }
        return ret;
    }

    /**
     * Removes special characters from a string
     */
    std::string removeSpecialCharacter(std::string_view const s) {
        auto filteredView = s | std::views::filter([](char c) {
                                return std::isalnum(c) || c == ' ';
                            });
        std::string stringy(filteredView.begin(), filteredView.end());
        return stringy;
    }

    std::string toLower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    std::string toLower(std::string_view s) {
        return toLower(std::string(s));
    }

    std::string toLower(char const* s) {
        return toLower(std::string(s));
    }

    bool IsSpace(char x) {
        return x == ' ' || !isalnum(x);
    };

    std::string httpErrorToString(int code) {
        switch (code) {
            case 400:
                return "잘못된 요청";
            case 401:
                return "인증되지 않음";
            case 403:
                return "접근이 거부되었습니다";
            case 404:
                return "찾을 수 없습니다";
            case 405:
                return "허용되지 않은 요청 방식";
            case 429:
                return "요청이 너무 많습니다";
            case 500:
                return "서버 내부 오류";
            case 502:
                return "게이트웨이 오류";
            case 503:
                return "서비스를 사용할 수 없습니다";
            case 504:
                return "게이트웨이 응답 시간 초과";
            default:
                return fmt::format("HTTP 오류 {}", code);
        }
    }

    std::string curlErrorToString(int code) {
        switch (code) {
            case 0:  // CURLE_OK
                return "오류 없음";
            case 1:  // CURLE_UNSUPPORTED_PROTOCOL
                return "지원하지 않는 프로토콜";
            case 2:  // CURLE_FAILED_INIT
                return "cURL 초기화 실패";
            case 3:  // CURLE_URL_MALFORMAT
                return "잘못된 URL 형식";
            case 6:  // CURLE_COULDNT_RESOLVE_HOST
                return "호스트 주소를 확인할 수 없습니다";
            case 7:  // CURLE_COULDNT_CONNECT
                return "서버에 연결할 수 없습니다";
            case 16:  // CURLE_HTTP2
                return "HTTP/2 통신 오류";
            case 28:  // CURLE_OPERATION_TIMEDOUT
                return "작업 시간이 초과되었습니다";
            case 35:  // CURLE_SSL_CONNECT_ERROR
                return "SSL 연결 오류";
            case 52:  // CURLE_GOT_NOTHING
                return "서버에서 응답이 없습니다";
            case 78:  // CURLE_REMOTE_FILE_NOT_FOUND
                return "원격 파일을 찾을 수 없습니다";

            default:
                return fmt::format("오류 코드 {}", code);
        }
    }
}  // namespace BetterSongSearch::Util
