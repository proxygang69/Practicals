#!/bin/bash

file="Employee_Record.txt"

# Check if file exists
if [ ! -e "$file" ]; then
    echo "File does not exist. Creating file: $file"
    touch "$file"
else
    echo "File already exists."
fi

# Main program loop
while true; do
    echo -e "\nEmployee Record Management\n"
    echo "1. View File"
    echo "2. Insert Record"
    echo "3. Delete Record"
    echo "4. Calculate Gross Pay"
    echo "5. Exit"

    read -p "Enter Choice: " choice

    case $choice in
        1)
            echo "Contents of $file:"
            cat "$file"
            ;;
        2)
            read -p "Enter Employee ID: " id
            read -p "Enter Name: " name
            read -p "Enter Designation: " designation
            read -p "Enter Basic Pay: " bpay

            echo "$id | $name | $designation | $bpay" >> "$file"
            echo "Record inserted successfully."
            ;;
        3)
            read -p "Enter Employee ID to delete: " id

            if grep -i "$id" "$file"; then
                sed -i "/$id/d" "$file"
                echo "Record deleted successfully."
            else
                echo "Record not found."
            fi
            ;;
        4)
            read -p "Enter Employee ID: " id

            if grep -i "$id" "$file"; then
                bpay=$(grep -i "$id" "$file" | awk -F ' \| ' '{print $4}')
                gross_pay=$(echo "scale=2; $bpay * 1.2" | bc)
                echo "Gross Pay for Employee ID $id: $gross_pay"
            else
                echo "Record not found."
            fi
            ;;
        5)
            echo "Exiting program."
            exit
            ;;
        *)
            echo "Invalid Choice"
            ;;
    esac
done
