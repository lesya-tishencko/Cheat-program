#include <iostream>
#include <fstream>
#include <cassert>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include "d_player.h"
#include <cstddef>
#include <cstdio>

using namespace std;
#define CHILD_LOGGING_FILE "child_log.txt"
template<typename T>
void debug(const T &x) {
    cout << x << endl;
}

//#define HEALTH_MEMORY 0x75456c
//#define HEALTH_MEMORY 0x7533ec // DEBUG
#define HEALTH_MEMORY 0x72e90c // RELEASE
#define PLAYER_OFFSET HEALTH_MEMORY - 0x02c
#define CHEATS_OFFSET
//#define PTR_ENTRY_ADDR(ptr, entry) (&((ptr)->entry) - ptr)
#define ERR_OK 0
#define HEALTH_STEP 20

typedef int32_t word_t;

word_t get_word(pid_t pid, uintptr_t addr) {
    long err_code = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    int status; waitpid(pid, &status, 0);
    if (WIFEXITED(status)) exit(0);
    int32_t next_word = ptrace(PTRACE_PEEKDATA, pid, addr);
    err_code = ptrace(PTRACE_DETACH, pid, NULL, NULL);
    assert(err_code == ERR_OK);
    return next_word;
}

// returns error_code
int change_word(pid_t pid, uintptr_t addr, word_t new_value) {
    long err_code = -1;
    err_code = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    if (err_code != ERR_OK) return err_code;
    int status; waitpid(pid, &status, 0);
    if (WIFEXITED(status)) exit(0);
    err_code = ptrace(PTRACE_POKEDATA, pid, addr, new_value);
    if (err_code != ERR_OK) return err_code;
    err_code = ptrace(PTRACE_DETACH, pid, NULL, NULL);
    if (err_code != ERR_OK) return err_code;
    return ERR_OK;
}

uintptr_t cheat_addr() {
    uintptr_t res = PLAYER_OFFSET + offsetof(player_t, cheats);
    res = res + 3 * NUMCARDS;// boolean apparent is integer is not counted in offsetof.
    while (res % 4) res++; // alignment.
//    res += (NUMPOWERS - 1) * sizeof(int);
//    res += (NUMCARDS - 1) * sizeof(boolean);

//    res += (MAXPLAYERS - 1) * sizeof(int);

//    res += (NUMWEAPONS - 1) * sizeof(int);
//    res += (NUMAMMO - 1) * sizeof(int);
//    res += (NUMAMMO - 1) * sizeof(int);
    return res;
}

int parent(pid_t pid) {
    while (true) {
        string line = "";
        while (getline(cin, line) && line != "exit") {
            const uintptr_t health_addr = PLAYER_OFFSET + offsetof(player_t, health);
            if (line.substr(0, 2) == "gm") {
                word_t cur_mod = get_word(pid, cheat_addr());
//                cur_mod ^= CF_GODMODE;
                if (line == "gm off") {
                    cur_mod &= ~CF_GODMODE;
                }
                else if (line == "gm on") {
                    cur_mod = cur_mod | CF_GODMODE;
                }
                assert(change_word(pid, cheat_addr(), cur_mod) == ERR_OK);
            }
            else if (line.front() == 'h') {
                word_t cur_health = get_word(pid, health_addr);
                if (line.back() == '+') {
                    cur_health += HEALTH_STEP;
                    assert(change_word(pid, health_addr, cur_health) == ERR_OK);
                }
                else if (line.back() == '-') {
                    if (cur_health > HEALTH_STEP) {
                        cur_health -= HEALTH_STEP;
                        assert(change_word(pid, health_addr, cur_health) == ERR_OK);
                    }
                }
            }
        }
        if (line == "exit") return 0;
    }
    return -1;
}

int main(int argc, char **argv)
{
    pid_t pid = fork();
    assert(pid >= 0);
    if (pid) {
        return parent(pid);
    }
    else {
        freopen(CHILD_LOGGING_FILE, "w", stdout);
        char **args = (char **)calloc(argc, sizeof(char *));
        for (int i = 0; i+1 < argc; ++i) {
            args[i] = strdup(argv[i+1]);
        }
        args[argc-1] = NULL;
        if (execvp(args[0], args) < 0) {
            exit(1);
        }
    }
    return 0;
}
