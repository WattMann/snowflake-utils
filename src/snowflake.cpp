#include <cstdio>
#include <ctime>
#include <string>
#include <inttypes.h>

void _handle_err(const char* num) {
    printf("Failed to parse %s... Skipping\n ", num);
}

int main(int argc, char* argv[]) {
    
    if(argc < 2) {
        printf("Specify a snowflake!\nusage: snowflake-extractor <snowflake...>\nYou can specify more snowflakes if you separate them with space.\n");
        return -1;
    }
    uint64_t snowflake;
    for(int index = 1; index < argc; index++) {
        try {
            snowflake = std::stoull(argv[index]);
        } catch (...) {
            _handle_err(argv[index]);
            continue;
        }
        int64_t timestamp = (snowflake >> 22);
        uint32_t worker_id = (snowflake & 0x3E0000) >> 17;
        uint32_t process_id = (snowflake & 0x1f000) >> 12;
        uint32_t increment = (snowflake & 0xFFF);
        uint64_t milis = timestamp + 1420070400000;
        int32_t unix_time = milis/1000;
        time_t time = unix_time;        
    
        printf("===========================\n");
        printf("%" PRIu64 " analysis:\n", snowflake);
        printf("Timestamp: %" PRIu64 "\n", timestamp);
        printf("Timestamp since epoch: %" PRIu64 "\n", milis);
        printf("Local time: %s", ctime(&time));
        printf("Internal worker ID: %d\n", worker_id);
        printf("Internal process ID: %d\n", process_id);
        printf("Increment: %d\n", increment);
        printf("==========================\n");
    }
			
    return 0;
}

