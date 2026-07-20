
path_to_parameters = ".//include//Parameters.h"
path_to_output = ".//source//output_test.cpp"

parameters = dict()

with open(path_to_parameters, 'r') as fin:
    readLine = False;
    for line in fin:
        # print(f"||{line.strip()}||")
        if line.strip() == "//--start parameters":
            readLine = True;            
        elif line.strip() == "//--stop parameters":
            readLine = False;
        if bool(readLine):            
            split = line.strip().split(' ');
            print(split)
            # parameters[split[0]] = split[1]

# https://markvtechblog.wordpress.com/2024/04/28/code-generation-in-python-with-jinja2/

for e in parameters:
    print(f"{e.key} {e.value}")








