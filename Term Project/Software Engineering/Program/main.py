from indexing import *
import pymysql


# ==========================[Connecting to BD]=============================
connection = pymysql.connect(host='localhost',
                             user='root',
                             password='Yxv-v9K-vLs-NFt',
                             db='table_storage')
cursor = connection.cursor()
# ===========================[Choosing Table]==============================
table_db = PrettyTable()
table_data = make_list_from_tuple(get_data_from_base(cursor, "SHOW TABLES"))
table_data_matrix = []

count = 0
for item in table_data:
    if str(item[0]) == 'users' or 'Description' in str(item[0]):
        continue
    table_data_matrix.append([count, item[0]])
    count += 1

table_db.field_names = ['Number', 'Tables']
for item in table_data_matrix:
    table_db.add_row(item)
print(table_db)

ans_range = [str(item) for item in range(len(table_data))]
while True:
    ans = input('Choose table: ')
    if ans in ans_range:
        break

table_name = table_data_matrix[int(ans)][1]
print('Table name: {0}'.format(table_name))

ans_range = [str(item / 10.0) for item in range(1, 11)]
while True:
    ans = input('Choose max weight: ')
    if ans in ans_range:
        break
num = float(ans)
# ==========================[Reading From DB ]=============================
table_columns_description_tuples = get_data_from_base(cursor, "DESCRIBE {0}".format(table_name))
parametrs_and_answer_names_list = get_parametrs_and_answer_names_list(table_columns_description_tuples)

parametrs_description_tuples = get_data_from_base(cursor, "SELECT * FROM {0}".format(table_name + 'Description'))

parameters_weights = [str[7] for str in parametrs_description_tuples]

# =========================[Modifying From DB ]============================

info = make_list_of_lists_from_tuple_of_tuples(get_data_from_base(cursor, 'SHOW INDEX FROM {0}'.format(table_name)))
if isIndexed(info, table_name):
    ans_range = ['Y', 'y', 'N', 'n']
    while True:
        ans = input('Database has already been indexed. Do you want to delete it ? [Y/N]: ')
        if ans in ans_range:
            break

    if ans == 'Y' or ans == 'y':
        delete_index(table_name, cursor, connection)

info = make_list_of_lists_from_tuple_of_tuples(get_data_from_base(cursor, 'SHOW INDEX FROM {0}'.format(table_name)))
if not isIndexed(info, table_name):
    ans_range = ['Y', 'y', 'N', 'n']
    while True:
        ans = input('Do you want to create index ? [Y/N]: ')
        if ans in ans_range:
            break

    if ans == 'Y' or ans == 'y':
        indexing(parametrs_and_answer_names_list, parameters_weights, table_name, num, cursor, connection)
else:
    print("Error: The database '{0}' already has been indexed!".format(table_name))

# =========================[Print Information]=============================
ans_range = ['Y', 'y', 'N', 'n']
while True:
    ans = input('Do you want to see more information ? [Y/N]: ')
    if ans in ans_range:
        break

if ans == 'Y' or ans == 'y':
    # Printing Case Base
    table_data = make_list_from_tuple(get_data_from_base(cursor, "SELECT * FROM {0}".format(table_name)))

    table_db = PrettyTable()

    fields = make_list_from_tuple(table_columns_description_tuples)
    table_db.field_names = [str[0] for str in fields]

    for item in table_data:
        table_db.add_row(item)
    print(table_db)

    # Printing Description Table
    table_db = PrettyTable()
    table_data = make_list_from_tuple(parametrs_description_tuples)
    fields = make_list_from_tuple(get_data_from_base(cursor, "DESCRIBE {0}".format(table_name + 'Description')))
    table_db.field_names = [str[0] for str in fields]

    for item in table_data:
        table_db.add_row(item)
    print(table_db)

connection.close()

table = PrettyTable()
# table.field_names = ["City name", "Area", "Population", "Annual Rainfall"]
table.add_row(["Adelaide", 1295, 1158259, 600.5])
table.add_row(["Brisbane", 5905, 1857594, 1146.4])
table.add_row(["Darwin", 112, 120900, 1714.7])
table.add_row(["Hobart", 1357, 205556, 619.5])
table.add_row(["Sydney", 2058, 4336374, 1214.8])
table.add_row(["Melbourne", 1566, 3806092, 646.9])
table.add_row(["Perth", 5386, 1554769, 869.4])
print(table)