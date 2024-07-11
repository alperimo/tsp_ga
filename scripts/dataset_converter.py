# "tspdata.ndjson" file needs to be in the same directory

import json
import csv
import re

def extract_index_from_iso(city_iso):
    index = re.findall(r'-(\d+)$', city_iso)  # Extract numeric part after the last dash
    if not index:
        index = re.findall(r'\d+', city_iso)  # Extract all numeric characters if no dash found
    if index:
        return int(index[0])
    return None

def write_coordinates_to_csv(idx, data, file_name):
    with open(file_name, mode='a', newline='') as file:
        writer = csv.writer(file)
        for _, location in enumerate(data, start=1):
            writer.writerow([idx, *location])

def write_names_to_csv(data, file_name):
    with open(file_name, mode='a', newline='', encoding='utf-8-sig') as file:
        writer = csv.writer(file)
        for name_data in data:
            writer.writerow(name_data)

def read_ndjson_and_write_to_csv(ndjson_data):
    cities_data = []
    for idx, map_data in enumerate(ndjson_data, start=0):
        location = map_data.get('location')
        name = map_data.get('name')
        city_iso = map_data.get('address', {}).get('ISO3166-2-lvl4')
        city_index = extract_index_from_iso(city_iso)
        if location and name and city_index is not None:
            cities_data.append([city_index, name, location])
    # Sort cities_data by index
    cities_data.sort(key=lambda x: x[0])
    # Write sorted data to CSV
    for data in cities_data:
        city_index, name, location = data
        write_coordinates_to_csv(city_index, [[location[1], location[0]]], output_csv_file)
        write_names_to_csv([[city_index, name]], output_names_file)

output_csv_file = '../data/tsp81cities_coords.csv'
output_names_file = '../data/tsp81cities_names.csv'

# Clear existing content in files
with open(output_csv_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Index', 'Latitude', 'Longitude'])

with open(output_names_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Index', 'Name'])

with open('tspdata.ndjson', 'r', encoding='utf-8') as ndjson_file:
    ndjson_data = [json.loads(line) for line in ndjson_file]

print("Reading ndjson file...")
read_ndjson_and_write_to_csv(ndjson_data)
print("Finished reading and processing ndjson file.")
