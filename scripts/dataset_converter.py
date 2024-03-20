import json
import csv

def write_coordinates_to_csv(idx, data, file_name):
    with open(file_name, mode='a', newline='') as file:
        writer = csv.writer(file)
        for _, location in enumerate(data, start=1):
            writer.writerow([idx, *location])
            
def write_names_to_csv(data, file_name):
    with open(file_name, mode='a', newline='', encoding='UTF-8') as file:
        writer = csv.writer(file)
        for name_data in data:
            writer.writerow(name_data)

def read_ndjson_and_write_to_csv(ndjson_data):
    for idx, map_data in enumerate(ndjson_data, start=1):
        location = map_data.get('location')
        name = map_data.get('name')
        if location and name:
            print(location)
            write_coordinates_to_csv(idx, [[location[1], location[0]]], output_csv_file)
            write_names_to_csv([[idx, name]], output_names_file)

output_csv_file = 'all_coordinates.csv'
output_names_file = 'all_names.csv'

with open(output_csv_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Index', 'Latitude', 'Longitude'])
    
with open(output_names_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Index', 'Name'])

with open('tspdata.ndjson', 'r', encoding='utf-8') as ndjson_file:
    ndjson_data = [json.loads(line) for line in ndjson_file]

read_ndjson_and_write_to_csv(ndjson_data)

print("All coordinates have been succesfully saved into csv file:", output_csv_file)
