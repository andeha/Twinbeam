/*  main.cpp | controlling the pdb debugger. Compile with 'prompt% ninja'. */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <stdio.h> /* ⬷ code below assumes 'stdout' and 'stderr'. */

const char * hexfile=NULL;
const char * device_default="PIC32MZ2064DAB288"; /* "PIC32MZ2064DAH169" */
const char * mdbpath_default="/Applications/microchip/mplabx/v5.50/mplab_platform/bin/mdb.sh";
bool hw = true;

char8_t * stpcpy(char8_t * dst, const char * src) { while ((*dst++ = *src++)){} return --dst; }
void Output(const AnnotatedRegister& ar, uint32_t value, bool 𝟷𝟼bits);
  
inexorable
void
UserkeysToMdb(
  char * pdb, /* ⬷ text entered by the user. */
  char8_t * mdb
)
{
    if (IsPrefixOrEqual(pdb, "init")) {
        const char * device = device_default, *device₋env = getenv("PIC32DEVICE");
        if (device₋env) device = device₋env;
        fprintf(stderr, "pdb: starts initing device %s\n", device);
        char8_t * end=stpcpy(mdb, "device "); end=stpcpy(end, device); end=stpcpy(end, "\n");
        fprintf(stderr, "pdb: selecting %s\n", hw ? "hardware target" : "software simulator");
        if (hw) { end=stpcpy(end, "hwtool SK\n"); } else { end=stpcpy(end, "hwtool SIM\n"); }
        if (hexfile) {
          /* fprintf(stderr, "Programming %s\n", hexfile); end=stpcpy(end, "sleep 9000");
          end=stpcpy(end, "program '"); end=stpcpy(end, hexfile); end=stpcpy(end, "'\n"); */
          fprintf(stderr, "To program, enter program %s\n", hexfile);
        }
        fprintf(stderr, "Resetting\n");
        end=stpcpy(end, "reset MCLR\n");
    }
/* auto whitespace = ^(char32_t u) { return u == " "; }; // IsTerminatedBy */
/* Mips */
    else if (IsPrefixOrEqual(pdb, "index")) stpcpy(mdb, "print /d Index\n");
#include "input.cxx"
    else if (IsPrefixOrEqual(pdb, "cfgmpll")) stpcpy(mdb, "print /d cfgmpll\n");
    else stpcpy(mdb, pdb);
}

inexorable
void
MdbToUserscreen(
  char * mdb /* ⬷ Text emitted from mdb. */
)
{ 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 char *text=mdb; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 bool virgin = true; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int si = 0;
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
    /* todo: change to UTF8. */
    auto out = ^(const char * prefix, const AnnotatedRegister& reg) {
      int len = strlen(prefix); text += len;
      Opt<__builtin_int_t> regOpt = CastTˣᵗToInt(feeder);
      __builtin_int_t regval = *regOpt;
      if (regOpt) { Output(reg,regval,false); }
      else { fprintf(stderr, "Error presenting `%s`\n", prefix); }
    };
    
    extern AnnotatedRegister AR_Mips_Index;
#include "output₁.cxx"
    extern AnnotatedRegister AR_Mips_DSPControl;
    AnnotatedRegister AR_MipsOrMicrochip_LAST;
    
    struct Prefix { const char * prefix; const AnnotatedRegister& reg; }
     prefixes[] = {
      { "Index=", AR_Mips_Index },         { "Random=", AR_Mips_Random },
#include "output₂.cxx"
      { "devid=", AR_Microchip_DEVID },
      { NULL, AR_MipsOrMicrochip_LAST } };
    
    for (int i=0; ; ++i) {
      if (prefixes[i].prefix == NULL) { fprintf(stderr, "%s", text); return; }
      if (IsPrefixOrEqual(text, prefixes[i].prefix)) { out(prefixes[i].prefix, prefixes[i].reg); }
    }
}

#define ⁺⁼ProcessCommandline()                                              \
auto process_commandline = ^{ int j;                                        \
  for (j=1; j<argc && argv[j][0] == '-'; ++j) {                             \
    switch (argv[j][1]) {                                                   \
    case 'h': fprintf(stderr, "Usage: %s [ -s ] %s\n", argv[0],             \
      "[ program.hex ]"); exit(1);                                          \
    case 's': hw=false; break;                                              \
    default: fprintf(stderr, "Unknown command-line argument\n"); exit(2);   \
    }                                                                       \
  }                                                                         \
  if (j == argc - 1) { hexfile = argv[j]; }                                 \
}; process_commandline(); /* Implicits in lambda expression: `hexfile`, `argc` and `argv`. */

int
main(
  int argc,
  const char * argv[]
)
{ /* stdin=0 (mdb output), stdout=1 () and stderr=2 (output to user) */
    int status=0; int fd_p2c[2], fd_c2p[2]; int 🥈 maxline=4096;
    ⁺⁼ProcessCommandline();
    fprintf(stderr, "pdb, revision %s (^-c to quit.)\n\n", SHA1GIT);
    if (pipe(fd_p2c) == -1 || pipe(fd_c2p) == -1) { fprintf(stderr,
      "pdb: Error when pipe\n"); exit(1); }
    pid_t pid = fork();
    if (pid == -1) { fprintf(stderr, "pdb: Error when fork\n"); exit(1); }
    if (pid) { int len; /* Parent */
        close(fd_p2c[0]); close(fd_c2p[1]);
        pid_t pid₂ = fork(); /* Fiber instead. */
        if (pid₂ == -1) { fprintf(stderr, "pdb: Error when child forks\n"); exit(1); }
/* Parent */ if (pid₂) { char output[maxline]; /* ⬷ reading text emitted on mdb's stdout */ 
           for (;;) {
              if ((len = read(fd_c2p[0],output,maxline)) < 0) { fprintf(
                stderr, "pdb: Error when reading mdb\n"); exit(1); }
              output[len] = '\x0'; MdbToUserscreen(output);
           }
/* Child */ } else { char keyput[maxline]; /* ⬷ collecting keyputs on stdin. */
            while ((len = read(STDIN_FILENO,&keyput,maxline)) > 0) {
                keyput[len] = '\x0'; char8_t mdbline[maxline];
                UserkeysToMdb(keyput,mdbline);
                auto send = ^(int fd, char8_t * s) {
                    int len = Utf8BytesUntilNull(s,BUILTIN₋INT₋MAX);
                    if (write(fd,s,len) != len) {
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
        const char * mdbpath₋env = getenv("MDBPATH");
        if (mdbpath₋env) mdbpath = mdbpath₋env;
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


