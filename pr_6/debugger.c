#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <sys/types.h>

void run_debugger(pid_t child_pid) {
    int wait_status;
    struct user_regs_struct regs;

    printf("[DB] Налагоджувач запущено для PID: %d\n", child_pid);

    wait(&wait_status);

    while (WIFSTOPPED(wait_status)) {
        ptrace(PTRACE_GETREGS, child_pid, NULL, &regs);
        printf("[DB] Instruction Pointer (RIP): 0x%llx\n", regs.rip);

        int sig = WSTOPSIG(wait_status);
        printf("[DB] Дочірній процес зупинено сигналом: %d\n", sig);

        if (sig == SIGTRAP) {
            printf("[DB] Спрацював Breakpoint або Singlestep!\n");
        }

        printf("[DB] Натисніть Enter для наступного кроку (Single Step)...");
        getchar();

        if (ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL) < 0) {
            perror("ptrace_singlestep");
            return;
        }
        wait(&wait_status);
    }
    printf("[DB] Цільовий процес завершено.\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <шлях_до_програми>\n", argv[0]);
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(argv[1], argv[1], NULL);
    } else if (child_pid > 0) {
        run_debugger(child_pid);
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}