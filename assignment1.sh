#!/bin/bash

file="addressbook.txt"

add_record() {
    echo -n "Name: "; read name
    echo -n "Phone: "; read phone
    
    grep -qw "$phone" "$file" 2>/dev/null && { 
        echo "Error: Phone number already exists. Record not added."
        return
    }

    echo -n "Address: "; read addr
    echo -e "$name\t$phone\t$addr" >> "$file"
    echo "Record added."
}

while true; do
    echo -e "\n--- Address Book ---"
    echo "1) Create New Address Book"
    echo "2) View Address Book"
    echo "3) Insert Record"
    echo "4) Delete Record"
    echo "5) Modify Record"
    echo "6) Exit"
    echo -n "Enter choice: "
    read ch

    case $ch in
        1) echo -e "NAME\tPHONE\tADDRESS" > "$file"
           echo "Address Book Created." ;;

        2) [ -e "$file" ] && cat "$file" || echo "No address book found." ;;

        3) [ -e "$file" ] && add_record || echo "Create address book first." ;;

        4) if [ -e "$file" ]; then
               echo -n "Enter Name/Phone to delete: "; read key
               sed -i "/$key/d" "$file"
               echo "Record deleted (if existed)."
           else echo "Create address book first."
           fi ;;

        5) if [ -e "$file" ]; then
               echo -n "Enter Name/Phone to modify: "; read key
               sed -i "/$key/d" "$file"
               echo "Enter new details:"
               add_record
               echo "Record modified."
           else echo "Create address book first."
           fi ;;

        6) echo "Goodbye!"; exit ;;

        *) echo "Invalid choice." ;;
    esac
done
