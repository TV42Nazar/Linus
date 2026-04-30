#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>

#define MAX_EVENTS 10
#define CHILD_COUNT 5

typedef struct {
    pid_t pid;
    double arrival_time;
} Event;

Event timeline[MAX_EVENTS];
int event_count = 0;
struct timeval start_time;

double get_elapsed_time() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec - start_time.tv_sec) + (now.tv_usec - start_time.tv_usec) / 1000000.0;
}

void signal_handler(int sig, siginfo_t *info, void *context) {
    if (event_count < MAX_EVENTS) {
        timeline[event_count].pid = info->si_pid;
        timeline[event_count].arrival_time = get_elapsed_time();
        event_count++;
    }
}

void draw_graph() {
    printf("\n--- ЧАСОВА ЛІНІЯ ПОДІЙ (ГРАФ) ---\n");
    printf("Час (с) | Процеси\n");
    printf("--------------------------\n");

    for (int i = 0; i < event_count; i++) {
        printf("%7.2f | ", timeline[i].arrival_time);
        
        int spaces = (int)(timeline[i].arrival_time * 10);
        for (int s = 0; s < spaces; s++) printf(" ");
        
        printf("● [PID: %d]\n", timeline[i].pid);
    }
    printf("--------------------------\n");
}

int main() {
    gettimeofday(&start_time, NULL);

    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    printf("Контролер (PID: %d) запущено. Створюю %d процесів...\n", getpid(), CHILD_COUNT);

    for (int i = 0; i < CHILD_COUNT; i++) {
        if (fork() == 0) {
            srand(getpid());
            float wait_time = (rand() % 50) / 10.0;
            sleep(wait_time);
            
            kill(getppid(), SIGUSR1);
            exit(0);
        }
    }

    for (int i = 0; i < CHILD_COUNT; i++) {
        wait(NULL);
    }

    draw_graph();

    return 0;
}