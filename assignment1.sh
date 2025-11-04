#!/bin/bash # use bash shell
# Problem Statement 1:
# Write a program to implement an address book with options:
# a) Create address book
# b) View address book
# c) Insert a record
# d) Delete a record
# e) Modify a record
# f) Exit

fileName="addressbook.txt" # data file name
opt=0 # menu option variable

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
    echo -e "\n--- Address Book ---" # title
    echo "1. Create New Address Book (erases old)" # create
    echo "2. View Address Book" # view
    echo "3. Insert a Record" # insert
    echo "4. Delete a Record" # delete
    echo "5. Modify a Record" # modify
    echo "6. Exit" # exit
    echo -n "Enter your choice: " # ask choice
    read opt # read choice

    case $opt in
     
        1) echo -e "NAME\tNUMBER\t\tADDRESS" > "$fileName"; echo "Created $fileName" ;; # create

        2) if [ -e "$fileName" ]; then cat "$fileName"; else echo "No file. Use option 1."; fi ;; # view

        3) if [ -e "$fileName" ]; then addRecord; else echo "No file. Use option 1."; fi ;; # insert

        4) if [ -e "$fileName" ]; then echo -n "Enter Name/Number to delete: "; read k; sed -i "/$k/d" "$fileName"; echo "Deleted (if matched)."; else echo "No file. Use option 1."; fi ;; # delete

        5) if [ -e "$fileName" ]; then echo -n "Enter Name/Number to modify: "; read k; sed -i "/$k/d" "$fileName"; echo "Enter new details:"; addRecord; echo "Modified."; else echo "No file. Use option 1."; fi ;; # modify
        
        6) echo "Exiting." ;; # exit
        *) echo "Invalid choice." ;; # default
    esac
done
