#include <iostream>
#include <fstream>
#include <cassert>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include "d_player.h"
#include <cstdio>


using namespace std;
std::ofstream fout("child_log.txt");
template<typename T>
void debug(const T &x) {
    fout << x << endl;
}

//long ptrace(enum __ptrace_request request, pid_t pid, void *addr, void *data);

#define PLAYER_MEMORY 0x754540
#define HEALTH_MEMORY 0x75456c
#define INCREASE_HEALTH_BUTTON 'i'
#define ERR_OK 0
#define WORD_BYTES (WORD_BIT/8)
#define HEALTH_STEP 20

//WORD_BIT

int parent(pid_t pid) {
    int status;
//    waitpid(pid, &status, 0);
//    while (!WIFEXITED(status)) {
    while (true) {
        player_t player;
        player_t *plptr = &player;
        int player_t_wcount = sizeof(player) / WORD_BYTES;
        long err_code = -1;
        string line = "";
        while (getline(cin, line) && line != "exit")
//        char c = ' ';
//        while (c = getchar() && c != 'q')
//        while (cin >> c && c != 'q')
        {
            err_code = ptrace(PTRACE_ATTACH, pid, 0, 0);
            assert(err_code == ERR_OK);
            waitpid(pid, &status, 0);
            int32_t next_word = ptrace(PTRACE_PEEKDATA, pid, HEALTH_MEMORY);
//            for (int i = 0; i < player_t_wcount; ++i) {
//                int32_t next_word = ptrace(PTRACE_PEEKDATA, pid, PLAYER_MEMORY, NULL);
////                int32_t next_word = ptrace(PTRACE_PEEKUSER, pid, PLAYER_MEMORY, &err_code);
//                assert(err_code == ERR_OK);
////                waitpid(pid, &status, 0);
//                memcpy((char *)(plptr) + 4*i, &next_word, 4);
//            }
            if (line == "-") {
                if (next_word >= HEALTH_STEP) {
                    next_word -= HEALTH_STEP;
                }
            }
            else {
                next_word += HEALTH_STEP;
            }
            err_code = ptrace(PTRACE_POKEDATA, pid, HEALTH_MEMORY, next_word);
            assert(err_code == ERR_OK);
            err_code = ptrace(PTRACE_DETACH, pid, NULL, NULL);
            assert(err_code == ERR_OK);
            waitpid(pid, &status, NULL);
        }
//        }
//        struct user_regs_struct state;
//        ptrace(PTRACE_SYSCALL, pid, 0, 0);
//        waitpid(pid, &status, 0);
    }
    return -1;
}

int child(int argc, char *argv[]) {
    (void)argc;
    debug("Entering child");
    long int err_code = ERR_OK;
//    long int err_code = ptrace(PTRACE_TRACEME, 0, 0, 0);
//    if (err_code != ERR_OK) {
//        debug("Ptrace error #" + to_string(err_code));
//    }
//    assert(err_code == ERR_OK);

    err_code = execv(argv[0], argv);
    if (err_code != ERR_OK) {
        debug("execv error #" + to_string(err_code));
    }
    assert(err_code == ERR_OK);
    perror("execv");
    return -1;
}

int main(int argc, char **argv)
{
//    struct user_regs_struct state;
//    player_t *player;
//    pid_t pid = fork();
//    assert(pid != -1);
//    if (pid) {
//        return parent(pid);
//    }
//    else {
//        return child(argc - 1, argv + 1);
//    }

    return parent(atoi(argv[1]));
}

