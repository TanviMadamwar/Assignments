#!/bin/sh
#FUNCTION TO INSERT RECORD
insert()
{
        echo "Enter Info \n  " 
        echo "ID \c : "
        aid=$((aid+1))
        echo "$aid"
        echo "Enter First Name : \c :  "
        read name 
        echo "Enter Last Name :\c : "
        read sname 
        echo "Enter city :\c : "        
        read city
        echo "Enter area :\c :"
        read area
        
        ok=0                                                    #TO CHECK 10 DIGIT MOBILE NUMBER
        while [ $ok = 0 ]
        do
            echo "Enter phone no. :\c :" 
            read phone
            if [ ${#phone} -ne 10 ]
            then
                echo "!!... Phone Number must be of 10 digits..!!"
            else
                ok=1
            fi
        done
        
        echo "Enter Pincode :\c : "
        read pin
        temp=`echo $pin|egrep '^[0-9]+$'`                     #TO CHECK WEATHER PIN IS NUMERIC OR NOT
        if [ $? -eq 0 ]; then
             record="$aid\t$name\t\t$sname\t\t$city\t\t\t$area\t\t\t$phone\t\t\t$pin"
             echo $record >> $filenm
        else
              echo "\nPincode should always be numeric"
              echo "\n!!....Insert data again......!!"  
        fi
        
}


#FUNCTION TO DISPLAY ADDRESS BOOK
display()
{ 
       echo "\nDisplay in sorted formatted by \n1.Pincode\n2.Name\n3.Address\nEnter your choice : "
       read choice
       echo "\n------------------------------------------------------------------------------------------------------------------------------------"
       echo "ID\tFName\t\tLName\t\tCity\t\t\tArea\t\t\tPhone No.\t\t\tPincode"
       echo "------------------------------------------------------------------------------------------------------------------------------------"
       case $choice in
       1) sort -k 7n $filenm ;;
       2) sort -k 2 $filenm ;;
       3) sort -k 4 $filenm ;;
       *) sort -k 2 $filenm ;;
       esac 
       echo "------------------------------------------------------------------------------------------------------------------------------------"
       
}

#FUNCTION TO SEARCH THE ADDRESS
search()
{
        echo "Enter ID to search: "
        read sid
        record=`grep "^$sid" "$filenm"`
        if [ $? -ne 0 ]; then
            echo "Address doesnt exist. "
        else
            echo "Address found"
            echo "\n------------------------------------------------------------------------------------------------------------------------------------"
            echo "\nID\tFName\t\tLName\t\tCity\t\t\tArea\t\t\tPhone No.\t\t\t\Pincode"
            echo "------------------------------------------------------------------------------------------------------------------------------------"
            echo $record
            echo "------------------------------------------------------------------------------------------------------------------------------------"
        fi
}

#FUNCTION TO DELETE A  RECORD
delete()
{
        echo "Delete By?\n1.ID\n2.Pincode\nEnter your choice :  "
        read choice
        case $choice in 
        
        1)  echo "Enter ID to delete: "                     #DELETE RECORD USING ID
            read sid
            record=`grep "^$sid" "$filenm"`
            if [ $? -ne 0 ]; then
                echo "ID doesnt exist. "
            else
                grep -v $sid $filenm>tmp
                mv tmp $filenm
                echo "Record is deleted"
            fi ;;
        
        
        2)  echo "Enter Picode to delete: "                 #DELETE ALL RECORDS OF ENTERED PINCODE
            read pin
            record=`sed -i "/$pin/p" "$filenm"`
            if [ $? -ne 0 ]; then
                echo "Pincode doesnt exist. "
            else
                grep -v $pin $filenm>tmp
                mv tmp $filenm
                echo "Record is deleted"
            fi ;;
       *) echo "\nInvalid choice" ;;
       esac
       
}

#FUNCTION TO MODIFY A RECORD
modify()
{
        
        echo "Enter ID to modify: "
        read sid
        grep "^$sid" $filenm > temp1.txt
        grep -v "^$sid" $filenm > temp2.txt
        mv temp2.txt $filenm
        if [ $? -ne 0 ]; 
        then
            echo "ID doesnt exist. "
        else
            name=`cut -d ";" -f2 "temp1.txt"`
            sname=`cut -d ";" -f3 "temp1.txt"`
            city=`cut -d ";" -f4 "temp1.txt"`
            area=`cut -d ";" -f5 "temp1.txt"`
            phone=`cut -d ";" -f6 "temp1.txt"`
            pin=`cut -d ";" -f7 "temp1.txt"`
            
            echo "Enter first name : "
            read name
            echo "Enter last name : " 
            read sname
            echo "Enter city : "
            read city
            echo "Enter area : "
            read area
            echo "Enter phone no. : "
            read phone
            echo "Enter pincode : "
            read pincode
            record="$sid\t$name\t\t$sname\t\t$city\t\t\t$area\t\t\t$phone\t\t\t$pincode"
            echo $record >> "$filenm"
            echo "Address is modified"
         fi
}

#MAIN PROGRAM
echo "Enter File Name : \c "
read filenm

touch $filenm
chmod u+x $filenm 

aid=0

#MENU FOR PERFORMING OPEARTIONS ON ADDRESS BOOK

while :
do

echo "\nMENU\n1.Insert Data\n2.Display Data\n3.Search Data\n4.Delete a Data\n5.Modify Data\n6.EXIT\nEnter Your Choice : \c"
read choice

case "$choice" in

    1) insert;;
        
    2) display ;;
    
    3) search;;
    
    4) delete;;
    
    5) modify;;
    
    6)  exit ;;
    
    *)  echo "Invalid Choice" ;;

esac
done
