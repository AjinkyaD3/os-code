#!/bin/bash

fileName="addressbook.txt"
opt=0

addRecord() {
    echo -n "Enter Name: "
    read name
    echo -n "Enter Phone Number of $name: "
    read number
    echo -n "Enter Address of $name: "
    read address
    echo -e "$name\t$number\t\t$address" >> "$fileName"
}

while [ "$opt" -ne 6 ]; do
    echo -e "\n--- Address Book Menu ---"
    echo "1. Create a New Address Book"
    echo "2. View Records"
    echo "3. Insert New Record"
    echo "4. Delete a Record"
    echo "5. Modify a Record"
    echo "6. Exit"
    echo -n "Enter your choice: "
    read opt

    case $opt in
        1)
            echo -n "Enter new filename (or press Enter for $fileName): "
            read newFile
            [ -n "$newFile" ] && fileName="$newFile"
            [ -e "$fileName" ] && rm "$fileName" && echo "Removed existing file."
            echo -e "NAME\tNUMBER\t\tADDRESS" >> "$fileName"
            echo "New address book '$fileName' created with headers."
            cont=1
            while [ "$cont" -gt 0 ]; do
                addRecord
                echo -n "Enter 0 to Stop, 1 to Enter next: "
                read cont
            done
            ;;
        2)
            if [ -e "$fileName" ]; then
                echo -e "\n--- Address Book: $fileName ---"
                cat "$fileName"
            else
                echo "File not found! Please create an address book first (Option 1)."
            fi
            ;;
        3)
            if [ ! -e "$fileName" ]; then
                echo "File not found! Please create an address book first (Option 1)."
            else
                addRecord
                echo "Record inserted successfully!"
            fi
            ;;
        4)
            if [ ! -e "$fileName" ]; then
                echo "File not found! Please create an address book first (Option 1)."
            else
                echo -n "Enter Name or Phone Number to delete: "
                read pattern
                grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"
                echo "Record deleted (if found)."
            fi
            ;;
        5)
            if [ ! -e "$fileName" ]; then
                echo "File not found! Please create an address book first (Option 1)."
            else
                echo -n "Enter Name or Phone Number of record to modify: "
                read pattern
                if grep -q "$pattern" "$fileName"; then
                    grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"
                    echo "Record found. Enter new details:"
                    echo -n "Enter New Name: "
                    read name
                    echo -n "Enter New Phone Number of $name: "
                    read number
                    echo -n "Enter New Address of $name: "
                    read address
                    echo -e "$name\t$number\t\t$address" >> "$fileName"
                    echo "Record modified successfully!"
                else
                    echo "Record not found."
                fi
            fi
            ;;
        6) echo "Exiting program..." ;;
        *) echo "Invalid option! Please try again." ;;
    esac
done

