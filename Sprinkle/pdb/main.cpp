//
//  main.cpp
//  pdb
//  

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <stdio.h>
#include <string.h>
#include "pdb.h"

const char *hexfile=NULL, *device_default="PIC32MZ2064DAB288" /*"PIC32MZ2064DAH169"*/, 
  *mdbpath_default="/Applications/microchip/mplabx/v5.20/mplab_platform/bin/mdb.sh";

inexorable
void
userTowardsMdb(
  const char *pdb,
  char *mdb
)
{
    auto copy_𝘗𝘳𝘰𝘨𝘳𝘢𝘮_command = ^(char * dst, char * path) { strcpy(dst, "program '");
      strcpy(dst + 8, path); int len = Utf8BytesUntilNull(dst, BUILTIN_INT_MAX); strcpy(
      dst + len, "'"); };
    if (IsPrefixOrEqual(pdb, "init")) {
        const char *device = device_default, *deviceᵉⁿᵛ = getenv("PIC32DEVICE");
        if (deviceᵉⁿᵛ) device = deviceᵉⁿᵛ;
        char * end = stpcpy(mdb, "device ");
        end = stpcpy(end, device);
        strcpy(end, "\nhwtool SK\n");
   /*     if (hexfile) { int len = Utf8BytesUntilNull(dst, BUILTIN_INT_MAX);
      copy_𝘗𝘳𝘰𝘨𝘳𝘢𝘮_command(mdb+len, hexfile); } */
    }
/*
    auto whitespace = ^(char32_t u) { return u == " "; }; // IsTerminatedBy
    
    
    auto view = ^{
      auto eightbitIsCommand(const char *text, const char *cmd) {
        Opt<bool> isStem = BytesPrefixOrEqual(text, cmd, ^(Opt<char> t, Opt<char> s) {
        });
    };
    else if (IsPrefixOrEqual(pdb, "flash", { U" " }) { // %𝚏𝚕𝚊𝚜𝚑 takes one argument.
      copy_𝘗𝘳𝘰𝘨𝘳𝘢𝘮_command(mdb, pdb + 5);
    } 
*/
/* Mips */
    else if (IsPrefixOrEqual(pdb, "debug")) strcpy(mdb, "print /x debug\n");
    else if (IsPrefixOrEqual(pdb, "prid")) strcpy(mdb, "print /x prid\n");
    else if (IsPrefixOrEqual(pdb, "status")) strcpy(mdb, "print /x status\n");
// Resets
    else if (IsPrefixOrEqual(pdb, "rcon")) strcpy(mdb, "print /x rcon\n");
// Interrupts
    else if (IsPrefixOrEqual(pdb, "ifs")) strcpy(mdb, "print /x ifs0\nprint /x ifs1\nprint /x ifs2\nprint /x ifs3\nprint /x ifs4\nprint /x ifs5\nprint /x ifs6\n");
    else if (IsPrefixOrEqual(pdb, "iec")) strcpy(mdb, "print /x iec0\nprint /x iec1\nprint /x iec2\nprint /x iec3\nprint /x iec4\nprint /x iec5\nprint /x iec6\n");
// Real-time Clock
    else if (IsPrefixOrEqual(pdb, "rtccon")) strcpy(mdb, "print /x rtccon\n");
    else if (IsPrefixOrEqual(pdb, "setclk")) strcpy(mdb, "w /mx syskey 0xAA996655\nw /mx syskey 0x556699AA\nw /mx rtccon 0x0008\nw /mx rtccon 0x8008\nw /mx syskey 0x0\nprint /x rtccon\nprint /x rtctime\n");
// Timers (Timer1 = T1CON, TMR1, PR1, Timer2 - 9 = TxCON, TMRx, PRx)
    else if (IsPrefixOrEqual(pdb, "t1con")) strcpy(mdb, "print /x t1con\n");
    else if (IsPrefixOrEqual(pdb, "t2con")) strcpy(mdb, "print /x t2con\n");
    else if (IsPrefixOrEqual(pdb, "t3con")) strcpy(mdb, "print /x t3con\n");
    else if (IsPrefixOrEqual(pdb, "t4con")) strcpy(mdb, "print /x t4con\n");
    else if (IsPrefixOrEqual(pdb, "t5con")) strcpy(mdb, "print /x t5con\n");
    else if (IsPrefixOrEqual(pdb, "t6con")) strcpy(mdb, "print /x t6con\n");
    else if (IsPrefixOrEqual(pdb, "t7con")) strcpy(mdb, "print /x t7con\n");
    else if (IsPrefixOrEqual(pdb, "t8con")) strcpy(mdb, "print /x t8con\n");
    else if (IsPrefixOrEqual(pdb, "t9con")) strcpy(mdb, "print /x t9con\n");
// Input Capture IC1-IC9
    else if (IsPrefixOrEqual(pdb, "ic1con")) strcpy(mdb, "print /x ic1con\n");
// Output Compare OC1-OC9
    else if (IsPrefixOrEqual(pdb, "oc1con")) strcpy(mdb, "print /x oc1con\n");
// Port A - Port K
    else if (IsPrefixOrEqual(pdb, "a")) strcpy(mdb, "print /x porta\nprint /x lata\nprint /x trisa\n");
    // ...
    else if (IsPrefixOrEqual(pdb, "k")) strcpy(mdb, "print /x portk\nprint /x latk\nprint /x trisk\n");
// DDR
    else if (IsPrefixOrEqual(pdb, "ddrtsel")) strcpy(mdb, "print /x ddrtsel\n");
    else if (IsPrefixOrEqual(pdb, "ddrminlim")) strcpy(mdb, "print /x ddrminlim\n");
    else if (IsPrefixOrEqual(pdb, "ddrmqper")) strcpy(mdb, "print /x ddrmqper\n");
    else if (IsPrefixOrEqual(pdb, "ddrmincmd")) strcpy(mdb, "print /x ddrmincmd\n");
// GLCD
    else if (IsPrefixOrEqual(pdb, "glcdmode")) strcpy(mdb, "print /x glcdmode\n");
    else strcpy(mdb, pdb);
}

