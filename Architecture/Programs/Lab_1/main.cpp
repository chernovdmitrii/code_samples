//Перевести из двоично-десятичной в шестнадцатеричную

#include <iostream>
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

// Global variables
const char file_in[] = "input.txt";
const char file_out[] = "output.txt";
int eps = 10;

//Functions
bool checkInput(string);

string toDecimal(const string &);

string hexadecimal(int, double);

tuple<int, double> parseNumber(string);


int main() {

    ifstream input(file_in);
    ofstream output(file_out);
    string data;

    if (!input) {
        cerr << "Error: no such file or directory: " << file_in << endl;
        return -1;
    }

    cout << "Enter number of digits after the decimal point: ";
    cin >> eps;

    while (getline(input, data)) {

        if (!checkInput(data)) {
            output << "Number [" << data << "] is in incorrect format. Thus, it cannot be processed! " << endl;
            continue;
        }

        string digit = toDecimal(data);
        tuple<int, double> digit_div = parseNumber(digit);
        string result = hexadecimal(get<0>(digit_div), get<1>(digit_div));
        output << result << endl;
    }

    input.close();
    output.close();

    return 0;
}

bool checkInput(string number) {
    int count_dot = 0;
    int count_0 = 0;
    int count_1 = 0;

    for (const auto &item : number) {
        switch (item) {
            case '.':
                count_dot++;
                break;
            case '0':
                count_0++;
                break;
            case '1':
                count_1++;
                break;
        }
    }

    if (count_dot > 1) {
        return false;
    } else if (number.substr(0, number.find('.')).length() % 4 != 0) {
        return false;
    } else if (number.substr(number.find('.') + 1).length() % 4 != 0) {
        return false;
    } else {
        return number.length() == (count_dot + count_0 + count_1);
    }
}

string toDecimal(const string &number) {
    int count = 0;
    string temp;
    string digits;

    for (int i = 0; i < number.length(); ++i) {
        if (count == 4) {
            //From 2-10 to 10
            digits += to_string((temp[0] - 48) * 8 + (temp[1] - 48) * 4 + (temp[2] - 48) * 2 + (temp[3] - 48));

            //Nullifying
            temp = "";
            count = 0;
        }

        if (number[i] == '.') {
            digits += '.';
            continue;
        }

        temp += number[i];
        count++;

        if (i == number.length() - 1) {
            digits += to_string((temp[0] - 48) * 8 + (temp[1] - 48) * 4 + (temp[2] - 48) * 2 + (temp[3] - 48));
        }
    }
    return digits;
}

tuple<int, double> parseNumber(string data) {
    const char delimiter = '.';
    string integer;
    string decimal ;

    if(data.find(delimiter) != string::npos){
        integer = data.substr(0, data.find(delimiter));
        decimal = '0' + data.substr(data.find(delimiter));
    } else {
        integer = data;
        decimal = '0';
    }

    return {stoi(integer), stod(decimal)};
}

string hexadecimal(int integer, double decimal) {
    // Dictionary
    const char hex[] = "0123456789ABCDEF";
    int remainder;
    int count = 0;
    string result_d;
    string result_f;

    //Dealing with integer part
    if (integer == 0) {
        result_d += '0';
    } else {
        while (integer > 0) {
            remainder = integer % 16;
            result_d += hex[remainder];
            integer = integer / 16;
        }
    }

    reverse(result_d.begin(), result_d.end());

    //Dealing with decimal part
    while (count < eps) {
        decimal *= 16;
        result_f += to_string((int) decimal);
        decimal -= int(decimal);
        count++;
    }
    return result_d + '.' + result_f;
}
