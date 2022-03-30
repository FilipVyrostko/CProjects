# CProjects

## Topology Mapping 

Tools for looking up IP addresses for list of hostnames, cereating formatted files for dot package to create topology maps
1. *dnslookup.c* - C programm to look up IP addresses give a list of valid hostnames, uses Linux socket API
2. *parse_lookup.sh* - Bash script to parse output from *dnslookup*, for each IP addresses returned by lookup, run tracerout, storing result in IPv4.txt or IPv6.txt
3. *parse_files.py* - Python programm to parse IPv4.txt and IPv6.txt, for each tracerout, gourps IP addresses in pairs. Sorts files of pairs, concatines them together and adds opening and closing tags for dot package.

***How to run***: 
1. run parse_lookup.sh with list of valid hostnames
2. run parse_files.py producing 2 topology maps (IPv4 and IPv6) both as PDF files
