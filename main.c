#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "logger.h"

void send_log_packet(const char* phase) {
    printf("-> Attempting to write 3 messages (MIN, STD, MAX)...\n");
    logger_write(MIN, "[%s] This is a CRITICAL message (MIN)", phase);
    logger_write(STANDARD, "[%s] This is an INFO message (STD)", phase);
    logger_write(MAX, "[%s] This is a DEBUG message (MAX)", phase);
}

int main() {
    int sig_dump = SIGRTMIN;
    int sig_toggle = SIGRTMIN + 1;
    int sig_level = SIGRTMIN + 2;

    printf("Process PID: %d\n", getpid());
    remove("test_log.txt");

    if (logger_init("test_log.txt", sig_dump, sig_toggle, sig_level) != 0) {
        printf("Library failed to start.\n");
        return 1;
    }

    // Testing different log levels
    send_log_packet("PHASE_1_STD");

    // Increase log level
    kill(getpid(), sig_level);
    usleep(10000); // Small delay to ensure state updates

    send_log_packet("PHASE_2_MAX");

    // Increase log level again (wraps around to MIN)
    kill(getpid(), sig_level);
    usleep(10000);

    send_log_packet("PHASE_3_MIN");

    // Toggle logging OFF
    kill(getpid(), sig_toggle);
    usleep(10000);

    logger_write(MIN, "THIS SHOULD NOT APPEAR IN THE FILE");

    // Toggle logging ON
    kill(getpid(), sig_toggle);
    usleep(10000);

    // Testing state dumps
    union sigval val;

    printf("Dump with value 100\n");
    val.sival_int = 100;
    sigqueue(getpid(), sig_dump, val);

    // Give the background thread time to wake up and write the file
    sleep(1);

    printf("Dump with value 255\n");
    val.sival_int = 255;
    sigqueue(getpid(), sig_dump, val);

    // Give the background thread time to process before shutting down
    sleep(1);

    printf("\nDone!\n");
    logger_kill();

    return 0;
}