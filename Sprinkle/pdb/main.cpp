/*  main.cpp | controlling the mdb debugger. */

#include <Twinbeam.h>
#include <Additions/Additions.h> /* ⬷ import Twinbeam. */
#include <stdio.h> /* ⬷ code below assumes 'stdout' and 'stderr'. */
#include "all-regs.h"

/* To compile enter 'prompt% ninja'. */

struct Prefix {
const char * prefix;
const AnnotatedRegister& reg;
};

enum class Registerset { pic32mzda, pic32mm };

struct {
 Registerset registers;
 const char *device, *mdbpath;
} defaults {
 Registerset::pic32mzda, /* ⬷ note multiple images via 'fork'. */
 "PIC32MZ2064DAB288", /* PIC32MZ2064DAH169, PIC32MM0064GPL036 */ 
 "/Applications/microchip/mplabx/v5.50/mplab_platform/bin/mdb.sh"
};

const char * hexfile=NULL, *cmdfile=NULL; bool hw=true;

char8_t * stpcpy(char8_t * dst, const char * src) { while ((*dst++ = *src++)) {
} return --dst; }

inexorable Registerset Selected()
{
  Registerset regset = defaults.registers;
  const char * device = getenv("__PDB_CURRDEV");
  if (device == NULL) { fprintf(stderr, "pdb: environment error\n"); }
  if (IsPrefixOrEqual(device,"PIC32MZ")) { regset = Registerset::pic32mzda; }
  if (IsPrefixOrEqual(device,"PIC32MM")) { regset = Registerset::pic32mm; }
  return regset;
}

inexorable const char * Device()
{
   const char * device = defaults.device, *device₋env = getenv("PIC32DEVICE");
   if (device₋env) device = device₋env;
   if (setenv("__PDB_CURRDEV",device,1)) {
     fprintf(stderr, "pdb: environment error\n"); exit(1); }
   return device;
}

inexorable
void
UserkeyedToMdb(
  char * pdb, /* ⬷ text entered by the user. */
  char8_t * mdb
)
{
    if (IsPrefixOrEqual(pdb,"init")) { const char * device = Device(); 
      fprintf(stderr, "pdb: starts initing device %s\n", device);
      char8_t * end=stpcpy(mdb,"device "); end=stpcpy(end,device); 
      end=stpcpy(end,"\n"); fprintf(stderr, "pdb: selecting %s\n", 
      hw ? "hardware target" : "software simulator");
      if (hw) { end=stpcpy(end,"hwtool SK\n"); }
      else { end=stpcpy(end,"hwtool SIM\n"); }
      if (hexfile) {
        fprintf(stderr,"Programming %s\n",hexfile); end=stpcpy(end,"sleep 9000\n");
        end=stpcpy(end,"program '"); end=stpcpy(end,hexfile); end=stpcpy(end,"'\n");
      }
      if (hw) { fprintf(stderr,"Resetting\n"); end=stpcpy(end,"reset MCLR\n"); }
      return;
    } /* To reprogram, enter 'init' at pdb prompt. */
    Registerset regset = Selected();
    switch (regset) {
    case Registerset::pic32mm:
      if (IsPrefixOrEqual(pdb, "userlocal")) stpcpy(mdb, "print /d UserLocal\n");
#include "input-mm.cxx"
      else if (IsPrefixOrEqual(pdb, "ancfg")) stpcpy(mdb, "print /d Ancfg\n");
      else stpcpy(mdb,pdb);
    break; case Registerset::pic32mzda:
      if (IsPrefixOrEqual(pdb, "index")) stpcpy(mdb, "print /d Index\n");
#include "input-mz.cxx"
      else if (IsPrefixOrEqual(pdb, "cfgmpll")) stpcpy(mdb, "print /d cfgmpll\n");
      else stpcpy(mdb,pdb);
    }
}

AnnotatedRegister AR_MipsOrMicrochip_LAST;

Prefix mm_prefixes[] = {
  { "Config=", AR_MipsMM_Config },
#include "parse-mm.cxx"
  { NULL, AR_MipsOrMicrochip_LAST }
};

Prefix mz_prefixes[] = {
  { "Index=", AR_Mips_Index },
  { "Random=", AR_Mips_Random },
#include "parse-mz.cxx"
  { "devid=", AR_Microchip_DEVID },
  { NULL, AR_MipsOrMicrochip_LAST }
};

