//
//  main.cpp
//  pdb
//

#include <System.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pdb.h"

extern void Present(Utf8Terminal &term, const AnnotatedRegister& r,
  __builtin_uint_t value);

INNER_FUNCTION
void 
userTowardsMdb(
  const char *pdb,
  char *mdb
)
{
    auto strcmp = ^(const char *s1, const char *s2) { while (*s1 && (*s1 == *s2)) {
      s1++; s2++; } return *(const unsigned char *)s1 - *(const unsigned
      char *)s2; };
    auto strcpy = ^(char dest[], const char source[]) { int i = 0; while ((dest[i] =
      source[i]) != '\0') { i++; } };
    strcpy(mdb, pdb);
}

INNER_FUNCTION
void
mdbTowardsUser(
  char *mdb
)
{
    __block bool virgin = true; static int si = 0;
    auto feeder = ^(unsigned short& digit) {
      auto utf8byte = (unsigned short)*(mdb + si++);
      if (utf8byte == '\n') return virgin ? CastToIntOpinion::annul :
        CastToIntOpinion::commit;
      auto asciidigit = ^(char32_t u) { return 0x30 <= u && u < 0x40; };
      if (asciidigit(utf8byte)) { digit = (unsigned short)(utf8byte - '0');
        virgin = false; return CastToIntOpinion::accept; }
      if (utf8byte == U'-') return CastToIntOpinion::negate;
      if (utf8byte == 1) return virgin ? CastToIntOpinion::rejecting :
        CastToIntOpinion::commit;
      return CastToIntOpinion::rejecting; };
    if (EightBitIsPrefixOrEqual(mdb, "rcon=")) { mdb += 5;
        Opt<__builtin_int_t> rconOpt = CastToInt(feeder);
        if (__builtin_int_t rcon = *rconOpt) {
           Present(Termlog, AR_Microchip_RCON, rcon);
        } else { fprintf(stderr, "Error presenting `RCON`"); }
    } else if (EightBitIsPrefixOrEqual(mdb, "debug=")) { mdb += 6;
        Opt<__builtin_int_t> debugOpt = CastToInt(feeder);
        if (__builtin_int_t debug = *debugOpt) {
           Present(Termlog, AR_Mips_Debug, debug);
        } else { fprintf(stderr, "Error presenting `Debug`"); }
    } else fprintf(stderr, "%s", mdb);
}

int
main(
  int argc,
  char * argv[]
)
{ // stdin=0, stdout=1 and stderr=2
    
    int status = 0;
    int fd_p2c[2], fd_c2p[2]; const int maxline = 1024;
    if (argc != 2) { fprintf(stderr, "Usage: pdb <program.hex>\n"); exit(1); }
    else { fprintf(stderr, "pdb, revision %s (^-c to quit.)\n\n", SHA1GIT); }
    if (pipe(fd_p2c) == -1 || pipe(fd_c2p) == -1) { fprintf(stderr, 
      "pdb: Error when pipe\n"); exit(1); }
    pid_t pid = fork();
    if (pid == -1) { fprintf(stderr, "pdb: Error when fork\n"); exit(1); }
    if (pid) { // Parent
        close(fd_p2c[0]); close(fd_c2p[1]);
        pid_t pid₂ = fork(); // Fiber instead.
        if (pid₂ == -1) { fprintf(stderr, "pdb: Error when child forks\n"); exit(1); }
        if (pid₂) { // Parent (reading the debuggers' stdout)
            for (;;) { char line[maxline]; int len = 0;
                if ((len = read(fd_c2p[0], line, maxline)) < 0) { fprintf(
                  stderr, "pdb: Error when reading mdb\n"); exit(1); }
                line[len] = 0; mdbTowardsUser(line);
            }
        } else { char pdbline[maxline]; // Child (writing the debuggers' stdin)
            while (read(STDIN_FILENO, &pdbline, maxline) > 0) {
                char mdbline[maxline];
                userTowardsMdb(pdbline, mdbline);
                auto toMdb = ^(int fd, char *s) {
                    int len = Utf8BytesUntilNull(s, BUILTIN_INT_MAX);
                    if (write(fd, s, len) != len) {
                        fprintf(stderr, "pdb: Error when writing mdb\n");
                        exit(1);
                    }
                };
                toMdb(fd_p2c[1], mdbline);
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
        if (status == -1) { fprintf(stderr, "pdb: Error when execlp\n"); exit(1); }
        fflush(stdout);
    }
    
    return status;
}
