KEYCUT
======

A C Program that breaks an ASCII HEX string into smaller chunks with configurable chunk size and separator.
This program works by reading an ASCII string from STDIN, command line input or PIPEd STDIN and breaking this 
into substrings by inserting a separator ('chop') character at a specified interval (chop size). The modified
string is then copied to STDOUT. The default separator is the pipe symbol '|', but this can be changed to any 
printable character using the '-c' or '--chop' command line arg, e.g. keycut -c " ", will insert spaces at the 
chop interval. The chop interval defaults to 16 characters, but can be changed to any valid integer value using 
the '-s' or '--size' command line arg, e.g. keycut -s 4, will insert chop characters at 4 character intervals. 

EXAMPLES
--------
```
> keycut 0000000000000000FFFFBBBBCCCCEEEE
0000000000000000|FFFFBBBBCCCCEEEE

> keycut -c '/' -s 4 0000000000000000FFFFBBBBCCCCEEEE
0000/0000/0000/0000/FFFF/BBBB/CCCC/EEEE
```
INSTALLING
----------

See INSTALL for instructions on building and installing this program


