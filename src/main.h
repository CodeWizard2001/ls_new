#ifndef MAIN_H
#define MAIN_H

#include "filesystem.h"
#include "threads.h"
#include "output.h"

#define HELP_TEXT \
"Usage: ls_new [OPTION]... [FILE]...\n\
List information about the FILEs (the current directory by default).\n\
Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -a, --all                  do not ignore entries starting with .\n\
  -A, --almost-all           do not list implied . and ..\n\
      --author               with -l, print the author of each file\n\
  -b, --escape               print C-style escapes for nongraphic characters\n\
      --block-size=SIZE      with -l, scale sizes by SIZE when printing them;\n\
                             e.g., '--block-size=M'; see SIZE format below\n\
\n\
  -B, --ignore-backups       do not list implied entries ending with ~\n\
  -c                         with -lt: sort by, and show, ctime (time of last\n\
                             change of file status information);\n\
                             with -l: show ctime and sort by name;\n\
                             otherwise: sort by ctime, newest first\n\
\n\
  -C                         list entries by columns\n\
      --color[=WHEN]         color the output WHEN; more info below\n\
  -d, --directory            list directories themselves, not their contents\n\
  -D, --dired                generate output designed for Emacs' dired mode\n\
  -f                         list all entries in directory order\n\
  -F, --classify[=WHEN]      append indicator (one of */=>@|) to entries WHEN\n\
      --file-type            likewise, except do not append '*'\n\
      --format=WORD          across -x, commas -m, horizontal -x, long -l,\n\
                             single-column -1, verbose -l, vertical -C\n\
\n\
      --full-time            like -l --time-style=full-iso\n\
  -g                         like -l, but do not list owner\n\
      --group-directories-first\n\
                             group directories before files;\n\
                             can be augmented with a --sort option, but any\n\
                             use of --sort=none (-U) disables grouping\n\
\n\
  -G, --no-group             in a long listing, don't print group names\n\
  -h, --human-readable       with -l and -s, print sizes like 1K 234M 2G etc.\n\
      --si                   likewise, but use powers of 1000 not 1024\n\
  -H, --dereference-command-line\n\
                             follow symbolic links listed on the command line\n\
      --dereference-command-line-symlink-to-dir\n\
                             follow each command line symbolic link\n\
                             that points to a directory\n\
\n\
      --hide=PATTERN         do not list implied entries matching shell PATTERN\n\
                             (overridden by -a or -A)\n\
\n\
      --hyperlink[=WHEN]     hyperlink file names WHEN\n\
      --indicator-style=WORD\n\
                             append indicator with style WORD to entry names:\n\
                             none (default), slash (-p),\n\
                             file-type (--file-type), classify (-F)\n\
\n\
  -i, --inode                print the index number of each file\n\
  -I, --ignore=PATTERN       do not list implied entries matching shell PATTERN\n\
  -k, --kibibytes            default to 1024-byte blocks for file system usage;\n\
                             used only with -s and per directory totals\n\
\n\
  -l                         use a long listing format\n\
  -L, --dereference          when showing file information for a symbolic\n\
                             link, show information for the file the link\n\
                             references rather than for the link itself\n\
\n\
  -m                         fill width with a comma separated list of entries\n\
  -n, --numeric-uid-gid      like -l, but list numeric user and group IDs\n\
  -N, --literal              print entry names without quoting\n\
  -o                         like -l, but do not list group information\n\
  -p, --indicator-style=slash\n\
                             append / indicator to directories\n\
  -q, --hide-control-chars   print ? instead of nongraphic characters\n\
      --show-control-chars   show nongraphic characters as-is (the default,\n\
                             unless program is 'ls' and output is a terminal)\n\
\n\
  -Q, --quote-name           enclose entry names in double quotes\n\
      --quoting-style=WORD   use quoting style WORD for entry names:\n\
                             literal, locale, shell, shell-always,\n\
                             shell-escape, shell-escape-always, c, escape\n\
                             (overrides QUOTING_STYLE environment variable)\n\
\n\
  -r, --reverse              reverse order while sorting\n\
  -R, --recursive            list subdirectories recursively\n\
  -s, --size                 print the allocated size of each file, in blocks\n\
  -S                         sort by file size, largest first\n\
      --sort=WORD            sort by WORD instead of name: none (-U), size (-S),\n\
                             time (-t), version (-v), extension (-X), width\n\
\n\
      --time=WORD            select which timestamp used to display or sort;\n\
                               access time (-u): atime, access, use;\n\
                               metadata change time (-c): ctime, status;\n\
                               modified time (default): mtime, modification;\n\
                               birth time: birth, creation;\n\
                             with -l, WORD determines which time to show;\n\
                             with --sort=time, sort by WORD (newest first)\n\
\n\
      --time-style=TIME_STYLE\n\
                             time/date format with -l; see TIME_STYLE below\n\
  -t                         sort by time, newest first; see --time\n\
  -T, --tabsize=COLS         assume tab stops at each COLS instead of 8\n\
  -u                         with -lt: sort by, and show, access time;\n\
                             with -l: show access time and sort by name;\n\
                             otherwise: sort by access time, newest first\n\
\n\
  -U                         do not sort; list entries in directory order\n\
  -v                         natural sort of (version) numbers within text\n\
  -w, --width=COLS           set output width to COLS.  0 means no limit\n\
  -x                         list entries by lines instead of by columns\n\
  -X                         sort alphabetically by entry extension\n\
  -Z, --context              print any security context of each file\n\
      --zero                 end each output line with NUL, not newline\n\
  -1                         list one file per line\n\
      --help        display this help and exit\n\
      --version     output version information and exit\n\
\n\
The SIZE argument is an integer and optional unit (example: 10K is 10*1024).\n\
Units are K,M,G,T,P,E,Z,Y,R,Q (powers of 1024) or KB,MB,... (powers of 1000).\n\
Binary prefixes can be used, too: KiB=K, MiB=M, and so on.\n\
\n\
The TIME_STYLE argument can be full-iso, long-iso, iso, locale, or +FORMAT.\n\
FORMAT is interpreted like in date(2).  If FORMAT is FORMAT1<newline>FORMAT2,\n\
then FORMAT1 applies to non-recent files and FORMAT2 to recent files.\n\
TIME_STYLE prefixed with 'posix-' takes effect only outside the POSIX locale.\n\
Also the TIME_STYLE environment variable sets the default style to use.\n\
\n\
The WHEN argument defaults to 'always' and can also be 'auto' or 'never'.\n\
\n\
Using color to distinguish file types is disabled both by default and\n\
with --color=never.  With --color=auto, ls emits color codes only when\n\
standard output is connected to a terminal.  The LS_COLORS environment\n\
variable can change the settings.  Use the dircolors(1) command to set it.\n\
\n\
Exit status:\n\
 0  if OK,\n\
 1  if minor problems (e.g., cannot access subdirectory),\n\
 2  if serious trouble (e.g., cannot access command-line argument).\n\
\n\
GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n\
Report any translation bugs to <https://translationproject.org/team/>\n\
Full documentation <https://www.gnu.org/software/coreutils/ls>\n\
or available locally via: info '(coreutils) ls invocation'\n"

// Struktur für Programmoptionen
typedef struct {
    int show_hidden;     // Flag für -a
    int detailed;        // Flag für -l
    int recursive;       // Flag für -r
    int threads;         // Flag für -t
    int sort_by_size;    // Flag für -S
    char path[512];      // Zielverzeichnis (Standard: aktuelles Verzeichnis)

} Options;


// Funktionen (falls spezifische Hauptfunktionen ausgegliedert werden sollen)
void parse_arguments(int argc, char *argv[], Options *opts);

#endif // MAIN_H
