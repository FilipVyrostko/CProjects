#!/bin/bash


for ARG in "$@" # iterate over all arguments
do
    IFS=$'\n' read -rd '' -a lines <<<"$(./dnslookup ${ARG})" # parse output of ./dnslookup by "\n" and store in lines array

    printf "Tracerouting ${ARG}...\n"

    for line in "${lines[@]}"
    do
        IFS=' ' 
        read -ra strings <<< "$line"

        if [ "${strings[1]}" = "IPv4" ]
        then
            traceroute -4 -q 1 -n -m20 ${strings[2]} >> IPv4.txt

        elif [ "${strings[1]}" = "IPv6" ]
        then
            traceroute -6 -q 1 -n -m20 ${strings[2]} >> IPv6.txt

        else
            echo "Unexpected input: ${string[1]}"
            exit 1
        fi

    done

done

exit 0