inexorable
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
    extern void Present(Utf8Terminal &term, const AnnotatedRegister& r,
      __builtin_uint_t value);
    if (IsPrefixOrEqual(mdb, "debug=")) { mdb += 6;
          Opt<__builtin_int_t> debugOpt = CastᵗˣᵗToInt(feeder);
          if (__builtin_int_t val = *debugOpt) {
             extern AnnotatedRegister AR_Mips_Debug;
             Present(Termlog, AR_Mips_Debug, val);
          } else { fprintf(stderr, "Error presenting `Debug`\n"); }
    } else if (IsPrefixOrEqual(mdb, "prid=")) { mdb += 5;
        Opt<__builtin_int_t> pridOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *pridOpt) {
            extern AnnotatedRegister AR_Mips_Prid;
           Present(Termlog, AR_Mips_Prid, val);
        } else { fprintf(stderr, "Error presenting `Prid`\n"); }
    } else if (IsPrefixOrEqual(mdb, "status=")) { mdb += 7;
        Opt<__builtin_int_t> statusOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *statusOpt) {
            extern AnnotatedRegister AR_Mips_Status;
           Present(Termlog, AR_Mips_Status, val);
        } else { fprintf(stderr, "Error presenting `Status`\n"); }
    }
/* Pic32 */
    else if (IsPrefixOrEqual(mdb, "devid=")) { mdb += 6;
        Opt<__builtin_int_t> devidOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *devidOpt) {
           extern AnnotatedRegister AR_Microchip_DEVID;
           Present(Termlog, AR_Microchip_DEVID, val);
        } else { fprintf(stderr, "Error presenting `DEVID`\n"); }
    } else if (IsPrefixOrEqual(mdb, "rcon=")) { mdb += 5;    // Reset
        Opt<__builtin_int_t> rconOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *rconOpt) {
           extern AnnotatedRegister AR_Microchip_RCON;
           Present(Termlog, AR_Microchip_RCON, val);
        } else { fprintf(stderr, "Error presenting `RCON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "rtccon=")) { mdb += 7;  // Real-time Clock
        Opt<__builtin_int_t> rtcconOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *rtcconOpt) {
           extern AnnotatedRegister AR_Microchip_RTCCON;
           Present(Termlog, AR_Microchip_RTCCON, val);
        } else { fprintf(stderr, "Error presenting `RTCCON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t1con=")) { mdb += 6;   // Timers
        Opt<__builtin_int_t> t1conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t1conOpt) {
           extern AnnotatedRegister AR_Microchip_T1CON;
           Present(Termlog, AR_Microchip_T1CON, val);
        } else { fprintf(stderr, "Error presenting `T1CON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t2con=")) { mdb += 6;
        Opt<__builtin_int_t> t2conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t2conOpt) {
           extern AnnotatedRegister AR_Microchip_T29CON;
           Present(Termlog, AR_Microchip_T29CON, val);
        } else { fprintf(stderr, "Error presenting `T2CON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t3con=")) { mdb += 6;
        Opt<__builtin_int_t> t3conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t3conOpt) {
           extern AnnotatedRegister AR_Microchip_T29CON;
           Present(Termlog, AR_Microchip_T29CON, val);
        } else { fprintf(stderr, "Error presenting `T3CON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t4con=")) { mdb += 6;
        Opt<__builtin_int_t> t4conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t4conOpt) {
           extern AnnotatedRegister AR_Microchip_T29CON;
           Present(Termlog, AR_Microchip_T29CON, val);
        } else { fprintf(stderr, "Error presenting `T4CON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t5con=")) { mdb += 6;
        Opt<__builtin_int_t> t5conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t5conOpt) {
           extern AnnotatedRegister AR_Microchip_T29CON;
           Present(Termlog, AR_Microchip_T29CON, val);
        } else { fprintf(stderr, "Error presenting `T5CON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t6con=")) { mdb += 6;
        Opt<__builtin_int_t> t6conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t6conOpt) {
           extern AnnotatedRegister AR_Microchip_T29CON;
           Present(Termlog, AR_Microchip_T29CON, val);
        } else { fprintf(stderr, "Error presenting `T6CON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t7con=")) { mdb += 6;
        Opt<__builtin_int_t> t7conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t7conOpt) {
           extern AnnotatedRegister AR_Microchip_T29CON;
           Present(Termlog, AR_Microchip_T29CON, val);
        } else { fprintf(stderr, "Error presenting `T7CON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t8con=")) { mdb += 6;
        Opt<__builtin_int_t> t8conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t8conOpt) {
           extern AnnotatedRegister AR_Microchip_T29CON;
           Present(Termlog, AR_Microchip_T29CON, val);
        } else { fprintf(stderr, "Error presenting `T8CON`\n"); }
    } else if (IsPrefixOrEqual(mdb, "t9con=")) { mdb += 6;
        Opt<__builtin_int_t> t9conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *t9conOpt) {
           extern AnnotatedRegister AR_Microchip_T29CON;
           Present(Termlog, AR_Microchip_T29CON, val);
        } else { fprintf(stderr, "Error presenting `T9CON`\n"); }
    }
    
    else if (IsPrefixOrEqual(mdb, "ic1con=")) { mdb += 7;   // Input capture IC1-IC9
        Opt<__builtin_int_t> ic1conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *ic1conOpt) {
           extern AnnotatedRegister AR_Microchip_ICxCON;
           Present(Termlog, AR_Microchip_ICxCON, val);
        } else { fprintf(stderr, "Error presenting `IC1CON`\n"); }
    }
    else if (IsPrefixOrEqual(mdb, "oc1con=")) { mdb += 7;   // Output compare OC1-OC9
        Opt<__builtin_int_t> oc1conOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *oc1conOpt) {
           extern AnnotatedRegister AR_Microchip_OCxCON;
           Present(Termlog, AR_Microchip_OCxCON, val);
        } else { fprintf(stderr, "Error presenting `OC1CON`\n"); }
    }
