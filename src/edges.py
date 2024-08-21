import xml.etree.ElementTree as ET
from collections import defaultdict

def parse_osm(file_path):
    tree = ET.parse(file_path)
    root = tree.getroot()

    nodes = {}
    ways = defaultdict(list)

    # Extract nodes
    for node in root.findall('node'):
        node_id = int(node.attrib['id'])
        lat = float(node.attrib['lat'])
        lon = float(node.attrib['lon'])
        nodes[node_id] = (lat, lon)

    # Extract ways and group by node ids
    for way in root.findall('way'):
        way_id = int(way.attrib['id'])
        for nd in way.findall('nd'):
            ref = int(nd.attrib['ref'])
            ways[way_id].append(ref)

    return nodes, ways

def main():
    file_path = './data/Botkyrka.osm'  # Path to your .osm file
    nodes, ways = parse_osm(file_path)

    # Output nodes
    print("Nodes:")
    for node_id, (lat, lon) in nodes.items():
        print(f"ID: {node_id}, Latitude: {lat}, Longitude: {lon}")

    # Output ways
    print("\nWays:")
    for way_id, node_ids in ways.items():
        print(f"Way ID: {way_id}, Node IDs: {node_ids}")

if __name__ == "__main__":
    main()
