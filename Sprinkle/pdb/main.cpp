/* main.cpp for the pdb debugger. */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <stdio.h> /* We use `stdout` and `stderr`. */

/* Compile this debugger by writing 'prompt% ninja' at your prompt. (Ninja is 
  available from http://ninja-build.org.) */

const char *hexfile=NULL, *device_default="PIC32MZ2064DAB288" /*"PIC32MZ2064DAH169"*/, 
  *mdbpath_default="/Applications/microchip/mplabx/v5.20/mplab_platform/bin/mdb.sh";

char * stpcpy(char * dst, const char * src) { while ((*dst++ = *src++)){} return --dst; }

inexorable
void
userkeysToMdb(
  const char *pdb, /* ⬷ Text the user has keyed. */
  char *mdb
)
{
    if (IsPrefixOrEqual(pdb, "init")) {
        const char *device = device_default, *deviceᵉⁿᵛ = getenv("PIC32DEVICE");
        if (deviceᵉⁿᵛ) device = deviceᵉⁿᵛ;
        fprintf(stderr, "pdb: starts initing device %s\n", device);
        char * end=stpcpy(mdb, "device "); end=stpcpy(end, device); end=stpcpy(end, "\n"); 
        end=stpcpy(end, "hwtool SK\n");
        if (hexfile) {
          end=stpcpy(end, "program '"); end=stpcpy(end, hexfile); end=stpcpy(end, "'\n");
        }
        end=stpcpy(end, "reset MCLR\n");
    } /* On append, change, delete, see also --<🥽 McIlroy.cpp>. */
/* auto whitespace = ^(char32_t u) { return u == " "; }; // IsTerminatedBy */
/* Mips */
    else if (IsPrefixOrEqual(pdb, "entrylo0")) stpcpy(mdb, "print /x EntryLo0\n");
    else if (IsPrefixOrEqual(pdb, "entrylo1")) stpcpy(mdb, "print /x EntryLo1\n");
    else if (IsPrefixOrEqual(pdb, "context")) stpcpy(mdb, "print /x Context\n");
    else if (IsPrefixOrEqual(pdb, "pagemask")) stpcpy(mdb, "print /x PageMask\n");
    else if (IsPrefixOrEqual(pdb, "pagegrain")) stpcpy(mdb, "print /x PageGrain\n");
    else if (IsPrefixOrEqual(pdb, "hwrena")) stpcpy(mdb, "print /x HWREna\n");
    else if (IsPrefixOrEqual(pdb, "entryhi")) stpcpy(mdb, "print /x EntryHi\n");
    else if (IsPrefixOrEqual(pdb, "status")) stpcpy(mdb, "print /x Status\n");
    else if (IsPrefixOrEqual(pdb, "intctl")) stpcpy(mdb, "print /x IntCtl\n");
    else if (IsPrefixOrEqual(pdb, "srsctl")) stpcpy(mdb, "print /x SRSCtl\n");
    else if (IsPrefixOrEqual(pdb, "srsmap")) stpcpy(mdb, "print /x SRSMap\n");
    else if (IsPrefixOrEqual(pdb, "srsmap2")) stpcpy(mdb, "print /x SRSMap2\n");
    else if (IsPrefixOrEqual(pdb, "cause")) stpcpy(mdb, "print /x Cause\n");
    else if (IsPrefixOrEqual(pdb, "view_ripl")) stpcpy(mdb, "print /x View_RIPL\n");
    else if (IsPrefixOrEqual(pdb, "nestedexc")) stpcpy(mdb, "print /x View_RIPL\n");
    // else if (IsPrefixOrEqual(pdb, "prid")) stpcpy(mdb, "print /x PRID\n");
    else if (IsPrefixOrEqual(pdb, "ebase")) stpcpy(mdb, "print /x EBase\n");
    else if (IsPrefixOrEqual(pdb, "cdmmbase")) stpcpy(mdb, "print /x CDMMBase\n");
    else if (IsPrefixOrEqual(pdb, "config")) stpcpy(mdb, "print /x Config\n");
    else if (IsPrefixOrEqual(pdb, "config1")) stpcpy(mdb, "print /x Config1\n");
    else if (IsPrefixOrEqual(pdb, "config3")) stpcpy(mdb, "print /x Config3\n");
    else if (IsPrefixOrEqual(pdb, "config5")) stpcpy(mdb, "print /x Config5\n");
    else if (IsPrefixOrEqual(pdb, "config7")) stpcpy(mdb, "print /x Config7\n");
    else if (IsPrefixOrEqual(pdb, "watchlo")) stpcpy(mdb, "print /x WatchLo\n");
    else if (IsPrefixOrEqual(pdb, "watchhi")) stpcpy(mdb, "print /x WatchHi\n");
    else if (IsPrefixOrEqual(pdb, "debug")) stpcpy(mdb, "print /x Debug\n");
    else if (IsPrefixOrEqual(pdb, "tracecontrol")) stpcpy(mdb, "print /x TraceControl\n");
    else if (IsPrefixOrEqual(pdb, "tracecontrol2")) stpcpy(mdb, "print /x TraceControl2\n");
    else if (IsPrefixOrEqual(pdb, "tracebpc")) stpcpy(mdb, "print /x TraceBPC\n");
    else if (IsPrefixOrEqual(pdb, "debug2")) stpcpy(mdb, "print /x Debug2\n");
    else if (IsPrefixOrEqual(pdb, "perfctl0")) stpcpy(mdb, "print /x PerfCtl0\n");
    else if (IsPrefixOrEqual(pdb, "perfctl1")) stpcpy(mdb, "print /x PerfCtl1\n");
    else if (IsPrefixOrEqual(pdb, "perfcnt0")) stpcpy(mdb, "print /x PerfCnt0\n");
    else if (IsPrefixOrEqual(pdb, "perfcnt1")) stpcpy(mdb, "print /x PerfCnt1\n");
    else if (IsPrefixOrEqual(pdb, "errctl")) stpcpy(mdb, "print /x ErrCtl\n");
    else if (IsPrefixOrEqual(pdb, "cacheerr")) stpcpy(mdb, "print /x CacheErr\n");
//    else if (IsPrefixOrEqual(pdb, "taglo")) stpcpy(mdb, "print /x TagLo\n");
//    else if (IsPrefixOrEqual(pdb, "kscratch1")) stpcpy(mdb, "print /x KScratch1\n");
//    else if (IsPrefixOrEqual(pdb, "kscratch2")) stpcpy(mdb, "print /x KScratch2\n");
//    else if (IsPrefixOrEqual(pdb, "fir")) stpcpy(mdb, "print /x FIR\n");
//    else if (IsPrefixOrEqual(pdb, "fccr")) stpcpy(mdb, "print /x FCCR\n");
//    else if (IsPrefixOrEqual(pdb, "fexr")) stpcpy(mdb, "print /x FEXR\n");
//    else if (IsPrefixOrEqual(pdb, "fenr")) stpcpy(mdb, "print /x FENR\n");
//    else if (IsPrefixOrEqual(pdb, "fcsr")) stpcpy(mdb, "print /x FCSR\n");
    
// Resets
    else if (IsPrefixOrEqual(pdb, "rcon")) stpcpy(mdb, "print /x rcon\n");
// Interrupts
    else if (IsPrefixOrEqual(pdb, "ifs")) stpcpy(mdb, "print /x ifs0\nprint /x ifs1\nprint /x ifs2\nprint /x ifs3\nprint /x ifs4\nprint /x ifs5\nprint /x ifs6\n");
    else if (IsPrefixOrEqual(pdb, "iec")) stpcpy(mdb, "print /x iec0\nprint /x iec1\nprint /x iec2\nprint /x iec3\nprint /x iec4\nprint /x iec5\nprint /x iec6\n");
// Real-time Clock
    else if (IsPrefixOrEqual(pdb, "rtccon")) stpcpy(mdb, "print /x rtccon\n");
    else if (IsPrefixOrEqual(pdb, "setclk")) stpcpy(mdb, "w /mx syskey 0xAA996655\nw /mx syskey 0x556699AA\nw /mx rtccon 0x0008\nw /mx rtccon 0x8008\nw /mx syskey 0x0\nprint /x rtccon\nprint /x rtctime\n");
// Timers (Timer1 = T1CON, TMR1, PR1, Timer2 - 9 = TxCON, TMRx, PRx)
    else if (IsPrefixOrEqual(pdb, "t1con")) stpcpy(mdb, "print /x t1con\n");
    else if (IsPrefixOrEqual(pdb, "t2con")) stpcpy(mdb, "print /x t2con\n");
    else if (IsPrefixOrEqual(pdb, "t3con")) stpcpy(mdb, "print /x t3con\n");
    else if (IsPrefixOrEqual(pdb, "t4con")) stpcpy(mdb, "print /x t4con\n");
    else if (IsPrefixOrEqual(pdb, "t5con")) stpcpy(mdb, "print /x t5con\n");
    else if (IsPrefixOrEqual(pdb, "t6con")) stpcpy(mdb, "print /x t6con\n");
    else if (IsPrefixOrEqual(pdb, "t7con")) stpcpy(mdb, "print /x t7con\n");
    else if (IsPrefixOrEqual(pdb, "t8con")) stpcpy(mdb, "print /x t8con\n");
    else if (IsPrefixOrEqual(pdb, "t9con")) stpcpy(mdb, "print /x t9con\n");
// Input Capture IC1-IC9
    else if (IsPrefixOrEqual(pdb, "ic1con")) stpcpy(mdb, "print /x ic1con\n");
// Output Compare OC1-OC9
    else if (IsPrefixOrEqual(pdb, "oc1con")) stpcpy(mdb, "print /x oc1con\n");
// Port A - Port K
    else if (IsPrefixOrEqual(pdb, "a")) stpcpy(mdb, "print /x porta\nprint /x lata\nprint /x trisa\n");
    // ...
    else if (IsPrefixOrEqual(pdb, "k")) stpcpy(mdb, "print /x portk\nprint /x latk\nprint /x trisk\n");
// DDR
    else if (IsPrefixOrEqual(pdb, "ddrtsel")) stpcpy(mdb, "print /x ddrtsel\n");
    else if (IsPrefixOrEqual(pdb, "ddrminlim")) stpcpy(mdb, "print /x ddrminlim\n");
    else if (IsPrefixOrEqual(pdb, "ddrmqper")) stpcpy(mdb, "print /x ddrmqper\n");
    else if (IsPrefixOrEqual(pdb, "ddrmincmd")) stpcpy(mdb, "print /x ddrmincmd\n");
// GLCD
    else if (IsPrefixOrEqual(pdb, "glcdmode")) stpcpy(mdb, "print /x glcdmode\n");
    else stpcpy(mdb, pdb);
}

