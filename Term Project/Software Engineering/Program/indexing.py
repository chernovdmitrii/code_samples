from dbLoad import *
from prettytable import PrettyTable

# creating an index for bd
def indexing(StrNames, Weights_mas, BPName, num, cursor, connection):
    indexDescription = BPName + 'Index'
    ind = findColumn_1(Weights_mas, num, StrNames)
    if (len(ind) == 0):
        print("Warning! Index will not be created due to minimum requirement has not met! \nMaximum weight: ", max(Weights_mas), '\nValue: ', num)
    else:
        col = ', '.join([str for str in ind.keys()])

        try:
            if col != '':
                cursor.execute('CREATE INDEX {0} ON {1} ({2})'.format(indexDescription, BPName, col))
                connection.commit()
                print('Indexing has been successfully created!')



        except Exception as e:
            print('Exception has occured: ', make_string_from_list(make_list_from_tuple(e.args)))

    printTableIndex(cursor, BPName)

# function to find right weights
def findColumn_1(weights, num, Names):
    ind = {}
    for i in range(len(weights)):
        if weights[i] >= num:
            ind[Names[i]] = weights[i]

    return ind

# checking if the bd has already been indexed
def isIndexed(data, BPName):
    indexDescription = BPName + 'Index'

    for item in data:
        if item[2] == indexDescription:
            return True
    return False

# deleting index if there is one
def delete_index(BPName, cursor, connection):
    indexDescription = BPName + 'Index'
    try:
        cursor.execute('DROP INDEX {0} ON {1}'.format(indexDescription, BPName))
        connection.commit()
        print('Indexing has been successfully deleted!')
    except Exception as e:
        print('Exception has occured: ', make_string_from_list(make_list_from_tuple(e.args)))

# print the table of all existing indexes
def printTableIndex(cursor, BPName):
    # Printing index table
    table_db = PrettyTable()
    table_data = make_list_from_tuple(get_data_from_base(cursor, "SHOW INDEX FROM {0}".format(BPName)))
    table_db.field_names = ['Table', 'Non_unique', 'Key_name', 'Seq_in_index', 'Column_name', 'Collation',
                            'Cardinality', 'Sub_part', 'Packed', 'Null', 'Index_type', 'Comment',
                            'Index_comment',
                            'Visible', 'Expression']

    for item in table_data:
        table_db.add_row(item)
    print(table_db)

