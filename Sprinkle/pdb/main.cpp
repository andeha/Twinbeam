//
//  main.cpp
//  pdb
//

#include <Twinbeam.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <Additions.h>
#include "pdb.h"

uint8_t getutf8() { return (uint8_t)getc(stdin); }
void putch(char utf8) { putchar(utf8); }
auto Putch = ^(char utf8) { putch(utf8); };
auto Getch = ^{ return getutf8(); };
auto alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
inline void dbgout(const char *utf8) { while (*utf8) { putch(*utf8++); } } // Note: U+007f=DELETE.
auto Put = ^(char32_t unicode) {
  if (UnicodeToUtf8(unicode, ^(const uint8_t *p, int bytes) {
      for (int i = 0; i < bytes; i++) Putch(*(p + i));	
  })) { dbgout("Unicode error"); } };

INNER_FUNCTION
void 
pdbToMdb(
    const char *line,
    void (^output)(char utf8)
)
{
    auto strcmp = ^(const char * s1, const char * s2) {
      while (*s1 == *s2 && *s1++ | *s2++);
      int i = *s1 - *s2;
      return i < 0 ? -1 : i > 0 ? 1 : 0; };
    // TODO: Translate pdb line to mdb commands.
    while (*line) { output(*line++); } 
}

INNER_FUNCTION
void 
mdbToPdb(
    char c
)
{
    enum class State { init, found };
    static struct { State state; } context = { State::init };
    // TODO: Translate mdb to pdb.
}

typedef void (^Request)(); 
typedef void (^Response)(const char *resp);
typedef Tuple<Request, Response> Query;

extern AnnotatedRegister AR_Mips_Debug;
extern AnnotatedRegister AR_Microchip_RCON;
extern void Present(Utf8Terminal &term, const AnnotatedRegister& r, 
  __builtin_uint_t value);

Map<const char *, Query> pic32mzda = { 
    { "fpu", Tuple<Request, Response>(
      ^{ Termlog << "device PIC32MZ2064DAH169\nhwtool SK\nprogram \"../fpu.hex\" \n"; }, 
      ^(const char *resp) { })
    },
    { "debug", Tuple<Request, Response>(
      ^{ Termlog << "print /x debug\n"; }, 
      ^(const char *resp) { __builtin_uint_t val = 0x12341234; Present(Termlog, AR_Mips_Debug, val); })
    },
    { "rcon", Tuple<Request, Response>(
      ^{ Termlog << "print /x rcon\n";  }, 
      ^(const char *resp) { __builtin_uint_t val = 0x12341234; Present(Termlog, AR_Microchip_RCON, val); })
    },
};

int
main(
    int argc,
    char * argv[]
)
{ // stdin=0, stdout=1 and stderr=2
    int status = 0;
    int fd_p2c[2], fd_c2p[2];
    if (argc != 2) { fprintf(stderr, "Usage: pdb <program.hex>\n"); exit(1); }
    if (pipe(fd_p2c) == -1 || pipe(fd_c2p) == -1) { fprintf(stderr, "pdb: Error when pipe\n"); exit(1); }
    pid_t pid = fork();
    if (pid == -1) { fprintf(stderr, "pdb: Error when initial fork\n"); exit(1); }
    if (pid) { // Parent
        close(fd_p2c[0]);
        close(fd_c2p[1]);
        pid_t pid2 = fork(); // Fiber instead.
        if (pid2 == -1) { fprintf(stderr, "pdb: Error when second fork\n"); exit(1); }
        if (pid2) { // Parent (reading the debuggers' stdout)
            for (;;) { const int maxLine = 1024; char line[maxLine]; int len = 0;
                if ((len = read(fd_c2p[0], line, maxLine)) < 0) { fprintf(stderr, "pdb: Error when reading mdb\n"); exit(1); }
                line[len] = 0; pdbToMdb(line, ^(char utf8) { });
                fprintf(stderr, "%s", line);
            }
        } else { char c; // Child (writing the debuggers' stdin)
            while (read(STDIN_FILENO, &c, 1) > 0) {
                mdbToPdb(c);
                // TODO: Translate pdb to mdb.
                if (write(fd_p2c[1], &c, 1) != 1) {
                    fprintf(stderr, "pdb: Error when writing mdb\n");
                    exit(1);
                }
            }
        }
        
        close(fd_c2p[0]); close(fd_p2c[1]);
        // waitpid(pid, &status, 0);
        
    } else { // Child
        if (dup2(fd_p2c[0], 0) != 0 ||
            close(fd_p2c[0])   != 0 ||
            close(fd_p2c[1])   != 0)
        {
            fprintf(stderr, "pdb: Error when setting up childs' standard input\n");
            exit(1);
        }
        if (dup2(fd_c2p[1], 1) != 1 ||
            close(fd_c2p[1])   != 0 ||
            close(fd_c2p[0])   != 0)
        {
            fprintf(stderr, "pdb: Error when setting up childs' standard output\n");
            exit(1);
        }
        status = execlp("/Applications/microchip/mplabx/v4.20/mplab_platform/bin/mdb.sh", "", (char *)NULL);
        if (status == -1) { fprintf(stderr, "pdb: Error in execlp\n"); exit(1); }
        fflush(stdout);
    }
    return status;
}