inexorable
void
mdbToUserscreen(
  char *mdb /* ⬷ Text emitted from mdb. */
)
{ 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 char *text=mdb; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 bool virgin = true; static int si = 0;
    auto feeder = ^(unsigned short& digit) {
      auto utf8byte = (unsigned short)*(text + si++);
      if (utf8byte == '\n') return virgin ? CastToIntOpinion::annul :
        CastToIntOpinion::commit;
      auto asciidigit = ^(char32_t u) { return 0x30 <= u && u < 0x40; };
      if (asciidigit(utf8byte)) { digit = (unsigned short)(utf8byte - '0');
        virgin = false; return CastToIntOpinion::accept; }
      if (utf8byte == U'-') return CastToIntOpinion::negate;
      if (utf8byte == 1) return virgin ? CastToIntOpinion::rejecting :
        CastToIntOpinion::commit;
      return CastToIntOpinion::rejecting; };
    
    auto strlen = ^(const char *s) { const char *p = s; while (*s) ++s; return s - p; };
    auto out = ^(const char * prefix, const AnnotatedRegister& reg) {
        int len = strlen(prefix); text += len;
        Opt<__builtin_int_t> regOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *regOpt) {
           Present(Termlog, reg, val);
        } else { fprintf(stderr, "Error presenting `%s`\n", prefix); }
    };
    
    extern AnnotatedRegister AR_Mips_Status;
    extern AnnotatedRegister AR_Mips_IntCtl;
    extern AnnotatedRegister AR_Mips_Cause;
    extern AnnotatedRegister AR_Mips_Config;
    extern AnnotatedRegister AR_Mips_Config1;
    extern AnnotatedRegister AR_Mips_Config3;
    extern AnnotatedRegister AR_Mips_Debug;
    
    struct Prefix { const char * prefix; const AnnotatedRegister& reg; } prefixes[] = {
      { "Status=", AR_Mips_Status },
      { "IntCtl=", AR_Mips_IntCtl },
      { "Cause=", AR_Mips_Cause },
      { "Config=", AR_Mips_Config },
      { "Config1=", AR_Mips_Config1 },
      { "Config3=", AR_Mips_Config3 },
      { "Debug=", AR_Mips_Debug },
      { NULL, AR_Mips_Debug } };
    
  //    if (IsPrefixOrEqual(mdb, "Debug=")) { out("Debug=", AR_Mips_Debug); }
  //    else { fprintf(stderr, "%s", text); }
    
    for (int i = 0; ; i++) {
     if (prefixes[i].prefix == NULL) { fprintf(stderr, "%s", text); return; }
     if (IsPrefixOrEqual(text, prefixes[i].prefix)) { out(prefixes[i].prefix, prefixes[i].reg); }
    }
    
    return;
    
    if (IsPrefixOrEqual(mdb, "Debug=")) { mdb += 6;
          Opt<__builtin_int_t> debugOpt = CastᵗˣᵗToInt(feeder);
          if (__builtin_int_t val = *debugOpt) {
             extern AnnotatedRegister AR_Mips_Debug;
             Present(Termlog, AR_Mips_Debug, val);
          } else { fprintf(stderr, "Error presenting `Debug`\n"); }
//    } else if (IsPrefixOrEqual(mdb, "Prid=")) { mdb += 5;
//        Opt<__builtin_int_t> pridOpt = CastᵗˣᵗToInt(feeder);
//        if (__builtin_int_t val = *pridOpt) {
//            extern AnnotatedRegister AR_Mips_Prid;
//           Present(Termlog, AR_Mips_Prid, val);
//        } else { fprintf(stderr, "Error presenting `Prid`\n"); }
    } else if (IsPrefixOrEqual(mdb, "Status=")) { mdb += 7;
        Opt<__builtin_int_t> statusOpt = CastᵗˣᵗToInt(feeder);
        if (__builtin_int_t val = *statusOpt) {
            extern AnnotatedRegister AR_Mips_Status;
           Present(Termlog, AR_Mips_Status, val);
        } else { fprintf(stderr, "Error presenting `Status`\n"); }
    }
