#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>


using namespace std;

// Global variables
const char file_in[] = "input.txt";
const char file_out[] = "output.txt";
const int precision = 11;
int count_equ = 1;

//Functions
bool checkInput(string);
pair<string, string> Parse(string);
tuple<int, double, bool> parseNumber(string);
string toQuaternary(int, double);
void Correction(string &, string &);
pair<vector<int>, vector<int>> toVectorReversed(string, string);
string Multiplication(vector<int>, vector<int>, int, int, bool);
double toDecimal(string);
void outputFile(ofstream &, string, string, string, string, string);


int main() {

    ifstream input(file_in);
    ofstream output(file_out);
    string data;
    bool minus;

    if (!input) {
        cerr << "Error: no such file or directory: " << file_in << endl;
        return -1;
    }


    while (getline(input, data)) {

        string first_raw = Parse(data).first;
        string second_raw = Parse(data).second;

        if (!checkInput(first_raw) or !checkInput(second_raw)) {
            output << "--------------------------------- Error --------------------------------" << endl;
            output << "Number [" << data << "] is in incorrect format. Thus, it cannot be processed! " << endl;
            continue;
        }

        tuple<int, double, bool> first_number = parseNumber(first_raw);
        tuple<int, double, bool> second_number = parseNumber(second_raw);

        if (get<2>(first_number) && get<2>(second_number)) {
            minus = false;
        } else if (!get<2>(first_number) && !get<2>(second_number)) {
            minus = false;
        } else {
            minus = true;
        }

        string first = toQuaternary(get<0>(first_number), get<1>(first_number));
        string second = toQuaternary(get<0>(second_number), get<1>(second_number));

        Correction(first, second);

        pair<vector<int>, vector<int>> number = toVectorReversed(first, second);

        string result = Multiplication(number.first, number.second, 4, precision, minus);

        outputFile(output, result, first_raw, second_raw, first, second);

    }

    input.close();
    output.close();

    return 0;
}

pair<string, string> Parse(string data) {
    string first = data.substr(0, data.find(' '));
    string second = data.substr(data.find(' ') + 1);

    return {first, second};
}

bool checkInput(string number) {
    int count_dot = 0;
    int cout_minus = 0;
    int cout_space = 0;
    int count_numbers = 0;

    for (const auto &item : number) {
        switch (item) {
            case '.': count_dot++; break;
            case '-': cout_minus++; break;
            case ' ': cout_space++; break;
            case '0': count_numbers++; break;
            case '1': count_numbers++; break;
            case '2': count_numbers++; break;
            case '3': count_numbers++; break;
            case '4': count_numbers++; break;
            case '5': count_numbers++; break;
            case '6': count_numbers++; break;
            case '7': count_numbers++; break;
            case '8': count_numbers++; break;
            case '9': count_numbers++; break;
        }
    }
    if (cout_space != 0) {
        return false;
    } else if (count_dot > 1) {
        return false;
    } else if (cout_minus > 1) {
        return false;
    } else {
        return number.size() == (count_dot + count_numbers + cout_space + cout_minus);
    }
}

tuple<int, double, bool> parseNumber(string data) {
    const char delimiter = '.';
    const char minus_c = '-';
    string integer;
    string decimal;
    bool minus = false;

    if (data.find(delimiter) != string::npos) {
        if (data.find(minus_c) != string::npos) {
            minus = true;
            integer = data.substr(1, data.find(delimiter));
            decimal = '0' + data.substr(data.find(delimiter));
        } else {
            integer = data.substr(0, data.find(delimiter));
            decimal = '0' + data.substr(data.find(delimiter));
        }
    } else {
        integer = data;
        decimal = '0';
    }

    return {stoi(integer), stod(decimal), minus};
}

string toQuaternary(int integer, double decimal) {
    int remainder;
    int count = 0;
    string result_i;
    string result_d;

    if (integer == 0) {
        result_i += '0';
    } else {
        while (integer > 0) {
            remainder = integer % 4;
            result_i += to_string(remainder);
            integer /= 4;
        }
    }

    reverse(result_i.begin(), result_i.end());

    while (count < precision) {
        decimal *= 4;
        result_d += to_string((int) decimal);
        decimal -= int(decimal);
        count++;
    }

    return result_i + '.' + result_d;
}

void Correction(string &first, string &second) {
    int size_one = first.substr(0, first.find('.')).size();
    int size_two = second.substr(0, second.find('.')).size();
    int difference = abs(size_one - size_two);

    if (size_one == size_two) {
        return;
    } else if (size_one > size_two) {
        do {
            second.insert(second.begin(), '0');
            --difference;
        } while (difference > 0);
    } else {
        do {
            first.insert(first.begin(), '0');
            --difference;
        } while (difference > 0);
    }
}

pair<vector<int>, vector<int>> toVectorReversed(string first, string second) {
    vector<int> result_one;
    vector<int> result_two;
    for (int i = 0; i < first.size(); ++i) {
        if (first[i] != '.') {
            result_one.push_back(first[i] - '0');
        }
    }

    for (int i = 0; i < second.size(); ++i) {
        if (second[i] != '.') {
            result_two.push_back(second[i] - '0');
        }
    }

    reverse(result_one.begin(), result_one.end());
    reverse(result_two.begin(), result_two.end());

    return {result_one, result_two};
}

string Multiplication(vector<int> first, vector<int> second, int base, int point, bool minus) {
    int length = first.size() + second.size() + 1;
    vector<int> result(length, 0);
    string answer;
    int position = 0;

    for (int i = 0; i < first.size(); i++) {
        for (int j = 0; j < second.size(); j++) {
            result[i + j] += first[i] * second[j];
            result[i + j + 1] = result[i + j + 1] + result[i + j] / base;
            result[i + j] %= base;
        }
    }

    for (int k = 0; k < result.size(); ++k) {
        answer.push_back('0' + result[k]);
        if (k == point * 2 - 1) {
            answer.push_back('.');
        }
    }

    reverse(answer.begin(), answer.end());

    for (int k = 0; k < answer.size(); ++k) {
        if (answer[k] != '0') {
            break;
        }
        position++;
    }
    answer.erase(0, position);

    if (minus) {
        answer.insert(answer.begin(), '-');
    }

    return answer;
}

double toDecimal(string data) {
    bool minus = false;
    if (data.find('-') != string::npos) {
        minus = true;
        data = data.substr(1);
    }

    double result = 0;
    int power = data.substr(0, data.find('.')).size() - 1;


    for (int i = 0; i < data.size(); ++i) {
        if (data[i] == '.') {
            continue;
        }
        result += (data[i] - '0') * pow(4, power);
        power--;
    }

    if (minus) {
        result *= -1;
    }

    return result;
}

void outputFile(ofstream &stream, string result, string first_number_raw, string second_numbe_raw, string first,
                string second) {
    stream << "------------------------------ Equation " << count_equ << " ------------------------------" << endl;

    stream << "Solved in decimal with raw numbers:" << endl;
    double answer = stof(first_number_raw) * stof(second_numbe_raw);
    stream << first_number_raw << " * " << second_numbe_raw << " = " << answer << endl << endl;

    stream << "Solved in quaternary:" << endl;
    stream << first << " * " << second << " = " << result << endl << endl;

    stream << "Convert from quaternary to decimal:" << endl;
    double result_decimal = toDecimal(result);
    stream << result_decimal << endl << endl;


    stream << "Conclusion: " << result_decimal << " = " << answer << endl;

    count_equ++;
}