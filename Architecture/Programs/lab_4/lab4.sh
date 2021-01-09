#!/bin/bash
if test "$1" != "" 
then 
	echo "Number in 2-10 = $1"
	x=""
	len=${#1}
	correct=1
	eps=10
#sign check
	if test "${1:0:1}" = "-"
	then stop=1
	sign="-";
	elif test "${1:0:1}" = "+"
	then stop=1
	sign="";
	else stop=0
	sign="";
	fi
#finding the dot 
	l=$(($stop+1))
	while [ "${1:$l:1}" != "." ]&&[ "$l" -ne "$len" ];
	do
 	l=$(($l+1))
	done
#translating into decimal befor the dot 
	dot=$l
	while [ "$l" -gt "$stop" ];	do 
	case ${1:$((l-4)):4} in
	"0000") x='0'$x;;
	"0001") x='1'$x;;
	"0010") x='2'$x;;
	"0011") x='3'$x;;
	"0100") x='4'$x;;
	"0101") x='5'$x;;
	"0110") x='6'$x;;
	"0111") x='7'$x;;
	"1000") x='8'$x;;
	"1001") x='9'$x;;
	*) echo "Syntax error!"
	l=0
	correct=0;;
	esac;
	l=$(($l - 4));
	done
# translating number after the dot
	l=$(($dot+1))
	if test "$l" != $(($len+1))
	then 
	if test "${1:$(($len-1)):1}" = "." 
	then echo "Syntax error!" 
		correct=0;
	else x=$x'.';	
	fi
	fi 
	while [ "$l" -lt "$len" ];
	do
	case ${1:$l:4} in
	"0000") x=$x"0";;
	"0001") x=$x'1';;
	"0010") x=$x'2';;
	"0011") x=$x'3';;
	"0100") x=$x'4';;
	"0101") x=$x'5';;
	"0110") x=$x'6';;
	"0111") x=$x'7';;
	"1000") x=$x'8';;
	"1001") x=$x'9';;
	*) echo "Syntax error!"
	l=$len
	correct=0;;
	esac;
	l=$(($l + 4));
	done

# Input of decimal result
	if test "$correct" = 1
	then echo "Number in decimal = "$sign"$x";
	fi
# translating the first part into hexadecimal
	# dictionary of the hexadecimal
	dic='0123456789ABCDEF' 
	# for integer part
	reminder=0
	# for decimal part
	count=0
	# new dot in decimal
	new_dot=$(($dot / 4))
	# intger part of the number
	integer=${x:0:new_dot}
	# decimal part if the number
	decimal='0'
	decimal=$decimal${x:new_dot:${#x} - ${#integer}}
	# Results 
	result_d=""
	result_f=""

# translating whole part 
	while [[ $integer -gt 0 ]]; do
		remainder=$(($integer % 16))
        result_d=$result_d${dic:remainder:1}
        integer=$(($integer / 16))

	done

	result_d=$(echo $result_d | rev)

# translating the part after dot
	while [[ $count -lt $eps ]]; do
	 	decimal=$(echo $decimal*16 | bc)
	 	# echo "decimal1 $decimal"
	 	temp1=${decimal:0:1}
	 	temp2=${decimal:0:2}
	 	if [[ ${decimal:1:1} == "." ]]; then
	 		result_f=$result_f${dic:temp1:1}
	 		decimal=$(echo $decimal - $temp1 | bc)
	 	else 
	 		result_f=$result_f${dic:temp2:1}
	 		decimal=$(echo $decimal - $temp2 | bc)
	 	fi
	 	 # echo "decimal2 $decimal"
	 	count=$(($count + 1))
	 	# echo "result_f $result_f"
	done

	resut="$sign$result_d.$result_f"

	if test "$correct" = 1
	then echo "Number in hexadecimal = $resut";
	fi
	
fi