//	>print /x IntCtl
//	IntCtl=0
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
    else fprintf(stderr, "%s", mdb);
}

#define ⁺⁼ProcessCommandline()                                              \
auto process_command_line = ^{ int j;                                       \
  for (j = 1; j < argc - 1 && argv[j][0] == '-'; j++) { fprintf(stderr,     \
    "Usage: %s %s\n", argv[0], "[ program.hex ]"); exit(1); }               \
  if (j != argc - 1) { hexfile = argv[j]; }                                 \
}; process_command_line(); /* Implicits in lambda expression: `hexfile`, `argc` and `argv`. */

int
main(
  int argc,
  const char * argv[]
)
{ /* stdin=0 (mdb output), stdout=1 () and stderr=2 (output to user) */
    int status = 0;
    int fd_p2c[2], fd_c2p[2]; int 🥈 maxline = 4096;
    ⁺⁼ProcessCommandline();
    fprintf(stderr, "pdb, revision %s (^-c to quit.)\n\n", SHA1GIT);
    if (pipe(fd_p2c) == -1 || pipe(fd_c2p) == -1) { fprintf(stderr,
      "pdb: Error when pipe\n"); exit(1); }
    pid_t pid = fork();
    if (pid == -1) { fprintf(stderr, "pdb: Error when fork\n"); exit(1); }
    if (pid) { int len; /* Parent */
        close(fd_p2c[0]); close(fd_c2p[1]);
        pid_t pid₂ = fork(); // Fiber instead.
        if (pid₂ == -1) { fprintf(stderr, "pdb: Error when child forks\n"); exit(1); }
/* Parent */ if (pid₂) { char output[maxline]; /* Reading text emitted on mdb's stdout */ 
           for (;;) {
              if ((len = read(fd_c2p[0], output, maxline)) < 0) { fprintf(
                stderr, "pdb: Error when reading mdb\n"); exit(1); }
              output[len] = '\x0'; mdbToUserscreen(output);
           }
/* Child */ } else { char keyput[maxline]; /* Collecting keyputs on stdin */
            while ((len = read(STDIN_FILENO, &keyput, maxline)) > 0) {
                keyput[len] = '\x0'; char mdbline[maxline];
                userkeysToMdb(keyput, mdbline);
                auto send = ^(int fd, char *s) {
                    int len = Utf8BytesUntilNull(s, BUILTIN_INT_MAX);
                    if (write(fd, s, len) != len) {
                        fprintf(stderr, "pdb: Error when writing to mdb\n");
                        exit(1);
                    }
                };
                send(fd_p2c[1], mdbline);
            }
        }
        
        close(fd_c2p[0]); close(fd_p2c[1]);
        /* waitpid(pid, &status, 0); */
        
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
        fprintf(stderr, "pdb: Starting %s\n", mdbpath);
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


