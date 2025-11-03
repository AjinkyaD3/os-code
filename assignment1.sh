#!/bin/bash

fileName="addressbook.txt"
opt=0

# This function is good and simple, so it stays.
addRecord() {
    echo -n "Enter Name: "
    read name
    echo -n "Enter Phone Number of $name: "
    read number
    echo -n "Enter Address of $name: "
    read address
    echo -e "$name\t$number\t\t$address" >> "$fileName"
}

# Loop until the user picks option 5 (Exit)
while [ "$opt" -ne 5 ]; do
    echo -e "\n--- Simple Address Book ---"
    echo "1. Create New Book (Erases old one!)"
    echo "2. View Book"
    echo "3. Add Record"
    echo "4. Delete Record"
    echo "5. Exit"
    echo -n "Enter your choice: "
    read opt

    case $opt in
        1) # Create / Overwrite
            echo -e "NAME\tNUMBER\t\tADDRESS" > "$fileName"
            echo "New book '$fileName' created. Now add one record:"
            addRecord
            ;;
        2) # View
            if [ ! -e "$fileName" ]; then
                echo "File not found. Use Option 1."
            else
                cat "$fileName"
            fi
            ;;
        3) # Add
            if [ ! -e "$fileName" ]; then
                echo "File not found. Use Option 1."
            else
                addRecord
            fi
            ;;
        4) # Delete
            if [ ! -e "$fileName" ]; then
                echo "File not found. Use Option 1."
            else
                echo -n "Enter Name or Number to delete: "
                read pattern
                # This is the "magic." It's one command, no temp file.
                # sed -i means "edit the file in-place."
                # "/$pattern/d" means "find the line with this pattern and delete it."
                sed -i "/$pattern/d" "$fileName"
                echo "Record deleted (if it existed)."
            fi
            ;;
        5) # Exit
            echo "Exiting."
            ;;
        *) # Default
            echo "Invalid choice. Try again."
            ;;
    esac
done
