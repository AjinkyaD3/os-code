#!/bin/bash # use bash shell

fileName="addressbook.txt" # data file name
opt=0 # menu option variable

# show quick demo of basic linux commands (Part A)
demoCommands() {
    echo "[echo] Hello" # print text
    echo "[ls]"; ls # list files
    echo -n "[read] Enter a word: "; read w; echo "you typed: $w" # read user input
    echo "[touch] making demo.txt"; touch demo.txt # create empty file
    echo "demo" > demo.txt # write into file
    echo "[cat] show file"; cat demo.txt # print file
    if [ -f demo.txt ]; then echo "[test] demo.txt exists"; fi # test file exists
    for i in 1 2 3; do echo "[loop] i=$i"; done # simple loop
    a=5; b=3; if [ $a -gt $b ]; then echo "[arith] $a > $b"; fi # comparison
    echo -e "red\nblue\nred" > colors.txt # make sample lines
    echo "[grep] lines with red:"; grep red colors.txt # grep match
    echo "[sed] replace red->green:"; sed 's/red/green/g' colors.txt # sed replace
}

# add one address record (Part B)
addRecord() {
    echo -n "Enter Name: " # ask name
    read name # read name
    echo -n "Enter Phone Number of $name: " # ask phone
    read number # read phone
    echo -n "Enter Address of $name: " # ask address
    read address # read address
    echo -e "$name\t$number\t\t$address" >> "$fileName" # append to file
}

# loop menu until Exit
while [ "$opt" -ne 6 ]; do
    echo -e "\n--- Assignment 1 ---" # title
    echo "0. Demo basic Linux commands" # Part A
    echo "1. Create New Address Book (erases old)" # create
    echo "2. View Address Book" # view
    echo "3. Insert a Record" # insert
    echo "4. Delete a Record" # delete
    echo "5. Modify a Record" # modify
    echo "6. Exit" # exit
    echo -n "Enter your choice: " # ask choice
    read opt # read choice

    case $opt in
        0) demoCommands ;; # run demo
        1) echo -e "NAME\tNUMBER\t\tADDRESS" > "$fileName"; echo "Created $fileName" ;; # create
        2) if [ -e "$fileName" ]; then cat "$fileName"; else echo "No file. Use option 1."; fi ;; # view
        3) if [ -e "$fileName" ]; then addRecord; else echo "No file. Use option 1."; fi ;; # insert
        4) if [ -e "$fileName" ]; then echo -n "Enter Name/Number to delete: "; read k; sed -i "/$k/d" "$fileName"; echo "Deleted (if matched)."; else echo "No file. Use option 1."; fi ;; # delete
        5) if [ -e "$fileName" ]; then echo -n "Enter Name/Number to modify: "; read k; sed -i "/$k/d" "$fileName"; echo "Enter new details:"; addRecord; echo "Modified."; else echo "No file. Use option 1."; fi ;; # modify
        6) echo "Exiting." ;; # exit
        *) echo "Invalid choice." ;; # default
    esac
done
