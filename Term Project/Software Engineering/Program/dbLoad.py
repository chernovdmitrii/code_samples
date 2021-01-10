import pymysql
import numpy as np

# converting list to string
def make_string_from_list(splitted_list):
    string_with_comma_separated_elements = ', '.join(str(element) for element in splitted_list)

    return string_with_comma_separated_elements


# getting columns name as string
def get_parametrs_and_answer_names_string(table_columns_description_tuples):
    parametrs_and_answer_names_list = [str[0] for str in table_columns_description_tuples if
                                       (str[0] != 'id') and (str[0] != 'sampleCode') and (
                                                   str[0] != 'qualityCode')]
    parametrs_and_answer_names_string = make_string_from_list(parametrs_and_answer_names_list)

    return parametrs_and_answer_names_string

# getting columns name as list
def get_parametrs_and_answer_names_list(table_columns_description_tuples):
    parametrs_and_answer_names_list = [str[0] for str in table_columns_description_tuples if
                                       (str[0] != 'id') and (str[0] != 'sampleCode') and (
                                                   str[0] != 'qualityCode')]

    return parametrs_and_answer_names_list

# converting array of tuples to list array
def make_list_from_tuple(splitted_tuple):
    result_list = [elem for elem in splitted_tuple]

    return result_list

# executing some queries
def get_data_from_base(cur, query):
    cur.execute(query)
    data_from_base = cur.fetchall()

    return data_from_base

# creating connection to database
def create_connection():
    con = pymysql.connect(host='localhost',
                          user='root',
                          password='Yxv-v9K-vLs-NFt',
                          db='table_storage')
    return con

# converting matrix of tuples to lists matrix
def make_list_of_lists_from_tuple_of_tuples(splitted_tuple):
    arr = [np.array(row) for row in splitted_tuple]
    return np.array(arr)
