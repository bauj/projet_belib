import json

ddj="2023-01-27"
basename_jsonfile=f"raw_data_belib_"+ddj
basename_jsonfile_pretty=f"pretty_data_belib_"+ddj

path_to_jsonfile = "./AJC_projet_belib/"+basename_jsonfile+".json"
path_to_pretty_jsonfile = "./AJC_projet_belib/"+basename_jsonfile_pretty+".json"

with open(path_to_jsonfile, 'r') as data_file:
    content = data_file.read()

data_json = json.loads(content)
pretty_content=json.dumps(data_json, indent=4)

with open(path_to_pretty_jsonfile, 'w') as pretty_data_file:
    pretty_data_file.write(pretty_content)
    
