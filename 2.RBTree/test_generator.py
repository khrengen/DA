import os, sys
import random
import string

import subprocess

import time

str_length = 10
# exec_path  = "../build/run" # path to yours executable
exec_path  = "../solution/solution" # path to yours executable
pic_fold = "../format/pic/"
out_test_file = "./generated.tst"

invalid_val = -1
invalid_key = ""

output_process   = False
output_main_test = False
run_tests        = True
save_tests       = True
load_tests       = True
save_main_test   = True
build_benchmark  = True

# create array of array
def preprocess_tests(arr):
    for i, entry in enumerate(arr):
        p = random.random()
        if p > 0.4:
            entry[0] = "+ " + entry[0]
        elif p < 0.4:
            entry[0] = "- " + entry[0]
            entry[1] = invalid_val
            
        else:
            entry[1] = invalid_val

def generate_tests(qty):
    val_min = 0
    val_max = 200

    letters = string.ascii_lowercase
    tests = []
    for _ in range(qty):
        key = "".join(random.choice(letters) for _ in range(str_length))
        val = int(random.random() * (val_max-val_min) + val_min) 

        # list1  = [str(key), str(val)]
        tests.append([str(key), int(val)])
    return tests


def check(inp,out):
    # create my dictiony
    # compare what returns implemented and program
    d = {}
    for i, entry in enumerate(inp):
        key = entry[0].lower()
        if key.startswith("+ "):
            if key[2:] in d:
                assert out[i] in "Exist", \
                    "{}. error appending {} (must Exist) but get {}".format(
                            i,
                            key,
                            out[i])
            else:
                d[key[2:]] = entry[1]
                assert out[i] in "OK", \
                    "{}. error appending {} (must OK) but get {}".format(
                            i,
                            key, 
                            out[i])
        elif key.startswith("- "):
            val = d.pop(key[2:],None)
            if val is not None:
                assert out[i] in "OK", \
                    "{}. error removing {} (must OK) but get {}".format(
                            i,
                            key,
                            out[i])
            else:
                assert out[i] in "NoSuchWord", \
                    "{}. error removing {} (must NSW) but get {}".format(
                            i,
                            key,
                            out[i])
        else:
            val = d.get(key, None)
            if val:
                assert out[i] in "OK: {}".format(val), \
                    "{}. error searching {} (must OK: {}) but get {}".format(
                            i,
                            key,
                            val, out[i])
            else:
                assert out[i] in "NoSuchWord", \
                    "{}. error searching {} (must NSW) but get {}".format(
                            i,
                            key,
                            out[i])
    return True

# create array of str inputs
def create_inp(arr):
    ret = []
    for entry in arr:
        if entry[0] in invalid_key:
            continue
        ret.append(entry[0])
        if entry[1] != invalid_val:
            ret[-1] += " " + str(entry[1])
    return (ret)



nums  = []
times = []
num_qty = 1;
num_max = int(sys.argv[1])
if len(sys.argv) > 2: num_qty = int(sys.argv[2])
if output_process: print("running tests for", nums)

if output_main_test or run_tests: 
    test_set = generate_tests(num_max)  # generate main test
    preprocess_tests(test_set)  # append some chars, key words, etc
inp = create_inp(test_set)
print("generated")
if output_main_test: 
    print("output main test:")
    print("\n".join(inp))
if save_main_test:
    with open(out_test_file, "w") as fl:
        fl.write("\n".join(inp))
if run_tests: 
    for i in range(num_qty):
        num = int(num_max / (2 ** i))
        if output_process: 
            print("\n\nrunning test for", num)
        sub_input = inp[:num]

        if output_process: 
            print("\n\nInput:\n{}".format(sub_input))

        process = subprocess.Popen(
                exec_path, stdin=subprocess.PIPE,
                # stderr=sys.stdout, bufsize=16384,
                stderr=sys.stdout, bufsize=8192,
                stdout=subprocess.PIPE)
        start_time = time.time() # start recording time
        # sub_output = ""
        # for i, line in enumerate(sub_input):
        #     print("entering {} entry {}".format(i, str(line)))
            # process.stdin.write((str(line)+"\n").encode('utf-8'))   # write to out prog
        out, err = process.communicate("\n".join(sub_input).encode('utf-8'))
        if err is not None:
            print("Error: {}".format(err.decode()))
        sub_output = out.decode()      # read from prog
        time_taken = str((time.time() - start_time) / 60)  # capture the time
        process.stdin.close()

        if output_process: print("\n\nOutput:\n{}".format(sub_output))
        if output_process: print("Time taken (sec): {}".format(time_taken))

        print("time taken {} for numbers: \t{}".format(num, time_taken))
        nums.append(num)
        times.append(str(time_taken)[:7])
        assert check(test_set[:num], sub_output.split("\n")), "Not right check :(\n"

if build_benchmark:
    import matplotlib.pyplot as plt
    plt.suptitle('Benchmark')
    # plt.plot(nums, times)
    plt.plot(nums, times)
    plt.gca().invert_yaxis()
    
    plt.xlabel('entries quantity')
    plt.ylabel('time taken (sec)')

    print("saving plt")
    plt.savefig(os.path.join(pic_fold, "benchmark.png"), bbox_inches='tight')
    # plt.savefig("test.png",bbox_inches='tight')
    print("saved")
    plt.show()