inexorable
void
MdbToUserscreen(
  char * mdb /* ⬷ text emitted from mdb. */
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
    
    auto strlen = ^(const char *s) { const char *p = s; while (*s) ++s; 
     return s - p; };
    
    auto out = ^(const char * prefix, const AnnotatedRegister& reg) {
      int len = strlen(prefix); text += len;
      Opt<__builtin_int_t> regOpt = CastTˣᵗToInt(feeder);
      __builtin_int_t regval = *regOpt;
      void Output(const AnnotatedRegister& ar, uint32_t value, bool 𝟷𝟼bits);
      if (regOpt) { Output(reg,regval,false); }
      else { fprintf(stderr, "Error presenting `%s`\n", prefix); }
    };
    
    Registerset regset = Selected();
    
    Prefix * transl = NULL; switch (regset) {
    case Registerset::pic32mm: transl=mm_prefixes; break;
    case Registerset::pic32mzda: transl=mz_prefixes; break;
    }
    
    for (int i=0; ; ++i) { if (transl[i].prefix == NULL) { fprintf(stderr, 
   "%s", text); return; } if (IsPrefixOrEqual(text,transl[i].prefix)) { 
      out(transl[i].prefix,transl[i].reg); }
    }
}

#define ⁺⁼ProcessCommandline()                                              \
auto process_commandline = ^{ int j;                                        \
  for (j=1; j<argc && (argv[j][0] == '-' || argv[j][0] == '@'); ++j) {      \
    if (argv[j][0] == '@' && argv[j][1] != '\x0') { cmdfile=&(argv[j][1]);  \
     continue; }                                                            \
    switch (argv[j][1]) {                                                   \
    case 'h': fprintf(stderr, "Usage: %s [ -s ] [ %s ] %s\n", argv[0],      \
     "@commandfile", "[ program.hex ]"); exit(1);                           \
    case 's': hw=false; break;                                              \
    default: fprintf(stderr, "Unknown command-line argument\n"); exit(2);   \
    }                                                                       \
  }                                                                         \
  if (j == argc - 1) { hexfile = argv[j]; }                                 \
}; process_commandline();

int
main(
  int argc,
  const char * argv[]
)
{ /* stdin=0 (mdb output), stdout=1 () and stderr=2 (output to user) */
    int status=0; int fd_p2c[2], fd_c2p[2]; int 🥈 maxline=4096; 
    ⁺⁼ProcessCommandline(); const char * device = Device();
    fprintf(stderr, "pdb (%s), revision %s (^-c to quit.)\n\n", device, SHA1GIT);
    if (pipe(fd_p2c) == -1 || pipe(fd_c2p) == -1) { fprintf(stderr,
      "pdb: Error when pipe\n"); exit(1); }
    pid_t pid = fork();
    if (pid == -1) { fprintf(stderr, "pdb: Error when fork\n"); exit(1); }
    if (pid) { int len; /* Parent ⤐ */ 
        close(fd_p2c[0 /* ⬷ not STDIN_FILENO! */]);
        close(fd_c2p[1 /* ⬷ not STDOUT_FILENO! */]);
        /* when 'left is fd_p2c STDOUT_FILENO, fd_p2c STDERR_FILENO, 
          fd_c2p STDIN_FILENO and fd_c2p STDERR_FILENO': */
   // close(fd_p2c[2]); close(fd_c2p[2]);
        pid_t pid₂ = fork();
        if (pid₂ == -1) { fprintf(stderr, "pdb: Error when child forks\n"); exit(1); }
/* parent */ if (pid₂) { char output[maxline]; /* ⬷ reading text emitted on mdb's stdout */ 
          for (;;) {
            if ((len = read(fd_c2p[0],output,maxline)) < 0) { fprintf(
             stderr, "pdb: Error when reading mdb\n"); exit(1); }
            output[len] = '\x0'; MdbToUserscreen(output);
          }
/* child */ } else { char keytext[maxline]; /* ⬷ collecting keyputs on stdin. */
          char8_t mdbline[maxline];
          auto send = ^(int fd, char8_t * s) {
           int len = Utf8BytesUntilNull(s,BUILTIN₋INT₋MAX);
           if (write(fd,s,len) != len) {
             fprintf(stderr, "pdb: Error when writing to mdb\n");
             exit(1);
           } };
          const char * startup = "init\n"; int stdout₋term = fd_p2c[1];
          UserkeyedToMdb((char *)startup,mdbline); send(stdout₋term,mdbline);
          while ((len = read(STDIN_FILENO,&keytext,maxline)) > 0) {
            keytext[len] = '\x0'; 
            UserkeyedToMdb(keytext,mdbline);
            send(stdout₋term,mdbline);
          }
       }
       
       close(fd_c2p[0]); close(fd_p2c[1]);
       /* waitpid(pid, &status, 0); */
       
    } else { /* Child ⤐ */
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
       const char * mdbpath = defaults.mdbpath;
       const char * mdbpath₋env = getenv("MDBPATH");
       if (mdbpath₋env) mdbpath = mdbpath₋env;
       fprintf(stderr, "pdb: Starting %s\n", mdbpath);
       /* if (cmdfile) { "loadscript ./target_mz" } */
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


