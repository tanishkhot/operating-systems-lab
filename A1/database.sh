#!/bin/bash

database="database.txt"

#echo "name:phone:city" >> "$database"

add_entry() {
    echo "Enter name:"
    read name
    echo "Enter phone number:"
    read phone
    echo "Enter Email"
    read email
    echo "Enter city:"
    read city

    echo "$name:$phone:$city" >> "$database"
    echo "Entry added to database."
}


search_entry(){
    echo "Enter name to search for:"
    read search_name

    found=0
    while IFS=: read -r name phone city; do         #This is Internal Field Separtor. separates fields according to : 
        if [ "$name" = "$search_name" ]; then
            echo "Name: $name, Phone: $phone, City: $city, Email: $email"
            found=1
        fi
    done < "$database"

    if [ $found -eq 0 ]; then
        echo "Entry not found."
    fi
}

modify_entry(){
    read -p "Enter the name of the reocrd that you want to alter: "
    if grep -q "$name" "$database"; then
        echo -e "Record found"
        echo -e "Current details: "
        grep "$name" "$database"
        sed -i "/$name/d" "$database"
        echo -e "Enter updated details: "
        add_entry
        return
    else   
        echo "Record not found"
        return
    fi
}

delete_entry(){
    read -p "Enter Name: " name
    if grep -q "$name" "$database"; then        #silent reading
        sed -i "/$name/d" "$database"           #deleting everything in that line   using /d    -i : make it case insenstitive
        echo "Record deleted"
    else
        echo "Record not found"
    fi
}



list_entries() {
    echo "Listing all entries:"
    while IFS=: read -r name phone city; do
        echo "Name: $name, Phone: $phone, City: $city, Email: $email"
    done < "$database"
}


while true; do
    echo "1. Add entry"
    echo "2. Search entry"
    echo "3. List all entries"
    echo "4. Delete"
    echo "5. Modify Entry"
    echo "6. Exit"
    read choice

    case $choice in
        1) add_entry ;;
        2) search_entry ;;
        3) list_entries ;;
        4) delete_entry ;;
        5) modify_entry ;;
        6) exit ;;
        *) echo "Invalid option. Please choose 1, 2, 3, or 4." ;;
    esac
done