/* mzda */
    else if (IsPrefixOrEqual(mdb, "glcdmode=")) { mdb += 9;  // GLCD
        Opt<__builtin_int_t> glcdModeOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *glcdModeOpt) {
           extern AnnotatedRegister AR_Microchip_GLCD_MODE;
           Present(Termlog, AR_Microchip_GLCD_MODE, val);
        } else { fprintf(stderr, "Error presenting `GLCD_MODE`\n"); }
    }
    else fprintf(stderr, "%s\n", mdb);
}

int
main(
  int argc,
  const char * argv[]
)
{ /* stdin=0 (mdb output), stdout=1 () and stderr=2 (output to user) */
    int status = 0;
    int fd_p2c[2], fd_c2p[2]; const int maxline = 1024;
    auto process_command_line = ^{ int j;
      for (j = 1; j < argc - 1 && argv[j][0] == '-'; j++) { fprintf(stderr,
        "Usage: %s %s\n", argv[0], "[ program.hex ]"); exit(1); }
      if (j != argc - 1) { hexfile = argv[j]; }
    }; process_command_line();
    fprintf(stderr, "pdb, revision %s (^-c to quit.)\n\n", SHA1GIT);
    if (pipe(fd_p2c) == -1 || pipe(fd_c2p) == -1) { fprintf(stderr,
      "pdb: Error when pipe\n"); exit(1); }
    pid_t pid = fork();
    if (pid == -1) { fprintf(stderr, "pdb: Error when fork\n"); exit(1); }
    if (pid) { /* Parent */
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
                toMdb(fd_p2c[1], mdbline); pdbline[0] = '0';
            }
        }
        
        close(fd_c2p[0]); close(fd_p2c[1]);
        // waitpid(pid, &status, 0);
        
    } else { /* Child */
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
        const char * mdbpath = mdbpath_default;
        const char * mdbpathᵉⁿᵛ = getenv("MDBPATH");
        if (mdbpathᵉⁿᵛ) mdbpath = mdbpathᵉⁿᵛ;
        status = execlp(mdbpath, "", (char *)NULL);
        if (status == -1) { fprintf(stderr, "pdb: Error when execlp\n"); exit(1); }
        fflush(stdout);
    }
    
    return status;
}

/*
 
 To view a man page, write 'nroff -man pdb.1'
 …and 'groff -man  pdb.1 > pdb.ps' to generate a printable.
 
 */


