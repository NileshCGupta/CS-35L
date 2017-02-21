#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import sys, locale
from optparse import OptionParser

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE
`
Output results of comparing FILE1 and FILE2."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",  action="store_true", 
                      dest="col_one", default=False,
                      help="suppress column one (lines unique to FILE1)")
    parser.add_option("-2",  action="store_true", 
                      dest="col_two", default=False,
                      help="suppress column two (lines unique to FILE2)")
    parser.add_option("-3",  action="store_true", 
                      dest="col_three", default=False,
                      help="suppress column three (common lines)")
    parser.add_option("-u",  action="store_true", 
                      dest="unsorted", default=False,                        
                      help="suppress column one (lines unique to ONE)")
    
    options, args = parser.parse_args(sys.argv[1:])

    # there must be two files to compare
    if len(args) != 2:
        parser.error("Error: missing operand(s)")
    
    indent1 = ""
    indent2 = ""

    # set appropriate tabs
    if options.col_one == False:
        indent1 = "\t"
    if options.col_two == False:
        indent2 = "\t"

    f1 = ""
    f2 = ""
    lines1 = ""
    lines2 = ""

    # checks for stdin input in either the first or second argument
    if args[0] == "-":
        f2 = open(args[1], 'r')
        lines2 = f2.read().splitlines()
        f2.close()
        lines1 = sys.stdin.read().splitlines()
    elif args[1] == "-":
        f1 = open(args[0], 'r')
        lines1 = f1.read().splitlines()
        f1.close()
        lines2 = sys.stdin.read().splitlines()
    else:
        f1 = open(args[0], 'r')
        lines1 = f1.read().splitlines()
        f1.close()
        f2 = open(args[1], 'r')
        lines2 = f2.read().splitlines()
        f2.close()

    count1 = 0
    count2 = 0

    total = len(lines1) + len(lines2)
    
    # unsorted option uses brute force search with nested for loops
    if options.unsorted == True:
        for line in lines1:
            if line in lines2:
                if options.col_three == False:
                    sys.stdout.write(indent1)
                    sys.stdout.write(indent2)
                    sys.stdout.write(line)
                    sys.stdout.write("\n")
                lines2.remove(line)
            else:
                if options.col_one == False:
                    sys.stdout.write(line)
                    sys.stdout.write("\n")
        for curline in lines2:
            if options.col_two == False:
                sys.stdout.write(indent1)
                sys.stdout.write(curline)
                sys.stdout.write("\n")
    
    # sorted option uses two pointers to each lines file
    # compare the two pointer values 
    # if not equal, print item with alphabetical priority  and inc respective count
    # if equal, print item and inc both counts
    else:
        for i in range(total):
            if count1 < len(lines1) and count2 < len(lines2):
                if locale.strcoll(lines1[count1], lines2[count2]) < 0:
                    if options.col_one == False:
                        sys.stdout.write(lines1[count1])
                        sys.stdout.write("\n")
                    count1 += 1
                elif locale.strcoll(lines1[count1], lines2[count2]) > 0:
                    if options.col_two == False:
                        sys.stdout.write(indent1)
                        sys.stdout.write(lines2[count2])
                        sys.stdout.write("\n")
                    count2 += 1
                else:
                    if options.col_three == False:
                        sys.stdout.write(indent1)
                        sys.stdout.write(indent2)
                        sys.stdout.write(lines1[count1])
                        sys.stdout.write("\n")
                    count1 += 1
                    count2 += 1
        # prints residual items
        if options.col_one == False:
            while count1 < len(lines1):
                sys.stdout.write(lines1[count1] + "\n")
                count1 += 1
        if options.col_two == False:
            while count2 < len(lines2):
                sys.stdout.write(indent1)
                sys.stdout.write(lines2[count2] + "\n")
                count2 += 1
        
if __name__ == "__main__":
    main()
