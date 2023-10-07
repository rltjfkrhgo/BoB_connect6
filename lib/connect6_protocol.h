#ifndef __CONNECT6_PROTOCOL_H__
#define __CONNECT6_PROTOCOL_H__

#include <stdint.h>
#include <stddef.h>

#if defined _WIN32 || defined __CYGWIN__
    #ifdef WIN_EXPORT
        #ifdef __GNUC__
            #define EXPORTED __attribute__ ((dllexport))
        #else
            #define EXPORTED __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define EXPORTED __attribute__ ((dllimport))
        #else
            #define EXPORTED __declspec(dllimport)
        #endif
    #endif
    #define NOT_EXPORTED
#else
    #if __GNUC__ >= 4
        #define EXPORTED __attribute__ ((visibility ("default")))
        #define NOT_EXPORTED __attribute__ ((visibility ("hidden")))
    #else
        #define EXPORTED
        #define NOT_EXPORTED
    #endif
#endif

#define PROTOCOL_HEADER_SIZE 4
#define PROTOCOL_VER 0
#define MAX_NAME_LENGTH 100
#define BOARD_SIZE 19

// Protocol types
enum ProtocolType {
    GAME_START,
    PUT,
    TURN,
    GAME_OVER,
    ERROR,
    TIMEOUT,
    GAME_DISCARD
};

// Error types
enum ErrorType {
    ERROR_SERVER_INTERNAL_ERROR,
    ERROR_PROTOCOL_NOT_VALID,
    ERROR_EXCEED_COORDINATE_RANGE,
    ERROR_GAME_NOT_STARTED,
    ERROR_EXCEED_CAPACITY,
    ERROR_EXCEED_NAME_LENGTH,
    ERROR_OTHER_PLAYER_DISCONNECTED,
    ERROR_GAME_ALREADY_STARTED,
    ERROR_MISUSE_FUNCTION = 0xFF
};

enum GameResultType {
    RESULT_GAME_DISCARDED,
    RESULT_WIN_OR_LOSE,
    RESULT_DRAW,
    RESULT_CONNECTION_ERROR,
    RESULT_TIMEOUT
};

#ifdef __cplusplus
extern "C" {
#endif
    // Protocol header
    struct Connect6ProtocolHdr {
        uint8_t version;
        uint8_t type;
        uint8_t player_num;
        uint8_t data_length;
    };

    // GAME_START data field
    struct GameStartData {
        uint8_t req_res_flag;
        uint8_t name_length;
        char name[MAX_NAME_LENGTH];
    };

    // PUT or TURN data field
    struct PutTurnData {
        uint8_t coord_num;
        uint8_t xy[2*2];
    };

    // GAME_OVER data field
    struct GameOverData {
        uint8_t result;
        uint8_t coord_num;
        uint8_t xy[2*6];
    };

    uint8_t EXPORTED hdr_parsing(const unsigned char *payload, size_t payload_size, struct Connect6ProtocolHdr *header);
    uint8_t EXPORTED game_start_data_parsing(const unsigned char *data_payload, size_t data_payload_size, struct GameStartData *data);
    uint8_t EXPORTED put_turn_data_parsing(const unsigned char *data_payload, size_t data_payload_size, struct PutTurnData *data);
    uint8_t EXPORTED game_over_data_parsing(const unsigned char *data_payload, size_t data_payload_size, struct GameOverData *data);
    uint8_t EXPORTED error_data_parsing(const unsigned char *data_payload, size_t data_payload_size, uint8_t *error_type);

    uint8_t EXPORTED make_game_start_payload(unsigned char *payload, size_t payload_size, size_t *payload_len_written,
                                             const uint8_t player_num, const struct GameStartData data);

    uint8_t EXPORTED make_put_payload(unsigned char *payload, size_t payload_size, size_t *payload_len_written,
                                      const uint8_t player_num, const struct PutTurnData data);

    uint8_t EXPORTED make_turn_payload(unsigned char *payload, size_t payload_size, size_t *payload_len_written,
                                       const uint8_t player_num, const struct PutTurnData data);

    uint8_t EXPORTED make_game_over_payload(unsigned char *payload, size_t payload_size, size_t *payload_len_written,
                                            const uint8_t player_num, const struct GameOverData data);

    uint8_t EXPORTED make_error_payload(unsigned char *payload, size_t payload_size, size_t *payload_len_written,
                                        const uint8_t player_num, const uint8_t error_type);

    uint8_t EXPORTED make_timeout_payload(unsigned char *payload, size_t payload_size, size_t *payload_len_written,
                                          const uint8_t player_num);

    uint8_t EXPORTED make_game_discard_payload(unsigned char *payload, size_t payload_size, size_t *payload_len_written,
                                               const uint8_t player_num);

#ifdef __cplusplus
}
#endif

#endif
