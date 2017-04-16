#!/bin/bash
# freq -- compute word frequencies from standard input

PATH=/bin:/usr/bin

tr '[:upper:]' '[:lower:]' |
tr -sc '[:lower:]' '\n' |
sed '/^[ \t]*$/d' |
awk '
        {
            ++freq[$1]
        }
    END {
        for (word in freq) {
            printf("%-16s %d\n",word,freq[word])
        }
    }
' | sort --key=2nr --key=1 -